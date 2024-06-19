
#include <sys/timerfd.h>
#include <unistd.h>
#include <cmath>

#include "PeriodicTask.hpp"
#include "Timer.h"

PeriodicTask::PeriodicTask(PeriodicTaskManager* taskManager, float period,
                           std::string name)
    : _period(period), _name(name) {
  taskManager->addTask(this);
}

void PeriodicTask::start() {
  if (_running) {
    printf("[PeriodicTask] Tried to start %s but it was already running!\n",
           _name.c_str());
    return;
  }
  init();
  _running = true;
  _thread = std::thread(&PeriodicTask::loopFunction, this);//创建一个新线程，参数1为线程的函数，参数2为函数所需要的参数
}

void PeriodicTask::stop() {
  if (!_running) {
    printf("[PeriodicTask] Tried to stop %s but it wasn't running!\n",
           _name.c_str());
    return;
  }
  _running = false;
  printf("[PeriodicTask] Waiting for %s to stop...\n", _name.c_str());
  _thread.join();//停止thread
  printf("[PeriodicTask] Done!\n");
  cleanup();
}

// 如果最大周期超过期望周期的 30%，则速度慢
bool PeriodicTask::isSlow() {
  return _maxPeriod > _period * 1.3f || _maxRuntime > _period;
}

// 重置最大统计数据
void PeriodicTask::clearMax() {
  _maxPeriod = 0;
  _maxRuntime = 0;
}

// 打印状态
void PeriodicTask::printStatus() {
  if (!_running) return;
  if (isSlow()) {
    printf("\033[0m\033[1;31m%s\033[0m", "WARNING.\n");
    printf("|%-20s|%6.4f|%6.4f|%6.4f|%6.4f|%6.4f\n",
                 _name.c_str(), _lastRuntime, _maxRuntime, _period,
                 _lastPeriodTime, _maxPeriod);
  } else {
    printf("|%-20s|%6.4f|%6.4f|%6.4f|%6.4f|%6.4f\n", _name.c_str(),
           _lastRuntime, _maxRuntime, _period, _lastPeriodTime, _maxPeriod);
  }
}


void PeriodicTask::loopFunction() {
  //创建一个不被外接打断的timer
  auto timerFd = timerfd_create(CLOCK_MONOTONIC, 0);
  //将period的整数位取为second
  int seconds = (int)_period;
  //小数位乘1e9作为ns
  int nanoseconds = (int)(1e9 * std::fmod(_period, 1.f));

  Timer t;//这个timer不是挂墙时钟而是定时器作用
  //初始化定时器
  itimerspec timerSpec;
  timerSpec.it_interval.tv_sec = seconds;
  timerSpec.it_value.tv_sec = seconds;
  timerSpec.it_value.tv_nsec = nanoseconds;
  timerSpec.it_interval.tv_nsec = nanoseconds;
  //创建定时任务
  timerfd_settime(timerFd, 0, &timerSpec, nullptr);

  unsigned long long missed = 0;

  printf("[PeriodicTask] Start %s (%d s, %d ns)\n", _name.c_str(), seconds, nanoseconds);
  while (_running) {
    _lastPeriodTime = (float)t.getSeconds();//距离上次运行run所花的时间
    t.start();
    run();
    _lastRuntime = (float)t.getSeconds();//run运行的总时间
    int m = read(timerFd, &missed, sizeof(missed));
    // 当定时器超时，read读事件发生即可读，返回超时次数（从上次调用timerfd_settime()启动开始或上次read成功读取开始）
    // 它是一个8字节的unit64_t类型整数，如果定时器没有发生超时事件，则read将阻塞；
    (void)m;//消除未使用变量的警告
    _maxPeriod = std::max(_maxPeriod, _lastPeriodTime);//所有轮询中最大的时间
    _maxRuntime = std::max(_maxRuntime, _lastRuntime);//所有轮询中最大的时间
  }
  printf("[PeriodicTask] %s has stopped!\n", _name.c_str());
}

void PeriodicTask::set_schedule_arg(int policy, int priority)
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, policy);
    sched_param param;
    param.sched_priority = priority;
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_t thread_handle = _thread.native_handle();
    pthread_setschedparam(thread_handle, policy, &param);
}


PeriodicTaskManager::~PeriodicTaskManager() {}


void PeriodicTaskManager::addTask(PeriodicTask* task) {
  //vector容器压入新的task
  _tasks.push_back(task);
}

//打印出所有task的状态
void PeriodicTaskManager::printStatus() {
  printf("\n----------------------------TASKS----------------------------\n");
  printf("|%-20s|%-6s|%-6s|%-6s|%-6s|%-6s\n", "name", "rt", "rt-max", "T-des",
         "T-act", "T-max");
  printf("-----------------------------------------------------------\n");
  for (auto& task : _tasks) {
    task->printStatus();
    task->clearMax();
  }
  printf("-------------------------------------------------------------\n\n");
}

//打印出所有慢的线程
void PeriodicTaskManager::printStatusOfSlowTasks() {
  for (auto& task : _tasks) {
    if (task->isSlow()) {
      task->printStatus();
      task->clearMax();
    }
  }
}

//停止该manager中的所有线程
void PeriodicTaskManager::stopAll() {
  for (auto& task : _tasks) {
    task->stop();
  }
}

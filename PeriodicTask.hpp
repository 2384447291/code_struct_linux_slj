#ifndef PROJECT_PERIODICTASK_HPP
#define PROJECT_PERIODICTASK_HPP

#include <string>
#include <thread>
#include <pthread.h>
#include <vector>

class PeriodicTaskManager;

class PeriodicTask {
 public:
  PeriodicTask(PeriodicTaskManager* taskManager, float period,
               std::string name);
  void start();
  void stop();
  void printStatus();
  void clearMax();
  bool isSlow();
  // 纯虚函数,必须被重载
  virtual void init() = 0;
  virtual void run() = 0;
  virtual void cleanup() = 0;
  virtual ~PeriodicTask() { stop(); }

  float getPeriod() { return _period; }

  float getRuntime() { return _lastRuntime; }

  float getMaxPeriod() { return _maxPeriod; }

  float getMaxRuntime() { return _maxRuntime; }

 private:
  void loopFunction();

  void set_schedule_arg(int policy, int priority);

  float _period;
  volatile bool _running = false;
  float _lastRuntime = 0;
  float _lastPeriodTime = 0;
  float _maxPeriod = 0;
  float _maxRuntime = 0;
  std::string _name;
  std::thread _thread;
};

/*!
 * A collection of periodic tasks which can be monitored together
 */
class PeriodicTaskManager {
 public:
  PeriodicTaskManager() = default;
  ~PeriodicTaskManager();
  void addTask(PeriodicTask* task);
  void printStatus();
  void printStatusOfSlowTasks();
  void stopAll();

 private:
  std::vector<PeriodicTask*> _tasks;//STL库中的动态数组
};

#endif  

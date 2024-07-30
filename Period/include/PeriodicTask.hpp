#ifndef PERIODICTASK_HPP
#define PERIODICTASK_HPP

#include <string>
#include <thread>
#include <pthread.h>
#include <vector>
#include <iostream>

class PeriodicTaskManager;

class PeriodicTask {
 public:
  PeriodicTask(float period, std::string name, uint8_t prefer_cpu, int policy, int priority);
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

  std::string get_name()
  {
    return _name;
  }

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
  uint8_t _prefer_cpu = 0;
  std::thread _thread;
};

/*!
 * A collection of periodic tasks which can be monitored together
 */
class PeriodicTaskManager {
 public:
  static PeriodicTaskManager* Instance()
  {
      static PeriodicTaskManager instance;
      return &instance;
  }
  PeriodicTaskManager() = default;
  ~PeriodicTaskManager();
  void addTask(PeriodicTask* task);
  void printStatus();
  void printStatusOfSlowTasks();
  void stopAll();

  PeriodicTask* FindTask(std::string _name)
  {
    PeriodicTask* temp = nullptr;
    for (auto& task : _tasks) 
    {
      if (task->get_name() == _name) 
      {
        return task;
      }
    }
    std::cout << _name << " is not in the task_manager" << std::endl;
    return temp;
  }

 private:
  std::vector<PeriodicTask*> _tasks;
};

#endif  

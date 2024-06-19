#ifndef PROJECT_TIMER_H
#define PROJECT_TIMER_H

#include <assert.h>
#include <stdint.h>
#include <time.h>

class Timer {
 public:

  // 构造了之后开始计时，之后的所有拿去，都要减去start_time（当作挂墙时钟）
  explicit Timer() { start(); }

  /*!
   * Start the timer
   */
  void start() { clock_gettime(CLOCK_MONOTONIC, &_startTime); }

  /*!
   * Get milliseconds elapsed
   */
  double getMs() { return (double)getNs() / 1.e6; }

  /*!
   * Get nanoseconds elapsed
   */
  int64_t getNs() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);//系统运行时间，从系统启动时开始计时，系统休眠时不再计时
    return (int64_t)(now.tv_nsec - _startTime.tv_nsec) +
           1000000000 * (now.tv_sec - _startTime.tv_sec);
  }

  /*!
   * Get seconds elapsed
   */
  double getSeconds() { return (double)getNs() / 1.e9; }

  struct timespec _startTime;//时间集合体（int代表的s + long代表的ns（1s = 1.e9ns））
};

#endif  

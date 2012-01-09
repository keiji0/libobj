#ifndef OBJ_TIME_HPP
#define OBJ_TIME_HPP

#include <iostream>
#include <unistd.h>
#include <sys/times.h>
#include <obj/util.hpp>
#include <obj/error.hpp>

namespace obj
{

  class timer {
  PRIVATE:
    tms start_time_;
    tms end_time_;
    clock_t start_clock_;
    clock_t end_clock_;
    long clk_;
  PUBLIC:
    timer () {
      restart();
      if ((clk_ = sysconf(_SC_CLK_TCK)) < 0)
        ERR_SYS("sysconf error");
    }
    void restart () {
      if (static_cast<int>(start_clock_ = times(&start_time_)) == -1)
        ERR_SYS("times error");
    }
    void print () {
      snapshot();
      std::cerr << std::fixed
                << "real: " << ((end_clock_ - start_clock_) / (double)clk_) << ", "
                << "user: " << ((end_time_.tms_utime - start_time_.tms_utime) / (double)clk_) << ", "
                << "sys: "  << ((end_time_.tms_stime - start_time_.tms_stime) / (double)clk_)
                << std::dec
                << std::endl;
    }
  PRIVATE:
    void snapshot () {
      if (static_cast<int>(end_clock_ = times(&end_time_)) == -1)
        ERR_SYS("times error");
    }
  };

#define DOTIMES(c, max, body) {                             \
    int c = 0;                                              \
    for (;;) { if (c < max) { body; c++; } else break; } }

#define TIME(body) {                                                \
    obj::timer timer;                                               \
    body;                                                           \
    timer.print();                                                  \
  }

#define TIMEC(c, body) { TIME(DOTIMES(_, c, body)); }

}

#endif

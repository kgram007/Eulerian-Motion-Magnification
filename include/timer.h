//*****************************************************************************
// Copyright 2016 Ramsundar K G. All Rights Reserved.
//
// This source code is licensed as defined by the LICENSE file found in the
// root directory of this source tree.
//
// Author: Ramsundar K G (kgram007@gmail.com)
//
// This file is a part of C++ implementation of Eulerian Motion Magnification
// adapted from https://github.com/wzpan/QtEVM
//
//*****************************************************************************

#ifndef TIMER_H_
#define TIMER_H_

#define __cplusplus 201103L

#include <iostream>
#include <chrono>  // NOLINT [build/c++11]
#include <string>

class Timer
{
 public:
    typedef std::chrono::steady_clock Clock;
    typedef std::chrono::time_point<Clock> Time;

 public:
    Timer()
        : t_start_(Clock::now())
    {
    }

    virtual ~Timer()
    {
    }

    inline void start()
    {
        t_start_ = Clock::now();
    }

    template <typename T>
    inline double getTimeDuration()
    {
        Time t = Clock::now();
        return std::chrono::duration_cast<T>(t - t_start_).count();
    }

    inline double getTimeNanoSec()
    {
        return getTimeDuration<std::chrono::nanoseconds>();
    }

    inline double getTimeMicroSec()
    {
        return getTimeDuration<std::chrono::microseconds>();
    }

    inline double getTimeMilliSec()
    {
        return getTimeDuration<std::chrono::milliseconds>();
    }

    inline double getTimeSec()
    {
        return getTimeDuration<std::chrono::seconds>();
    }

    inline double printTimeNanoSec(const std::string& msg = std::string(""))
    {
        double t = getTimeNanoSec();
        std::cout << msg << ": " << t << " nsec" << std::endl;
        return (t);
    }

    inline double printTimeMicroSec(const std::string& msg = std::string(""))
    {
        double t = getTimeMicroSec();
        std::cout << msg << ": " << t << " usec" << std::endl;
        return (t);
    }

    inline double printTimeMilliSec(const std::string& msg = std::string(""))
    {
        double t = getTimeMilliSec();
        std::cout << msg << ": " << t << " msec" << std::endl;
        return (t);
    }

    inline double printTimeSec(const std::string& msg = std::string(""))
    {
        double t = getTimeSec();
        std::cout << msg << ": " << t << " sec" << std::endl;
        return (t);
    }

 private:
    Time t_start_;
};

#endif  // TIMER_H_

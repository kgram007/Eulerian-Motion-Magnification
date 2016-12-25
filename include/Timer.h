//***********************************************************************//
//
//	File Name:	 Timer.h
//	Author:		 Ramsundar K G (ramsundar@asu.edu)
//	Date:		 December 22, 2016
//
//	Description: Timer Header file. Used for measuring time intervals.
//
//***********************************************************************//

#pragma once

#define __cplusplus 201103L

#include <iostream>
#include <chrono>

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
		Time t =  Clock::now();
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
		std::cout << msg << ": "  << t << " nsec" << std::endl;
		return (t);
	}

	inline double printTimeMicroSec(const std::string& msg = std::string(""))
	{
		double t = getTimeMicroSec();
		std::cout << msg << ": "  << t << " usec" << std::endl;
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

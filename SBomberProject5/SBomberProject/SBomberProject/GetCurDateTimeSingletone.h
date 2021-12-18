#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <numeric>
#include <time.h>



class GetCurDateTimeSingletone
{ 
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
public:
	static GetCurDateTimeSingletone& getInstance() {
		static GetCurDateTimeSingletone theInstance;
		return theInstance;
	}

	std::string GetCurDateTime();
	void Start();
	void SaveTime();
	double Calculating();

private:
	GetCurDateTimeSingletone() {}
	GetCurDateTimeSingletone(const GetCurDateTimeSingletone& root) = delete;
	GetCurDateTimeSingletone& operator=(const GetCurDateTimeSingletone&) = delete;
private:
	std::chrono::time_point<clock_t> m_beg;
	std::vector<double> storage_time;
};


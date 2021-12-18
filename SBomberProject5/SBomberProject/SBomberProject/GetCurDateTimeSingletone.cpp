#include "GetCurDateTimeSingletone.h"

std::string GetCurDateTimeSingletone::GetCurDateTime()
{
	auto cur = std::chrono::system_clock::now();
	time_t time = std::chrono::system_clock::to_time_t(cur);
	char buf[64] = { 0 };
	ctime_s(buf, 64, &time);
	buf[strlen(buf) - 1] = '\0';
	return std::string(buf);
}

void GetCurDateTimeSingletone::Start()
{
	m_beg = clock_t::now();
}

void GetCurDateTimeSingletone::SaveTime()
{
	storage_time.push_back(std::chrono::duration_cast<second_t>(clock_t::now() -
		m_beg).count());
}

double GetCurDateTimeSingletone::Calculating()
{
	/*double res{};*/
	
	auto res = std::accumulate(storage_time.begin(), storage_time.end(), 0.0);
	return res / storage_time.size();
}

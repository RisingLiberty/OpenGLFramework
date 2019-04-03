#include "GlobalTimer.h"

typedef std::chrono::time_point<std::chrono::steady_clock> TimeStamp;

namespace
{
	TimeStamp GetCurrentTime()
	{
		return std::chrono::high_resolution_clock::now();
	}

	float GetTimeSince(const TimeStamp& timeStamp)
	{
		return std::chrono::duration_cast<std::chrono::duration<float>>(GetCurrentTime() - timeStamp).count();
	}

	float GetTimeDifference(TimeStamp first, TimeStamp last)
	{
		return std::chrono::duration_cast<std::chrono::duration<float>>(first - last).count();
	}
}

GlobalTimer::GlobalTimer():
	m_StartTime(std::chrono::high_resolution_clock::now()),
	m_IsPaused(false)
{
}

void GlobalTimer::Reset()
{
	m_StartTime = std::chrono::high_resolution_clock::now();

	m_PrevTime = m_StartTime;

	m_PausedTime = 0.0f;
	m_IsPaused = false;
}

void GlobalTimer::Start()
{
	TimeStamp now = GetCurrentTime();
	float time = GetTimeSince(m_StopTime);

	if (m_IsPaused)
	{
		m_PausedTime += time;

		m_PrevTime = now;
		m_IsPaused = false;
	}
}

void GlobalTimer::Stop()
{
	if (!m_IsPaused)
	{
		m_StopTime = std::chrono::high_resolution_clock::now();
		m_IsPaused = true;
	}
}

void GlobalTimer::Tick()
{
	if (m_IsPaused)
	{
		m_DeltaTime = 0.0f;
		return;
	}

	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = GetTimeDifference(m_CurrentTime, m_PrevTime);

	m_PrevTime = m_CurrentTime;

	
	if (m_DeltaTime < 0.0f)
		m_DeltaTime = 0.0f;
}

float GlobalTimer::GetTotalTime() const
{
	if (m_IsPaused)
	{
		float time = GetTimeDifference(m_StopTime, m_StartTime);
		time -= m_PausedTime;
		return time;
	}

	float time = GetTimeDifference(m_CurrentTime, m_StartTime);
	time -= m_PausedTime;
	return time;
}

float GlobalTimer::GetDeltaTime() const
{
	return m_DeltaTime;
}
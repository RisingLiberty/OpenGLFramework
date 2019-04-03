#pragma once

#include <chrono>

class GlobalTimer
{
public:
	GlobalTimer();

	float GetTotalTime() const;
	float GetDeltaTime() const;

	void Reset();

	void Start();
	void Stop();
	void Tick();

private:
	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
	std::chrono::time_point<std::chrono::steady_clock> m_CurrentTime;
	std::chrono::time_point<std::chrono::steady_clock> m_PrevTime;
	std::chrono::time_point<std::chrono::steady_clock> m_StopTime;

	float m_PausedTime;
	float m_DeltaTime;
	
	bool m_IsPaused;
};
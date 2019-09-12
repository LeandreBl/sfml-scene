#include "Clock.hpp"

namespace sfs
{
Clock::Clock(uint32_t fps) noexcept
    : _clock(), _timeScale(1.f), _time(0.f), _prevTime(0.f), _deltaTime(0.f)
{
	framerate(fps);
}

void Clock::reset() noexcept
{
	_clock.restart();
	_time = 0;
	_prevTime = 0;
}

void Clock::timeScale(float timeScale) noexcept
{
	_timeScale = timeScale;
}

float Clock::timeScale() const noexcept
{
	return _timeScale;
}

uint32_t Clock::framerate() const noexcept
{
	return 1.0 / _deltaTime;
}

void Clock::framerate(uint32_t framerate) noexcept
{
	_deltaTime = 1.0 / framerate;
}

float Clock::time() const noexcept
{
	return _time;
}

float Clock::refresh() noexcept
{
	float rtime = _clock.getElapsedTime().asSeconds();

	_time += (rtime - _prevTime) * _timeScale;
	_deltaTime = rtime - _prevTime;
	_prevTime = rtime;
	return rtime;
}

float Clock::deltaTime() const noexcept
{
	return _deltaTime * _timeScale;
}
}
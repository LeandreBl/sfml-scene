#include "Clock.hpp"

namespace sfs
{
Clock::Clock(uint32_t fps) noexcept
    : _clock(), _timeScale(1.f), _time(0.f), _prevTime(0.f), _framerate(fps),
      _lastDeltaTime(1.f / fps)
{
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
	return _framerate;
}

void Clock::framerate(uint32_t framerate) noexcept
{
	_framerate = framerate;
	_lastDeltaTime = 1.f / _framerate;
}

float Clock::getTime() const noexcept
{
	return _time;
}

float Clock::getRealTime() const noexcept
{
	return _clock.getElapsedTime().asSeconds();
}

float Clock::getDeltaTime() const noexcept
{
	return _lastDeltaTime * _timeScale;
}

sf::Time Clock::getNative() const noexcept
{
	return _clock.getElapsedTime();
}

void Clock::refreshDeltaTime() noexcept
{
	float rtime = _clock.getElapsedTime().asSeconds();
	float diff = rtime - _prevTime;

	_time += diff * _timeScale;
	_lastDeltaTime = diff;
	_prevTime = rtime;
}
} // namespace sfs
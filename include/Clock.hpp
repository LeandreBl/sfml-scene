#pragma once

#include <SFML/System.hpp>

namespace sfs
{

class Clock
{
	public:
	Clock(uint32_t fps) noexcept;
	void reset() noexcept;

	void timeScale(float timeScale) noexcept;
	float timeScale() const noexcept;

	uint32_t framerate() const noexcept;
	void framerate(uint32_t framerate) noexcept;

	float getDeltaTime() const noexcept;
	float getTime() const noexcept;
	float getRealTime() const noexcept;
	void refreshDeltaTime() noexcept;
	sf::Time getNative() const noexcept;

	private:
	sf::Clock _clock;
	float _timeScale;
	float _time;
	float _prevTime;
	float _framerate;
	float _lastDeltaTime;
};
} // namespace sfs
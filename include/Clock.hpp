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

	float time() const noexcept;
	float refresh() noexcept;
	float deltaTime() const noexcept;

	private:
	sf::Clock _clock;
	float _timeScale;
	float _time;
	float _prevTime;
	float _deltaTime;
};
} // namespace sfs
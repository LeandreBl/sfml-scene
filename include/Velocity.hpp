#pragma once

#include <SFML/System.hpp>

#include "IComponent.hpp"

namespace sfs
{
class Velocity : public sfs::IComponent
{
      public:
	Velocity(const sf::Vector2f &speed = sf::Vector2f(0, 0),
		 const sf::Vector2f &accel = sf::Vector2f(0, 0)) noexcept
	    : _speed(speed), _accel(accel){};
	void addAcceleration(const sf::Vector2f &add) noexcept
	{
		_accel += add;
	}
	void setAcceleration(const sf::Vector2f &accel) noexcept
	{
		_accel = accel;
	}
	sf::Vector2f getAcceleration() const noexcept
	{
		return _accel;
	}
	void addSpeed(const sf::Vector2f &add) noexcept
	{
		_speed += add;
	}
	void setSpeed(const sf::Vector2f &speed) noexcept
	{
		_speed = speed;
	}
	sf::Vector2f getSpeed() const noexcept
	{
		return _speed;
	}
	void update(sfs::Scene &scene, GameObject &go) noexcept
	{
		_speed.x *= _accel.x;
		_speed.y *= _accel.y;
		go.move(_speed * scene.deltaTime());
	}

      protected:
	sf::Vector2f _speed;
	sf::Vector2f _accel;
};
} // namespace sfs

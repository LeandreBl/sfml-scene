#pragma once

#include <SFML/System.hpp>

#include "IComponent.hpp"
#include "GameObject.hpp"

namespace sfs {
class Velocity : public sfs::IComponent {
      public:
	Velocity(const sf::Vector2f &speedv = sf::Vector2f(0, 0),
		 const sf::Vector2f &accelv = sf::Vector2f(1, 1)) noexcept
		: speed(speedv)
		, acceleration(accelv)
	{
	}
	void start(GameObject &) noexcept
	{
	}
	void update(GameObject &go) noexcept
	{
		go.move(this->speed * go.scene().deltaTime());
		this->speed.x *= this->acceleration.x;
		this->speed.y *= this->acceleration.y;
	}
	void onDestroy() noexcept
	{
	}
	sf::Vector2f speed;
	sf::Vector2f acceleration;
};
} // namespace sfs

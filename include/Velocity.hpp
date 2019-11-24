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
	void update(Scene &scene, GameObject &go) noexcept
	{
		go.move(this->speed * scene.deltaTime());
		this->speed.x *= this->acceleration.x;
		this->speed.y *= this->acceleration.y;
	}
	sf::Vector2f speed;
	sf::Vector2f acceleration;
};
} // namespace sfs

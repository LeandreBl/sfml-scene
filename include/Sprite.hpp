#pragma once

#include "IComponent.hpp"


namespace sfs
{
class Sprite : public IComponent, public sf::Sprite
{
      public:
	Sprite(const sf::Texture &texture = sf::Texture()) noexcept;
	void display(sf::RenderWindow &) noexcept;
	void update(Scene &, GameObject &) noexcept;
};
} // namespace sfs
#include "UI.hpp"
#include "Sprite.hpp"

namespace sfs
{
Sprite::Sprite(const sf::Texture &texture) noexcept
    : sf::Sprite(texture)
{
}

void Sprite::display(sf::RenderWindow &window) noexcept
{
	window.draw(*this);
}

void Sprite::update(Scene &, GameObject &object) noexcept
{
	setPosition(object.getPosition());
}
} // namespace sfs
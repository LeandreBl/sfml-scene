#include "Shape.hpp"
#include "GameObject.hpp"

namespace sfs
{
// sfs::Rectangle

Rectangle::Rectangle(const sf::Vector2f &position, const sf::Vector2f &size, const sf::Color &color) noexcept
    : sf::RectangleShape(size)
{
	setPosition(position);
	setFillColor(color);
}

void Rectangle::display(sf::RenderWindow &window) noexcept
{
	window.draw(*this);
}

// sfs::Circle

Circle::Circle(const sf::Vector2f &position, float radius, const sf::Color &color) noexcept
    : sf::CircleShape(radius)
{
	setPosition(position);
	setFillColor(color);
}

void Circle::display(sf::RenderWindow &window) noexcept
{
	window.draw(*this);
}
} // namespace sfs
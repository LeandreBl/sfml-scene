#pragma once

#include "IComponent.hpp"

#include <SFML/Graphics.hpp>

namespace sfs
{
class Rectangle : public IComponent, public sf::RectangleShape
{
      public:
	Rectangle(const sf::Vector2f &position,
		  const sf::Vector2f &size = sf::Vector2f(0, 0),
		  const sf::Color &color = sf::Color::White) noexcept
	    : sf::RectangleShape(size)
	{
		setPosition(position);
		setFillColor(color);
	}
	void display(sf::RenderWindow &window) noexcept
	{
		window.draw(*this);
	}
};

class Circle : public IComponent, public sf::CircleShape
{
      public:
	Circle(const sf::Vector2f &position, float radius = 0,
	       const sf::Color &color = sf::Color::White) noexcept
	    : sf::CircleShape(radius)
	{
		setPosition(position);
		setFillColor(color);
	}
	void display(sf::RenderWindow &window) noexcept
	{
		window.draw(*this);
	}
};
} // namespace sfs
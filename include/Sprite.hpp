#pragma once

#include "IComponent.hpp"


namespace sfs
{
class Sprite : public IComponent, public sf::Sprite
{
      public:
	Sprite(const sf::Texture &texture = sf::Texture(), const sf::Vector2f &offset = sf::Vector2f(0, 0)) noexcept
	: sf::Sprite(texture), _offset(offset)
	{

	}

	void display(sf::RenderWindow &window) noexcept
	{
		window.draw(*this);
	}

	void update(Scene &, GameObject &go) noexcept
	{
		setPosition(go.getPosition() + _offset);
	}

	void setOffset(const sf::Vector2f &offset) noexcept
	{
		_offset = offset;
	}

	sf::Vector2f getOffset() const noexcept
	{
		return _offset;
	}

	protected:
		sf::Vector2f _offset;
};
} // namespace sfs
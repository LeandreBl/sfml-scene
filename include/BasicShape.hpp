#pragma once

#include <SFML/Graphics.hpp>

#include "IComponent.hpp"
#include "GameObject.hpp"

namespace sfs
{
template <typename DrawableShape>
class BasicShape : public IComponent, public DrawableShape
{
      public:
	template <typename... Args>
	BasicShape(const sf::Vector2f &offset, Args &&... args)
	    : DrawableShape(args...), _offset(offset)
	{
	}

	void update(Scene &, GameObject &go) noexcept
	{
		DrawableShape::setPosition(go.getPosition() + _offset);
	}

	void display(sf::RenderWindow &window) noexcept
	{
		window.draw(*this);
	}

	void setOffset(const sf::Vector2f &offset) noexcept
	{
		_offset = offset;
	}

	sf::Vector2f getOffset() const noexcept
	{
		return _offset;
	}

      private:
	sf::Vector2f _offset;
};

class Rectangle : public BasicShape<sf::RectangleShape>
{
      public:
	Rectangle(const sf::Vector2f &offset = sf::Vector2f(0, 0),
		  const sf::Vector2f &size = sf::Vector2f(0, 0),
		  const sf::Color &color = sf::Color::White) noexcept
	    : BasicShape<sf::RectangleShape>(offset, size)
	{
		setFillColor(color);
	}
};

class Circle : public BasicShape<sf::CircleShape>
{
      public:
	Circle(const sf::Vector2f &offset = sf::Vector2f(0, 0),
	       float radius = 0,
	       const sf::Color &color = sf::Color::White) noexcept
	    : BasicShape<sf::CircleShape>(offset, radius)
	{
		setFillColor(color);
	}
};

class Sprite : public BasicShape<sf::Sprite>
{
      public:
	Sprite(const sf::Texture &texture = sf::Texture(),
	       const sf::Vector2f &offset = sf::Vector2f(0, 0)) noexcept
	    : BasicShape<sf::Sprite>(offset, texture)
	{
	}
};

class Text : public BasicShape<sf::Text>
{
      public:
	Text(const sf::Font &font, const std::string &text = "",
	     const sf::Color &color = sf::Color::White,
	     uint32_t characterSize = 32,
	     const sf::Vector2f &offset = sf::Vector2f(0, 0)) noexcept
	    : BasicShape<sf::Text>(offset, text, font, characterSize)
	{
		setFillColor(color);
	}
};

class MultiSprite : public BasicShape<sf::Sprite>
{
	public:
	template <typename T>
	MultiSprite(const sf::Texture &texture, const T &container, float deltaTime = 1, const sf::Vector2f &offset = sf::Vector2f(0, 0))
		: BasicShape<sf::Sprite>(offset, texture)
		, _delta(deltaTime / container.size())
		, _elapsed(0)
		, _index(0)
	{
		for (auto &&i : container)
			_frames.emplace_back(i);
	}
	void start(sfs::Scene &scene, sfs::GameObject &) noexcept
	{
		this->setTextureRect(_frames[0]);
	}
	void update(sfs::Scene &scene, sfs::GameObject &go) noexcept
	{
		BasicShape<sf::Sprite>::update(scene, go);
		float dt = scene.deltaTime();

		_elapsed += dt;
		if (_elapsed >= _delta) {
			_index = (_index + 1 == _frames.size()) ? 0 : _index + 1;
			setTextureRect(_frames[_index]);
			_elapsed = 0;
		}
	}
	protected:
		std::vector<sf::IntRect> _frames;
		float _delta;
		float _elapsed;
		size_t _index;
};

} // namespace sfs
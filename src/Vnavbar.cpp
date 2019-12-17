#include <math.h>

#include "Vnavbar.hpp"
#include "Colors.hpp"

namespace sfs {

constexpr float percentage = 0.85;

Vnavbar::Vnavbar(const sf::Vector2f &position, const sf::Vector2f &size,
		 const sf::Color &color) noexcept
	: UI("Vnavbar", position)
	, _background(addComponent<Rectangle>(sf::Vector2f(0, 0), size, color))
	, _cursor(addComponent<Rectangle>(
		  sf::Vector2f(size.x * (1 - percentage) / 2, size.x * (1 - percentage) / 2),
		  sf::Vector2f(size.x * percentage, size.y / 3), color * 0.7))
	, _color(color)
	, _clickPosY(0)
	, _clicked(false)
{
	setPosition(position);
}

sf::FloatRect Vnavbar::getGlobalBounds() const noexcept
{
	return _background.getGlobalBounds();
}

void Vnavbar::start(Scene &scene) noexcept
{
	scene.subscribe(*this, sf::Event::MouseButtonPressed);
	scene.subscribe(*this, sf::Event::MouseButtonReleased);
	scene.subscribe(*this, sf::Event::MouseMoved);
}

void Vnavbar::setCursorColor(int x, int y) noexcept
{
	if (_cursor.getGlobalBounds().contains(x, y))
		_cursor.setFillColor(_color * 0.5);
	else
		_cursor.setFillColor(_color * 0.7);
}

float Vnavbar::maxOffset() const noexcept
{
	return _background.getSize().y - minOffset() - _cursor.getSize().y;
}

float Vnavbar::minOffset() const noexcept
{
	return _background.getSize().x * (1 - percentage) / 2;
}

void Vnavbar::onEvent(Scene &, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::MouseMoved) {
		if (_clicked == false) {
			setCursorColor(event.mouseMove.x, event.mouseMove.y);
		}
		else {
			auto offset = _cursor.getOffset();
			offset.y += event.mouseMove.y - _clickPosY;
			float bound = maxOffset();
			if (offset.y > bound)
				offset.y = bound;
			bound = minOffset();
			if (offset.y < bound)
				offset.y = bound;
			_clickPosY = event.mouseMove.y;
			_cursor.setOffset(offset);
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed) {
		if (_cursor.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			_clicked = true;
			_clickPosY = event.mouseButton.y;
			_cursor.setFillColor(_color * 0.3);
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		_clicked = false;
		setCursorColor(event.mouseButton.x, event.mouseButton.y);
	}
}

float Vnavbar::getValue() const noexcept
{
	float min = minOffset();
	float max = maxOffset() - min;
	float pos = _cursor.getOffset().y - min;
	return pos / max;
}

void Vnavbar::setTexture(const sf::Texture &texture) noexcept
{
	_background.setTexture(&texture);
}

void Vnavbar::setCursorTexture(const sf::Texture &texture) noexcept
{
	_cursor.setTexture(&texture);
}

} // namespace sfs

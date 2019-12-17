#include <math.h>

#include "Hnavbar.hpp"
#include "Colors.hpp"

namespace sfs {

constexpr float percentage = 0.85;

Hnavbar::Hnavbar(Scene &scene, const sf::Vector2f &position, const sf::Vector2f &size,
		 const sf::Color &color) noexcept
	: UI(scene, "Hnavbar", position)
	, _background(addComponent<Rectangle>(sf::Vector2f(0, 0), size, color))
	, _cursor(addComponent<Rectangle>(
		  sf::Vector2f(size.y * (1 - percentage) / 2, size.y * (1 - percentage) / 2),
		  sf::Vector2f(size.x / 3, size.y * percentage), color * 0.7))
	, _color(color)
	, _clickPosX(0)
	, _clicked(false)
{
	setPosition(position);
}

sf::FloatRect Hnavbar::getGlobalBounds() const noexcept
{
	return _background.getGlobalBounds();
}

void Hnavbar::start() noexcept
{
	subscribe(sf::Event::MouseButtonPressed);
	subscribe(sf::Event::MouseButtonReleased);
	subscribe(sf::Event::MouseMoved);
}

void Hnavbar::update() noexcept
{
}

void Hnavbar::onDestroy() noexcept
{
}

void Hnavbar::setCursorColor(int x, int y) noexcept
{
	if (_cursor.getGlobalBounds().contains(x, y))
		_cursor.setFillColor(_color * 0.5);
	else
		_cursor.setFillColor(_color * 0.7);
}

float Hnavbar::maxOffset() const noexcept
{
	return _background.getSize().x - minOffset() - _cursor.getSize().x;
}

float Hnavbar::minOffset() const noexcept
{
	return _background.getSize().y * (1 - percentage) / 2;
}

void Hnavbar::onEvent(const sf::Event &event) noexcept
{
	if (event.type == sf::Event::MouseMoved) {
		if (_clicked == false) {
			setCursorColor(event.mouseMove.x, event.mouseMove.y);
		}
		else {
			auto offset = _cursor.getOffset();
			offset.x += event.mouseMove.x - _clickPosX;
			float bound = maxOffset();
			if (offset.x > bound)
				offset.x = bound;
			bound = minOffset();
			if (offset.x < bound)
				offset.x = bound;
			_clickPosX = event.mouseMove.x;
			_cursor.setOffset(offset);
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed) {
		if (_cursor.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			_clicked = true;
			_clickPosX = event.mouseButton.x;
			_cursor.setFillColor(_color * 0.3);
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		_clicked = false;
		setCursorColor(event.mouseButton.x, event.mouseButton.y);
	}
}

float Hnavbar::getValue() const noexcept
{
	float min = minOffset();
	float max = maxOffset() - min;
	float pos = _cursor.getOffset().x - min;
	return pos / max;
}

void Hnavbar::setTexture(const sf::Texture &texture) noexcept
{
	_background.setTexture(&texture);
}

void Hnavbar::setCursorTexture(const sf::Texture &texture) noexcept
{
	_cursor.setTexture(&texture);
}

} // namespace sfs

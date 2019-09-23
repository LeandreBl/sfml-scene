#pragma once

#include "UI.hpp"
#include "Shape.hpp"

namespace sfs
{
class Hnavbar : public UI
{
      public:
	Hnavbar(const sf::Vector2f &position = sf::Vector2f(0, 0),
		const sf::Vector2f &size = sf::Vector2f(30, 100),
		const sf::Color &color = sf::Color::White) noexcept;
	Hnavbar(const Hnavbar &) noexcept = default;
	Hnavbar &operator=(Hnavbar &) noexcept = default;
	void start(Scene &scene) noexcept;
	void onEvent(Scene &scene, const sf::Event &event) noexcept;
	float getValue() const noexcept;

      protected:
	float maxPosY() const noexcept;
	float minPosY() const noexcept;
	void setCursorColor(int x, int y) noexcept;
	Rectangle &_background;
	Rectangle &_cursor;
	sf::Color _color;
	float _clickPosY;
	float _cursorPosY;
	bool _clicked;
};
} // namespace sfs
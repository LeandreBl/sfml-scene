#pragma once

#include "UI.hpp"
#include "BasicShape.hpp"

namespace sfs
{
class Vnavbar : public UI
{
      public:
	Vnavbar(const sf::Vector2f &position = sf::Vector2f(0, 0),
		const sf::Vector2f &size = sf::Vector2f(30, 100),
		const sf::Color &color = sf::Color::White) noexcept;
	Vnavbar(const Vnavbar &) noexcept = default;
	Vnavbar &operator=(Vnavbar &) noexcept = default;
	void start(Scene &scene) noexcept;
	void onEvent(Scene &scene, const sf::Event &event) noexcept;
	float getValue() const noexcept;
	sf::FloatRect getGlobalBounds() const noexcept;
	void setCursorTexture(const sf::Texture &texture) noexcept;
	void setTexture(const sf::Texture &texture) noexcept;

      protected:
	float maxOffset() const noexcept;
	float minOffset() const noexcept;
	void setCursorColor(int x, int y) noexcept;
	Rectangle &_background;
	Rectangle &_cursor;
	sf::Color _color;
	float _clickPosY;
	bool _clicked;
};
} // namespace sfs

#pragma once

#include "UI.hpp"
#include "BasicShape.hpp"

namespace sfs {
class Hnavbar : public UI {
      public:
	Hnavbar(Scene &scene, const sf::Vector2f &position = sf::Vector2f(0, 0),
		const sf::Vector2f &size = sf::Vector2f(30, 100),
		const sf::Color &color = sf::Color::White) noexcept;
	Hnavbar(const Hnavbar &) noexcept = default;
	Hnavbar &operator=(Hnavbar &) noexcept = default;
	void start() noexcept;
	void update() noexcept;
	void onEvent(const sf::Event &event) noexcept;
	void onDestroy() noexcept;
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
	float _clickPosX;
	bool _clicked;
};
} // namespace sfs

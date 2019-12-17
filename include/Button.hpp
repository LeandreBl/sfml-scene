#pragma once

#include <functional>

#include "UI.hpp"
#include "BasicShape.hpp"

namespace sfs {
class Button : public UI {
      public:
	Button(Scene &scene, const sf::Texture &texture, const sf::Font &font,
	       const sf::Vector2f &position = sf::Vector2f(0.f, 0.f),
	       const std::function<void()> &onClick = []() {}, const std::string &text = "",
	       const sf::Color &color = sf::Color::White, uint32_t charSize = 32) noexcept;
	Button(const Button &) noexcept = default;
	Button &operator=(Button &) noexcept = default;
	sf::FloatRect getGlobalBounds() const noexcept;
	void setText(const std::string &buttonText) noexcept;
	void setTexture(const sf::Texture &texture, bool resetRect = false) noexcept;
	void setTexture(const sf::Texture &texture, const sf::IntRect &rectangle) noexcept;
	void setOnClick(const std::function<void()> &onClick) noexcept;
	void setFont(const sf::Font &font) noexcept;
	void setTextSize(uint32_t size) noexcept;
	void setTextColor(const sf::Color &color) noexcept;
	void setScale(const sf::Vector2f &scale) noexcept;
	void setRotate(const float &angle) noexcept;
	void setString(const std::string &str) noexcept
	{
		_text.setString(str);
	};
	std::string getString() noexcept
	{
		return _text.getString();
	};
	void start() noexcept;
	void update() noexcept;
	void onEvent(const sf::Event &event) noexcept;
	void onDestroy() noexcept;

      protected:
	Sprite &_sprite;
	Text &_text;
	std::function<void()> _onClick;
	bool _pressed;
};
} // namespace sfs

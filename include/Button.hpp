#pragma once

#include <functional>

#include "UI.hpp"
#include "Text.hpp"

namespace sfs
{
class Button : public UI
{
      public:
	Button(const sf::Vector2f &position = sf::Vector2f(0.f, 0.f),
	       const std::string &textureName = "",
		   const std::string &fontName = "",
		   const std::string &placeHolder = "",
	       const std::function<void()> &onClick = []() {}) noexcept;
	void start(Scene &scene) noexcept;
	void update(Scene &scene) noexcept;
	void onEvent(Scene &scene) noexcept;

      protected:
	Text *_text;
	std::string _placeholder;
	std::string _textureName;
	std::string _fontName;
	std::function<void ()> _onClick;
	sf::Vector2f _clickPos;
	sf::Vector2f _movePos;
	bool _moved;
	bool _pressed;
};
} // namespace sfs
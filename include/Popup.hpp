#pragma once

#include <queue>
#include "UI.hpp"
#include "BasicShape.hpp"

namespace sfs
{
class Popup : public UI
{
	public:
	Popup(const sf::Font &font, const sf::Vector2f &position = sf::Vector2f(0, 0)) noexcept;
	void setTexture(const sf::Texture &texture) noexcept;
	void setCharacterSize(uint32_t size) noexcept;
	void setBoxColor(const sf::Color &color) noexcept;
	void setTextColor(const sf::Color &color) noexcept;
	void push(const sf::String &string, float duration = 3) noexcept;
	void clear() noexcept;
	void pop(size_t n = 1) noexcept;
	void update(Scene &scene) noexcept;
        sf::FloatRect getGlobalBounds() noexcept {return _box.getGlobalBounds();};
	protected:
	void clean() noexcept;
	sf::Uint8 getAlpha() const noexcept;
	void updateString() noexcept;
	Rectangle &_box;
	Text &_text;
	std::queue<std::pair<sf::String, float>> _queue;
	float _elapsed;
};
} // namespace sfs

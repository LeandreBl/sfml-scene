#include "Popup.hpp"
#include "Colors.hpp"

namespace sfs
{
Popup::Popup(const sf::Font &font, const sf::Vector2f &position) noexcept
    : UI(position, "Popup"), _box(addComponent<Rectangle>()),
      _text(addComponent<Text>(font, "", sf::Color::Black)), _queue(),
      _elapsed(0.f)
{
}

void Popup::updateString() noexcept
{

	_text.setString(_queue.front().first);
	auto rect = _text.getLocalBounds();
	float gapx = rect.width * 1.5;
	float gapy = rect.height * 2;
	_box.setSize(sf::Vector2f(gapx, gapy));
	_box.setOffset(sf::Vector2f(-rect.width, 0));
	auto boxrect = _box.getLocalBounds();
	_text.setOffset(
		sf::Vector2f((boxrect.width - rect.width) / 2 - rect.left,
			     (boxrect.height - rect.height) / 2 - rect.top)
		+ _box.getOffset());
}

sf::Uint8 Popup::getAlpha() const noexcept
{
	if (_elapsed <= _queue.front().second / 3) {
		return _elapsed * 255 / (_queue.front().second / 3);
	} else if (_elapsed <= _queue.front().second * 2 / 3) {
		return 255;
	}
	return 255 - (_elapsed * 255 / (_queue.front().second / 3));
}

void Popup::clean() noexcept
{
	auto color = _box.getFillColor();
	color.a = 0;
	_box.setFillColor(color);
	_text.setString("");
	_elapsed = 0;
}

void Popup::update(Scene &scene) noexcept
{
	if (_queue.size() > 0) {
		_elapsed += scene.deltaTime();
		if (_elapsed >= _queue.front().second) {
			_queue.pop();
			_elapsed = 0.f;
			if (_queue.size() > 0) {
				updateString();
			} else {
				Popup::clean();
				return;
			}
		}
		auto color = _box.getFillColor();
		auto alpha = getAlpha();
		color.a = alpha;
		_box.setFillColor(color);
		color = _text.getFillColor();
		color.a = alpha;
		_text.setFillColor(color);
	}
}

void Popup::setTexture(const sf::Texture &texture) noexcept
{
	_box.setTexture(&texture);
}

void Popup::setCharacterSize(uint32_t size) noexcept
{
	_text.setCharacterSize(size);
}

void Popup::setBoxColor(const sf::Color &color) noexcept
{
	_box.setFillColor(color);
}

void Popup::setTextColor(const sf::Color &color) noexcept
{
	_text.setFillColor(color);
}

void Popup::push(const sf::String &string, float duration) noexcept
{
	_queue.emplace(string, duration);
	if (_queue.size() == 1)
		updateString();
}

void Popup::clear() noexcept
{
	pop(_queue.size());
}

void Popup::pop(size_t n) noexcept
{
	while (_queue.size() > 0 && n > 0)
		_queue.pop();
	if (_queue.size() == 0)
		Popup::clean();
}

} // namespace sfs

#include "Scene.hpp"
#include "Button.hpp"

namespace sfs
{
Button::Button(const sf::Vector2f &position, const std::string &textureName,
	       const std::string &fontName, const std::string &placeHolder,
	       const std::function<void()> &onClick) noexcept
    : UI(position, "Button"), _placeholder(placeHolder),
      _textureName(textureName), _fontName(fontName), _text(nullptr),
      _onClick(std::move(onClick)), _clickPos(), _movePos(), _moved(false),
      _pressed(false)
{
}

void Button::start(Scene &scene) noexcept
{
	auto font = scene.getAssetFont(_fontName);
	auto texture = scene.getAssetTexture(_textureName);

	if (font == nullptr) {
		errorLog("Could not load " + _fontName + " font");
		destroy();
		return;
	} else if (texture == nullptr) {
		errorLog("Could not load " + _textureName + " texture");
		destroy();
		return;
	}
	//_text = &addComponent<Text>(_placeholder, *font,
}

void Button::update(Scene &scene) noexcept
{
}

void Button::onEvent(Scene &scene) noexcept
{
}
} // namespace sfs
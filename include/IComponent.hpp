#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace sfs
{
class Scene;
class GameObject;

class IComponent
{
      public:
	virtual ~IComponent() noexcept = default;
	virtual void start(Scene &, GameObject &) noexcept {};
	virtual void display(sf::RenderWindow &) noexcept {};
	virtual void onEvent(Scene &, const sf::Event &, GameObject &) noexcept {};
	virtual void update(Scene &, GameObject &) noexcept {};
};
} // namespace sfs
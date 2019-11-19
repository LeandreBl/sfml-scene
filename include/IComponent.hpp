#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace sfs {
class Scene;
class GameObject;

class IComponent {
      public:
	virtual ~IComponent() noexcept = default;
	virtual void start(Scene &, GameObject &) noexcept {};
	virtual void display(sf::RenderWindow &) noexcept {};
	virtual void update(Scene &, GameObject &) noexcept {};
	void destroy() noexcept
	{
		_toDestroy = true;
	}
	bool toDestroy() const noexcept
	{
		return _toDestroy;
	}

      protected:
	bool _toDestroy = false;
};
} // namespace sfs

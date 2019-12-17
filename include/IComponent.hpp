#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace sfs {
class Scene;
class GameObject;

class IComponent {
      public:
	IComponent() noexcept;
	virtual ~IComponent() noexcept = default;
	virtual void start(Scene &, GameObject &) noexcept {};
	virtual void display(sf::RenderWindow &) noexcept {};
	virtual void update(Scene &, GameObject &) noexcept {};
	virtual void onDestroy() noexcept {};
	uint64_t getId() const noexcept;
	void destroy() noexcept;
	bool toDestroy() const noexcept;
	bool isActive() const noexcept;
	void setActive(bool state) noexcept;

      protected:
	const uint64_t _id;
	bool _toDestroy;
	bool _isActive;
};
} // namespace sfs

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
	virtual void start(GameObject &) noexcept = 0;
	virtual void display(sf::RenderWindow &) noexcept {};
	virtual void update(GameObject &) noexcept = 0;
	virtual void onDestroy() noexcept = 0;
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

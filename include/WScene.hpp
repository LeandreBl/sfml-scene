#pragma once

#include "Scene.hpp"

namespace sfs
{

class UI;

class WScene : public Scene
{
      public:
	WScene(const std::string &name, uint32_t fps) noexcept;
	sf::RenderWindow *getWindow() noexcept;
	void subscribe(const GameObject &object, const IComponent &component,
		       const sf::Event::EventType &type) noexcept override;
	void unsubscribe(const IComponent &component,
			 const sf::Event::EventType &type) noexcept override;
	void framerate(uint32_t framerate) noexcept;
	void run() noexcept;

      protected:
	void callSubscribedEvents() noexcept;
	sf::RenderWindow _window;
	std::vector<std::pair<GameObject *, IComponent *>>
		_subscribedEvents[sf::Event::Count + 1];
};
} // namespace sfs
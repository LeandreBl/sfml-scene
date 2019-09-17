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
	void subscribe(const GameObject &object,
		       const sf::Event::EventType &type) noexcept;
	void unsubscribe(const GameObject &object,
			 const sf::Event::EventType &type) noexcept;
	void framerate(uint32_t framerate) noexcept;
	void run() noexcept;

      protected:
	void callSubscribedEvents() noexcept;
	sf::RenderWindow _window;
	std::vector<GameObject *> _subscribedEvents[sf::Event::Count + 1];
};
} // namespace sfs
#pragma once

#include "Scene.hpp"

namespace sfs
{
class WScene : public Scene
{
      public:
	WScene(const std::string &name, uint32_t fps) noexcept;
	sf::RenderWindow *getWindow() noexcept;
	void subscribe(const GameObject *object,
		       const sf::Event::EventType &type) noexcept;
	void unsubscribe(const GameObject *object,
			 const sf::Event::EventType &type) noexcept;
	void framerate(uint32_t framerate) noexcept;
	void run() noexcept;
      private:
	void callSubscribedEvents() noexcept;
	std::vector<GameObject *> _subscribedEvents[sf::Event::Count + 1];
	sf::RenderWindow _window;
};
} // namespace sfs
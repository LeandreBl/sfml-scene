#include <iostream>

#include "include/Text.hpp"
#include "include/WScene.hpp"
#include "include/GameObject.hpp"

class Pulse : public sfs::IComponent
{
      public:
	Pulse(const sf::Vector2f &force) noexcept : _force(force){};
	void update(sfs::Scene &scene, sfs::GameObject &object) noexcept
	{
		object.move(_force * scene.deltaTime());
	}

      protected:
	sf::Vector2f _force;
};

struct CloseHandler : public sfs::IComponent {
	void start(sfs::Scene &scene, sfs::GameObject &object) noexcept
	{
		scene.subscribe(object, *this, sf::Event::Closed);
	}
	void onEvent(sfs::Scene &scene, const sf::Event &event, sfs::GameObject &object) noexcept
	{
		scene.close();
	}
};

struct CircleSprite : public sfs::IComponent {
	CircleSprite(const sf::Color &color, float size) : _shape(size)
	{
		_shape.setFillColor(color);
	}

	void update(sfs::Scene &scene, sfs::GameObject &object) noexcept
	{
		_shape.setPosition(object.getPosition());
		if (object.getPosition().x > 2000
		    || object.getPosition().y > 2000)
			object.destroy();
	}

	void display(sf::RenderWindow &window) noexcept
	{
		window.draw(_shape);
	};
	sf::CircleShape _shape;
};

class Circle : public sfs::GameObject
{
	void start(sfs::Scene &scene) noexcept
	{
		addComponent<Pulse>(
			sf::Vector2f(std::rand() % 400, std::rand() % 400));
		addComponent<CircleSprite>(sf::Color(std::rand()), 5.f);
	}
};

struct Slower : public sfs::IComponent {
	void start(sfs::Scene &scene, sfs::GameObject &object) noexcept
	{
		scene.subscribe(object, *this, sf::Event::KeyPressed);
	}
	void onEvent(sfs::Scene &scene, const sf::Event &event, sfs::GameObject &object) noexcept
	{
		float v;
		if (event.key.code == sf::Keyboard::Up) {
			v = 0.1;
			scene.timeScale(scene.timeScale() + v);
		} else if (event.key.code == sf::Keyboard::Down) {
			v = -0.1;
			scene.timeScale(scene.timeScale() + v);
		} else if (event.key.code == sf::Keyboard::Space) {
			for (size_t i = 0; i < 1000; ++i)
				object.addChild<Circle>(scene);
		} else if (event.key.code == sf::Keyboard::Return) {
			for (auto &&i : object.getChilds())
				i->destroy();
		}
	}
};

class Manager : public sfs::GameObject
{
      public:
	void start(sfs::Scene &scene) noexcept
	{
		auto font = scene.getAssetFont(
			"/usr/share/fonts/truetype/ubuntu/UbuntuMono-BI.ttf");

		if (font != nullptr) {
			_text = &addComponent<sfs::Text>("", *font);
		} else {
			scene.close();
		}
		addComponent<CloseHandler>();
		addComponent<Slower>();

		setPosition(1500, 0);
	};
	void update(sfs::Scene &scene) noexcept
	{
		_text->setString(std::to_string(scene.timeScale()) + " "
				 + std::to_string(scene.framerate()) + "\n" + std::to_string(_childs.size()));
	}
	sfs::Text *_text;
};

int main()
{
	sfs::WScene scene("test", 120);

	std::srand(time(NULL));
	scene.addGameObject<Manager>();
	scene.run();
	return 0;
}

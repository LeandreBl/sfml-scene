#include <iostream>

#include "include/Text.hpp"
#include "include/WScene.hpp"
#include "include/GameObject.hpp"
#include "include/InputBox.hpp"

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
		addComponent<CircleSprite>(sf::Color(std::rand()), 1 + std::rand() % 10);
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

		_input = &scene.addGameObject<sfs::InputBox>(
			sf::Vector2f(10, 10), "", "Write here");

		scene.subscribe(*this, sf::Event::Closed);
		scene.subscribe(*this, sf::Event::KeyPressed);
		setPosition(1500, 0);
	};
	void update(sfs::Scene &scene) noexcept
	{
		_text->setString(std::to_string(scene.timeScale()) + " "
				 + std::to_string(scene.framerate()) + "\n"
				 + std::to_string(_childs.size()));
	}
	void onEvent(sfs::Scene &scene, const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed) {
			float v;
			if (event.key.code == sf::Keyboard::Up) {
				v = 0.1;
				scene.timeScale(scene.timeScale() + v);
			} else if (event.key.code == sf::Keyboard::Down) {
				v = -0.1;
				scene.timeScale(scene.timeScale() + v);
			} else if (event.key.code == sf::Keyboard::Space) {
				size_t n = atoi(_input->string().c_str());
				for (size_t i = 0; i < n; ++i)
					addChild<Circle>(scene);
			} else if (event.key.code == sf::Keyboard::Return) {
				for (auto &&i : _childs)
					i->destroy();
			}
		} else if (event.type == sf::Event::Closed) {
			scene.close();
		}
	}
	sfs::Text *_text;
	sfs::InputBox *_input;
};

int main()
{
	sfs::WScene scene("test", 120);

	std::srand(time(NULL));
	scene.addGameObject<Manager>();
	scene.run();
	return 0;
}

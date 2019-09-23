#include <iostream>

#include "include/Text.hpp"
#include "include/WScene.hpp"
#include "include/GameObject.hpp"
#include "include/InputBox.hpp"
#include "include/Button.hpp"
#include "include/Hnavbar.hpp"

class Pulse : public sfs::IComponent
{
      public:
	Pulse(const sf::Vector2f &force) noexcept : _force(force){};
	void update(sfs::Scene &scene, sfs::GameObject &object) noexcept
	{
		_gravity += 1;
		_force.y += _gravity * scene.deltaTime();
		object.move(_force * scene.deltaTime());
		if (object.getPosition().y > 1080)
			_force.y *= -0.7;
		if (object.getPosition().x > 1920)
			_force.x *= -1;
	}

      protected:
	sf::Vector2f _force;
	float _gravity = 1;
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
		    || object.getPosition().y > 1100
		    || object.getPosition().x < 0 || object.getPosition().y < 0)
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
		addComponent<Pulse>(sf::Vector2f(300 + std::rand() % 400,
						 std::rand() % 100));
		addComponent<CircleSprite>(sf::Color(std::rand()),
					   1 + std::rand() % 10);
	}
};

class Manager : public sfs::GameObject
{
      public:
	void removeSpheres()
	{
		for (auto &&i : _childs)
			i->destroy();
	}

	void start(sfs::Scene &scene) noexcept
	{
		auto font = scene.getAssetFont(
			"/usr/share/fonts/truetype/ubuntu/UbuntuMono-BI.ttf");
		auto texture = scene.getAssetTexture(
			"/home/leandre/TEST_FOLDER/button.png");

		if (font != nullptr) {
			_text = &addComponent<sfs::Text>(*font, "");
		} else if (texture == nullptr) {
			errorLog("Could not load texture");
			scene.close();
		} else {
			scene.close();
		}

		_navbar = scene.getGameObjects<sfs::Hnavbar>()[0];

		_input = &scene.addGameObject<sfs::InputBox>(
			*font, sf::Vector2f(10, 10), "spawn n*");

		auto &button = scene.addGameObject<sfs::Button>(
			sf::Vector2f(200, 10), *texture,
			std::bind(&Manager::removeSpheres, this), *font,
			"Reset");

		button.setTextColor(sf::Color(110, 110, 110));
		button.setTextSize(26);

		scene.subscribe(*this, sf::Event::Closed);
		scene.subscribe(*this, sf::Event::KeyPressed);
		setPosition(1500, 0);
	};
	void update(sfs::Scene &scene) noexcept
	{
		_text->setString("x" + std::to_string(scene.timeScale()) + " "
				 + std::to_string(scene.framerate()) + "\n"
				 + std::to_string(_childs.size()) + "\n"
				 + std::to_string(_navbar->getValue()));
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
				removeSpheres();
			}
		} else if (event.type == sf::Event::Closed) {
			scene.close();
		}
	}
	sfs::Text *_text;
	sfs::InputBox *_input;
	sfs::Hnavbar *_navbar;
};

int main()
{
	sfs::WScene scene("test", 120);

	std::srand(time(NULL));
	scene.addGameObject<Manager>();
	scene.addGameObject<sfs::Hnavbar>(
		sf::Vector2f(0, 0), sf::Vector2f(30, 1080), sf::Color::White);
	scene.run();
	return 0;
}

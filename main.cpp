#include <SFML/Graphics.hpp>
#include <iostream>

using namespace::std;
using namespace::sf;

Vector2f operator*(Vector2f vec, float scalar) {
	return {vec.x * scalar, vec.y * scalar};
}

int main()
{
	sf::Clock clock;
	sf::Time elapsed;

	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!", sf::Style::Default);
	window.setFramerateLimit(144);


	sf::RectangleShape shape({50.f, 50.f});
	sf::RectangleShape rectangle({700.f, 500.f});

	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition({50.0f,50.0f});

	shape.setFillColor(sf::Color::Green);

	window.setKeyRepeatEnabled(false);

	Vector2f velocity = {0,0};

	while (window.isOpen())
	{

		elapsed = clock.restart();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				switch (keyPressed->scancode) {
					case sf::Keyboard::Scancode::D:
						velocity = {0.0001f,0.f};
						break;
					case sf::Keyboard::Scancode::S:
						velocity = {0.f,0.0001f};
						break;
					case sf::Keyboard::Scancode::A:
						velocity = {-0.0001f,0.f};
						break;
					case sf::Keyboard::Scancode::W:
						velocity = {0.f,-0.0001f};
						break;
				}
			}
		}

		shape.setPosition(shape.getPosition() + velocity * elapsed.asMicroseconds());

		window.clear();
		window.draw(rectangle);
		window.draw(shape);
		window.display();
	}
}
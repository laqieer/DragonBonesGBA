/** @file DragonBoy.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include <GBA/Graphics.hpp>

#include <dragonBones/GBAFactory.h>
#include <dragonBones/GBAArmatureDisplay.h>


int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "My window");
	window.setFramerateLimit(60);

	dragonBones::GBAFactory factory;

	sf::Texture texture;
	texture.loadFromFile("DragonBoy_tex.png");

	factory.loadDragonBonesData("DragonBoy_ske.json");
	factory.loadTextureAtlasData("DragonBoy_tex.json", &texture);

	auto armatureDisplay = new dragonBones::GBAArmatureDisplay("Dragon");
	armatureDisplay->getAnimation()->play("walk");
	armatureDisplay->setPosition({ 512.f, 440.f });

	sf::Clock clock;

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		factory.update(deltaTime);

		window.clear();
		window.draw(*armatureDisplay);
		window.display();
	}
	
	return 0;
}

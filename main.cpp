#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <fstream>

#include "vehicle.h"
#include "shared.h"

void resizeWindow(sf::RenderWindow & window, std::vector<Vehicle> &vehicles) {
	float endX = vehicles[0].x + 2.5f;
	float startX = vehicles[vehicles.size() - 1].x - 2.5f;
	float dist = endX - startX;

	window.setView(sf::View(sf::FloatRect(startX, -dist/2, dist, dist)));
}

int main()
{
	std::ofstream filePosition, fileVelocity, fileAcceleration;
	filePosition.open("position.csv");
	fileVelocity.open("velocity.csv");
	fileAcceleration.open("acceleration.csv");
	filePosition << ",V1,V2,V3,V4,V5,V6,V7,V8,V9,V10" << std::endl;
	fileVelocity << ",V1,V2,V3,V4,V5,V6,V7,V8,V9,V10" << std::endl;
	fileAcceleration << ",V1,V2,V3,V4,V5,V6,V7,V8,V9,V10" << std::endl;

	std::vector<Vehicle> vehicles;

	for (int i = 0; i < 10; ++i)
		vehicles.push_back(Vehicle((float)(10 - i)));

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::Texture roadTexture;
	if (!roadTexture.loadFromFile("road.jpg"))
		return 1;
	roadTexture.setRepeated(true);

	sf::Sprite roadSprite;
	roadSprite.scale(0.01f, 0.01f);
	roadSprite.setPosition(0.0f, -0.75f);
	roadSprite.setTexture(roadTexture);
	roadSprite.rotate(0);
	roadSprite.setTextureRect(sf::IntRect(0, 0, 999 * 1200, 300));

	window.setFramerateLimit(FPS);
	int t = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				filePosition.close();
				fileVelocity.close();
				fileAcceleration.close();
			}
		}

		vehicles[0].braking = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

		vehicles[0].tick();


		for (int i = 1; i < vehicles.size(); ++i)
			vehicles[i].tick(vehicles[i - 1]);

		filePosition << ((float)t++)/FPS;
		fileVelocity << ((float)t++) / FPS;
		fileAcceleration << ((float)t++) / FPS;

		for (int i = 0; i < vehicles.size(); ++i) {
			filePosition << "," << vehicles[i].x;
			fileVelocity << "," << vehicles[i].v;
			fileAcceleration << "," << vehicles[i].acc;
		}
		filePosition << std::endl;
		fileVelocity << std::endl;
		fileAcceleration << std::endl;

		resizeWindow(window, vehicles);

		window.clear();

		window.draw(roadSprite);
		for (Vehicle & veh : vehicles)
			veh.draw(window);

		window.display();
	}

	return 0;
}
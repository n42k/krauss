#pragma once

#include <SFML/Graphics.hpp>
class Vehicle {
public:
	Vehicle(float x);
	void setPosition(float x);
	void tick();
	void tick(Vehicle & carInFront);
	void draw(sf::RenderWindow & window);
	float getPreviousVelocity(int t);
	float getPreviousPosition(int t);

	float x;
	float v;
	float vsafe;
	float acc;
	sf::CircleShape shape;
	bool braking;
private:
	void _tick();
	std::vector<float> xs;
	std::vector<float> vs;
};
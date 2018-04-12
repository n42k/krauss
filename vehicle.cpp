#include "vehicle.h"

#include <algorithm>

#include "shared.h"

const float vmax = 1.f;
const float a = 3.5f;
const float b = 6.f;
const float tau = 0.01f * FPS;
const float eta = 0.01f;

Vehicle::Vehicle(float x)
	:x(x), shape(0.1f), v(0), braking(false), vsafe(0)
{
	shape.setFillColor(sf::Color::Green);
}

void Vehicle::setPosition(float x)
{
}

void Vehicle::tick()
{
	vsafe = vmax;
	_tick();
}

void Vehicle::tick(Vehicle & carInFront)
{
	float g = carInFront.x - x - 0.3;

	vsafe = carInFront.v + (g - tau * carInFront.v) / (v/b + tau);
	_tick();
}

void Vehicle::draw(sf::RenderWindow & window)
{
	shape.setPosition(x, 0);
	window.draw(shape);
}

float Vehicle::getPreviousVelocity(int t)
{
	if (vs.size() == 0)
		return v;

	int index = vs.size() - t;

	if (index < 0)
		return vs[0];

	return vs[index];
}

float Vehicle::getPreviousPosition(int t)
{
	if (xs.size() == 0)
		return x;

	int index = xs.size() - t;

	if (index < 0)
		return xs[0];

	return xs[index];
}

void Vehicle::_tick()
{
	float vdes;

	if (braking)
		vdes = v - b / FPS;
	else
		vdes = std::min(vmax, std::min(v + a / FPS, vsafe));

	float nextV = std::max(0.f, vdes - eta);

	acc = nextV - v;

	v = nextV;
	vs.push_back(v);

	x += v / FPS;
	xs.push_back(x);
}
#pragma once
#include <SFML/Graphics.hpp>
#include "PositionHistory.h"


struct Attributes {

	sf::Vector2f velocity;
	sf::Vector2f pos;
	float mass;
	PositionHistory posHist;
	sf::Color color;


	Attributes() {
		// Default Constructer
	}

	Attributes(sf::Vector2f v, sf::Vector2f p, float m, sf::Color c) {
		velocity = v;
		pos = p;
		mass = m;
		color = c;
	}
};


float length(sf::Vector2f a) {
	return sqrtf(a.x*a.x + a.y*a.y);
}

float length(sf::VertexArray a) {
	return length(a[0].position - a[1].position);
}


sf::Vector2f calcForce(float m1, float m2, sf::Vector2f p1, sf::Vector2f p2) {

	float d = length(p1 - p2) + 1e-10;

	// Vector form of Newton formula
	return -m1 * m2 * (p1 - p2) / (d*d*d);
}
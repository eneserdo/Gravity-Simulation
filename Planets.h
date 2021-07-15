#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include "PositionHistory.h"

using namespace std;


float length(sf::Vector2f a);

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
		posHist.init(p, c);
	}

};

class Planets : public sf::Drawable, public sf::Transformable
{
private:

	unsigned int width, height;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	vector<sf::CircleShape> vertices;
	vector<Attributes> attr;

public:
	Planets(unsigned int n, unsigned int w, unsigned int h);
	void init();

	Attributes operator[](unsigned int i);
	void update(vector<sf::Vector2f>& force, float delta, bool isBoundsOn = true);
	void addPlanet(Attributes newObj, int index);
	void deleteCurserPlanet();
	void setVelocity(sf::Vector2f v);

	int getSize();
};


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>

using namespace std;

class PositionHistory : public sf::Drawable, public sf::Transformable {

	deque<sf::Vector2f> ph;
	sf::Color color;
public:

	void init(sf::Vector2f initial, sf::Color c);

	void add(sf::Vector2f current);

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};


#include "PositionHistory.h"

void PositionHistory::init(sf::Vector2f initial, sf::Color c)
{
	ph = deque<sf::Vector2f>(80, initial);
	color = c;
}

void PositionHistory::add(sf::Vector2f current) {

	ph.push_front(current);
	ph.pop_back();
}

void PositionHistory::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL;

	states.blendMode = sf::BlendAdd;

	sf::VertexArray vertices(sf::LineStrip);

	for (size_t i = 0; i < ph.size(); i++)
	{
		vertices.append(ph[i]);
		vertices[i].color = color;
	}

	target.draw(vertices, states);
}


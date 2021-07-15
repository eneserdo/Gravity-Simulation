#include "Planets.h"
#include <iostream>


float mToR(float x) {
	return sqrtf(sqrtf(x*x*x));
}

float dot(sf::Vector2f a, sf::Vector2f b) {
	return a.x*b.x + a.y*b.y;
}

Attributes Planets::operator[](unsigned int i)
{
	attr[i].pos = vertices[i].getPosition();
	return attr[i];
}

Planets::Planets(unsigned int n, unsigned int w, unsigned int h) :
	attr(n),
	vertices(n),
	width(w),
	height(h)
{}

void Planets::init()
{
	float R;

	for (size_t i = 0; i < attr.size(); i++)
	{
		
		vertices[i].setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		
		attr[i].mass = (rand() % 140+10);
		R = mToR(attr[i].mass);

		vertices[i].setRadius(R);
		vertices[i].setOrigin(R, R);

		vertices[i].setPosition(sf::Vector2f((rand() % (width - (int)R)) + R, (rand() % (height - (int)R)) + R));

		attr[i].posHist.init(vertices[i].getPosition(),vertices[i].getFillColor());
		
		attr[i].velocity = sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50);

	}

	cout << "Particles are initialized" << endl;
}


// Adapted from SFML tutorial 
void Planets::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL;

	for (auto v : vertices)
	{
		target.draw(v, states);
	}
}

void Planets::update(vector<sf::Vector2f> &force, float delta, bool isBoundsOn) {

	float damping = 1.f;
	int slowdownCoef = 1;

	if (true) {

		delta /= slowdownCoef;

		for (size_t i = 0; i < slowdownCoef; i++)
		{

			for (size_t i = 0; i < attr.size(); i++)
			{
				sf::CircleShape& vi = vertices[i];

				// Update Velocity
				// F=m*a -> F=m*dv/dt -> dv=F*dt/m
				attr[i].velocity += delta * force[i] / attr[i].mass;

				// Update Position
				// v=dx/dt -> dx=v*dt -> x_new=x_old + v*dt
				vi.setPosition(vi.getPosition() + attr[i].velocity*delta);
			}

			for (size_t i = 0; i < attr.size(); i++)
			{
				sf::CircleShape& vi = vertices[i];
				const float& Ri = vi.getRadius();
				// // Elastic collision calculations
				// For boundaries
				if (isBoundsOn)
				{
					if (vi.getPosition().x < Ri) {
						vi.setPosition(vi.getPosition() - attr[i].velocity * (Ri - vi.getPosition().x) / length(attr[i].velocity));
						attr[i].velocity.x *= -damping;
					}

					if (vi.getPosition().x > width - Ri) {
						vi.setPosition(vi.getPosition() - attr[i].velocity * (vi.getPosition().x - (width - Ri)) / length(attr[i].velocity));
						attr[i].velocity.x *= -damping;
					}

					if (vi.getPosition().y < Ri) {
						vi.setPosition(vi.getPosition() - attr[i].velocity*(Ri - vi.getPosition().y) / length(attr[i].velocity));
						attr[i].velocity.y *= -damping;
					}

					if (vi.getPosition().y > height - Ri) {
						vi.setPosition(vi.getPosition() - attr[i].velocity * (vi.getPosition().y - (height - Ri)) / length(attr[i].velocity));
						attr[i].velocity.y *= -damping;
					}
				}

				// For other circles
				for (size_t j = i + 1; j < attr.size(); j++)
				{

					sf::CircleShape& vj = vertices[j];
					const float& Rj = vj.getRadius();

					const float dist = length(vj.getPosition() - vi.getPosition());

					if (dist < Rj + Ri) {

						//cout << "Collusion: " << i << " to " << j << endl;

						vi.setPosition(vi.getPosition() - 0.5f*attr[i].velocity * (Rj + Ri - dist) / length(attr[i].velocity));
						vj.setPosition(vj.getPosition() - 0.5f*attr[j].velocity * (Rj + Ri - dist) / length(attr[j].velocity));

						// Elastic

						sf::Vector2f v_dif = attr[i].velocity - attr[j].velocity;
						sf::Vector2f p_dif = vi.getPosition() - vj.getPosition();
						const float M = attr[i].mass + attr[j].mass;

						attr[i].velocity -= (2 * attr[j].mass / M) * dot(v_dif, p_dif)*p_dif / (length(p_dif)*length(p_dif));

						attr[j].velocity += (2 * attr[i].mass / M) * dot(v_dif, p_dif)*p_dif / (length(p_dif)*length(p_dif));



					}

				}

			}

		}

	}

	for (size_t i = 0; i < attr.size(); i++)
	{
		attr[i].posHist.add(vertices[i].getPosition());
	}

}

void Planets::addPlanet(Attributes newAttr, int index)
{
	sf::CircleShape newCircle;
	newCircle.setFillColor(newAttr.color);

	newAttr.posHist.init(newAttr.pos, newAttr.color);
	
	float R = mToR(newAttr.mass);

	newCircle.setPosition(newAttr.pos);

	newCircle.setRadius(R);
	newCircle.setOrigin(R, R);

	if (index == -1) {
		attr.push_back(newAttr);
		vertices.push_back(newCircle);
	}
	else {
		attr[index] = newAttr;
		vertices[index] = newCircle;
	}

}

void Planets::deleteCurserPlanet()
{

	//vertices[i].setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

	//attr[i].mass = (rand() % 20 + 10) / 2.f;
	//R = attr[i].mass * 3;

	//vertices[i].setRadius(R);
	//vertices[i].setOrigin(R, R);

	//vertices[i].setPosition(sf::Vector2f((rand() % (width - (int)R)) + R, (rand() % (height - (int)R)) + R));

	//attr[i].posHist.init(vertices[i].getPosition(), vertices[i].getFillColor());

	//attr[i].velocity = sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50);

}

void Planets::setVelocity(sf::Vector2f v)
{
	attr.back().velocity = v;
}

int Planets::getSize()
{
	return attr.size();
}

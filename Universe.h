// For templated classes, declarations and implementations can only be imlemented in header file.
// So, there is no "Universe.cpp" file.
// For further information, 
// see https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file 

const int FPS = 60;


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

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

template<typename Type>
class Universe
{
	Type planets;

	sf::Vector2f cm;
	sf::CircleShape cmCircle;

	sf::RenderWindow *window;
	sf::Event ev;
	vector<sf::Vector2f> forces;
	sf::VertexArray line;
	float G;
	sf::View view;
	sf::View resetView;
	float speed, speedMemory;

	bool isGravityOn, curserMass, isBoundsOn, CMIsOn=false;

	sf::Vector2f pressedLoc, currentLoc;
	sf::Vector2i mousePos;
	bool mousePressed = false;


public:

	Universe(float g, unsigned int np, int mode, unsigned int w = 1200, unsigned int h = 900) :
		planets(np, w, h),
		G(g),
		forces(np),
		speed(3.f),
		line(sf::Lines, 2),
		cmCircle(3.f)
	{
		
		cmCircle.setOrigin(3.f, 3.f);
		cmCircle.setPosition(cm);
		cmCircle.setFillColor(sf::Color(200, 10, 10, 100));

		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		this->window = new sf::RenderWindow(sf::VideoMode(w, h), "Animation", sf::Style::Close | sf::Style::Titlebar, settings);
		window->setFramerateLimit(FPS);
		view = window->getDefaultView();
		resetView = window->getDefaultView();

		switch (mode)
		{
		case 0:
			isBoundsOn = true;
			isGravityOn = false;
			planets.init();
			break;
		case 1:

			isGravityOn = true;
			isBoundsOn = false;

			planets.addPlanet(Attributes(sf::Vector2f(0,0), sf::Vector2f(100, 100), 1000.f, sf::Color::Red), 0);
			planets.addPlanet(Attributes(sf::Vector2f(0, 100), sf::Vector2f(1100, 100), 10.f, sf::Color::Blue), 1);

			break;
		case 2:

			isGravityOn = true;
			isBoundsOn = false;

			planets.addPlanet(Attributes(sf::Vector2f(0, 0), sf::Vector2f(100, 100), 1000.f, sf::Color::Red), 0); //Sun
			planets.addPlanet(Attributes(sf::Vector2f(0, 100), sf::Vector2f(1100, 100), 10.f, sf::Color::Blue), 1);	// Earth
			planets.addPlanet(Attributes(sf::Vector2f(0, 120), sf::Vector2f(1350, 100), 0.1f, sf::Color::Yellow), 2); // Moon

			break;

		default:
			cout << "ERROR: Mode Selection" << endl;
			break;
		}

	};

	void update(sf::Time elapsed) 
	{
		//Update Force
		fill(forces.begin(), forces.end(), sf::Vector2f(0, 0));
		
		if (isGravityOn) {

			sf::Vector2f temp;
			for (size_t i = 0; i < planets.getSize(); i++)
			{
				for (size_t j = i + 1; j < planets.getSize(); j++)
				{
					temp = G * calcForce(planets[i].mass, planets[j].mass, planets[i].pos, planets[j].pos);

					forces[i] += temp;
					forces[j] -= temp;
				}
			}
		}

		// Update velocity and position
		planets.update(forces, elapsed.asSeconds()*speed, isBoundsOn);


		// Find center of mass
		cm = sf::Vector2f(0, 0);
		float M=0;

		for (size_t i = 0; i < planets.getSize(); i++) {
			cm += planets[i].mass*planets[i].pos;
			M += planets[i].mass;
		}
	
		cmCircle.setPosition(cm/M);
	}


	void clear() {
		window->clear();
	}

	void draw() {

		for (size_t i = 0; i < planets.getSize(); i++)
			window->draw(planets[i].posHist);
		
		window->draw(planets);

		if (length(line)!=0) 
			window->draw(line);
		
		if (CMIsOn)
			window->draw(cmCircle);
			

		window->display();
	}

	bool isOpen() {
		return window->isOpen();
	}

	void eventPolling() 
	{
		float delta;
	
		while (window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window->close();

			if (ev.type == sf::Event::KeyPressed) {
				if (ev.key.code == sf::Keyboard::Escape)
					window->close();

				if (ev.key.code == sf::Keyboard::R)
					view = resetView;
				
				if (ev.key.code == sf::Keyboard::Q)
					speed = (speed - 0.5f) < 2.f ? 2.f : speed - 0.5f;

				if (ev.key.code == sf::Keyboard::W)
					speed = (speed + 0.5f) > 15.f ? 15.f : speed + 0.5f;

				if (ev.key.code == sf::Keyboard::G) {
					isGravityOn = !isGravityOn;
					cout << "Gravity: " << isGravityOn << endl;
				}
				if (ev.key.code == sf::Keyboard::M) {
					curserMass = !curserMass;
					cout << "Curser mass: " << curserMass << endl;
				}
				if (ev.key.code == sf::Keyboard::B) {
					isBoundsOn = !isBoundsOn;
					cout << "Bounds are on: " << isBoundsOn << endl;
				}
				if (ev.key.code == sf::Keyboard::A) {
					CMIsOn = !CMIsOn;
					cout << "Center of Mass Is On: " << CMIsOn << endl;
				}

			}


			if (ev.type == sf::Event::MouseWheelScrolled)
			{
				delta = ev.mouseWheelScroll.delta;
				mousePos = sf::Mouse::getPosition(*window);

				if (ev.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
					view.move(0, -delta * 50);
					std::cout << "wheel type: vertical" << std::endl;

				}
				if (ev.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
					view.move(-delta * 50, 0);
					std::cout << "wheel type: horizontal" << std::endl;

				}


				if (delta == -1) {
					cout << "Zoom out" << endl;

					auto before = window->mapPixelToCoords(mousePos);
					view.zoom(1.1f);
					window->setView(view);
					auto after = window->mapPixelToCoords(mousePos);
					view.move(before - after);
				}
				if (delta == 1)
				{
					cout << "Zoom in" << endl;
					auto before = window->mapPixelToCoords(mousePos);
					view.zoom(0.9f);
					window->setView(view);
					auto after = window->mapPixelToCoords(mousePos);
					view.move(before - after);
				}


			}
			if (ev.type == sf::Event::MouseButtonPressed) {

				pressedLoc = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
				line[0] = pressedLoc;

				//cout << "Mouse pressed: " << pressedLoc.x << ", " << pressedLoc.y << endl;
				mousePressed = true;

				speedMemory = speed;
				speed = 0;

				planets.addPlanet(Attributes(sf::Vector2f(0,0), pressedLoc,10.f,sf::Color::Cyan), -1);
				forces.push_back(sf::Vector2f(0.f, 0.f));

			}
			if (ev.type == sf::Event::MouseButtonReleased) {
				
				planets.setVelocity(line[1].position - line[0].position);


				line[1] = line[0];

				mousePressed = false;
				cout << "mouse released" << endl;
				speed = speedMemory;
				
			}
			
			if (mousePressed) {

				currentLoc = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
				line[1].position = 2.f*pressedLoc - currentLoc;
			}
			


		}

		// Update the view
		window->setView(view);

		if (mousePressed) {
			sf::CircleShape newCircle(20.f);
			newCircle.setPosition(pressedLoc);
			newCircle.setOrigin(20.f, 20.f);
			sf::VertexArray line(sf::Lines, 2);

			line[0] = pressedLoc;
			currentLoc = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			line[1] = 2.f*pressedLoc - currentLoc;

			window->draw(line);
			window->draw(newCircle);
		}

		//if (creationState == 2) {
		//	universe.addPlanet(newCircle);
		//	creationState = 0;
		//}
	};

	~Universe() {
		delete window;
	}

};

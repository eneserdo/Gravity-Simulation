#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Menu
{
	sf::RenderWindow *window;
	sf::Event ev;
	sf::Vector2i mousePos;
	sf::Font font;
	vector<sf::Text> screen0, screen1, screen2;

	vector<vector<sf::Text>> screens;

	int activeBlock;
	int selection;
	int state;

public:

	Menu();
	~Menu();

	bool isOpen();

	void eventPolling();
	
	void update(int& mode);
	void draw();
};


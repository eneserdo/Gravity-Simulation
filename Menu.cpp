#include "Menu.h"

Menu::Menu():
	screen0(3),
	screen1(4),
	screen2(3),
	state(0),
	selection(0),
	screens(3)
{
	window = new sf::RenderWindow(sf::VideoMode(900, 600), "Select the Simulation Mode", sf::Style::Close | sf::Style::Titlebar);

	if (!font.loadFromFile(R"(C:\Users\Enes\source\repos\ParticleSim_v2\font.ttf)"))
		cout << "Font can not be loaded" << endl;

	int hm=50, wm=50, ws=150;

	// Screen 0:

	for (size_t i = 0; i < screen0.size(); i++)
	{
		screen0[i].setFont(font);
		screen0[i].setCharacterSize(42);
		screen0[i].setPosition(hm, i*ws+wm);
		screen0[i].setFillColor(sf::Color(220, 220, 220));
		screen0[i].setOutlineThickness(2);
	}

	screen0[0].setString("2D Animations");
	screen0[1].setString("3D Animations (Coming Soon)");
	screen0[1].setFillColor(sf::Color(150,10,10));
	screen0[2].setString("Exit");

	// Screen 1:

	for (size_t i = 0; i < screen1.size(); i++)
	{
		screen1[i].setFont(font);
		screen1[i].setCharacterSize(42);
		screen1[i].setPosition(hm, i*ws + wm);
		screen1[i].setFillColor(sf::Color(220, 220, 220));
		screen1[i].setOutlineThickness(2);
	}

	screen1[0].setString("Elastic Collusion");
	screen1[1].setString("2 Moving Body ");
	screen1[2].setString("2 Body: Steady and Moving");
	screen1[3].setString("Back");

	// Screen 2:

	screens[0] = screen0;
	screens[1] = screen1;
	screens[2] = screen2;



}

bool Menu::isOpen()
{
	return window->isOpen();
}

void Menu::draw()
{
	//cout << "state: " << state<< endl;
	auto activeScreen = screens[state];

	window->clear(sf::Color::Black);

	for (auto &text : activeScreen)
		window->draw(text);
	
	window->display();

}

void Menu::eventPolling()
{
	selection = -1;

	//cout << "eventPolling" << endl;

	//cout << "state2: " << state << endl;
	auto &activeScreen = screens[state];

	while (window->pollEvent(ev))
	{
		
		if (ev.type == sf::Event::Closed)
			window->close();

		if (ev.type==sf::Event::MouseMoved)
		{
			mousePos = sf::Mouse::getPosition(*window);
			sf::FloatRect mouseRect(sf::Vector2f(mousePos.x - 2.f, mousePos.y - 2.f), sf::Vector2f(4.f, 4.f));

			for (size_t i = 0; i < activeScreen.size(); i++){

				auto &text = activeScreen[i];
				text.setOutlineColor(sf::Color::Black);
				
				if (text.getGlobalBounds().intersects(mouseRect))
					activeBlock = i;
				
			}

			activeScreen[activeBlock].setOutlineColor(sf::Color::Red);
		}

		if (ev.type == sf::Event::MouseButtonReleased) {
			selection = activeBlock;
			cout << "selection: " << selection << endl;
			cout << "state: " << state<< endl;
		}
		
	}
}

void Menu::update(int& mode)
{
	mode = -1;

	if (selection!=-1) {
		cout << "In selection: " << selection << endl;
		cout << "In state: " << state << endl;
		switch (state)
		{
		case 0:
			// Starting screen: 2D, 3D, exit.

			if (selection <= 1)
				state = selection+1;

			else if(selection==2)
				window->close();


			break;

		case 1:
			// 2D screen:

			if (selection <= 2) {
				mode = selection;
				window->close();
			}

			else if (selection == 3) {
				state = 0;
				cout << "state, selection: " <<state <<", "<<selection << endl;
			}

			else
				cout << "Error: Menu" << endl;

			break;

		case 2:
			// 3D screen: 

			break;

		default:
			break;
		}

	}

}


Menu::~Menu()
{
	delete window;
}



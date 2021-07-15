#include "Planets.h"
//#include "Planets3D.h"
#include "Universe.h"
#include "Menu.h"

// Constants
const unsigned int WINDOW_WIDTH = 1200;
const unsigned int WINDOW_HEIGHT = 900;
const float gravitational_const = 10000.f;
const unsigned int numParticlesInElasticMode = 15;

template <typename P>
void simulationLoop(Universe<P> &US) {

	sf::Clock clock;
	sf::Time elapsed;

	while (US.isOpen())
	{
		elapsed = clock.restart();

		US.clear();

		US.eventPolling();

		US.update(elapsed);

		US.draw();

	}
}


int main()
{
	int mode;
	Menu menu;

	while (menu.isOpen())
	{
		menu.eventPolling();

		menu.update(mode);
		menu.draw();
	}


	cout << "Mode: " << mode << endl;

	if (mode == -1)
		return 0;
	
	int np;

	if (mode == 0)
		np = numParticlesInElasticMode;

	else if (mode == 1)
		np = 2;

	else if (mode == 2)
		np = 3;

	if (mode<4)
	{
		Universe<Planets> universeSimulation(gravitational_const, np, mode, WINDOW_WIDTH, WINDOW_HEIGHT);
		simulationLoop(universeSimulation);
	}
	else if (mode > 4) {
		//Universe<Planets3D> universeSimulation(gravitational_const, np, mode, WINDOW_WIDTH, WINDOW_HEIGHT);
		//simulationLoop(universeSimulation);
	}

	return 0;
}



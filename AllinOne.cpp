//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//
//template<typename Type, int numParticles>
//class Universe
//{
//	Type universe;
//
//	vector<sf::Vector2f> forces;
//
//	sf::RenderWindow *window;
//	sf::Event ev;
//
//public:
//	Universe();
//	void update(sf::Time);
//	void draw();
//	bool isOpen();
//	void eventPolling();
//	void updateForce();
//
//};
//
//template<typename Type, int numParticles>
//Universe<Type, numParticles>::Universe() : universe(numParticles)
//{
//	this->window = new sf::RenderWindow(sf::VideoMode(1200, 900), "Universe");
//
//}
//
//template<typename Type, int numParticles>
//void Universe<Type, numParticles>::update(sf::Time elapsed)
//{
//	updateForce();
//	universe.updateV(forces, elapsed);
//	universe.updateL(elapsed);
//}
//
//template<typename Type, int numParticles>
//void Universe<Type, numParticles>::draw()
//{
//	window->clear();
//	window->draw(universe);
//	window->display();
//}
//
//template<typename Type, int numParticles>
//bool Universe<Type, numParticles>::isOpen()
//{
//	return window->isOpen();
//}
//
//template<typename Type, int numParticles>
//void Universe<Type, numParticles>::eventPolling()
//{
//	while (window->pollEvent(ev))
//	{
//		if (ev.type == sf::Event::Closed)
//			window->close();
//	}
//}
//
//template<typename Type, int numParticles>
//void Universe<Type, numParticles>::updateForce()
//{
//	fill(forces.begin(), forces.end(), sf::Vector2f(0, 0));
//}
//
//
//
//struct Attributes {
//	sf::Vector2f p_velocity;
//	double mass;
//};
//
//class Particle : public sf::Drawable, public sf::Transformable
//{
//private:
//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
//	sf::VertexArray vertices;
//	vector<Attributes> attr;
//
//public:
//
//	Particle(unsigned int n);
//	void updateV(vector<sf::Vector2f> force, sf::Time delta);
//
//	void updateL(sf::Time delta);
//
//};
//
//
//
//Particle::Particle(unsigned int n) : attr(n), vertices(sf::Points, n) {
//	// set colors for each
//	for (size_t i = 0; i < attr.size(); i++)
//	{
//		vertices[i].color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
//		vertices[i].position = sf::Vector2f(rand() % 500 + 100, rand() % 500 + 100);
//	}
//	cout << "color is set" << endl;
//}
//
//
//// Directly copyied from SFML API
//void Particle::draw(sf::RenderTarget & target, sf::RenderStates states) const
//{
//	// apply the transform
//	states.transform *= getTransform();
//
//	// our particles don't use a texture
//	states.texture = NULL;
//
//	// draw the vertex array
//	target.draw(vertices, states);
//}
//
//void Particle::updateV(vector<sf::Vector2f> force, sf::Time delta) {
//	//cout << "Update velocity" << endl;
//	for (size_t i = 0; i < attr.size(); i++)
//	{
//		attr[i].p_velocity = sf::Vector2f((rand() % 100) - 50.f, (rand() % 100) - 50.f);
//		//vertices[i].position += sf::Vector2f(0.1, 0.1);
//
//	}
//}
//
//void Particle::updateL(sf::Time delta) {
//
//	for (size_t i = 0; i < attr.size(); i++)
//	{
//		vertices[i].position += attr[i].p_velocity*4.f*delta.asSeconds();
//		//vertices[i].position += sf::Vector2f(0.1, 0.1);
//
//	}
//}
//
//
//int main()
//{
//	//sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Universe");
//
//	sf::Clock clock;
//	sf::Time elapsed;
//
//	Universe<Particle, 100> universeSimulation;
//
//	while (universeSimulation.isOpen())
//	{
//		////window->clear();
//
//		//while (window->pollEvent(ev))
//		//{
//		//	if (ev.type == sf::Event::Closed)
//		//		window->close();
//		//}
//
//		elapsed = clock.restart();
//
//		universeSimulation.update(elapsed);
//
//		////universe.updateV(calcForce(), elapsed);
//		////universe.updateL(elapsed);
//
//		////window->draw(universe);
//		////window->display();
//		universeSimulation.draw();
//	}
//
//	return 0;
//}

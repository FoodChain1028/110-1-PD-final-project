/*

# include <iostream>
# include "SFML/Graphics.hpp"
# include "SFML/Window.hpp"
# include "SFML/System.hpp"

using namespace sf;


int main() {

	RenderWindow window(VideoMode(640, 400), "triangle", Style::Default); // window
	//window.setFramerateLimit(60);

	// setting features/elements in my window
	CircleShape triangle;
	triangle.setRadius(50.f);
	triangle.setPointCount(3); // the key to making a triangle! To set the circle to 3 points
	triangle.setFillColor(Color::Green);
	triangle.setOutlineThickness(5.f);
	triangle.setOutlineColor(Color::Red);

	Vertex line[] = { Vertex(Vector2f(100.f, 400.f)), Vertex(Vector2f(50.f, 300.f)) };

	ConvexShape convex;
	convex.setPosition(Vector2f(100.f, 50.f));
	convex.setPointCount(4);

	convex.setPoint(0, Vector2f(20.f, 30.f));
	convex.setPoint(1, Vector2f(40.f, 20.f));
	convex.setPoint(2, Vector2f(10.f, 50.f));
	convex.setPoint(3, Vector2f(80.f, 10.f));


	// Execute!
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		// Update
		triangle.move(0.05f, 0.03f);
		triangle.rotate(0.2f);
	
		// Draw
		window.clear(Color::Black);

		// Draw everything
		window.draw(triangle);
		window.draw(line, 2, Lines);
		window.draw(convex);

		// Display it!
		window.display();

	}

	return 0;
}

*/
/*

# include <iostream>
# include "SFML/Graphics.hpp"
# include "SFML/Window.hpp"
# include "SFML/System.hpp"

using namespace sf;


int main() {

	RenderWindow window(VideoMode(640, 400), "Example 1", Style::Default);
	//window.setFramerateLimit(60);

	CircleShape circle(50.f);
	circle.setPosition(Vector2f(0.f, 0.f));
	circle.setFillColor(Color(255, 200, 100, 200));

	RectangleShape rect(Vector2f(50.f, 100.f));
	rect.setPosition(Vector2f(400.f, 200.f));
	rect.setFillColor(Color(255, 50, 200, 150));


	CircleShape triangle;
	triangle.setRadius(50.f);
	triangle.setPointCount(3);
	triangle.setFillColor(Color::Green);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		// Update
		circle.move(0.01f, 0.01f);
		circle.rotate(0.1f);
		rect.move(-0.01f, -0.01f);
		rect.rotate(0.5f);

		// Draw
		window.clear(Color::White);

		// Draw everything
		window.draw(circle);
		window.draw(rect);
		window.draw(triangle);

		window.display();

	}

	return 0;
}

*/
/*
# include <iostream>
# include "SFML/Graphics.hpp"
# include "SFML/Window.hpp"
# include "SFML/System.hpp"

using namespace sf;


int main() {

	RenderWindow window(VideoMode(640, 400), "keyboard and mouse", Style::Default); // window
	//window.setFramerateLimit(60);

	// setting features/elements in my window
	


	// Execute!
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) // terminate with keyboard
				window.close();
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Right) // terminate with mouse
				window.close();
		}

		//if (Mouse::isButtonPressed(Mouse::Right))
		//	window.close();

		// Update
		

		// Draw
		window.clear(Color::Black);

		// Draw everything
		

		// Display it!
		window.display();

	}

	return 0;
}

*/
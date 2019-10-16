//
// Created by notoraptor on 19-09-09.
//

#ifndef GUIRAPTOR_WINDOW_HPP
#define GUIRAPTOR_WINDOW_HPP

#include <SFML/Graphics.hpp>

struct Window {
	void* handle;

	explicit Window(unsigned int width, unsigned int height, const char* title): handle(nullptr) {
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		auto window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, settings);
		window->setVerticalSyncEnabled(true);
		handle = window;
	}
	~Window() {
		delete (sf::RenderWindow*)handle;
	}
	sf::RenderWindow* get() {
		return (sf::RenderWindow*)handle;
	}
	const sf::RenderWindow* get() const {
		return (sf::RenderWindow*)handle;
	}
};

#endif //GUIRAPTOR_WINDOW_HPP

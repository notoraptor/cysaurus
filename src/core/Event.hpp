//
// Created by notoraptor on 19-09-09.
//

#ifndef GUIRAPTOR_EVENT_HPP
#define GUIRAPTOR_EVENT_HPP

#include <SFML/Window.hpp>

struct Event {
	void* handle;

	Event(): handle(nullptr) {
		handle = new sf::Event();
	}
	~Event() {
		delete (sf::Event*)handle;
	}
	sf::Event* get() {
		return (sf::Event*)handle;
	}
	const sf::Event* get() const {
		return (sf::Event*)handle;
	}
};

#endif //GUIRAPTOR_EVENT_HPP

//
// Created by notoraptor on 19-09-09.
//

#include "core/core.hpp"
#include "gui.hpp"
#include <iostream>

Window* WindowNew(unsigned int width, unsigned int height, const char* title) {
	return new Window(width, height, title);
}

void WindowDelete(Window* window) {
	delete window;
}

bool WindowIsOpen(const Window* window) {
	return window->get()->isOpen();
}

bool WindowNextEvent(Window* window, Event* event) {
	bool retval = window->get()->pollEvent(*event->get());
	// Automatic event processing.
	switch (event->get()->type) {
		case sf::Event::Resized:
			window->get()->setView(sf::View(sf::FloatRect(
					0, 0, event->get()->size.width, event->get()->size.height)));
			break;
		default:
			break;
	}
	return retval;
}

void WindowClose(Window* window) {
	window->get()->close();
}

void WindowDraw(Window* window, Pattern** patterns, unsigned int length) {
	if (!length)
		return;
	sf::RenderWindow* renderWindow = window->get();
	renderWindow->clear(sf::Color::White);
	for (unsigned int i = 0; i < length; ++i) {
		if (patterns[i]) {
			drawPattern(patterns[i], renderWindow);
		}
	}
	renderWindow->display();
}

Event* EventNew() {
	return new Event();
}

void EventDelete(Event* event) {
	delete event;
}

bool EventClosed(const Event* event) {
	return event->get()->type == sf::Event::Closed;
}

PatternTextInfo* PatternTextInfoNew(PatternText* patternText) {
	return new PatternTextInfo(*patternText);
}

void PatternTextInfoDelete(PatternTextInfo* patternTextInfo) {
	delete patternTextInfo;
}

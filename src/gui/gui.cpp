//
// Created by notoraptor on 19-09-09.
//

#include "core/core.hpp"
#include "gui.hpp"
#include <iostream>

void* WindowNew(unsigned int width, unsigned int height, const char* title) {
	auto* window = new Window;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window->renderWindow.create(sf::VideoMode(width, height), title, sf::Style::Default, settings);
	window->renderWindow.setVerticalSyncEnabled(true);
	return window;
}

void WindowDelete(void* window) {
	delete (Window*)window;
}

bool WindowIsOpen(const void* window) {
	return ((Window*)window)->renderWindow.isOpen();
}

bool WindowNextEvent(void* opaque, Event* event) {
	auto* window = (Window*)opaque;
	bool retval = window->renderWindow.pollEvent(*event->get());
	// Automatic event processing.
	switch (event->get()->type) {
		case sf::Event::Resized:
			window->renderWindow.setView(sf::View(sf::FloatRect(
					0, 0, event->get()->size.width, event->get()->size.height)));
			break;
		default:
			break;
	}
	return retval;
}

void WindowClose(void* window) {
	((Window*)window)->renderWindow.close();
}

void WindowDraw(void* opaque, Pattern** patterns, unsigned int length) {
	auto* window = (Window*)opaque;
	if (!length)
		return;
	window->renderWindow.clear(sf::Color::White);
	for (unsigned int i = 0; i < length; ++i) {
		if (patterns[i]) {
			drawPattern(patterns[i], &window->renderWindow);
		}
	}
	window->renderWindow.display();
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

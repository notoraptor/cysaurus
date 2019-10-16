//
// Created by notoraptor on 19-09-09.
//

#ifndef GUIRAPTOR_GUIRAPTOR_HPP
#define GUIRAPTOR_GUIRAPTOR_HPP

#include <core/Window.hpp>
#include <core/Event.hpp>
#include <core/patterns/Pattern.hpp>
#include <core/patterns/PatternTextInfo.hpp>
#include <core/patterns/simplePatterns.hpp>

extern "C" {
	Window* WindowNew(unsigned int width, unsigned int height, const char* title);
	void WindowDelete(Window*);
	bool WindowIsOpen(const Window*);
	bool WindowNextEvent(Window*, Event*);
	void WindowClose(Window*);
	void WindowDraw(Window* window, Pattern** patterns, unsigned int length);

	Event* EventNew();
	void EventDelete(Event*);
	bool EventClosed(const Event*);

	PatternTextInfo* PatternTextInfoNew(PatternText*);
	void PatternTextInfoDelete(PatternTextInfo*);
};

#endif //GUIRAPTOR_GUIRAPTOR_HPP

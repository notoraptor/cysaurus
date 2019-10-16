//
// Created by notoraptor on 19-09-09.
//

#ifndef GUIRAPTOR_GUI_HPP
#define GUIRAPTOR_GUI_HPP

#include "core/Window.hpp"
#include "core/Event.hpp"
#include "core/patterns/Pattern.hpp"
#include "core/patterns/PatternTextInfo.hpp"
#include "core/patterns/simplePatterns.hpp"

extern "C" {
	// Window
	Window* WindowNew(unsigned int width, unsigned int height, const char* title);
	void WindowDelete(Window*);
	bool WindowIsOpen(const Window*);
	bool WindowNextEvent(Window*, Event*);
	void WindowClose(Window*);
	void WindowDraw(Window* window, Pattern** patterns, unsigned int length);
	// Event
	Event* EventNew();
	void EventDelete(Event*);
	bool EventClosed(const Event*);
	// PatternTextInfo
	PatternTextInfo* PatternTextInfoNew(PatternText*);
	void PatternTextInfoDelete(PatternTextInfo*);
};

#endif //GUIRAPTOR_GUI_HPP

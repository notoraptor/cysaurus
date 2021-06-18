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
	void* WindowNew(unsigned int width, unsigned int height, const char* title);
	void WindowDelete(void*);
	bool WindowIsOpen(const void*);
	bool WindowNextEvent(void*, Event*);
	void WindowClose(void*);
	void WindowDraw(void* window, Pattern** patterns, unsigned int length);
	// Event
	Event* EventNew();
	void EventDelete(Event*);
	bool EventClosed(const Event*);
	// PatternTextInfo
	PatternTextInfo* PatternTextInfoNew(PatternText*);
	void PatternTextInfoDelete(PatternTextInfo*);
};

#endif //GUIRAPTOR_GUI_HPP

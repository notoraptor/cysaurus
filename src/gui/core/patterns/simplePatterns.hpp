//
// Created by notoraptor on 19-09-09.
//

#ifndef GUIRAPTOR_SIMPLEPATTERNS_HPP
#define GUIRAPTOR_SIMPLEPATTERNS_HPP

#include <gui/core/patterns/DrawingType.hpp>
#include <gui/core/patterns/Pattern.hpp>

struct PatternText {
	float x;
	float y;
	const char* font;
	const char* content;
	unsigned int size;
	float outline;
	const char* color;
	const char* outlineColor;
	bool bold;
	bool italic;
	bool underline;
	bool strike;
};

struct PatternFrame {
	float x;
	float y;
	unsigned int width;
	unsigned int height;
	unsigned int count;
	Pattern** patterns;
};

struct PatternImage {
	float x;
	float y;
	float width;
	float height;
	const char* src;
};

struct PatternRectangle {
	float x;
	float y;
	float width;
	float height;
	float outline;
	const char* color;
	const char* outlineColor;
};

#endif //GUIRAPTOR_SIMPLEPATTERNS_HPP

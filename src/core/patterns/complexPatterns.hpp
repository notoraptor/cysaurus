//
// Created by notoraptor on 15/09/2019.
//

#ifndef GUIRAPTOR_COMPLEXPATTERNS_HPP
#define GUIRAPTOR_COMPLEXPATTERNS_HPP

#include <core/patterns/DrawingType.hpp>
#include <core/patterns/Pattern.hpp>

struct PatternCircle {
	float x;
	float y;
	float radius;
	float outline;
	const char* color;
	const char* outlineColor;
};

struct PatternRegularPolygon {
	float x;
	float y;
	unsigned int n;
	float radius;
	float outline;
	const char* color;
	const char* outlineColor;
};

struct PatternPolygon {
	unsigned int n;
	float* coordinates; // size should be 2*n
	float outline;
	const char* color;
	const char* outlineColor;
};

struct PatternEllipse {
	float x;
	float y;
	float width;
	float height;
	float outline;
	const char* color;
	const char* outlineColor;
};

#endif //GUIRAPTOR_COMPLEXPATTERNS_HPP

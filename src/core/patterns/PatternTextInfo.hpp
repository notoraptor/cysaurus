//
// Created by notoraptor on 19-09-16.
//

#ifndef GUIRAPTOR_PATTERNTEXTINFO_HPP
#define GUIRAPTOR_PATTERNTEXTINFO_HPP

#include <iostream>
#include <core/patterns/simplePatterns.hpp>

struct PatternTextInfo {
	size_t length;
	float width;
	float height;
	float left;
	float top;
	float* coordinates;

	explicit PatternTextInfo(const PatternText& patternText);
	~PatternTextInfo() {
		delete coordinates;
		std::cout << "destroyed a pattern text info" << std::endl;
	}
};

#endif //GUIRAPTOR_PATTERNTEXTINFO_HPP

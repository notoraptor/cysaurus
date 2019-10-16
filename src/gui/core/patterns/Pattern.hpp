//
// Created by notoraptor on 15/09/2019.
//

#ifndef GUIRAPTOR_PATTERN_HPP
#define GUIRAPTOR_PATTERN_HPP

#include <SFML/Graphics/RenderTarget.hpp>

struct Pattern {
	int type;
	void* pattern;
};

void drawPattern(Pattern* pattern, sf::RenderTarget* renderTarget);

#endif //GUIRAPTOR_PATTERN_HPP

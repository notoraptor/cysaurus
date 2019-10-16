//
// Created by notoraptor on 19-09-13.
//

#include <gui/core/core.hpp>
#include "simplePatterns.hpp"
#include "complexPatterns.hpp"
#include <gui/core/patterns/PatternTextInfo.hpp>
#include <gui/internal/ellipseShape.hpp>
#include <gui/core/unicode.hpp>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <iostream>

typedef void(*DrawingFunction)(const Pattern*, sf::RenderTarget*);

sf::Text patternTextToSFML(const PatternText& pattern) {
	sf::Text text;
	auto font = FontGetFromPath(pattern.font);
	if (font) {
		std::basic_string<sf::Uint32> basicString;
		unicode_convert(pattern.content, basicString);
		text.setFont(*font);
		text.setString(sf::String(basicString));
		text.setCharacterSize(pattern.size);
		text.setOutlineThickness(pattern.outline);
		text.setFillColor(ColorFromString(pattern.color));
		text.setOutlineColor(ColorFromString(pattern.outlineColor));
		text.setPosition(pattern.x, pattern.y);
		unsigned int flags = 0;
		if (pattern.bold)
			flags |= sf::Text::Bold;
		if (pattern.italic)
			flags |= sf::Text::Italic;
		if (pattern.underline)
			flags |= sf::Text::Underlined;
		if (pattern.strike)
			flags |= sf::Text::StrikeThrough;
		text.setStyle(flags);
	}
	return text;
}

PatternTextInfo::PatternTextInfo(const PatternText& patternText) {
	auto text = patternTextToSFML(patternText);
	const sf::String& realString = text.getString();
	auto bounds = text.getLocalBounds();

	auto fontPointer = text.getFont();
	auto firstGlyph = fontPointer->getGlyph(
			realString[0],
			text.getCharacterSize(),
			text.getStyle() & sf::Text::Bold,
			text.getOutlineThickness());
	float x = firstGlyph.bounds.left;
	float y = 0;
	float minTopOffset = firstGlyph.bounds.top;
	unsigned int size = realString.getSize();
	for (unsigned int i = 1; i < size; ++i) {
		minTopOffset = std::min(
				minTopOffset,
				fontPointer->getGlyph(
								realString[i],
								text.getCharacterSize(),
								text.getStyle() & sf::Text::Bold,
								text.getOutlineThickness())
						.bounds.top);
	}
	y = (float)text.getCharacterSize() + minTopOffset;

	this->length = size;
	this->width = bounds.width;
	this->height = bounds.height;
	this->left = x;
	this->top = y;
	if (size) {
		this->coordinates = new float[2 * length];
		for (size_t i = 0; i < size; ++i) {
			sf::Vector2f position = text.findCharacterPos(i);
			this->coordinates[2 * i] = position.x;
			this->coordinates[2 * i + 1] = position.y;
		}
	}
	std::cout << "Created a pattern text info" << std::endl;
}

void drawPattern(PatternImage* pattern, sf::RenderTarget* renderTarget) {
	if (pattern->width == 0 || pattern->height == 0)
		return;
	sf::Texture* texture = TextureGetFromFile(pattern->src);
	if (texture) {
		sf::Sprite sprite(*texture);
		sprite.setPosition(pattern->x, pattern->y);
		if (pattern->width > 0 || pattern->height > 0) {
			// unsigned int w = width < 0 ? texture->getSize().x : width;
			// unsigned int h = height < 0 ? texture->getSize().y : height;
			auto w = pattern->width;
			auto h = pattern->height;
			if (w > 0 && h < 0) {
				h = w * texture->getSize().y / texture->getSize().x;
			} else if (w < 0 && h > 0) {
				w = h * texture->getSize().x / texture->getSize().y;
			}
			sprite.setScale(w / texture->getSize().x, h / texture->getSize().y);
		}
		renderTarget->draw(sprite);
	}
}

void drawPattern(PatternText* pattern, sf::RenderTarget* renderTarget) {
	if (pattern->content)
		renderTarget->draw(patternTextToSFML(*pattern));
}

void drawPattern(PatternRectangle* pattern, sf::RenderTarget* renderTarget) {
	sf::RectangleShape rectangle;
	rectangle.setPosition(pattern->x, pattern->y);
	rectangle.setSize(sf::Vector2f(pattern->width, pattern->height));
	rectangle.setOutlineThickness(pattern->outline);
	rectangle.setFillColor(ColorFromString(pattern->color));
	rectangle.setOutlineColor(ColorFromString(pattern->outlineColor));
	renderTarget->draw(rectangle);
}

void drawPattern(PatternCircle* pattern, sf::RenderTarget* renderTarget) {
	if (pattern->radius <= 0)
		return;
	sf::CircleShape circle;
	circle.setPosition(pattern->x, pattern->y);
	circle.setRadius(pattern->radius);
	circle.setPointCount(2 * pattern->radius * 315 / 100);
	circle.setOutlineThickness(pattern->outline);
	circle.setFillColor(ColorFromString(pattern->color));
	circle.setOutlineColor(ColorFromString(pattern->outlineColor));
	renderTarget->draw(circle);
}

void drawPattern(PatternRegularPolygon* pattern, sf::RenderTarget* renderTarget) {
	if (!pattern->n)
		return;
	sf::CircleShape regularPolygon;
	regularPolygon.setPosition(pattern->x, pattern->y);
	regularPolygon.setRadius(pattern->radius);
	regularPolygon.setPointCount(pattern->n);
	regularPolygon.setOutlineThickness(pattern->outline);
	regularPolygon.setFillColor(ColorFromString(pattern->color));
	regularPolygon.setOutlineColor(ColorFromString(pattern->outlineColor));
	renderTarget->draw(regularPolygon);
}

void drawPattern(PatternPolygon* pattern, sf::RenderTarget* renderTarget) {
	if (!pattern->n)
		return;
	sf::ConvexShape convexShape(pattern->n);
	for (unsigned int i = 0; i < pattern->n; ++i) {
		convexShape.setPoint(i, sf::Vector2f(pattern->coordinates[2 * i], pattern->coordinates[2 * i + 1]));
	}
	convexShape.setOutlineThickness(pattern->outline);
	convexShape.setFillColor(ColorFromString(pattern->color));
	convexShape.setOutlineColor(ColorFromString(pattern->outlineColor));
	renderTarget->draw(convexShape);
}

void drawPattern(PatternEllipse* pattern, sf::RenderTarget* renderTarget) {
	EllipseShape ellipseShape;
	ellipseShape.setPosition(pattern->x, pattern->y);
	ellipseShape.setRadius(sf::Vector2f(pattern->width / 2, pattern->height / 2));
	ellipseShape.setOutlineThickness(pattern->outline);
	ellipseShape.setFillColor(ColorFromString(pattern->color));
	ellipseShape.setOutlineColor(ColorFromString(pattern->outlineColor));
	renderTarget->draw(ellipseShape);
}

void drawPattern(PatternFrame* pattern, sf::RenderTarget* renderTarget) {
	if (!pattern->width || !pattern->height || !pattern->count)
		return;
	sf::RenderTexture renderTexture;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	if (!renderTexture.create(pattern->width, pattern->height, settings))
		return;
	renderTexture.clear(sf::Color::White);
	for (unsigned int i = 0; i < pattern->count; ++i) {
		if (pattern->patterns[i])
			drawPattern(pattern->patterns[i], &renderTexture);
	}
	renderTexture.display();
	sf::Sprite sprite(renderTexture.getTexture());
	sprite.setPosition(pattern->x, pattern->y);
	renderTarget->draw(sprite);
}

#define GENERATE_DRAWING_FUNCTION(functionName, patternType) \
void functionName (const Pattern* pattern, sf::RenderTarget* renderTarget) \
{ drawPattern((patternType*)pattern->pattern, renderTarget); }

GENERATE_DRAWING_FUNCTION(drawPatternImage, PatternImage);
GENERATE_DRAWING_FUNCTION(drawPatternText, PatternText);
GENERATE_DRAWING_FUNCTION(drawPatternRectangle, PatternRectangle);
GENERATE_DRAWING_FUNCTION(drawPatternCircle, PatternCircle);
GENERATE_DRAWING_FUNCTION(drawPatternRegularPolygon, PatternRegularPolygon);
GENERATE_DRAWING_FUNCTION(drawPatternPolygon, PatternPolygon);
GENERATE_DRAWING_FUNCTION(drawPatternEllipse, PatternEllipse);
GENERATE_DRAWING_FUNCTION(drawPatternFrame, PatternFrame);

DrawingFunction drawingFunctions[] = {
		drawPatternImage,
		drawPatternText,
		drawPatternRectangle,
		drawPatternCircle,
		drawPatternRegularPolygon,
		drawPatternPolygon,
		drawPatternEllipse,
		drawPatternFrame,
};

void drawPattern(Pattern* pattern, sf::RenderTarget* renderTarget) {
	if (pattern->type < 0 || pattern->type >= NB_DRAWING_TYPE)
		return;
	drawingFunctions[pattern->type](pattern, renderTarget);
}

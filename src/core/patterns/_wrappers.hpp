//
// Created by notoraptor on 19-09-16.
//

#ifndef GUIRAPTOR__WRAPPERS_HPP
#define GUIRAPTOR__WRAPPERS_HPP

#include <core/patterns/Pattern.hpp>
#include <core/patterns/DrawingType.hpp>
#include <core/patterns/simplePatterns.hpp>
#include <core/patterns/complexPatterns.hpp>

#define PATTERN_WRAPPER(patternType, className) inline Pattern wrapPattern(const className& o) {return {patternType, (void*)&o};}

PATTERN_WRAPPER(DRAWING_TYPE_TEXT, PatternText);
PATTERN_WRAPPER(DRAWING_TYPE_SURFACE, PatternFrame);
PATTERN_WRAPPER(DRAWING_TYPE_IMAGE, PatternImage);
PATTERN_WRAPPER(DRAWING_TYPE_RECTANGLE, PatternRectangle);
PATTERN_WRAPPER(DRAWING_TYPE_CIRCLE, PatternCircle);
PATTERN_WRAPPER(DRAWING_TYPE_REGULAR_POLYGON, PatternRegularPolygon);
PATTERN_WRAPPER(DRAWING_TYPE_POLYGON, PatternPolygon);
PATTERN_WRAPPER(DRAWING_TYPE_ELLIPSE, PatternEllipse);

#endif //GUIRAPTOR__WRAPPERS_HPP

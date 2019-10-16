//
// Created by notoraptor on 08/09/2019.
//

#include <iostream>
#include <gui/core/core.hpp>
#include <gui/gui.hpp>
#include <gui/core/patterns/simplePatterns.hpp>
#include <gui/core/patterns/complexPatterns.hpp>
#include "_wrappers.hpp"

int main() {
	PatternImage di1{0, 0, -1, -1, "tigre.jpg"};
	PatternImage di2{10, 10, -1, -1, "tigre.jpg"};
	PatternImage di3{20, 100, -1, -1, "tigre.jpg"};
	PatternImage di4{100, 100, 500, 500, "Tigerramki.jpg"};
	PatternImage di5{200, 200, 500, -1, "Tigerramki.jpg"};
	PatternImage di6{300, 300, -1, -1, "Tigerramki.jpg"};
	PatternText text{
		.x = 0,
		.y = 0,
		.font = "serif",
		.content = u8"coordinates (漢字) = (2,5),",
		.size = 50,
		.outline = 0,
		.color = "#ffff00",
		.outlineColor = nullptr,
		.bold = false,
		.italic = true,
		.underline = true,
		.strike = true,
	};

	PatternTextInfo info(text);

	PatternRectangle background{info.left, info.top, info.width, info.height, 0, "green", nullptr};
	PatternRectangle rectangle{10, 20, 200, 150, 12, "red", "blue"};
	PatternCircle circle{10, 20, 100, 12, "red", "blue"};
	PatternEllipse ellipse{400, 20, 100, 200, 12, "red", "blue"};
	PatternRegularPolygon triangle{100, 100, 3, 100, 12, "white", "yellow"};
	float coordinates[] = {
			100, 100,
			200, 88,
			160, 200,
			80, 220
	};
	PatternPolygon polygon{4, coordinates, 12, "green", "black"};
	std::vector<Pattern> patterns = {
			wrapPattern(di1),
			wrapPattern(di2),
			wrapPattern(di3),
			wrapPattern(di4),
			wrapPattern(di5),
			wrapPattern(di6),
			wrapPattern(rectangle),
			wrapPattern(circle),
			wrapPattern(triangle),
			wrapPattern(polygon),
			wrapPattern(ellipse),
			wrapPattern(background),
	};

	std::vector<PatternRectangle> rectangles(info.length);
	auto gray = rgb(128, 128, 128);
	std::cout << gray << std::endl;
	const char* color[] = {"black", gray.c_str()};
	std::cout << info.left << ", " << info.top << std::endl;
	std::cout << info.length << " " << info.width << " " << info.height << std::endl;
	for (size_t i = 0; i < info.length; ++i) {
		float x = info.coordinates[2 * i];
		float y = info.coordinates[2 * i + 1];
		PatternRectangle& r = rectangles[i];
		r.x = x + info.left;
		r.y = y + info.top;
		r.width = info.width - x;
		r.height = info.height;
		r.outline = 0;
		r.color = color[i % 2];
		r.outlineColor = nullptr;
		patterns.push_back(wrapPattern(r));
	}
	patterns.push_back(wrapPattern(text));

	std::vector<Pattern*> list;
	for (Pattern& pattern: patterns)
		list.push_back(&pattern);

	Pattern** pointer = list.data();
	PatternFrame patternFrame{100, 100, 700, 300, (unsigned int)list.size(), pointer};
	Pattern frame = wrapPattern(patternFrame);
	Pattern* pFrame = &frame;

	auto window = WindowNew(900, 500, "This is a render window!");
	while (WindowIsOpen(window)) {
		auto event = EventNew();
		while (WindowNextEvent(window, event)) {
			if (EventClosed(event)) {
				WindowClose(window);
			}
		}
		if (WindowIsOpen(window)) {
			// WindowDraw(window, list.data(), list.size());
			WindowDraw(window, &pFrame, 1);
		}
		EventDelete(event);
	}
	WindowDelete(window);
	return 0;
}

int main1() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	window.setVerticalSyncEnabled(true);
	auto fontMonospace = FontGetFromPath("monospace");
	auto fontSerif = FontGetFromPath("serif");
	auto fontSansSerif = FontGetFromPath("sans-serif");
	if (!fontMonospace || !fontSansSerif || !fontSerif)
		std::cout << "not loaded" << std::endl;
	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen()) {
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event{};
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					// évènement "fermeture demandée" : on ferme la fenêtre
					window.close();
					break;
				case sf::Event::Resized:
					window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
					break;
				default:
					break;
			}
		}

		/* Cycle clear/draw/display. */

		// Clear window.
		window.clear(sf::Color::White);
		// Draw window. What can we draw: sprite, text, shape, array of vertices.
		sf::Text textMonospace;
		textMonospace.setFont(*fontMonospace);
		textMonospace.setFillColor(sf::Color::Black);
		textMonospace.setFillColor(sf::Color::Black);
		textMonospace.setString("hello world");
		textMonospace.setPosition(0, 0);
		textMonospace.setOutlineColor(sf::Color::Cyan);
		textMonospace.setOutlineThickness(5);
		window.draw(textMonospace);

		sf::Text textMonospace2;
		textMonospace2.setFont(*fontMonospace);
		textMonospace2.setFillColor(sf::Color::Black);
		textMonospace2.setFillColor(sf::Color::Black);
		textMonospace2.setString("Hello world");
		textMonospace2.setPosition(300, 0);
		textMonospace2.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined | sf::Text::StrikeThrough);
		window.draw(textMonospace2);

		sf::Text textSansSerif;
		textSansSerif.setFont(*fontSansSerif);
		textSansSerif.setFillColor(sf::Color::Black);
		textSansSerif.setFillColor(sf::Color::Black);
		textSansSerif.setString("Hello world");
		textSansSerif.setPosition(0, 30);
		window.draw(textSansSerif);

		sf::Text textSansSerif2;
		textSansSerif2.setFont(*fontSansSerif);
		textSansSerif2.setFillColor(sf::Color::Black);
		textSansSerif2.setFillColor(sf::Color::Black);
		textSansSerif2.setString("Hello world");
		textSansSerif2.setPosition(300, 30);
		textSansSerif2.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined | sf::Text::StrikeThrough);
		window.draw(textSansSerif2);

		sf::Text textSerif;
		textSerif.setFont(*fontSerif);
		textSerif.setFillColor(sf::Color::Black);
		textSerif.setFillColor(sf::Color::Black);
		textSerif.setString("Hello world");
		textSerif.setPosition(0, 60);
		window.draw(textSerif);

		sf::Text textSerif2;
		textSerif2.setFont(*fontSerif);
		textSerif2.setFillColor(sf::Color::Black);
		textSerif2.setFillColor(sf::Color::Black);
		textSerif2.setString("Hello world");
		textSerif2.setPosition(300, 60);
		textSerif2.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined | sf::Text::StrikeThrough);
		window.draw(textSerif2);

		// Display window.
		window.display();
	}

	return 0;
}
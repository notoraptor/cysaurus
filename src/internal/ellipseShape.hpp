//
// Created by notoraptor on 19-09-13.
//

#ifndef GUIRAPTOR_ELLIPSESHAPE_HPP
#define GUIRAPTOR_ELLIPSESHAPE_HPP

#include <SFML/Graphics/Shape.hpp>
#include <cmath>

/** Adapted from SFML documentation: (2019/09/13) https://www.sfml-dev.org/tutorials/2.5/graphics-shape-fr.php **/

class EllipseShape : public sf::Shape {
	sf::Vector2f m_radius;

public :

	explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0.f, 0.f)) :
			m_radius(radius) {
		update();
	}

	void setRadius(const sf::Vector2f& radius) {
		m_radius = radius;
		update();
	}

	const sf::Vector2f& getRadius() const {
		return m_radius;
	}

	std::size_t getPointCount() const override {
		return 2 * std::max(m_radius.x, m_radius.y) * 315 / 100;
	}

	sf::Vector2f getPoint(std::size_t index) const override {
		static const float pi = 3.141592654f;

		float angle = index * 2 * pi / getPointCount() - pi / 2;
		float x = std::cos(angle) * m_radius.x;
		float y = std::sin(angle) * m_radius.y;

		return {m_radius.x + x, m_radius.y + y};
	}
};

#endif //GUIRAPTOR_ELLIPSESHAPE_HPP

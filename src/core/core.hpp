//
// Created by notoraptor on 19-09-09.
//

#ifndef GUIRAPTOR_CORE_HPP
#define GUIRAPTOR_CORE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

sf::Texture* TextureGetFromFile(const char* path);
sf::Font* FontGetFromPath(const char* path);
sf::Color ColorFromString(const char* color);
std::string ColorToString(const sf::Color& color);
std::string rgba(unsigned char red, unsigned char green, unsigned char blue, float alpha);
std::string rgb(unsigned char red, unsigned char green, unsigned char blue);

// Alpha: 0 = transparent, 255 = opaque

#endif //GUIRAPTOR_CORE_HPP

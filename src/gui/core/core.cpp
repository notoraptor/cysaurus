//
// Created by notoraptor on 19-09-09.
//

#include "core.hpp"
#include <unordered_map>

extern unsigned char SourceCodePro_Regular_otf[];

extern unsigned char SourceSansPro_Regular_otf[];

extern unsigned char SourceSerifPro_Regular_otf[];

extern unsigned int SourceCodePro_Regular_otf_len;

extern unsigned int SourceSansPro_Regular_otf_len;

extern unsigned int SourceSerifPro_Regular_otf_len;

const char* _hex_digits = "0123456789ABCDEF";

inline unsigned int _hex_up(unsigned char c) {
	return c >> 4;
}

inline unsigned int _hex_down(unsigned char c) {
	return c & (((unsigned int) 1 << 4) - 1);
}

unsigned int _hex_to_digit(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return 10 + (c - 'a');
	if (c >= 'A' && c <= 'F')
		return 10 + (c - 'A');
	return 0;
}

class TexturesFromFile {
	std::unordered_map<std::string, sf::Texture*> textures;
public:
	TexturesFromFile(): textures() {}
	~TexturesFromFile() {
		for (auto it = textures.begin(); it != textures.end(); ++it) {
			delete it->second;
		}
	}
	sf::Texture* get(const char* path) {
		sf::Texture* texture = nullptr;
		std::string imagePath(path);
		auto it = textures.find(imagePath);
		if (it == textures.end()) {
			texture = new sf::Texture();
			if (texture->loadFromFile(imagePath)) {
				textures[imagePath] = texture;
				texture->setRepeated(true);
			} else {
				delete texture;
				texture = nullptr;
			}
		} else {
			texture = it->second;
		}
		return texture;
	}
};

class Fonts {
	std::unordered_map<std::string, sf::Font*> fonts;
public:
	Fonts(): fonts() {}
	~Fonts() {
		for (auto it = fonts.begin(); it != fonts.end(); ++it) {
			delete it->second;
		}
	}
	sf::Font* get(const char* path) {
		sf::Font* font = nullptr;
		std::string fontPath(path);
		auto it = fonts.find(fontPath);
		if (it == fonts.end()) {
			font = new sf::Font;
			bool loaded = false;
			if (fontPath == "monospace") {
				loaded = font->loadFromMemory(SourceCodePro_Regular_otf, SourceCodePro_Regular_otf_len);
			} else if (fontPath == "sans-serif") {
				loaded = font->loadFromMemory(SourceSansPro_Regular_otf, SourceSansPro_Regular_otf_len);
			} else if (fontPath == "serif") {
				loaded = font->loadFromMemory(SourceSerifPro_Regular_otf, SourceSerifPro_Regular_otf_len);
			} else {
				loaded = font->loadFromFile(fontPath);
			}
			if (loaded) {
				fonts[fontPath] = font;
			} else {
				delete font;
				font = nullptr;
			}
		} else {
			font = it->second;
		}
		return font;
	}
};

sf::Texture* TextureGetFromFile(const char* path) {
	static TexturesFromFile texturesFromFile;
	return texturesFromFile.get(path);
}

sf::Font* FontGetFromPath(const char* path) {
	static Fonts fonts;
	return fonts.get(path);
}

sf::Color ColorFromString(const char* color) {
	if (!color)
		return sf::Color::Transparent;
	std::string colorString(color);
	if (colorString[0] == '#') {
		unsigned char r = 0, g = 0, b = 0, a = 0;
		if (colorString.length() == 7) {
			r = _hex_to_digit(colorString[1]) * 16 + _hex_to_digit(colorString[2]);
			g = _hex_to_digit(colorString[3]) * 16 + _hex_to_digit(colorString[4]);
			b = _hex_to_digit(colorString[5]) * 16 + _hex_to_digit(colorString[6]);
			a = 255;
		} else if (colorString.length() == 9) {
			r = _hex_to_digit(colorString[1]) * 16 + _hex_to_digit(colorString[2]);
			g = _hex_to_digit(colorString[3]) * 16 + _hex_to_digit(colorString[4]);
			b = _hex_to_digit(colorString[5]) * 16 + _hex_to_digit(colorString[6]);
			a = _hex_to_digit(colorString[7]) * 16 + _hex_to_digit(colorString[8]);
		}
		return {r, g, b, a};
	}
	if (colorString == "black") return sf::Color::Black;
	if (colorString == "white") return sf::Color::White;
	if (colorString == "red") return sf::Color::Red;
	if (colorString == "green") return sf::Color::Green;
	if (colorString == "blue") return sf::Color::Blue;
	if (colorString == "yellow") return sf::Color::Yellow;
	if (colorString == "magenta") return sf::Color::Magenta;
	if (colorString == "cyan") return sf::Color::Cyan;
	return sf::Color::Transparent;
}

std::string ColorToString(const sf::Color& color) {
	std::string colorString(9, '#');
	colorString[1] = _hex_digits[_hex_up(color.r)];
	colorString[2] = _hex_digits[_hex_down(color.r)];
	colorString[3] = _hex_digits[_hex_up(color.g)];
	colorString[4] = _hex_digits[_hex_down(color.g)];
	colorString[5] = _hex_digits[_hex_up(color.b)];
	colorString[6] = _hex_digits[_hex_down(color.b)];
	colorString[7] = _hex_digits[_hex_up(color.a)];
	colorString[8] = _hex_digits[_hex_down(color.a)];
	return colorString;
}

std::string rgba(unsigned char red, unsigned char green, unsigned char blue, float alpha) {
	if (alpha < 0)
		alpha = 0;
	if (alpha > 1)
		alpha = 1;
	return ColorToString(sf::Color(red, green, blue, (unsigned char)(alpha * 255)));
}

std::string rgb(unsigned char red, unsigned char green, unsigned char blue) {
	return ColorToString(sf::Color(red, green, blue));
}

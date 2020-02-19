//
// Created by notoraptor-desktop on 18/02/2020.
//

#ifndef CYSAURUS_PRINTER_HPP
#define CYSAURUS_PRINTER_HPP

#include <cstring>
#include <sstream>

class Printer {
	std::ostringstream oss;
	const char* delimiter;
	bool written;
public:
	explicit Printer(const char* separator = nullptr): oss(), delimiter(nullptr), written(false) {
		setDelimiter(separator);
	}
	Printer& setDelimiter(const char* separator) {
		if (separator && strlen(separator))
			delimiter = separator;
		else
			delimiter = nullptr;
		return *this;
	}
	template <typename T>
	Printer& append(const T& value) {
		if (written && delimiter)
			oss << delimiter;
		oss << value;
		written = true;
		return *this;
	}
	Printer& append(const char* value) {
		if (value && strlen(value)) {
			if (written && delimiter)
				oss << delimiter;
			oss << value;
			written = true;
		}
		return *this;
	}
	std::string get() const {
		return oss.str();
	}
};

#endif //CYSAURUS_PRINTER_HPP

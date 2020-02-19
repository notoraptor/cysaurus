//
// Created by notoraptor-desktop on 18/02/2020.
//

#ifndef CYSAURUS_PROFILE_HPP
#define CYSAURUS_PROFILE_HPP

#include <core/printer.hpp>

inline std::string profile(size_t totalMicroseconds) {
	size_t solidSeconds = totalMicroseconds / 1000000;
	size_t solidMinutes = solidSeconds / 60;
	size_t solidHours = solidMinutes / 60;
	size_t days = solidHours / 24;
	size_t hours = solidHours % 24;
	size_t minutes = solidMinutes % 60;
	size_t seconds = solidSeconds % 60;
	size_t microseconds = totalMicroseconds % 1000000;
	Printer printer(" ");
	if (days)
		printer.append(days).append("d");
	if (hours)
		printer.append(hours).append("h");
	if (minutes)
		printer.append(minutes).append("m");
	if (seconds)
		printer.append(seconds).append("s");
	if (microseconds)
		printer.append(microseconds).append("microsec");
	return printer.get();
}

#endif //CYSAURUS_PROFILE_HPP

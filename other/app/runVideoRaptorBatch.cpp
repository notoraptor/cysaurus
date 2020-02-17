#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <video/videoRaptor.hpp>
#include <video/core/VideoRaptorContext.hpp>
#include <ctime>
#include <ratio>
#include <chrono>

#define BATCH_SIZE 250

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

std::string profile(size_t totalMicroseconds) {
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

int main(int nargs, char** args) {
	if (nargs != 3) {
		std::cerr << "Usage: " << args[0] << " <input-list-file> <output-jsonl-file>" << std::endl;
		return EXIT_FAILURE;
	}

	size_t count = 0;
	size_t countLoaded = 0;
	std::string line;
	std::ifstream listFile{args[1]};
	std::ofstream outputFile(args[2]);
	VideoRaptorContext context;
	VideoReport report{};

	if (!listFile.is_open()) {
		std::cerr << "Cannot open input list file: " << args[1] << std::endl;
		return EXIT_FAILURE;
	}
	if (!outputFile.is_open()) {
		std::cout << "Cannot open output JSONL file: " << args[2] << std::endl;
		return EXIT_FAILURE;
	}

	std::chrono::steady_clock::time_point timeStart = std::chrono::steady_clock::now();
	while (std::getline(listFile, line)) {
		if (line.length() && line[0] != '#') {
			++count;
			countLoaded += videoDetailsToJSON(context, line.c_str(), report, outputFile);
		}
		if (count % 250 == 0)
			std::cout << count << std::endl;
	}
	std::chrono::steady_clock::time_point timeEnd = std::chrono::steady_clock::now();

	auto timeSpent = std::chrono::duration_cast<std::chrono::duration<size_t, std::micro>>(timeEnd - timeStart);
	size_t totalMicroseconds = timeSpent.count();
	std::cout << "#count " << count << std::endl;
	std::cout << "#loaded " << countLoaded << std::endl;
	std::cout << "#microseconds " << totalMicroseconds << std::endl;
	std::cout << "#profile " << profile(totalMicroseconds) << std::endl;
	return EXIT_SUCCESS;
}
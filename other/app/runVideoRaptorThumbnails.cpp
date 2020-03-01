#include <iostream>
#include <fstream>
#include <video/videoRaptor.hpp>
#include <video/core/VideoRaptorContext.hpp>
#include <core/profile.hpp>
#include <ctime>
#include <ratio>
#include <chrono>

#define BATCH_SIZE 10

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
	VideoThumbnail videoThumbnail{};

	if (!listFile.is_open()) {
		std::cerr << "Cannot open input list file: " << args[1] << std::endl;
		return EXIT_FAILURE;
	}
	if (!outputFile.is_open()) {
		std::cerr << "Cannot open output JSONL file: " << args[2] << std::endl;
		return EXIT_FAILURE;
	}

	outputFile.put('[');
	std::chrono::steady_clock::time_point timeStart = std::chrono::steady_clock::now();
	while (std::getline(listFile, line)) {
		if (line.length() && line[0] != '#') {
			++count;
			auto posAfterFilename = line.find('\t');
			auto posAfterFolder = line.find('\t', posAfterFilename + 1);
			auto posAfterThumbname = line.find('\t', posAfterFolder + 1);
			line[posAfterFilename] = '\0';
			line[posAfterFolder] = '\0';
			line[posAfterThumbname] = '\0';
			const char* filename = &line[0];
			const char* thumbFolder = &line[posAfterFilename + 1];
			const char* thumbName = &line[posAfterFolder + 1];
			VideoThumbnail_init(&videoThumbnail, filename, thumbFolder, thumbName);
			bool ok = videoThumbnailsToJSON(context, videoThumbnail, outputFile);
			if (!ok)
				outputFile.put(',');
			countLoaded += ok;
		}
		if (count % BATCH_SIZE == 0)
			std::cout << count << std::endl;
	}
	std::chrono::steady_clock::time_point timeEnd = std::chrono::steady_clock::now();
	outputFile.write("null]", 5);

	auto timeSpent = std::chrono::duration_cast<std::chrono::duration<size_t, std::micro>>(timeEnd - timeStart);
	size_t totalMicroseconds = timeSpent.count();
	std::cout << "#count " << count << std::endl;
	std::cout << "#loaded " << countLoaded << std::endl;
	std::cout << "#microseconds " << totalMicroseconds << std::endl;
	std::cout << "#profile " << profile(totalMicroseconds) << std::endl;
	std::cout << "#end" << std::endl;
	return EXIT_SUCCESS;
}
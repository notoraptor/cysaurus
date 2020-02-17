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
#define LIMIT 0

int runBatch(VideoRaptorContext& context, const std::vector<std::string>& batch, size_t id, std::vector<VideoInfo*>& pointers) {
	int countLoaded = 0;
	if (batch.empty())
		return countLoaded;
	for (size_t i = 0; i < batch.size(); ++i)
		VideoInfo_init(pointers[i], batch[i].c_str());
	countLoaded = videoRaptorDetails(&context, pointers.size(), pointers.data());
	for (size_t i = 0; i < batch.size(); ++i)
	    VideoInfo_clear(pointers[i]);
	std::cout << "[" << id << "] Running " << batch.size() << " file(s)." << std::endl;
	return countLoaded;
}

int main(int nargs, char** args) {
	if (nargs != 2) {
		std::cerr << "No input file name given." << std::endl;
		return EXIT_FAILURE;
	}

	VideoRaptorContext context;

	size_t count = 0;
	size_t countLoaded = 0;
	std::string line;

    std::vector<VideoInfo> infoData(BATCH_SIZE);
    std::vector<VideoInfo*> pointers(BATCH_SIZE);
    for (size_t i = 0; i < BATCH_SIZE; ++i)
        pointers[i] = &infoData[i];

	std::vector<std::string> batch;
	std::ifstream listFile{args[1]};
	if (!listFile.is_open()) {
		std::cerr << "Cannot open file: " << args[1] << std::endl;
		return EXIT_FAILURE;
	}
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	while (std::getline(listFile, line)) {
		if (line.length() && line[0] != '#') {
			++count;
			batch.push_back(line);
		}
		if (LIMIT && count == LIMIT)
			break;
		if (batch.size() == BATCH_SIZE) {
			countLoaded += runBatch(context, batch, count, pointers);
			batch.clear();
		}
	}
	countLoaded += runBatch(context, batch, count, pointers);
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	listFile.close();
	std::chrono::duration<size_t, std::micro> timeSpent = std::chrono::duration_cast<std::chrono::duration<size_t, std::micro>>(t2 - t1);
	size_t totalMicroseconds = timeSpent.count();
	size_t solidSeconds = totalMicroseconds / 1000000;
	size_t solidMinutes = solidSeconds / 60;
	size_t solidHours = solidMinutes / 60;
	size_t days = solidHours / 24;
	size_t hours = solidHours % 24;
	size_t minutes = solidMinutes % 60;
	size_t seconds = solidSeconds % 60;
	size_t microseconds = totalMicroseconds % 1000000;
	std::ostringstream oss;
	if (days)
		oss << days << "d ";
	if (hours)
		oss << hours << "h ";
	if (minutes)
		oss << minutes << "m ";
	if (seconds)
		oss << seconds << "s ";
	if (microseconds)
		oss << microseconds << "ms";
	std::cout << countLoaded << " / " << count << " in " << oss.str() << std::endl;
	return EXIT_SUCCESS;
}
#include <sstream>
#include <video/videoRaptor.hpp>
#include <video/core/ErrorReader.hpp>
#include <video/core/VideoRaptorContext.hpp>

void printDetails(VideoInfo* videoDetails) {
	std::cout << "VIDEO" << std::endl;
	std::cout << "\tdevice            : " << (videoDetails->device_name ? videoDetails->device_name : "(none)") << std::endl;
	if (videoDetails->filename)
		std::cout << "\tfilename          : " << videoDetails->filename << std::endl;
	if (videoDetails->title)
		std::cout << "\ttitle             : " << videoDetails->title << std::endl;
	if (videoDetails->container_format)
		std::cout << "\tcontainer_format  : " << videoDetails->container_format << std::endl;
	if (videoDetails->video_codec)
		std::cout << "\tvideo_codec       : " << videoDetails->video_codec << std::endl;
	if (videoDetails->video_codec_description)
		std::cout << "\tvideo_codec_desc  : " << videoDetails->video_codec_description << std::endl;
	if (videoDetails->audio_codec)
		std::cout << "\taudio_codec       : " << videoDetails->audio_codec << std::endl;
	if (videoDetails->audio_codec_description)
		std::cout << "\taudio_codec_desc  : " << videoDetails->audio_codec_description << std::endl;
	std::cout << "\twidth             : " << videoDetails->width << std::endl;
	std::cout << "\theight            : " << videoDetails->height << std::endl;
	std::cout << "\tframe_rate_num    : " << videoDetails->frame_rate_num << std::endl;
	std::cout << "\tframe_rate_den    : " << videoDetails->frame_rate_den << std::endl;
	std::cout << "\tduration          : " << videoDetails->duration << std::endl;
	std::cout << "\tduration_time_base: " << videoDetails->duration_time_base << std::endl;
	std::cout << "\tsize              : " << videoDetails->size << std::endl;
	std::cout << "\tsample_rate       : " << videoDetails->sample_rate << std::endl;
	std::cout << "\taudio_bit_rate    : " << videoDetails->audio_bit_rate << std::endl;
	std::cout << "\tbit depth         : " << videoDetails->bit_depth << std::endl;
	if (videoDetails->report.errors && !VideoReport_isDone(&videoDetails->report)) {
		ErrorReader errorReader{};
		ErrorReader_init(&errorReader, videoDetails->report.errors);
		std::cout << "\terrors:" << std::endl;
		while (const char* errorString = ErrorReader_next(&errorReader)) {
			std::cout << "\t\t" << errorString << std::endl;
		}
	}
}

bool testDetails(VideoRaptorContext& context, const char* filename) {
	bool returnValue = false;
	VideoInfo videoInfo;
	VideoInfo_init(&videoInfo, filename);
	VideoInfo* pVideoDetails = &videoInfo;
	videoRaptorDetails(&context, 1, &pVideoDetails);
	if (VideoReport_isDone(&videoInfo.report)) {
		printDetails(&videoInfo);
		returnValue = true;
	} else {
		std::cout << "No details." << std::endl;
	}
	if (VideoReport_hasError(&videoInfo.report)) {
		std::cout << "Video details: error(s) occurred (" << videoInfo.report.errors << ")." << std::endl;
		VideoReport_print(&videoInfo.report);
	}
	VideoInfo_clear(&videoInfo);
	return returnValue;
}

bool testJSON(VideoRaptorContext& context, const char* filename) {
	bool returnValue = false;
	VideoReport videoReport;
	VideoReport* pVideoReport = &videoReport;
	videoRaptorJSON(&context, 1, &filename, &pVideoReport, "out.log");
	if (VideoReport_isDone(pVideoReport)) {
		returnValue = true;
	} else {
		std::cout << "No details." << std::endl;
	}
	if (VideoReport_hasError(pVideoReport)) {
		std::cout << "Video details: error(s) occurred (" << videoReport.errors << ")." << std::endl;
		VideoReport_print(pVideoReport);
	}
	return returnValue;
}

bool testThumbnail(VideoRaptorContext& context, const char* filename, const char* thumbName) {
	bool returnValue = false;
	VideoThumbnail videoThumbnail;
	VideoThumbnail_init(&videoThumbnail, filename, ".", thumbName);
	VideoThumbnail* pVideoThumbnailInfo = &videoThumbnail;
	videoRaptorThumbnails(&context, 1, &pVideoThumbnailInfo);
	if (VideoReport_isDone(&videoThumbnail.report)) {
		std::cout << "Thumbnail created: " << thumbName << ".png" << std::endl;
		returnValue = true;
	} else {
		std::cout << "No thumbnail." << std::endl;
	}
	if (VideoReport_hasError(&videoThumbnail.report)) {
		std::cout << "Video thumbnails: error(s) occurred (" << videoThumbnail.report.errors << ")." << std::endl;
		VideoReport_print(&videoThumbnail.report);
	}
	return returnValue;
}

void test(VideoRaptorContext& context, const char* filename, const char* thumbName) {
	if (testDetails(context, filename))
		testThumbnail(context, filename, thumbName);
}

void testErrorPrinting() {
	std::cout << "Testing errors printing ..." << std::endl;
	unsigned int errors = ERROR_OPEN_FILE | ERROR_CODE_000000032 | ERROR_CONVERT_CODEC_PARAMS | ERROR_PNG_CODEC;
	ErrorReader errorReader;
	ErrorReader_init(&errorReader, errors);
	while (const char* errorString = ErrorReader_next(&errorReader)) {
		std::cout << errorString << std::endl;
	}
	std::cout << "... Finished testing." << std::endl << std::endl;
}

int main(int n, char* args[]) {
	VideoRaptorContext context;

	std::cout << context.nbDevices() << " hardware device(s)";
	if (context.nbDevices())
		std::cout << ": " << context.devicesNames();
	std::cout << '.' << std::endl << std::endl;

	for (int i = 1; i < n; ++i) {
		std::ostringstream oss;
		oss << i;
		auto thumbName = oss.str();
		test(context, args[i], thumbName.c_str());
	}
	return EXIT_SUCCESS;
}

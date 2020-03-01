//
// Created by notoraptor on 27/05/2018.
//

#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "core/Video.hpp"
#include "core/errorCodes.hpp"
#include "videoRaptor.hpp"
#include "core/VideoRaptorContext.hpp"

typedef bool (* VideoWorkerFunction)(Video* video, void* context);

bool videoWorkerForInfo(Video* video, void* context) {
	video->extractInfo((VideoInfo*) context);
	return true;
}

bool videoWorkerForJSON(Video* video, void* context) {
	return video->json(*(std::ostream*)context);
}

bool videoWorkerForThumbnail(Video* video, void* context) {
	return video->generateThumbnail((VideoThumbnail*) context);
}

bool workOnVideo(HWDevices& devices, const char* videoFilename, VideoReport* videoReport, void* videoContext,
				 VideoWorkerFunction videoWorkerFunction) {
	for (size_t i = 0; i < devices.available.size(); ++i) {
		size_t indexToUse = (devices.indexUsed + i) % devices.available.size();
		VideoReport_init(videoReport);
		Video video(videoFilename, videoReport, devices, indexToUse);
		if (VideoReport_hasError(videoReport)) {
			if (VideoReport_hasDeviceError(videoReport)) {
				// Device error when loading video: move to next loop step.
				continue;
			}
			// Fatal error (no device error). Stop.
			return false;
		}
		// Video loaded. Do work.
		if (!videoWorkerFunction(&video, videoContext)) {
			if (VideoReport_hasDeviceError(videoReport)) {
				// Device error when working: move to next loop step.
				continue;
			}
			// Fatal error (no device error). Stop.
			return false;
		}
		// Update HW device index used.
		devices.indexUsed = indexToUse;
		return true;
	};
	// Device error for all devices. Don't use devices. Set index to invalid value.
	devices.indexUsed = devices.available.size();
	VideoReport_init(videoReport);
	Video video(videoFilename, videoReport, devices, devices.indexUsed);
	if (VideoReport_hasError(videoReport))
		return false;
	return videoWorkerFunction(&video, videoContext);
}

int videoRaptorThumbnails(void* context, int length, VideoThumbnail** pVideoThumbnail) {
	if (!context || length <= 0 || !pVideoThumbnail)
		return 0;
	HWDevices* devices = ((VideoRaptorContext*)context)->devices();
	int countLoaded = 0;
	for (int i = 0; i < length; ++i) {
		VideoThumbnail* videoThumbnail = pVideoThumbnail[i];
		countLoaded += (videoThumbnail
						&& videoThumbnail->filename
						&& videoThumbnail->thumbnailFolder
						&& videoThumbnail->thumbnailName
						&& workOnVideo(*devices, videoThumbnail->filename,
								&videoThumbnail->report, videoThumbnail,
								videoWorkerForThumbnail));
	}
	return countLoaded;
}

int videoRaptorDetails(void* context, int length, VideoInfo** pVideoInfo) {
	if (!context || length <= 0 || !pVideoInfo)
		return 0;
	HWDevices* devices = ((VideoRaptorContext*)context)->devices();
	int countLoaded = 0;
	for (int i = 0; i < length; ++i) {
		VideoInfo* videoDetails = pVideoInfo[i];
		countLoaded += (videoDetails
						&& videoDetails->filename
						&& workOnVideo(*devices, videoDetails->filename,
								&videoDetails->report, videoDetails, videoWorkerForInfo));
	}
	return countLoaded;
}

int videoRaptorJSON(void* context, int length, const char** videoFilenames, VideoReport** videoReports, const char* outputFilename) {
	if (!context || length <= 0 || !videoFilenames || !videoReports || !outputFilename)
		return 0;
	std::ofstream outputFile(outputFilename, std::ios::app);
	if (!outputFile.is_open())
		return 0;
	HWDevices* devices = ((VideoRaptorContext*)context)->devices();
	int countLoaded = 0;
	for (int i = 0; i < length; ++i) {
		const char* videoFilename = videoFilenames[i];
		VideoReport* videoReport = videoReports[i];
		if (videoFilename
			&& videoReport
			&& workOnVideo(*devices, videoFilename, videoReport, &outputFile, videoWorkerForJSON)) {
			++countLoaded;
			VideoReport_setDone(videoReport, true);
			outputFile.put('\r');
			outputFile.put('\n');
		}
	}
	outputFile.close();
	return countLoaded;
}

bool errorsToJSON(const char* filename, VideoReport& report, std::ostream& output) {
	if (!report.errors)
		return false;
	auto flags = report.errors;
	if (flags & SUCCESS_DONE)
		flags ^= SUCCESS_DONE;
	if (!flags)
		return false;
	auto object = cJSON_CreateObject();
	auto array = cJSON_AddArrayToObject(object, ERRORS);
	cJSON_AddStringToObject(object, FILE_NAME, filename);
	ErrorReader reader{};
	ErrorReader_init(&reader, flags);
	while (const char* errorString = ErrorReader_next(&reader)) {
		auto str = cJSON_CreateString(errorString);
		cJSON_AddItemToArray(array, str);
	}
	if (report.errorDetail[0]) {
		auto str = cJSON_CreateStringReference(report.errorDetail);
		cJSON_AddItemToArray(array, str);
	}
	auto jsonString = cJSON_PrintUnformatted(object);
	output.write(jsonString, strlen(jsonString));
	delete[] jsonString;
	cJSON_Delete(object);
	return true;
}

bool videoDetailsToJSON(VideoRaptorContext& context, const char* filename, VideoReport& report, std::ostream& output) {
	bool ok = true;
	if (!filename || !workOnVideo(*context.devices(), filename, &report, &output, videoWorkerForJSON)) {
		ok = false;
		errorsToJSON(filename, report, output);
	}
	return ok;
}

bool videoThumbnailsToJSON(VideoRaptorContext& context, VideoThumbnail& videoThumbnail, std::ostream& output) {
	bool ok = true;
	if (!workOnVideo(*context.devices(), videoThumbnail.filename, &videoThumbnail.report, &videoThumbnail, videoWorkerForThumbnail)) {
		ok = false;
		errorsToJSON(videoThumbnail.filename, videoThumbnail.report, output);
	}
	return ok;
}

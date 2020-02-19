//
// Created by notoraptor on 27/05/2018.
//

#ifndef VIDEORAPTOR_VIDEORAPTORBATCH_HPP
#define VIDEORAPTOR_VIDEORAPTORBATCH_HPP

#include <video/core/VideoRaptorContext.hpp>
#include "core/VideoInfo.hpp"
#include "core/VideoThumbnail.hpp"

extern "C" {
	int videoRaptorDetails(void* context, int length, VideoInfo** pVideoInfo);
	int videoRaptorThumbnails(void* context, int length, VideoThumbnail** pVideoThumbnail);
	int videoRaptorJSON(void* context, int length, const char** videoFilenames, VideoReport** videoReports, const char* outputFilename);

	bool videoDetailsToJSON(VideoRaptorContext& context, const char* filename, VideoReport& report, std::ostream& output);
	bool videoThumbnailsToJSON(VideoRaptorContext& context, VideoThumbnail& videoThumbnail, std::ostream& output);
};


#endif //VIDEORAPTOR_VIDEORAPTORBATCH_HPP

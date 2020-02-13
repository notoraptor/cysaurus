//
// Created by notoraptor on 27/05/2018.
//

#ifndef VIDEORAPTOR_VIDEORAPTORBATCH_HPP
#define VIDEORAPTOR_VIDEORAPTORBATCH_HPP

#include "core/VideoInfo.hpp"
#include "core/VideoThumbnail.hpp"

extern "C" {
	int videoRaptorDetails(int length, VideoInfo** pVideoInfo);
	int videoRaptorThumbnails(int length, VideoThumbnail** pVideoThumbnail);
	int videoRaptorJSON(int length, const char** videoFilenames, VideoReport** videoReports, const char* outputFilename);
};


#endif //VIDEORAPTOR_VIDEORAPTORBATCH_HPP

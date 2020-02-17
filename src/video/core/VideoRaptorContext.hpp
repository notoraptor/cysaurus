//
// Created by notoraptor-desktop on 15/02/2020.
//

#ifndef CYSAURUS_VIDEORAPTORCONTEXT_HPP
#define CYSAURUS_VIDEORAPTORCONTEXT_HPP

#include <video/core/utils.hpp>

class VideoRaptorContext {
	HWDevices hwDevices;
	char* hwDevicesNames;
public:
	VideoRaptorContext();
	~VideoRaptorContext();
	HWDevices* devices();
	size_t nbDevices() const;
	const char* devicesNames() const;
};

extern "C" {
	void* VideoRaptorContext_New();
	void VideoRaptorContext_Delete(void*);
}

#endif //CYSAURUS_VIDEORAPTORCONTEXT_HPP

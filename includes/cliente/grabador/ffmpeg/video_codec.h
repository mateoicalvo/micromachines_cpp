#ifndef	_VIDEO_CODEC_H_
#define _VIDEO_CODEC_H_

#include "includes/cliente/grabador/ffmpeg/codec.h"

extern "C" {
	#include <libswscale/swscale.h>
}

class VideoCodec : public Codec {
private:
    struct SwsContext *sws_ctx = NULL;
    VideoCodec(const VideoCodec&) = delete;
	VideoCodec& operator=(const VideoCodec&) = delete;
    VideoCodec& operator=(VideoCodec&& rhs) = delete;

public:
	VideoCodec(enum AVCodecID id, AVRational avr, Frame& fr, int width, int height, AVPixelFormat pix_fmt, bool header_flag);

	void copy_parameters(AVStream * st);

	void write_rgb_frame(Frame& dest, const char * data, int pts);

	VideoCodec(VideoCodec&& rhs);
    
	~VideoCodec();
};

#endif

#ifndef	_CODEC_H_
#define _CODEC_H_

extern "C" {
	#include <libavformat/avformat.h>
	#include <libavutil/opt.h>
	#include <libavutil/mathematics.h>
	#include <libavutil/timestamp.h>
	#include <libavcodec/avcodec.h>
}

#include "includes/cliente/grabador/ffmpeg/frame.h"

class Codec {
private:
    Codec(const Codec& rhs) = delete;
	Codec& operator=(const Codec& rhs) = delete;

protected:
    AVCodecContext *enc;
	AVCodec* codec;

public:
	Codec(enum AVCodecID id);

	void open();

	void copy_parameters(AVStream * st);

	void encode_frame(const Frame& f);

	int get_packet(AVPacket * pkt, AVRational *time_base);

	Codec(Codec&& rhs);

	Codec& operator=(Codec&& rhs);

	virtual ~Codec();
};

#endif

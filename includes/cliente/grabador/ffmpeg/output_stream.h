#ifndef	_OUTPUT_STREAM_H_
#define _OUTPUT_STREAM_H_

extern "C" {
	#include <libavutil/avassert.h>
	#include <libavformat/avformat.h>
	#include <libavutil/opt.h>
	#include <libavutil/mathematics.h>
	#include <libavutil/timestamp.h>
}

#include "includes/cliente/grabador/ffmpeg/frame.h"
#include "includes/cliente/grabador/ffmpeg/codec.h"
#include "includes/cliente/grabador/ffmpeg/output_format.h"

#define STREAM_PIX_FMT    AV_PIX_FMT_YUV420P /* default pix_fmt */
#define SCALE_FLAGS SWS_BICUBIC

class OutputStream {
protected:
    AVStream* st;
    Codec* enc;
    AVPacket* pkt;
    /* pts of the next frame that will be generated */
    int64_t current_pts = 0;
    OutputFormat& fmt;
    Frame frame;

public:
	OutputStream(OutputFormat &fmt);

    virtual void write_frame();

	virtual ~OutputStream();
};

#endif

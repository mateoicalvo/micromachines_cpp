#ifndef _FRAME_H_
#define _FRAME_H_

extern "C" {
	#include <libavutil/avassert.h>
	#include <libavutil/channel_layout.h>
	#include <libavutil/opt.h>
	#include <libavutil/mathematics.h>
	#include <libavutil/timestamp.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libswresample/swresample.h>	
}

class Frame {
private:
    AVFrame* fr;

    Frame(const Frame&) = delete;
	Frame& operator=(const Frame&) = delete;

public:
    Frame();

    void VideoFrame(enum AVPixelFormat pix_fmt, int width, int height);

    void make_writable();

    const AVFrame* get_frame() const;

    void fill_rgb(SwsContext* ctx, const char* data, int width, int pts);

    void AudioFrame(enum AVSampleFormat sample_fmt, uint64_t channel_layout, int sample_rate, int nb_samples);

    Frame(Frame&& rhs);


	Frame& operator=(Frame&& rhs);


	~Frame();
};

#endif

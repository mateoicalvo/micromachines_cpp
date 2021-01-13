#include "includes/cliente/grabador/ffmpeg/output_video.h"

#include <stdexcept>

OutputVideo::OutputVideo(OutputFormat &fmt, AVRational avr, int w, int h, AVPixelFormat pix) :
	OutputStream(fmt) {
	try {
		st->time_base = avr;
		enc = new VideoCodec(fmt.get_video_codec_id(), avr, frame, w, h, pix, fmt.is_flag_set(AVFMT_GLOBALHEADER));
		enc->copy_parameters(st);
	}
	catch (std::runtime_error &e) {
		throw std::runtime_error(e);
	}
}

void OutputVideo::rgb_line_to_frame(const char *v) {
	reinterpret_cast<VideoCodec*>(enc)->write_rgb_frame(frame, v, current_pts);
	current_pts++;
}

OutputVideo::~OutputVideo() {
	delete enc;
}

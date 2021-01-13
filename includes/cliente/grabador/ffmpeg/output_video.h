#ifndef	_OUTPUT_VIDEO_H_
#define _OUTPUT_VIDEO_H_

#include "includes/cliente/grabador/ffmpeg/output_stream.h"
#include "includes/cliente/grabador/ffmpeg/video_codec.h"

class OutputVideo : public OutputStream {
public:
	OutputVideo(OutputFormat &fmt, AVRational avr, int w, int h, AVPixelFormat pix);
	
    void rgb_line_to_frame(const char * v);
    
    ~OutputVideo();
};

#endif

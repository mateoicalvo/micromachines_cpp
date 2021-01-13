#ifndef	_OUTPUT_FORMAT_H_
#define _OUTPUT_FORMAT_H_

extern "C" {
	#include <libavutil/avassert.h>
	#include <libavformat/avformat.h>
}

#include <string>

class OutputFormat {
private:
    AVFormatContext* ctx;
    std::string filename;

public:
	OutputFormat(const std::string& file);

	AVStream* get_new_stream();

	bool is_flag_set(int flag);

    int write_pkt(AVPacket * pkt);

    void open();
    
    enum AVCodecID get_video_codec_id();

    enum AVCodecID get_audio_codec_id();

    void write_trailer();

    ~OutputFormat();
};

#endif

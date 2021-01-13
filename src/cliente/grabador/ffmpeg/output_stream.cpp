#include "includes/cliente/grabador/ffmpeg/output_stream.h"

#include <stdexcept>

#include "includes/cliente/grabador/ffmpeg/codec.h"

OutputStream::OutputStream(OutputFormat &fmt) : 
	fmt(fmt){
	st = fmt.get_new_stream();
	pkt = av_packet_alloc();
}

void OutputStream::write_frame() {
	try	{
		enc->encode_frame(frame);
		while (true) {
			AVRational time_base;
			if (!enc->get_packet(pkt, &time_base)) {
				break;
			}
			av_packet_rescale_ts(pkt, time_base, st->time_base);
			pkt->stream_index = st->index;
			//write
			if (fmt.write_pkt(pkt)) {
				throw std::runtime_error("No se pudo escribir paquete");
			}
			av_packet_unref(pkt);
		}
	}
	catch (std::runtime_error &e) {
		throw std::runtime_error(e);
	}
}

OutputStream::~OutputStream() {
	av_packet_free(&pkt);
}

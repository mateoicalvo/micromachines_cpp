#include "includes/cliente/grabador/ffmpeg/codec.h"

#include <stdexcept>

Codec::Codec(enum AVCodecID id){
	codec = avcodec_find_encoder(id);
	if (!codec) {
		throw std::runtime_error("Encoder no encontrado.");
	}
	enc = avcodec_alloc_context3(codec);
	if (!enc) {
		throw std::runtime_error("No se pudo alocar el contexto del encoder!");
	}
}

void Codec::open() {
	// NULL pero se puede agregar un diccionario de opciones
	if (avcodec_open2(enc, codec, NULL) < 0){
		throw std::runtime_error("No se puedo abrir el encoder");	        	
	}
}

void Codec::encode_frame(const Frame& f) {
	if (avcodec_send_frame(enc, f.get_frame())) {
	    throw std::runtime_error("Error al enviar frame");
	}
}

int Codec::get_packet(AVPacket * pkt, AVRational *time_base) {
	int ret = avcodec_receive_packet(enc, pkt);
	if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
		return 0;
	} else if (ret < 0) {
		throw std::runtime_error("Error al codificar");
	}
	time_base->num = enc->time_base.num;
	time_base->den = enc->time_base.den;
	return 1;
}

void Codec::copy_parameters(AVStream * st) {
	if (avcodec_parameters_from_context(st->codecpar, enc) < 0) {
		throw std::runtime_error("No se pudieron copiar los parametros del contexto al stream");
	}
}


Codec::Codec(Codec&& rhs){
	this->enc = rhs.enc;
	rhs.enc = NULL;
}

Codec& Codec::operator=(Codec&& rhs) {
	this->enc = rhs.enc;
	rhs.enc = NULL;
	return *this;
}

Codec::~Codec() {
	if (enc != nullptr) {
		avcodec_free_context(&enc);
	}
}

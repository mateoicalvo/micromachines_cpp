#include "includes/cliente/grabador/ffmpeg/output_format.h"

#include <iostream>
#include <cmath>
#include <exception>

OutputFormat::OutputFormat(const std::string &file) : filename(file) {
	//av_register_all();
	avformat_alloc_output_context2(&ctx, NULL, NULL, filename.c_str());
	if (!ctx) {
		// Si no se encuentra el formato del archivo, se usa MP4
		avformat_alloc_output_context2(&ctx, NULL, "mp4", filename.c_str());
	}
	if (!ctx) {
		throw std::runtime_error("No se pudo alocar el contexto del formato del archivo");
	}
}

AVStream* OutputFormat::get_new_stream() {
	AVStream *st = avformat_new_stream(ctx, NULL);
	st->id = ctx->nb_streams - 1;
	return st;
}

bool OutputFormat::is_flag_set(int flag) {
	return ctx->oformat->flags & AVFMT_GLOBALHEADER;
}

int OutputFormat::write_pkt(AVPacket *pkt) {
	return av_interleaved_write_frame(ctx, pkt);
}

void OutputFormat::open() {
	av_dump_format(ctx, 0, filename.c_str(), 1);
	if (!(ctx->oformat->flags & AVFMT_NOFILE)) {
		if (avio_open(&ctx->pb, filename.c_str(), AVIO_FLAG_WRITE) < 0) {
			throw std::runtime_error("No se pudo abrir el archivo");
		}
	}
	// EN VEZ DE NULL SE PUEDEN AGREGAR OPCIONES
	if (avformat_write_header(ctx, NULL) < 0) {
		throw std::runtime_error("No se pudo escribir el header");
	}
}

enum AVCodecID OutputFormat::get_video_codec_id() {
	return ctx->oformat->video_codec;
}

enum AVCodecID OutputFormat::get_audio_codec_id() {
	return ctx->oformat->audio_codec;
}

void OutputFormat::write_trailer() {
	if (av_write_trailer(ctx) < 0) {
		throw std::runtime_error("No se pudo escribir el trailer");
	}
}

OutputFormat::~OutputFormat() {
	if (!(ctx->oformat->flags & AVFMT_NOFILE)) {
		avio_closep(&ctx->pb);
	}
	if (ctx) {
		avformat_free_context(ctx);
	}
}

/*
 * speexplugin.cpp
 *
 *  Created on: 11/01/2010
 *      Author: ivocalado
 */

#include "speexplugin.h"
#include <ostream>
#include <sstream>

SpeexPlugin::SpeexPlugin() {
	initConstants();
	encoder = 0;
	decoder = 0;
	preprocess = 0;
}

void SpeexPlugin::initConstants() {
	/**Speex options*/
	constants["SpeexHighPass"] = __SPEEX_HIGHPASS;
	constants["SpeexVBRMaxBitRate"] = __SPEEX_VBR_MAX_BITRATE; //Just encoder
	constants["SpeexPLCTuning"] = __SPEEX_PLC_TUNING; //Just encoder
	constants["SpeexABR"] = __SPEEX_ABR; //Just encoder
	constants["SpeexDTX"] = __SPEEX_DTX; //Just encoder
	constants["SpeexVAD"] = __SPEEX_VAD; //Just encoder
	constants["SpeexResetState"] = __SPEEX_RESET_STATE;
	constants["SpeexSamplingRate"] = __SPEEX_SAMPLING_RATE;
	constants["SpeexBitRate"] = __SPEEX_BITRATE; //Just encoder to set, both to get
	constants["SpeexComplexity"] = __SPEEX_COMPLEXITY;
	constants["SpeexVBRQuality"] = __SPEEX_VBR_QUALITY; //Just encoder
	constants["SpeexVBR"] = __SPEEX_VBR;
	constants["SpeexMode"] = __SPEEX_MODE;
	constants["SpeexQuality"] = __SPEEX_QUALITY;
	constants["SpeexFrameSize"] = __SPEEX_FRAME_SIZE;
	constants["SpeexEHN"] = __SPEEX_ENH;
	constants["Decoder_Opt"] = __DECODER_OPT;
	constants["Encoder_Opt"] = __ENCODER_OPT;

	/**preprocessing options*/
	constants["SpeexPreprocess_Opt"] = __PREPROCESS_OPT;
	constants["SpeexPreprocessDENoise"] = __SPEEX_PREPROCESS_DENOISE;
	constants["SpeexPreprocessAGC"] = __SPEEX_PREPROCESS_AGC;
	constants["SpeexPreprocessAGCLevel"] = __SPEEX_PREPROCESS_AGC_LEVEL;
	constants["SpeexPreprocessDereverb"] = __SPEEX_PREPROCESS_DEREVERB;
	constants["SpeexPreprocessDereverbLevel"]
			= __SPEEX_PREPROCESS_DEREVERB_LEVEL;
	constants["SpeexPreprocessDereverbDecay"]
			= __SPEEX_PREPROCESS_DEREVERB_DECAY;
	constants["SpeexPreprocessProbStart"] = __SPEEX_PREPROCESS_PROB_START;
	constants["SpeexPreprocessProbContinue"] = __SPEEX_PREPROCESS_PROB_CONTINUE;
	constants["SpeexPreprocessNoiseSupress"] = __SPEEX_PREPROCESS_NOISE_SUPRESS;
	constants["SpeexPreprocessEchoSupress"] = __SPEEX_PREPROCESS_ECHO_SUPRESS;
	constants["SpeexPreprocessEchoSupressActive"]
			= __SPEEX_PREPROCESS_ECHO_SUPRESS_ACTIVE;
	constants["SpeexPreprocessEchoState"] = __SPEEX_PREPROCESS_ECHO_STATE;
}

SpeexPlugin::~SpeexPlugin() {
	if (encoder)
		destroyEncoder();
	if (decoder)
		destroyDecoder();
}

SpeexPlugin::SpeexMode SpeexPlugin::getMode(std::string modeName){
	SpeexMode mode = INVALID_MODE;
	if(modeName == "NarrowBand")
		mode = MODE_NB;
	else if(modeName == "WideBand")
		mode = MODE_WB;
	else if(modeName == "UltraWideBand")
		mode = MODE_UWB;
	return mode;
}

std::string SpeexPlugin::retrievePluginInformation(std::string info,
		std::string subInfo) throw (OperationNotSupportedException,
		OperationNotPerfomedException) {
	MessageType mainInfo = constants[info];
	MessageType secondaryInfo = constants[subInfo];
	std::ostringstream os;
	switch (mainInfo) {
	case __ENCODER_OPT:
		if (!encoder)
			throw OperationNotPerfomedException("encoder not initialized");

		switch (secondaryInfo) {
		case __SPEEX_FRAME_SIZE:
			spx_int32_t framesize;
			speex_encoder_ctl(encoder->state, SPEEX_GET_FRAME_SIZE, &framesize);
			os << framesize;
			return os.str();
			//		case __SPEEX_QUALITY:
			//			spx_int32_t quality;
			//			speex_encoder_ctl(encoderPtr, SPEEX_GET_FRAME_SIZE, &quality);
			//			os << framesize;
			//			return os.str();
		case __SPEEX_MODE:
			spx_int32_t mode;
			speex_encoder_ctl(encoder->state, SPEEX_GET_MODE, &mode);
			os << mode;
			return os.str();
		case __SPEEX_VBR:
			spx_int32_t vbr;
			speex_encoder_ctl(encoder->state, SPEEX_GET_VBR, &vbr);
			os << vbr;
			return os.str();
		case __SPEEX_VBR_QUALITY:
			float vbrquality;
			speex_encoder_ctl(encoder->state, SPEEX_GET_VBR_QUALITY,
					&vbrquality);
			os << vbr;
			return os.str();
		case __SPEEX_COMPLEXITY:
			spx_int32_t complexity;
			speex_encoder_ctl(encoder->state, SPEEX_GET_VBR_QUALITY,
					&complexity);
			os << complexity;
			return os.str();
		case __SPEEX_BITRATE:
			spx_int32_t bitrate;
			speex_encoder_ctl(encoder->state, SPEEX_GET_BITRATE, &bitrate);
			os << bitrate;
			return os.str();
		case __SPEEX_SAMPLING_RATE:
			spx_int32_t samplingrate;
			speex_encoder_ctl(encoder->state, SPEEX_GET_SAMPLING_RATE,
					&samplingrate);
			os << samplingrate;
			return os.str();
		case __SPEEX_VAD:
			spx_int32_t vad;
			speex_encoder_ctl(encoder->state, SPEEX_GET_VAD, &vad);
			os << vad;
			return os.str();
		case __SPEEX_DTX:
			spx_int32_t dtx;
			speex_encoder_ctl(encoder->state, SPEEX_GET_DTX, &dtx);
			os << dtx;
			return os.str();
		case __SPEEX_ABR:
			spx_int32_t abr;
			speex_encoder_ctl(encoder->state, SPEEX_GET_ABR, &abr);
			os << abr;
			return os.str();
		case __SPEEX_PLC_TUNING:
			spx_int32_t tuning;
			speex_encoder_ctl(encoder->state, SPEEX_GET_PLC_TUNING, &tuning);
			os << tuning;
			return os.str();
		case __SPEEX_VBR_MAX_BITRATE:
			spx_int32_t maxbitrate;
			speex_encoder_ctl(encoder->state, SPEEX_GET_VBR_MAX_BITRATE,
					&maxbitrate);
			os << maxbitrate;
			return os.str();
		case __SPEEX_HIGHPASS:
			spx_int32_t highpass;
			speex_encoder_ctl(encoder->state, SPEEX_GET_HIGHPASS, &highpass);
			os << highpass;
			return os.str();
		default:
			throw OperationNotSupportedException("param not supported");
		}
		break;
	case __DECODER_OPT:
		if (!decoder)
			throw OperationNotPerfomedException("decoder not initialized");

		switch (secondaryInfo) {
		case __SPEEX_ENH:
			spx_int32_t enh;
			speex_decoder_ctl(decoder->state, SPEEX_GET_ENH, &enh);
			os << enh;
			return os.str();
		case __SPEEX_FRAME_SIZE:
			spx_int32_t framesize;
			speex_decoder_ctl(decoder->state, SPEEX_GET_FRAME_SIZE, &framesize);
			os << framesize;
			return os.str();
		case __SPEEX_BITRATE:
			spx_int32_t bitrate;
			speex_decoder_ctl(decoder->state, SPEEX_GET_BITRATE, &bitrate);
			os << bitrate;
			return os.str();
		case __SPEEX_SAMPLING_RATE:
			spx_int32_t samplingrate;
			speex_decoder_ctl(decoder->state, SPEEX_GET_SAMPLING_RATE,
					&samplingrate);
			os << samplingrate;
			return os.str();
		case __SPEEX_HIGHPASS:
			spx_int32_t highpass;
			speex_decoder_ctl(decoder->state, SPEEX_GET_HIGHPASS, &highpass);
			os << highpass;
			return os.str();
		default:
			throw OperationNotSupportedException("param not supported");
		}
		break;
	case __PREPROCESS_OPT:
		if (!preprocess)
			throw OperationNotPerfomedException("Preprocess not initialized");
		switch (secondaryInfo) {
		case __SPEEX_PREPROCESS_DENOISE:
			spx_int32_t denoise;
			speex_preprocess_ctl(preprocess, SPEEX_PREPROCESS_GET_DENOISE,
					&denoise);
			os << denoise;
			return os.str();
		case __SPEEX_PREPROCESS_AGC:
			spx_int32_t agc;
			speex_preprocess_ctl(preprocess, SPEEX_PREPROCESS_GET_AGC, &agc);
			os << agc;
			return os.str();
		case __SPEEX_PREPROCESS_AGC_LEVEL:
			float agclevel;
			speex_preprocess_ctl(preprocess, SPEEX_PREPROCESS_GET_AGC_LEVEL,
					&agclevel);
			os << agclevel;
			return os.str();
		case __SPEEX_PREPROCESS_DEREVERB:
			spx_int32_t dereverb;
			speex_preprocess_ctl(preprocess, SPEEX_PREPROCESS_GET_DEREVERB,
					&dereverb);
			os << dereverb;
			return os.str();
		case __SPEEX_PREPROCESS_DEREVERB_LEVEL:
			spx_int32_t dereverblevel;
			speex_preprocess_ctl(preprocess,
					SPEEX_PREPROCESS_GET_DEREVERB_LEVEL, &dereverblevel);
			os << dereverblevel;
			return os.str();
		case __SPEEX_PREPROCESS_DEREVERB_DECAY:
			spx_int32_t dereverbdecay;
			speex_preprocess_ctl(preprocess,
					SPEEX_PREPROCESS_GET_DEREVERB_DECAY, &dereverbdecay);
			os << dereverbdecay;
			return os.str();
		case __SPEEX_PREPROCESS_PROB_START:
			spx_int32_t probstart;
			speex_preprocess_ctl(preprocess, SPEEX_PREPROCESS_GET_PROB_START,
					&probstart);
			os << probstart;
			return os.str();
		case __SPEEX_PREPROCESS_PROB_CONTINUE:
			spx_int32_t probcontinue;
			speex_preprocess_ctl(preprocess,
					SPEEX_PREPROCESS_GET_PROB_CONTINUE, &probcontinue);
			os << probcontinue;
			return os.str();
		case __SPEEX_PREPROCESS_NOISE_SUPRESS:
			spx_int32_t noisesupress;
			speex_preprocess_ctl(preprocess,
					SPEEX_PREPROCESS_GET_NOISE_SUPPRESS, &noisesupress);
			os << noisesupress;
			return os.str();
		case __SPEEX_PREPROCESS_ECHO_SUPRESS:
			spx_int32_t echosupress;
			speex_preprocess_ctl(preprocess,
					SPEEX_PREPROCESS_GET_ECHO_SUPPRESS, &echosupress);
			os << echosupress;
			return os.str();
		case __SPEEX_PREPROCESS_ECHO_SUPRESS_ACTIVE:
			spx_int32_t echosupressactive;
			speex_preprocess_ctl(preprocess,
					SPEEX_PREPROCESS_GET_ECHO_SUPPRESS_ACTIVE,
					&echosupressactive);
			os << echosupressactive;
			return os.str();
//		case __SPEEX_PREPROCESS_ECHO_STATE:  For now, it just disabled. Use enable/disable echo cancellation instead
//			spx_int32_t echostate;
//			speex_preprocess_ctl(preprocess, SPEEX_PREPROCESS_GET_ECHO_STATE,
//					&echostate);
//			os << echostate;
//			return os.str();
		default:
			throw OperationNotSupportedException("Invalid Option in preprocess");

		}

	default:
		throw OperationNotSupportedException("param not supported");
	};

}

void SpeexPlugin::adaptStream(std::string paramName, std::map<std::string,
		std::string> &params) throw (OperationNotPerfomedException,
		OperationNotSupportedException) {
	MessageType mainInfo = constants[paramName];
	switch (mainInfo) {
	case __ENCODER_OPT:
		if (!encoder)
			throw OperationNotPerfomedException("encoder not initialized");
		for (std::map<std::string, std::string>::iterator it = params.begin(); it
				!= params.end(); it++) {
			MessageType second = constants[it->first];
			std::istringstream is(it->first);
			switch (second) {
			case __SPEEX_QUALITY:
				spx_int32_t quality;
				is >> quality;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: quality");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_QUALITY,
						&quality))
					throw OperationNotPerfomedException(
							"Problem in set quality property");
				break;
			case __SPEEX_MODE:
				spx_int32_t mode;
				is >> mode;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: mode");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_MODE, &mode))
					throw OperationNotPerfomedException(
							"Problem in set mode property");
				break;
			case __SPEEX_VBR:
				spx_int32_t vbr;
				is >> vbr;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: vbr");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_VBR, &vbr))
					throw OperationNotPerfomedException(
							"Problem in set vbr property");
				break;
			case __SPEEX_VBR_QUALITY:
				float vbrquality;
				is >> vbrquality;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: vbrquality");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_VBR,
						&vbrquality))
					throw OperationNotPerfomedException(
							"Problem in set vbrquality property");
				break;
			case __SPEEX_COMPLEXITY:
				spx_int32_t complexity;
				is >> complexity;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: complexity");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_COMPLEXITY,
						&complexity))
					throw OperationNotPerfomedException(
							"Invalid parameter: complexity");
				break;
			case __SPEEX_BITRATE:
				spx_int32_t bitrate;
				is >> bitrate;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: complexity");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_BITRATE,
						&bitrate))
					throw OperationNotPerfomedException(
							"Invalid parameter: bitrate");
				break;
			case __SPEEX_SAMPLING_RATE:
				spx_int32_t samplingrate;
				is >> samplingrate;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: samplingrate");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_SAMPLING_RATE,
						&samplingrate))
					throw OperationNotPerfomedException(
							"Invalid parameter: bitsamplingraterate");
				break;
			case __SPEEX_RESET_STATE:
				speex_encoder_ctl(encoder->state, SPEEX_RESET_STATE, 0);
				break;
			case __SPEEX_VAD:
				spx_int32_t vad;
				is >> vad;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: vad");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_VAD, &vad))
					throw OperationNotPerfomedException(
							"Invalid parameter: vad");
				break;
			case __SPEEX_DTX:
				spx_int32_t dtx;
				is >> dtx;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: dtx");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_DTX, &dtx))
					throw OperationNotPerfomedException(
							"Invalid parameter: dtx");
				break;
			case __SPEEX_ABR:
				spx_int32_t abr;
				is >> abr;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: abr");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_ABR, &abr))
					throw OperationNotPerfomedException(
							"Invalid parameter: abr");
				break;
			case __SPEEX_PLC_TUNING:
				spx_int32_t plc;
				is >> plc;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: plc");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_PLC_TUNING,
						&plc))
					throw OperationNotPerfomedException(
							"Invalid parameter: plc");
				break;
			case __SPEEX_VBR_MAX_BITRATE:
				spx_int32_t vbrmaxbitrate;
				is >> vbrmaxbitrate;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: vbrmaxbitrate");
				if (speex_encoder_ctl(encoder->state,
						SPEEX_SET_VBR_MAX_BITRATE, &vbrmaxbitrate))
					throw OperationNotPerfomedException(
							"Invalid parameter: vbrmaxbitrate");
				break;
			case __SPEEX_HIGHPASS:
				spx_int32_t highpass;
				is >> highpass;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: highpass");
				if (speex_encoder_ctl(encoder->state, SPEEX_SET_HIGHPASS,
						&highpass))
					throw OperationNotPerfomedException(
							"Invalid parameter: highpass");
				break;
			default:
				throw OperationNotSupportedException();
			}
		}
		break;
	case __DECODER_OPT:
		if (!decoder)
			throw OperationNotPerfomedException("decoder not initialized");
		for (std::map<std::string, std::string>::iterator it = params.begin(); it
				!= params.end(); it++) {
			MessageType second = constants[it->first];
			std::istringstream is(it->first);

			switch (second) {
			case __SPEEX_ENH:
				spx_int32_t enh;
				is >> enh;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: enh");
				if (speex_decoder_ctl(decoder->state, SPEEX_SET_ENH, &enh))
					throw OperationNotPerfomedException(
							"Invalid parameter: enh");
				break;
			case __SPEEX_SAMPLING_RATE:
				spx_int32_t samplingrate;
				is >> samplingrate;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: samplingrate");
				if (speex_decoder_ctl(decoder->state, SPEEX_SET_SAMPLING_RATE,
						&samplingrate))
					throw OperationNotPerfomedException(
							"Invalid parameter: bitsamplingraterate");
				break;
			case __SPEEX_RESET_STATE:
				speex_decoder_ctl(decoder->state, SPEEX_RESET_STATE, 0);
				break;
			case __SPEEX_HIGHPASS:
				spx_int32_t highpass;
				is >> highpass;
				if (is.fail())
					throw OperationNotPerfomedException(
							"Invalid parameter: highpass");
				if (speex_decoder_ctl(decoder->state, SPEEX_SET_HIGHPASS,
						&highpass))
					throw OperationNotPerfomedException(
							"Invalid parameter: highpass");
				break;
			default:
				throw OperationNotSupportedException();

			}

		}
		break;
	default:
		throw OperationNotSupportedException();
	};
}

const char* SpeexPlugin::getName() const {
	return "SpeexPlugin";
}

void SpeexPlugin::buildEncoder(std::string modeName)
		throw(OperationNotPerfomedException) {
	if (encoder)
		throw OperationNotPerfomedException("The encoder already exists. "
			"Please call endEncoder before perform this task");

	SpeexMode mode = getMode(modeName);
	if(mode == INVALID_MODE)
		throw OperationNotPerfomedException("Invalid Mode");

	encoder = new HalfCodec;
	encoder->mode = mode;
	speex_bits_init(&encoder->bits);

	switch (mode) {
	case MODE_NB:
		encoder->state = speex_encoder_init(&speex_nb_mode);
		break;
	case MODE_WB:
		encoder->state = speex_encoder_init(&speex_wb_mode);
		break;
	case MODE_UWB:
		encoder->state = speex_encoder_init(&speex_uwb_mode);
		break;
	};
}
void SpeexPlugin::buildDecoder(std::string modeName)
		throw(OperationNotPerfomedException) {
	if (decoder)
		throw OperationNotPerfomedException("The decoder already exists. "
			"Please call endDecoder before perform this task");

	SpeexMode mode = getMode(modeName);
	if(mode == INVALID_MODE)
		throw OperationNotPerfomedException("Invalid Mode");

	decoder = new HalfCodec;
	decoder->mode = mode;
	speex_bits_init(&decoder->bits);

	switch (mode) {
	case MODE_NB:
		decoder->state = speex_decoder_init(&speex_nb_mode);
		break;
	case MODE_WB:
		decoder->state = speex_decoder_init(&speex_wb_mode);
		break;
	case MODE_UWB:
		decoder->state = speex_decoder_init(&speex_uwb_mode);
		break;
	};
}

void SpeexPlugin::destroyEncoder() throw(OperationNotPerfomedException) {
	if (!encoder)
		throw OperationNotPerfomedException("Encoder already destroyed");
	speex_encoder_destroy(encoder->state);

	speex_bits_destroy(&encoder->bits);

	delete encoder;
	encoder = 0;
}
void SpeexPlugin::destroyDecoder() throw(OperationNotPerfomedException) {
	if (!decoder)
		throw OperationNotPerfomedException("Decoder already destroyed");

	speex_decoder_destroy(decoder->state);

	speex_bits_destroy(&decoder->bits);

	delete decoder;
	decoder = 0;
}

uint16 SpeexPlugin::encode(int16 *sample_buf, uint16 nsamples, uint8 *payload,
		uint16 payload_size, bool &silence)
		throw(OperationNotPerfomedException) {

	if (payload_size < MAX_PAYLOAD_SIZE)
		throw OperationNotPerfomedException("The buffer is not large enough");

	if (!encoder)
		throw OperationNotPerfomedException("Encoder not ready");

	// Falta fazer o echo cancelling

	bool preprocessing_silence = false;
	if (preprocess) {
		preprocessing_silence = !speex_preprocess_run(preprocess, sample_buf); //Garantir que o nsamples sera sempre o mesmo
		bool speex_dsp_vad;
		speex_preprocess_ctl(preprocess, SPEEX_PREPROCESS_GET_VAD,
				&speex_dsp_vad);
		if (!speex_dsp_vad)
			preprocessing_silence = false;
	}

	silence = false;
	speex_bits_reset(&encoder->bits);

	silence = speex_encode_int(encoder->state, sample_buf, &encoder->bits) == 0;

	silence = silence || preprocessing_silence;

	return speex_bits_write(&encoder->bits, (char *) payload, payload_size);

}

uint16 SpeexPlugin::decode(uint8 *payload, uint16 payload_size, int16 *pcm_buf,
		uint16 pcm_buf_size) throw(OperationNotPerfomedException) {
	int retval;
	int speex_frame_size;

	speex_decoder_ctl(decoder->state, SPEEX_GET_FRAME_SIZE, &speex_frame_size);

	if (pcm_buf_size < speex_frame_size)
		throw OperationNotPerfomedException("The buffer is not large enough");

	speex_bits_read_from(&decoder->bits, reinterpret_cast<char *> (payload),
			payload_size);
	retval = speex_decode_int(decoder->state, &decoder->bits, pcm_buf);

	if (retval < 0) {
		throw OperationNotPerfomedException("Error on decode frame");
	}

	return speex_frame_size;
}

uint16 SpeexPlugin::getEncodingSampleRate() const
		throw(OperationNotPerfomedException) {
	if (!encoder)
		throw OperationNotPerfomedException("Encoder not initialized");
	spx_int32_t sample;
	speex_encoder_ctl(encoder->state, SPEEX_GET_SAMPLING_RATE, &sample);
	return sample;
}

uint16 SpeexPlugin::getDecodingSampleRate() const
		throw(OperationNotPerfomedException) {
	if (!decoder)
		throw OperationNotPerfomedException("Decoder not initialized");
	spx_int32_t sample;
	speex_decoder_ctl(decoder->state, SPEEX_GET_SAMPLING_RATE, &sample);
	return sample;
}

uint16 SpeexPlugin::getEncodingPtime() const {
	return PTIME_SPEEX;
}

uint16 SpeexPlugin::getDecodingPtime() const {
	return PTIME_SPEEX;
}

bool SpeexPlugin::enablePreprocessing() throw (OperationNotPerfomedException) {
	if (!encoder)
		throw OperationNotPerfomedException("Encoder not initialized");
	uint16 sampleRate = getEncodingSampleRate();

	this->preprocess = speex_preprocess_state_init(sampleRate / 1000 * getEncodingPtime(),
			sampleRate);

	return true;
}

bool SpeexPlugin::disablePreprocessing() throw(OperationNotPerfomedException) {
	if(preprocess) {
		speex_preprocess_state_destroy(preprocess);
		return true;
	}
	return false;
}

uint16 SpeexPlugin::getMaxPayloadSize() const {
	return MAX_PAYLOAD_SIZE;
}

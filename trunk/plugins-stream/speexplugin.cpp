/*
 * speexplugin.cpp
 *
 *  Created on: 11/01/2010
 *      Author: ivocalado
 */

#include "speexplugin.h"
#include <ostream>

SpeexPlugin::SpeexPlugin() {
	initConstants();
	encoderPtr = 0;
	decoderPtr = 0;
}

void SpeexPlugin::initConstants() {
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
}

SpeexPlugin::~SpeexPlugin() {
}

std::string SpeexPlugin::retrievePluginInformation(std::string info,
		std::string subInfo) throw (OperationNotSupportedException,
		OperationNotPerfomedException) {
	MessageType mainInfo = constants[info];
	MessageType secondaryInfo = constants[subInfo];

	switch (mainInfo) {
	case __ENCODER_OPT:
		if (encoderPtr)
			switch (secondaryInfo) {
			case __SPEEX_FRAME_SIZE:
				break;
			case __SPEEX_QUALITY:
				break;
			case __SPEEX_MODE:
				break;
			case __SPEEX_VBR:
				break;
			case __SPEEX_VBR_QUALITY:
				break;
			case __SPEEX_COMPLEXITY:
				break;
			case __SPEEX_BITRATE:
				break;
			case __SPEEX_SAMPLING_RATE:
				break;
			case __SPEEX_RESET_STATE:
				break;
			case __SPEEX_VAD:
				break;
			case __SPEEX_DTX:
				break;
			case __SPEEX_ABR:
				break;
			case __SPEEX_PLC_TUNING:
				break;
			case __SPEEX_VBR_MAX_BITRATE:
				break;
			case __SPEEX_HIGHPASS:
				break;

			default:
				throw OperationNotSupportedException("param not supported");
			}
		else
			throw OperationNotPerfomedException("encoder not inicialized");
		break;
	case __DECODER_OPT:
		if (decoderPtr)
			switch (secondaryInfo) {
			case __SPEEX_ENH:
				spx_int32_t enh;
				speex_decoder_ctl(decoderPtr, SPEEX_GET_ENH, &enh);
				std::ostringstream os;
				os<<enh;
				return os.str();
			case __SPEEX_FRAME_SIZE:
				break;
			case __SPEEX_BITRATE:
				break;
			case __SPEEX_SAMPLING_RATE:
				break;
			case __SPEEX_RESET_STATE:
				break;
			case __SPEEX_HIGHPASS:
				break;

			default:
				throw OperationNotSupportedException("param not supported");
			}
		else
			throw OperationNotPerfomedException("decoder not inicialized");
		break;

	default:
		throw OperationNotSupportedException("param not supported");
	};

}

void SpeexPlugin::adaptStream(std::string paramName, std::map<std::string,
		std::string> &params) throw (OperationNotPerfomedException) {
}

const char* SpeexPlugin::getName() const {
	return "StreamPlugin";
}

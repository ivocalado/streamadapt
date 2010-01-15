/*
 * speexplugin.h
 *
 *  Created on: 11/01/2010
 *      Author: ivocalado
 */

#ifndef SPEEXPLUGIN_H_
#define SPEEXPLUGIN_H_

#include <plugins/pluginsfactory.h>
#include <string>

#include "plugindefinitions.h"
#include <map>
#include <speex/speex.h>
#include <speex/speex_types.h>
#include <speex/speex_preprocess.h>

class SpeexPlugin : public PluginStreamIF {
	enum SpeexMode {
		MODE_NB,	// Narrow band
		MODE_WB,	// Wide band
		MODE_UWB	// Ultra wide band
	};

	struct HalfCodec {
		SpeexMode mode;
		SpeexBits bits;
		void* state;
	};

	map<std::string, MessageType> constants;
	void initConstants();
	HalfCodec* encoder;
	HalfCodec* decoder;
	SpeexPreprocessState* preprocess;
//	void* encoderPtr; //encoder
//	void* decoderPtr; //decoder
//	SpeexPreprocessState* preprocess; //preprocess
//	SpeexBits encoderBits;
//	SpeexBits decoderBits;
	void buildEncoder(SpeexMode mode) throw(OperationNotPerfomedException);
	void buildDecoder(SpeexMode mode) throw(OperationNotPerfomedException);

	void destroyEncoder() throw(OperationNotPerfomedException);
	void destroyDecoder() throw(OperationNotPerfomedException);
public:
	SpeexPlugin();
	virtual ~SpeexPlugin();

	virtual std::string retrievePluginInformation(std::string info, std::string subInfo = "")
				throw (OperationNotSupportedException, OperationNotPerfomedException);

	virtual void adaptStream(std::string paramName, std::map<std::string,
			std::string> &params)
				throw (OperationNotPerfomedException, OperationNotSupportedException);


	virtual uint16 encode(int16 *sample_buf, uint16 nsamples, uint8 *payload,
			uint16 payload_size, bool &silence) throw(OperationNotPerfomedException);

	virtual uint16 decode(uint8 *payload, uint16 payload_size, int16 *pcm_buf,
			uint16 pcm_buf_size) throw(OperationNotPerfomedException);

	virtual const char* getName() const;
};

#endif /* SPEEXPLUGIN_H_ */

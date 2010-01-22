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

class SpeexPlugin: public PluginStreamIF {

	enum SpeexMode {
		INVALID_MODE, MODE_NB, // Narrow band
		MODE_WB, // Wide band
		MODE_UWB
	// Ultra wide band
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
	//	SpeexEchoState* echocancellation;
	//	bool usingEchoCancellation;
	//	bool echoCapturedLast;


	void buildEncoder(std::string mode) throw(OperationNotPerfomedException);
	void buildDecoder(std::string mode) throw(OperationNotPerfomedException);
	SpeexMode getMode(std::string modeName);

	bool destroyEncoder() throw(OperationNotPerfomedException);
	bool destroyDecoder() throw(OperationNotPerfomedException);
public:

	SpeexPlugin();
	virtual ~SpeexPlugin();

	void buildSession(StreamType type, std::string codecName, bool enablePreprocessing);

	virtual void endSession();

	virtual std::string retrievePluginInformation(std::string info,
			std::string subInfo = "") throw (OperationNotSupportedException,
			OperationNotPerfomedException);

	virtual void adaptStream(std::string paramName, std::map<std::string,
			std::string> &params) throw (OperationNotPerfomedException,
			OperationNotSupportedException);

	virtual uint16 encode(int16 *sample_buf, uint16 nsamples, uint8 *payload,
			uint16 payload_size, bool &silence)
			throw(OperationNotPerfomedException);

	virtual uint16 decode(uint8 *payload, uint16 payload_size, int16 *pcm_buf,
			uint16 pcm_buf_size) throw(OperationNotPerfomedException);

	virtual uint16 getEncodingPtime() const;

	virtual uint16 getDecodingPtime() const;

	uint16 getEncodingSampleRate() const throw(OperationNotPerfomedException);

	virtual uint16 getDecodingSampleRate(void) const
			throw(OperationNotPerfomedException);

	virtual uint16 getMaxPayloadSize() const;

	/**
	 * Enable preprocessing step. If plugin doesn't support,
	 * just return false. It throws an exception if the state
	 * is invalid to make this operation
	 */
	virtual bool enablePreprocessing() throw (OperationNotPerfomedException);

	/**
	 * disable preprocessing step. If plugin doesn't support,
	 * just return false. It throws an exception if the state
	 * is invalid to make this operation
	 */
	virtual bool disablePreprocessing() throw(OperationNotPerfomedException);

	/**
	 * Enable echocancelling step. If plugin doesn't support,
	 * just return false. It throws an exception if the state
	 * is invalid to make this operation
	 */
	virtual bool enableEchoCancelling() throw(OperationNotPerfomedException) {
		return false;
	}

	/**
	 * Disable echocancelling step. If plugin doesn't support,
	 * just return false. It throw an exception if the state
	 * is invalid to make this operation
	 */
	virtual bool disableEchoCancelling() throw (OperationNotPerfomedException) {
		return false;
	}

	virtual uint32 getSampleSize();

	virtual const char* getName() const;
};

#endif /* SPEEXPLUGIN_H_ */

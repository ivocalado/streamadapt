/*
 * plugindefinitions.h
 *
 *  Created on: 22/12/2009
 *      Author: ivocalado
 */

#ifndef PLUGINDEFINITIONS_H_
#define PLUGINDEFINITIONS_H_

static const char* PLUGIN_NAME = "DCCPSocketPlugin";
static const char* PLUGIN_DESCRIPTION =
		"This plugin provides a transmission channel"
			"using DCCP transport protocol. Also, it enables adaptation process";
static const char* SDESITEM = "SDESItem";
static const char* SDESITEMTYPE = "SDESItemType";
static const char* EXPIRE_TIMEOUT = "ExpireTimeout";
static const char* SCHEDULING_TIMEOUT = "SchedulingTimeout";
static const char* PAYLOAD_FORMAT = "PayloadFormat";
static const char* CURRENT_RTP_CLOCK_RATE = "CurrentRTPClockRate";

static const char* DCCP_TX_CCID = "DCCPTXCCID";
static const char* DCCP_RX_CCID = "DCCPRXCCID";
static const char* DCCP_TX_QUEUELEN = "DCCPTXQUEUELEN";
static const char* DCCP_TX_POLICYID = "DCCPTXPOLICYID";



#endif /* PLUGINDEFINITIONS_H_ */

/**
 * BS2InputConfig.h
 *
 *  Created on: 2015. 3. 16.
 *      Author: yhlee
 */

/*
 *  Copyright (c) 2014 Suprema Co., Ltd. All Rights Reserved.
 *
 *  This software is the confidential and proprietary information of
 *  Suprema Co., Ltd. ("Confidential Information").  You shall not
 *  disclose such Confidential Information and shall use it only in
 *  accordance with the terms of the license agreement you entered into
 *  with Suprema.
 */
 
#ifndef __BS2_INPUT_CONFIG_H__
#define __BS2_INPUT_CONFIG_H__

#include "../BS2Types.h"


enum{
	BS2_MAX_INPUT_NUM =	8,
	BS2_MAX_INPUT_NUM_EX = 16,
};

enum{
	BS2_INPUT_TYPE_NORMAL,
	BS2_INPUT_TYPE_SUPERVISERD,
};

typedef struct{
	uint16_t	minValue; 	///< 0 ~ 3300 (0 ~ 3.3v)
	uint16_t	maxValue;	///< 0 ~ 3300 (0 ~ 3.3v)
} BS2SVInputRange;

/**
 *	BS2SupervisedInputConfig
 */
typedef struct {
	BS2SVInputRange shortInput;
	BS2SVInputRange openInput;
	BS2SVInputRange onInput;
	BS2SVInputRange offInput;
} BS2SupervisedInputConfig; /// < 16


enum{
	SUPERVISED_REG_1K = 0,
	SUPERVISED_REG_2_2K,
	SUPERVISED_REG_4_7K,
	SUPERVISED_REG_10K,

	SUPERVISED_REG_UNUSED = 254,
	SUPERVISED_REG_CUSTOM = 255,
};

enum {
	BS2_INPUT_NONE = 0,
	BS2_INPUT_AUX0 = 1,
	BS2_INPUT_AUX1 = 2,
	BS2_INPUT_AUXTYPENO = 0,
	BS2_INPUT_AUXTYPENC = 1,
};

/**
 *	BS2InputConfig
 */
typedef struct{
	uint8_t		numInputs;		///< 1 byte
	uint8_t		numSupervised;	///< 1 byte
	
	union {
		uint16_t value;			///< 2 byte
		struct {
			uint16_t tamperAuxIndex : 4;
			uint16_t acFailAuxIndex : 4;
			uint16_t aux0Type : 1;
			uint16_t aux1Type : 1;
			uint16_t reserved : 6;
		} field;
	} aux;

	struct {
		uint8_t		portIndex;				///< 1 byte
		BS2_BOOL	enabled;				///< 1 byte
		uint8_t		supervised_index;		///< 1 byte

		uint8_t		reserved[5];			///< 5 byte

		BS2SupervisedInputConfig	config; ///< 16 byte
	} supervised_inputs[BS2_MAX_INPUT_NUM]; ///<
} BS2InputConfig;

/**
 *	BS2InputConfigEx
 */
typedef struct{
	uint8_t		numInputs;		///< 1 byte
	uint8_t		numSupervised;	///< 1 byte
	uint8_t		reserved[18];	///< 18 bytes
	
	struct {
		uint8_t						portIndex;				///< 1 byte
		BS2_SWITCH_TYPE				switchType;				///< 1 byte
		uint16_t					duration;				///< 2 bytes
		
		uint8_t						reserved;				///< 1 byte
		uint8_t						supervisedResistor;		///< 1 byte
		uint8_t						reserved1[16];			///< 16 bytes
		
		uint8_t						reserved2[26];			///< 26 bytes
	} inputs[BS2_MAX_INPUT_NUM_EX]; 						///< 768 bytes

	uint8_t		reserved2[200];								///< 200 bytes
} BS2InputConfigEx;											///< 988 bytes

#endif	/* __BS2_INPUT_CONFIG_H__ */

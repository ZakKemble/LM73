/*
 * Project: LM73 Temperature Sensor Library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: https://github.com/zkemble/LM73
 */

#ifndef LM73_DEFS_H_
#define LM73_DEFS_H_

// Config reg bits
#define LM73_BIT_ONE_SHOT		0x04

// Control/status reg bits
#define LM73_BIT_ALRT_STAT		0x08
#define LM73_BIT_THI_FLAG		0x04
#define LM73_BIT_TLOW_FLAG		0x02
#define LM73_BIT_DAV_FLAG		0x01

//#define LM73_BIT_STATUS			0x0F

// Registers
#define LM73_REG_TEMPERATURE	0x00
#define LM73_REG_CONFIG			0x01
#define LM73_REG_THI			0x02
#define LM73_REG_TLOW			0x03
#define LM73_REG_CTRLSTATUS		0x04
#define LM73_REG_ID				0x05

// Register masks
// Config
#define LM73_MASK_PD			~(LM73_POWER_OFF | LM73_POWER_ON)
#define LM73_MASK_ALRT_EN		~()
#define LM73_MASK_ALRT_POL		~()
#define LM73_MASK_ALRT_RST		~()

// Control/status
#define LM73_MASK_TO_DIS		~()
#define LM73_MASK_RESOLUTION	~(LM73_RESOLUTION_11BIT | LM73_RESOLUTION_12BIT | LM73_RESOLUTION_13BIT | LM73_RESOLUTION_14BIT)

#endif /* LM73_DEFS_H_ */
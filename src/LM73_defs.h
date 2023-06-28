/*
 * Project: LM73 Temperature Sensor Library
 * Author: Zak Kemble
 * Copyright: (C) 2023 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: https://github.com/ZakKemble/LM73
 */

#ifndef LM73_DEFS_H_
#define LM73_DEFS_H_

// Config reg bits
#define LM73_BIT_ONE_SHOT		2
#define LM73_BIT_ALRT_RST		3
#define LM73_BIT_ALRT_POL		4
#define LM73_BIT_ALRT_EN		5
#define LM73_BIT_PWR_DOWN		7

// Control/status reg bits
#define LM73_BIT_TIMEOUT_DIS	7
#define LM73_BIT_TEMP_RES		5
#define LM73_BIT_DAV_FLAG		0

// Registers
#define LM73_REG_TEMPERATURE	0x00
#define LM73_REG_CONFIG			0x01
#define LM73_REG_THI			0x02
#define LM73_REG_TLOW			0x03
#define LM73_REG_CTRLSTATUS		0x04
#define LM73_REG_ID				0x05

#endif /* LM73_DEFS_H_ */

/*
 * Copyright 2018-21 CEVA, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License and 
 * any applicable agreements you may have with CEVA, Inc.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*  Modified 10/27/2023 by C. A. Ford
 *
 *  Changed the address used in dfu_hal_init(void)
 *  from ADDR_SH2_0 to ADDR_SH2_1 to be compatible with
 *  the Sparkfun BNO086 VR IMU Breakout board.
 */

/*
 * I2C HAL for BNO08x
 */

#include "i2c_hal.h"

#define ADDR_SH2_0 (0x4A)
#define ADDR_SH2_1 (0x4B)
#define ADDR_BNODFU_0 (0x28)
#define ADDR_BNODFU_1 (0x29)

i2c_hal_t sh2_hal;
i2c_hal_t dfu_hal;

sh2_Hal_t *sh2_hal_init(void)
{
    // Get instance of i2c hal suitable for SH2 on BNO08x
    return shtp_i2c_hal_init(&sh2_hal, false, ADDR_SH2_1);
}

sh2_Hal_t *dfu_hal_init(void)
{
    // Get instance of i2c hal suitable for SH2 on BNO08x
    return bno_dfu_i2c_hal_init(&sh2_hal, true, ADDR_BNODFU_0);
}

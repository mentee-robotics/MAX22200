/** \file MAX22200_driver.h ***********************************************************
 * 
 *             Project: MAX22200 driver for 8-Channel Solenoid/Motor driver
 *            Filename: MAX22200_driver.h
 *         Description: This module is an embedded controller driver for the MAX22200
 *
 *                      This driver can be dropped into a user's application as a starting
 *                      point for development of an end application
 * 
 *    Revision History:
 *                    2021_07_21		Rev 0.01    Konrad Scheuer		File created
  *
 *  -------------------------------------------------------------------- */
  
/*******************************************************************************
* Copyright (C) Maxim Integrated Products, Inc., All rights Reserved.
*
* This software is protected by copyright laws of the United States and
* of foreign countries. This material may also be protected by patent laws
* and technology transfer regulations of the United States and of foreign
* countries. This software is furnished under a license agreement and/or a
* nondisclosure agreement and may only be used or reproduced in accordance
* with the terms of those agreements. Dissemination of this information to
* any party or parties not specified in the license agreement and/or
* nondisclosure agreement is expressly prohibited.
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
*******************************************************************************
*/
#include <cstdint>
#include <cstring>
#include "gpio.h"
#include "spi.h"
#ifndef MAX22200_DRIVER_HPP
#define MAX22200_DRIVER_HPP

// define MAX22514 register adresses
#define  MAX22200_STATUS      0x00
#define  MAX22200_CFG_CH_0    0x01
#define  MAX22200_CFG_CH_1    0x02
#define  MAX22200_CFG_CH_2    0x03
#define  MAX22200_CFG_CH_3    0x04
#define  MAX22200_CFG_CH_4    0x05
#define  MAX22200_CFG_CH_5    0x06
#define  MAX22200_CFG_CH_6    0x07
#define  MAX22200_CFG_CH_7    0x08
#define  MAX22200_FAULT       0x09
#define  MAX22200_CFG_DPM     0x0a



// Bit definitions

// Bit definitions for the Channels:

/* Half/Full-scale select                   */    #define BIT_CH_HFS       0x80000000
/* Bits for HOLD Current                    */    #define BIT_CH_HOLD      0x7f000000
/* Trigger select bit                       */    #define BIT_CH_TRGnSPI   0x00800000
/* Bits for HIT Current                     */    #define BIT_CH_HIT       0x007f0000
/* Bits for HIT Time                        */    #define BIT_CH_HIT_T     0x0000ff00
/* Current / Voltage drive select bit       */    #define BIT_CH_VDRnCDR   0x00000080
/* High- / Low- Side mode select bit        */    #define BIT_CH_HSnLS     0x00000040
/* Chopping Frequency configuration bits    */    #define BIT_CH_FREQ_CFG  0x00000030
/* Slew-rate control enable bit             */    #define BIT_CH_SRC       0x00000008
/* Open-load detection enable bit           */    #define BIT_CH_OL_EN     0x00000004
/* Detection of Plunger Movement enable bit */    #define BIT_CH_DPM_EN    0x00000002
/* HIT Current check enable bit             */    #define BIT_CH_HHF_EN    0x00000001
// Define the struct that represents the STATUS register
typedef struct {
    uint8_t ONCH[8];
    uint8_t M_OVT;
    uint8_t M_OCP;
    uint8_t M_OLF;
    uint8_t M_HHF;
    uint8_t M_DPM;
    uint8_t M_COMF;
    uint8_t M_UVM;
    uint8_t FREQM;
    uint8_t CM76[2];
    uint8_t CM54[2];
    uint8_t CM32[2];
    uint8_t CM10[2];
    uint8_t OVT;
    uint8_t OCP;
    uint8_t OLF;
    uint8_t HHF;
    uint8_t DPM;
    uint8_t COMER;
    uint8_t UVM;
    uint8_t ACTIVE;
} MAX22200_StatusReg;


// CS comands
#define MAX22200_CS_LOW    HAL_GPIO_WritePin(CS_DRV_GPIO_Port,  CS_DRV_Pin,  GPIO_PIN_RESET);
#define MAX22200_CS_HIGH   HAL_GPIO_WritePin(CS_DRV_GPIO_Port,  CS_DRV_Pin,  GPIO_PIN_SET);
#define MAX22200_CMD_LOW   HAL_GPIO_WritePin(DRV_CMD_GPIO_Port, DRV_CMD_Pin, GPIO_PIN_RESET);
#define MAX22200_CMD_HIGH  HAL_GPIO_WritePin(DRV_CMD_GPIO_Port, DRV_CMD_Pin, GPIO_PIN_SET);


#define MAX22200_ENABLE_LOW   HAL_GPIO_WritePin(DRV_ENABLE_GPIO_Port, DRV_ENABLE_Pin, GPIO_PIN_RESET);
#define MAX22200_ENABLE_HIGH  HAL_GPIO_WritePin(DRV_ENABLE_GPIO_Port, DRV_ENABLE_Pin, GPIO_PIN_SET);


// Trigger Pins
#define MAX22200_TRIGA_LOW   HAL_GPIO_WritePin(DRV_TRIGA_GPIO_Port, DRV_TRIGA_Pin, GPIO_PIN_RESET);
#define MAX22200_TRIGA_HIGH  HAL_GPIO_WritePin(DRV_TRIGA_GPIO_Port, DRV_TRIGA_Pin, GPIO_PIN_SET);
#define MAX22200_TRIGB_LOW   HAL_GPIO_WritePin(DRV_TRIGB_GPIO_Port, DRV_TRIGB_Pin, GPIO_PIN_RESET);
#define MAX22200_TRIGB_HIGH  HAL_GPIO_WritePin(DRV_TRIGB_GPIO_Port, DRV_TRIGB_Pin, GPIO_PIN_SET);







/* Definitions and structures remain the same */

class MAX22200 {
    private:
        uint8_t MAX22200_tx[16];  // SPI TX buffer
        uint8_t MAX22200_rx[16];  // SPI RX buffer

    public:
        MAX22200();
        void MAX22200_init(const MAX22200_StatusReg *statusReg);
        uint8_t  MAX22200_write_register(uint8_t reg_adr, uint32_t data);   // returns the status byte
        uint32_t MAX22200_read_register (uint8_t reg_adr);                  // returns the register content
        //********************************************************************
        //*
        //* Function:    MAX22200_Set_CH
        //* Description: Set's up one Channel for driving
        //*
        //* Input:
        //*               channel          1 - 8  -> Selected channel to setup (We're counting Board Channels !! NOT Chip Channels )
        //*               HalfScale        0 = FullScale      1 = HalfScale
        //*               HOLD_DutyCycle   0 = OFF sate,      1-126 duty-cycle     127 ON state
        //*               TRIG_pin         0 = SPI Control    1 = TrigPin Control
        //*               HIT_DutyCycle    0 = OFF sate,      1-126 duty-cycle     127 ON state
        //*               HIT_Time         0 = no Hit         1-254 x40/F_Chop     255 continuous HIT
        //*               V_Mode           0 = CurrentMode    1 = VoltageMode
        //*               HighSideMode     0 = LowSide Mode   1 = HighSide Mode
        //*               FREQ_CFG         0 = FreqMain/4     1 = FreqMain/3       2 = FreqMain/2  3 = FreqMain
        //*               SRC              0 = No Slew Ctrl   1 = Slew rate controlled
        //*               OL_EN            0 = No OpenLoadD   1 = Open Load detection enabled
        //*               DPM_EN           0 = No PlungerD    1 = Plunger movement detect enabled
        //*               HHF_EN           0 = No HitCurr Chk 1 = Hit Current Check enabled
        //*
        //* Output, none
        //*
        //*
        //********************************************************************/

        uint32_t MAX22200_Set_CH (uint8_t channel, uint8_t HalfScale, uint8_t HOLD_DutyCycle, uint8_t TRIG_pin, uint8_t HIT_DutyCycle,  uint8_t HIT_Time, uint8_t V_Mode, uint8_t HighSideMode, uint8_t FREQ_CFG, uint8_t SRC, uint8_t OL_EN, uint8_t DPM_EN, uint8_t HHF_EN);
        void MAX22200_print_all_registers ();
        uint32_t buildStatusRegister(const MAX22200_StatusReg* status);
        void update_status_register(MAX22200_StatusReg *statusReg, uint8_t ONCH[], uint8_t M_OVT, uint8_t M_OCP, uint8_t M_OLF, uint8_t M_HHF, uint8_t M_DPM, uint8_t M_COMF, uint8_t M_UVM, uint8_t FREQM, uint8_t CM76[], uint8_t CM54[], uint8_t CM32[], uint8_t CM10[], uint8_t OVT, uint8_t OCP, uint8_t OLF, uint8_t HHF, uint8_t DPM, uint8_t COMER, uint8_t UVM, uint8_t ACTIVE);
        void MAX22200_build_and_send_status_register(const MAX22200_StatusReg *statusReg);
};

#endif

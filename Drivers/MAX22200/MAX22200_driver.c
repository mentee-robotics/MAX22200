/** \file MAX22200_driver.c ***********************************************************
 * 
 *             Project: MAX22200 driver for 8-Channel Solenoid/Motor driver
 *            Filename: MAX22200_driver.c
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

#include <stdio.h>
#include "MAX22200_driver.h"


uint8_t MAX22200_tx[16];  // SPI TX buffer
uint8_t MAX22200_rx[16];  // SPI RX buffer


void MAX22200_init(const MAX22200_StatusReg *statusReg)
{
	// Enable the device
	MAX22200_ENABLE_HIGH

	// Make sure Channels aren't triggered
	MAX22200_TRIGA_LOW
	MAX22200_TRIGB_LOW

	MAX22200_CS_HIGH  // Make sure CS  pin is high
	MAX22200_CMD_LOW  // Make sure CMD pin is low

    MAX22200_write_register(MAX22200_STATUS, statusReg);
}



uint8_t  MAX22200_write_register(uint8_t reg_adr, uint32_t data)
{
    // first we need to writ the Command byte to setup the SPI transfer
	MAX22200_tx[0] = ((reg_adr<<1) & 0x7e) | 0x80;                    // MSB = 1 -> write - LSB = 0 -> 32 bit register access

	MAX22200_CMD_HIGH
	MAX22200_CS_LOW

	HAL_SPI_TransmitReceive(&hspi1, MAX22200_tx, MAX22200_rx, 1, 2);  // SPI RW 1 bytes

	MAX22200_CS_HIGH
	MAX22200_CMD_LOW

	// now we write the actual data
	MAX22200_tx[3] = ( data >> 24 ) & 0xff;   // MS Byte
	MAX22200_tx[2] = ( data >> 16 ) & 0xff;   //
	MAX22200_tx[1] = ( data >> 8  ) & 0xff;   //
	MAX22200_tx[0] = ( data       ) & 0xff;   // LS Byte

	MAX22200_CS_LOW

	HAL_SPI_Transmit(&hspi1, MAX22200_tx, 4, 2);                      // SPI W 4 bytes

	MAX22200_CS_HIGH

	return MAX22200_rx[0];                                            // return the status byte
}

uint32_t MAX22200_read_register (uint8_t reg_adr)
{
    // first we need to write the Command byte to setup the SPI transfer
	MAX22200_tx[0] = ((reg_adr<<1) & 0x7e);                           // MSB = 0 -> read - LSB = 0 -> 32 bit register access

	MAX22200_CMD_HIGH
	MAX22200_CS_LOW

	HAL_SPI_TransmitReceive(&hspi1, MAX22200_tx, MAX22200_rx, 1, 2);  // SPI RW 1 bytes

	// KSTODO - KS_TODO - we have a status byte available - should we return it in some way ??
#if 0 // debug
	printf ("MAX22000 Read Register 0x%02x - Status: 0x%02x    ", reg_adr, MAX22200_rx[0]);
#endif


	MAX22200_CS_HIGH
	MAX22200_CMD_LOW

	// For read the TX bytes aren't important, but we set them to 0...
	MAX22200_tx[0] = 0;   // MS Byte
	MAX22200_tx[1] = 0;   //
	MAX22200_tx[2] = 0;   //
	MAX22200_tx[3] = 0;   // LS Byte

	MAX22200_CS_LOW

	HAL_SPI_TransmitReceive(&hspi1, MAX22200_tx, MAX22200_rx, 4, 2);  // SPI Read 4 bytes

	MAX22200_CS_HIGH

	uint32_t result = (( MAX22200_rx[0] << 24 ) | ( MAX22200_rx[1] << 16 ) | ( MAX22200_rx[2] << 8  ) | ( MAX22200_rx[3] ));

	return result;
}





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
void MAX22200_Set_CH (uint8_t channel, uint8_t HalfScale, uint8_t HOLD_DutyCycle, uint8_t TRIG_pin, uint8_t HIT_DutyCycle,  uint8_t HIT_Time, uint8_t V_Mode, uint8_t HighSideMode, uint8_t FREQ_CFG, uint8_t SRC, uint8_t OL_EN, uint8_t DPM_EN, uint8_t HHF_EN)
{
	// Check the data if it makes sense
	if ((channel > 8) || (channel < 1))  return;
	if  (HalfScale       > 1)            return;
	if  (HOLD_DutyCycle  > 127)          return;
	if  (TRIG_pin        > 1)            return;
	if  (HIT_DutyCycle   > 127)          return;
	if  (HIT_Time        > 255)          return;
	if  (V_Mode          > 1)            return;
	if  (HighSideMode    > 1)            return;
	if  (FREQ_CFG        > 3)            return;
	if  (SRC             > 1)            return;
	if  (OL_EN           > 1)            return;
	if  (DPM_EN          > 1)            return;
	if  (HHF_EN          > 1)            return;

	// construct the 32-bit data
	uint32_t data  = 0;
	         data |= ((HalfScale      << 31) & BIT_CH_HFS);
	         data |= ((HOLD_DutyCycle << 24) & BIT_CH_HOLD);
	         data |= ((TRIG_pin       << 23) & BIT_CH_TRGnSPI);
	         data |= ((HIT_DutyCycle  << 16) & BIT_CH_HIT);
	         data |= ((HIT_Time       <<  8) & BIT_CH_HIT_T);

	         data |= ((V_Mode         <<  7) & BIT_CH_VDRnCDR);
	         data |= ((HighSideMode   <<  6) & BIT_CH_HSnLS);
	         data |= ((FREQ_CFG       <<  4) & BIT_CH_FREQ_CFG);
	         data |= ((SRC            <<  3) & BIT_CH_SRC);
	         data |= ((OL_EN          <<  2) & BIT_CH_OL_EN);
	         data |= ((DPM_EN         <<  1) & BIT_CH_DPM_EN);
	         data |= ((HHF_EN         <<  0) & BIT_CH_HHF_EN);

   MAX22200_write_register(channel, data);
}

//********************************************************************
//*
//* Function:    MAX22200_print_all_registers
//* Description: For debugging only - uses printf to print all registers contents
//*
//* Input:
//*         none
//*
//* Output: printf of all register contents
//*
//*
//********************************************************************/
void MAX22200_print_all_registers ()
{
	uint32_t result = 0;

	for (int i=0; i<11; i++)
	{
		result = MAX22200_read_register(i);
		printf ("MAX22000 reg 0x%02x - 0x%08lx\r\n", i, result);
	}


}


// Function to build STATUS register
uint32_t buildStatusRegister(const MAX22200_StatusReg* status) {
    uint32_t result = 0;

    result |= (*status->ONCH) << 24;
    result |= (status->M_OVT << 23) | (status->M_OCP << 22) | (status->M_OLF << 21) | (status->M_HHF << 20);
    result |= (status->M_DPM << 19) | (status->M_COMF << 18) | (status->M_UVM << 17) | (status->FREQM << 16);
    result |= (*status->CM76 << 14) | (*status->CM54 << 12) | (*status->CM32 << 10) | (*status->CM10 << 8);
    result |= (status->OVT << 7) | (status->OCP << 6) | (status->OLF << 5) | (status->HHF << 4);
    result |= (status->DPM << 3) | (status->COMER << 2) | (status->UVM << 1) | status->ACTIVE;

    return result;
}

void update_status_register(MAX22200_StatusReg *statusReg, uint8_t ONCH[], uint8_t M_OVT, uint8_t M_OCP, uint8_t M_OLF, uint8_t M_HHF, uint8_t M_DPM, uint8_t M_COMF, uint8_t M_UVM, uint8_t FREQM, uint8_t CM76[], uint8_t CM54[], uint8_t CM32[], uint8_t CM10[], uint8_t OVT, uint8_t OCP, uint8_t OLF, uint8_t HHF, uint8_t DPM, uint8_t COMER, uint8_t UVM, uint8_t ACTIVE)
{
    // Update the status struct
    memcpy(statusReg->ONCH, ONCH, sizeof(statusReg->ONCH));
    statusReg->M_OVT = M_OVT;
    statusReg->M_OCP = M_OCP;
    statusReg->M_OLF = M_OLF;
    statusReg->M_HHF = M_HHF;
    statusReg->M_DPM = M_DPM;
    statusReg->M_COMF = M_COMF;
    statusReg->M_UVM = M_UVM;
    statusReg->FREQM = FREQM;
    memcpy(statusReg->CM76, CM76, sizeof(statusReg->CM76));
    memcpy(statusReg->CM54, CM54, sizeof(statusReg->CM54));
    memcpy(statusReg->CM32, CM32, sizeof(statusReg->CM32));
    memcpy(statusReg->CM10, CM10, sizeof(statusReg->CM10));
    statusReg->OVT = OVT;
    statusReg->OCP = OCP;
    statusReg->OLF = OLF;
    statusReg->HHF = HHF;
    statusReg->DPM = DPM;
    statusReg->COMER = COMER;
    statusReg->UVM = UVM;
    statusReg->ACTIVE = ACTIVE;

    // Now call the function to build the register and transmit it via SPI
    MAX22200_build_and_send_status_register(statusReg);
}

void MAX22200_build_and_send_status_register(const MAX22200_StatusReg *statusReg) {

    // Build the status register
    uint32_t statusRegister = buildStatusRegister(statusReg);

    // Send the register via SPI
    MAX22200_write_register(MAX22200_STATUS, statusRegister);
}


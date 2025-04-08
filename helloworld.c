/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdlib.h>
#include "xparameters.h"		// �Ѽƶ�.
#include "xgpio.h"	// ²��PS��PL��GPIO�ާ@����Ʈw.

// �w�q��l�����
#define DEFAULT_DELAY 150
#define FAST_DELAY 40  // ���U���s�᪺���ְ{�{�t��

// �����.
void delay(int dly)
{
    int i, j;
    for (i = 0; i < dly; i++) {
    	for (j = 0; j < 0xffff; j++) {
    		;
        }
    }
}

// �D�{��.
int main()
{
    XGpio LED_XGpio, BTN_XGpio; // �ŧi�@��GPIO�Ϊ����c.
    int LED_num = 0b00000001;	// ��l�� LED0 �}��.
    int delay_time = DEFAULT_DELAY; // ��l�{�{�t��
    int btn_state = 0;  // ���s���A
    int direction = 1;  // ��V�ܼ�: 1 ��ܥ��V�]�q 0 �� 7�^�A-1 ��ܤϦV�]�q 7 �� 0�^

    XGpio_Initialize(&LED_XGpio, XPAR_AXI_GPIO_0_DEVICE_ID);	// ��l��LED_XGpio.
    XGpio_Initialize(&BTN_XGpio, XPAR_AXI_GPIO_1_DEVICE_ID);	// ��l��BTN_XGpio.

    XGpio_SetDataDirection(&LED_XGpio, 1, 0);	// LED �]����X
    XGpio_SetDataDirection(&BTN_XGpio, 1, 1);  // ���s�]����J

    printf("Start!!!\n");

    while(1) {
        // Ū�����s���A (�p�G���U, `btn_state` �|�� 1)
        btn_state = XGpio_DiscreteRead(&BTN_XGpio, 1);

        // �p�G���s���U�A��֩���ɶ� (�[�ְ{�{)
        if (btn_state) {
            delay_time = FAST_DELAY;
            printf("Button Pressed! Speeding up.\n");

        } else {
            delay_time = DEFAULT_DELAY;
        }

        // ��ܥثe��LED���A
        printf("LED_num = 0x%x\n", LED_num);

        // �N LED ���A��X�� GPIO
        XGpio_DiscreteWrite(&LED_XGpio, 1, LED_num);	// LED_XGpio�q�D,�eLED_num�ȶi�h.

        // �ھڤ�V����LED�{�{
        if (direction == 1) {
            // ���V (�q0��7)
            if (LED_num == 0b10000000) {  // �p�GLED�w�g��F7�A�}�l�ϦV
                direction = -1;
            } else {
                LED_num <<= 1;  // LED_num �����@��
            }
        } else {
            // �ϦV (�q7�^��0)
            if (LED_num == 0b00000001) {  // �p�GLED�w�g��F0�A�}�l���V
                direction = 1;
            } else {
                LED_num >>= 1;  // LED_num �k���@��
            }
        }

        // ����
        delay(delay_time);
    }

    return 0;
}

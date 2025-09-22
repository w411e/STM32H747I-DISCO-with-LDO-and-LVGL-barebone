# Original Repo
https://github.com/trteodor/stm32h747_disco_lvgl_bare_metal (cloned 2025.09.16)

## About This Repo
This repo was used to setup an STM32H747I-DISCO board with example programs implementing LVGL. The PLL speed is set to 480MHz (max) and the power is delivered with LDO not with SMPS! Bypass needs to be disabled. For SMPS look into original repo.

Be carefull which powersource you use. There are hardware pins to be changed for changing from SMPS to LDO! Look on the ST website for further infos about the pins, the layout and how to set things up and what the differences are.

## Changes for this repo
This Version changes the power delivery from **SMPS** to **LDO**. The hardware needs to be prepared for this. The standard delivery is SMPS, so if you change to LDO hardware changes are mandatory.

There might be changes in System.c that are needed to be done for LDO with high speed 480MHz PLL configuration. The following changes are collected from the reference manual. Some changes to VOS0 and power setup are significant and the µc got stuck inside the setup if not done properly. (p. 297 f.)

Furthermore I used different tools to build/debug this:

- Cortex-Debug (1.12.1)
- GNU Linker Map files (1.1.0)
- LinkerScript (1.0.4)
- STM32Cube:
	- clangd (0.2.0)
	- Debug Core (0.19.0)
	- Debug STLink GDB Server (0.10.1)
	- for Vusual Studio Code (2.1.1)
- windows-arm-none-eabi (0.1.6)

## Changes To Make It Run On My System
| File | Changed Code | Comment |
|------------------|------------------|------------------|
| System.c         | #define PWR_SUPPLY_CONFIG_MASK (PWR_CR3_LDOEN \| PWR_CR3_SMPSEN \| PWR_CR3_BYPASS) | SMPS and Bypass need to be cleared with MODIFY_REG() |
| System.c         | MODIFY_REG (PWR->CR3, PWR_SUPPLY_CONFIG_MASK, PWR_CR3_LDO) | changed from SMPS to LDO |
| System.c         | while(wait for LDO) | Waiting for status flag of power supply to be stable |
| System.c         | set RCC_APB4ENR_SYSCFGEN | Enable SYSCFG Clock |
| System.c         | set SYSCFG_PWRCR_ODEN | Enable overdrive to boost to VOS0 voltage level (480MHz enable) |
| System.c         | while(wait for VOS0) | VOS0 makro not actually used but waiting for overdrive |
| System.c         | while(__RCC_GET_FLAG(RCC_FLAG_PLLRDY) == 0U){} | After PLL config and PLL1ON change to waiting for rdy flag (wrong in repo) before: while(true) |
| System.c         | FLASH_ACR_LATENCY_7WS | 7 WS recommended for 480MHz by ST |
| System.c         | SystemCoreClockUpdate() | Might need to be added at end of PLL Setup (maybe tests with osci needed) |
| stm32h747xx.h    | // #define  SMPS | Commented SMPS out |
| jsons and others | -/- | changes to jsons and makefile not listed |

# Original README
## stm32h747_lvgl_master_yt
This is an repository created to become be a master of stm32h747-disco board

## Demo lvgl video / test:
   https://youtu.be/5MxftdVXUOgd

By default DSI HOST is configured in command mode, screen is divided into 10 ares to remove totally tearing effect.
For me obtained result is fine.

## QSPI
All used images by LVGL lib are stored in QSPI memory. QSPI is configured in memory mapped mode. Thanks to that it's possible to simply execute code directly from QSPI memory. Check Linker file - all lvgl image files are linked to QSPI memory adress space.

## LVGL SQUARE LINE
#Configured by default example is created using Square line studio.

https://squareline.io/

https://lvgl.io/


![LvglStudioScreenShot](https://github.com/trteodor/stm32h747_disco_lvgl_bare_metal/blob/master/Pictures/LvglStudioDemo.png)

![Discoh747board](https://github.com/trteodor/stm32h747_disco_lvgl_bare_metal/blob/master/Pictures/h747lvgl_Photo.jpg)

## PROJECT

To check changes history please call: "gitk&" in this project at him location to see changes in diffrent implementation states

This project was created only for educational purposes.
Created software is prepared for Board- DISCO-H747

* You are ready to start adventure with this examples when you have this tools in your environment (environment variables)!

    * arm-none-eabi-gcc 9.3.1
    * OpenOCD 0.11.0
    * make 4.2.1 / or 3.81
    * STM32_Programmer_CLI
    * Variable to STM32_CubeProgrammer: STM32_CubeProgrammerPATH eg. path: **D:\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin**


To clone this repo please use following command:
* git clone --recurse-submodules

Finally:

 **_Call "make" in this project at him location to compile provided example

You can call "make cubeF" to program MCU and external QSPI memory.

## Free icons
https://all-free-download.com/free-icon/pack-jpeg.html 
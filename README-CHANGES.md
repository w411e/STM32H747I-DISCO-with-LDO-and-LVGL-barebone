# Original Repo
https://github.com/trteodor/stm32h747_disco_lvgl_bare_metal (cloned 2025.09.16)

## Changes for this repo
This Version changes the power delivery from **SMPS** to **LDO**. The hardware needs to be prepared for this. The standard delivery is SMPS, so if you change to LDO hardware changes are mandatory.

## Changes To Make It Run On My System
| File | Changed Code | Comment |
|------------------|------------------|------------------|
| stm32h747xx.h    | PWR_CR3_LDOEN    | Just info, what’s added|
| System.c         | #define PWR_SUPPLY_CONFIG_MASK (PWR_CR3_LDOEN) | changed from SMPS to LDO |
| System.c         | MODIFY_REG (PWR->CR3, PWR_SUPPLY_CONFIG_MASK, PWR_CR3_LDO) | changed from SMPS to LDO |
| OTM8009A_wrapper.c | LTDC_LAYER(0)->CFBAR = (uint32_t)ActualBufferPointer… | typecast against error |
| lv_gpu_stm32_dma2d.c | uint32_t HAL_RCC_GetHCLKFreq(void); | function prototype |
| c_cpp_properties.json | arm-none-eabi-gcc | full path to vscode extensions for arm compiler |

## Small Fixes/Changes
Changed the LED Pin setup to 3 (LedsInit()) to be consistent with the functioncall GPIO_Init() in main.c.

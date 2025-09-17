/*
#include "stm32h7xx.h"  // adjust include path if needed
#include "main.h"       // for LED pin/port definitions

void LedsInit(void)
{
    // Enable GPIOI clock
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOIEN;

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED2_Pin | LED3_Pin; // both LEDs
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);
}

void delay_ms(uint32_t ms)
{
    // Simple busy wait, assuming SysTick at 1ms
    uint32_t start = SysTick->VAL;
    for(uint32_t i = 0; i < ms*1000; i++) { __NOP(); }
}

int main(void)
{
    //PLL_Config480Mhz();
    ConfigSysTick1ms();
    LedsInit();

    while(1)
    {
        // Toggle LEDs
        LED3_GPIO_Port->ODR ^= LED3_Pin;
        LED2_GPIO_Port->ODR ^= LED2_Pin;

        // Delay ~500ms
        delay_ms(5000);
    }
}
*/



#include "main.h"


void LedsInit(void)
{
    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOIEN;

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED3_Pin|LED2_Pin; // both LEDs
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);
}


int main()
{
    PLL_Config480Mhz(); // NOT WORKING DEBUG
    ConfigSysTick1ms();
    LedsInit();
    LED3_GPIO_Port->ODR ^= LED3_Pin;
    UART1InitTransmitWithDMAand_ucDLTlib();
    LOG("Compilation date: %s time: %s Sw_ver: %s", __DATE__, __TIME__,SW_VERSION);
    SDRAM_FMC_Init();    
    QSPI_InitMemoryMappedMode();
    
    // work till here !!!!

    //SDRAM_test();
    LTDC_Init();
    DSIHOST_DSI_Init();
    //DMA2D_Init();
    OTM8009A_DISP_LCD_Init(0, LCD_ORIENTATION_LANDSCAPE);
    TS_InitIT_OTM8009a();

    LvglInitApp();

    static uint32_t HelpTimer = 0u;

    while(1)
    {
        if(GetSysTime()-HelpTimer>=10000)
        {
            HelpTimer = GetSysTime();
            LOG("StillAlive! SystemTime: %lu ", GetSysTime());
            tooglePIN(LED3_GPIO_Port,LED2_Pin);
        }

        static uint32_t SavedLvglTime =0;
        if(GetSysTime() -SavedLvglTime >= 5)
        {
            SavedLvglTime = GetSysTime();
            LvglProcesTask();
        }
    }
}



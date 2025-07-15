#include "board.h"
#include "stm32f1xx.h"  //这个才是HAL库的，明天文件夹再换一下，貌似env+keil配置更好

/* 堆的起始地址和大小 */
#define HEAP_BEGIN  ((void*)0x20000000)
#define HEAP_END    ((void*)(0x20000000 + 20 * 1024)) // STM32F103C8T6 有 20KB SRAM

/* 时钟初始化 */
static void SystemClock_Config(void)
{
    /* 配置系统时钟为72MHz */
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    while (RCC_WaitForHSEStartUp() == ERROR);

    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);

    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08);

    SystemCoreClockUpdate();
}

/* SysTick 初始化 */
static void SysTick_Init(void)
{
    /* 配置 SysTick 为 1ms 中断 */
    SysTick_Config(SystemCoreClock / 1000); // 假设 1ms 为系统节拍
    NVIC_SetPriority(SysTick_IRQn, 0xFF);
}

/* 板级初始化函数 */
void rt_hw_board_init(void)
{
    /* 初始化系统时钟 */
    SystemClock_Config();

    /* 初始化 SysTick */
    SysTick_Init();

    /* 初始化堆 */
    // 如果不需要 RT-Thread 的堆管理，可以注释掉以下代码
    // rt_system_heap_init(HEAP_BEGIN, HEAP_END);

    /* 硬件中断向量表初始化 */
    // 如果不需要组件初始化，可以移除以下代码
    // #ifdef RT_USING_COMPONENTS_INIT
    // rt_components_board_init();
    // #endif
}
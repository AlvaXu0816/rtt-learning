#include "board.h"
#include "stm32f1xx.h"  //�������HAL��ģ������ļ����ٻ�һ�£�ò��env+keil���ø���

/* �ѵ���ʼ��ַ�ʹ�С */
#define HEAP_BEGIN  ((void*)0x20000000)
#define HEAP_END    ((void*)(0x20000000 + 20 * 1024)) // STM32F103C8T6 �� 20KB SRAM

/* ʱ�ӳ�ʼ�� */
static void SystemClock_Config(void)
{
    /* ����ϵͳʱ��Ϊ72MHz */
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

/* SysTick ��ʼ�� */
static void SysTick_Init(void)
{
    /* ���� SysTick Ϊ 1ms �ж� */
    SysTick_Config(SystemCoreClock / 1000); // ���� 1ms Ϊϵͳ����
    NVIC_SetPriority(SysTick_IRQn, 0xFF);
}

/* �弶��ʼ������ */
void rt_hw_board_init(void)
{
    /* ��ʼ��ϵͳʱ�� */
    SystemClock_Config();

    /* ��ʼ�� SysTick */
    SysTick_Init();

    /* ��ʼ���� */
    // �������Ҫ RT-Thread �Ķѹ�������ע�͵����´���
    // rt_system_heap_init(HEAP_BEGIN, HEAP_END);

    /* Ӳ���ж��������ʼ�� */
    // �������Ҫ�����ʼ���������Ƴ����´���
    // #ifdef RT_USING_COMPONENTS_INIT
    // rt_components_board_init();
    // #endif
}
#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f1xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Board configuration */
#define STM32_FLASH_START_ADDRESS  ((uint32_t)0x08000000)
#define STM32_FLASH_SIZE           (64 * 1024)
#define STM32_FLASH_END_ADDRESS    (STM32_FLASH_START_ADDRESS + STM32_FLASH_SIZE)

#define STM32_SRAM_START           ((uint32_t)0x20000000)
#define STM32_SRAM_SIZE            (20 * 1024)
#define STM32_SRAM_END             (STM32_SRAM_START + STM32_SRAM_SIZE)

/* Heap configuration */
#define HEAP_BEGIN                 ((void*)STM32_SRAM_START)
#define HEAP_END                   ((void*)STM32_SRAM_END)

/* Function prototypes */
void rt_hw_board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
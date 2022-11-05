/* This code should be checked whether it runs correctly on platforms */
# define  STM32_BOOTLOADER_ADDRESS 0x1FFF0000
#define __ram0_end__ 0x2000FF00
#    define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))
#    define BOOTLOADER_MAGIC 0xDEADBEEF
#    define MAGIC_ADDR (unsigned long *)(__ram0_end__ - 4)

__attribute__((weak)) void bootloader_jump(void) {
    *MAGIC_ADDR = BOOTLOADER_MAGIC; // set magic flag => reset handler will jump into boot loader
    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {
    NVIC_SystemReset();
}

void enter_bootloader_mode_if_requested(void) {
    unsigned long *check = MAGIC_ADDR;
    if (*check == BOOTLOADER_MAGIC) {
        *check = 0;
        __set_CONTROL(0);
        __set_MSP(*(__IO uint32_t *)STM32_BOOTLOADER_ADDRESS);
        __enable_irq();

        typedef void (*BootJump_t)(void);
        BootJump_t boot_jump = *(BootJump_t *)(STM32_BOOTLOADER_ADDRESS + 4);
        boot_jump();
        while (1)
            ;
    }
}
#include "gd32vf103.h"
#include "riscv_encoding.h"
#include "rvl-jtag.h"
#include "rvl-jtag-inline.h"
#include "rvl-link-config.h"


void rvl_jtag_init(void)
{
#ifdef RVL_LINK_CONFIG_JTAG_PIN_ALT
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
#else
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_AF);
    AFIO_PCF0 = (AFIO_PCF0 & 0xF8FFFFFF) | 0x04000000;
#endif

    gpio_init(TCK_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_10MHZ, TCK_PIN);
    gpio_init(TMS_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_10MHZ, TMS_PIN);
    gpio_init(TDI_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_10MHZ, TDI_PIN);
    gpio_init(TDO_PORT, GPIO_MODE_IPU, 0, TDO_PIN);
    gpio_init(SRST_PORT, GPIO_MODE_OUT_OD, GPIO_OSPEED_10MHZ, SRST_PIN);
}


void rvl_jtag_fini(void)
{
    gpio_init(TCK_PORT, GPIO_MODE_AIN, 0, TCK_PIN);
    gpio_init(TMS_PORT, GPIO_MODE_AIN, 0, TMS_PIN);
    gpio_init(TDI_PORT, GPIO_MODE_AIN, 0, TDI_PIN);
    gpio_init(TDO_PORT, GPIO_MODE_AIN, 0, TDO_PIN);
    gpio_init(SRST_PORT, GPIO_MODE_AIN, 0, SRST_PIN);
}


void rvl_jtag_srst_put(int srst)
{
    if (srst) {
        gpio_bit_set(SRST_PORT, SRST_PIN);
    } else {
        gpio_bit_reset(SRST_PORT, SRST_PIN);
    }
}


void rvl_jtag_delay(uint32_t us)
{
    uint32_t start = read_csr(mcycle);
    uint32_t period = us * 96; // CPU run @96MHz

    while(read_csr(mcycle) - start < period);
}

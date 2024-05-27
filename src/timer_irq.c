#include "timer_irq.h"

// initialize GIC-400
void gic_init()
{
    unsigned int i;

    // disable Distributor and CPU interface
    PUT32(GICD_CTLR, 0);
    PUT32(GICC_CTLR, 0);

    // disable, acknowledge and deactivate all interrupts
    for (i = 0; i < (GIC_IRQS / 32); ++i)
    {
        PUT32(GICD_DISABLE + 4 * i, ~0);
        PUT32(GICD_PEND_CLR + 4 * i, ~0);
        PUT32(GICD_ACTIVE_CLR + 4 * i, ~0);
    }

    // direct all interrupts to core 0 (=01) with default priority a0
    for (i = 0; i < (GIC_IRQS / 4); ++i)
    {
        PUT32(GICD_TARGET + 4 * i, 0x01010101);
        PUT32(GICD_PRIO + 4 * i, 0xa0a0a0a0);
    }

    // config all interrupts to level triggered
    for (i = 0; i < (GIC_IRQS / 16); ++i)
    {
        PUT32(GICD_CFG + 4 * i, 0);
    }

    // enable Distributor
    PUT32(GICD_CTLR, 1);

    // set Core0 interrupts mask theshold prio to F0, to react on higher prio a0
    PUT32(GICC_PRIO, 0xF0);
    // enable CPU interface
    PUT32(GICC_CTLR, 1);
}

void dispatch()
{
    // get one of the pending "Shared Peripheral Interrupt"
    unsigned int spi = GET32(GICC_ACK);

    while (spi != GIC_SPURIOUS)
    { // loop until no SPIs are pending on GIC
        if (spi == PIT_SPI)
        {
            are_ghosts_moving = 1;
            PUT32(PIT_Compare3, GET32(PIT_LOW) + ghost_speed * 20 * 1000); // next in 5sec
            PUT32(PIT_STATUS, 1 << PIT_MASKBIT);                      // clear IRQ in System Timer chip
        }
        // clear the pending
        PUT32(GICC_EOI, spi);
        // get the next
        spi = GET32(GICC_ACK);
    }
}

void start_timer_irq()
{
    // interrupts off/mask
    asm volatile("msr daifset, #2");

    gic_init();

    // PIT plugin (System Timer)
    PUT32(GICD_ENABLE + 4 * (PIT_SPI / 32), 1 << (PIT_SPI % 32));
    PUT32(PIT_Compare3, ghost_speed * 20 * 1000); // inital first IRQ in ghost speed
    PUT32(PIT_STATUS, 1 << PIT_MASKBIT);

    // IRQs on
    asm volatile("msr daifclr, #2");
}

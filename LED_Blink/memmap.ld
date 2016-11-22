MEMORY
{
    SDRAM : ORIGIN = 0x80200000, LENGTH = 0x1B400
}

SECTIONS
{
    .text : { *(.text*) } > SDRAM
    .bss : { *(.bss*) } > SDRAM
}

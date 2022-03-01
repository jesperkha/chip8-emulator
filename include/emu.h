#ifndef EMU_H
#define EMU_H

#define RAM_SIZE 4096

#include <stdint.h>
typedef uint8_t byte;

typedef struct cpu_t
{
    byte* ram;   // 4K bytes of RAM
    uint16_t pc; // 16-bit address program counter

    byte delay_timer; // 60Hz
    byte sound_timer; // Beep if not 0

    uint16_t index;     // index register
    uint16_t stack[64]; // Stack for 16-bit addresses
    byte registers[16]; // 16 8-bit registers 0x0 -> 0xF
} cpu_t;

// Returns 0 on success, 1 on error. Prints error message.
int start_emulation();

#endif
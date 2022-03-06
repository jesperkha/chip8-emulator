#include <stdio.h>
#include <time.h>

#include "emu.h"
#include "draw.h"
#include "err.h"

int error(char* message)
{
    printf("ERROR: %s\n", message);
    return 1;
}

// Todo: make clock updater for timer register
// Todo: function for reading and writing files to RAM

int execute_instruction(cpu_t* cpu, window_t* window);

int start_emulation()
{
    window_t* window = chip8win_init("CHIP-8 emulator");
    if (window == NULL)
        return error(ErrWindowInit);

    cpu_t cpu;
    cpu.ram = calloc(RAM_SIZE, sizeof(byte));

    while (chip8win_update(window) != 1)
    {
        int err = execute_instruction(&cpu, window);
        if (err) return 1; // Error is fatal
    }

    free(cpu.ram);
    chip8win_quit(window);
    return 0;
}

int execute_instruction(cpu_t* cpu, window_t* window)
{
    // Fetch instruction from program counter address
    if (cpu->pc >= RAM_SIZE)
        return error(ErrMemOutOfRange);
    byte a = cpu->ram[cpu->pc];
    byte b = cpu->ram[cpu->pc + 1];

    // Increment counter by 2 (16-bit instruction)
    cpu->pc += 2;

    // Split instruction into 4 4-bit nibbles
    uint8_t args[4] = {
        (a & 0xF0) >> 4, (a & 0x0F),
        (b & 0xF0) >> 4, (b & 0x0F),
    };

    // Avoid code duplication by creating instruction values up front
    uint8_t x = args[1];
    uint8_t y = args[2];
    uint8_t n = args[3];
    uint8_t nn = b;
    // 12-bit address from nibbles 2, 3, and 4
    // 0x00aa << 8  ->  0xaa00 | 0x00bb  ->  0xaabb
    uint16_t nnn = ((uint16_t)args[1] << 8) | (uint16_t)b;

    // Todo: finish basic instructions and test IDM logo thing
    switch (args[0])
    {
    case 0x0: // 00E0 - Clear screen
        chip8win_clear(window);
        break;
    
    case 0x1: // 1NNN - Jump
        cpu->pc = nnn;
        break;
    
    case 0x6: // 6XNN - Set register 0xX
        cpu->registers[x] = nn;
        break;
    
    case 0x7: // 7XNN - Add value to register 0xX
        cpu->registers[x] += nn;
        break;
    
    case 0xA: // ANNN - Set index register
        cpu->index = nnn;
        break;
    
    case 0xD: // DXYN - Draw
        cpu->registers[0xF] = 0;

        // Draw n pixels tall sprite
        for (int i = 0; i < n; i++)
        {
            // Get n'th sprite byte at index location
            uint16_t index = cpu->index + i;
            byte sprite_data = cpu->registers[index];

            uint16_t _y = cpu->registers[y + i];
            for (int j = 0; j < 8; j++)
            {
                // Get x coordinate and pixel value
                uint16_t _x = cpu->registers[x + j];
                uint8_t pixel_value = (sprite_data >> j) & 0x1;

                // Draw pixel
                // Todo: flip pixel values instead of just drawing SDL_GetRGB
                // https://wiki.libsdl.org/SDL_GetWindowPixelFormat
                // Todo: set VF to 1 if changed pixel value
                if (pixel_value == 1)
                    chip8win_point(window, _x % 64, _y % 32);
            }
        }
        break;
    
    default:
        printf("opcode: %d\n", args[0]); // Debug
        return error(ErrUndefinedOpCode);
    }

    return 0;
}
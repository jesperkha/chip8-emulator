## Specifcs

- RAM: 4096 bytes (4KB)
- PC (program counter)
- index register (16-bit) I
- 64 byte stack for 16-bit addresses
- 8-bit delay timer (60Hz)
- 8-bit sound timer (beep for not 0)
- 16 8-bit registers (V0 -> VF) (VF is flag register)

<br>

## Notes

- Leave first 512 bytes empty (0x000 -> 0x1FF)
- Font is located at 0x050 -> 0x09F (as of popular convention)
- Display is 64x32 (boolean pixel values for black 0 and white 1)
- Timer should run independant of emulator and not halt other processes
- 700 instructions per second

<br>

## Cycle

### Fetch

1. Get instruction at current program counter address in RAM
2. Increment counter by 2 (each instruction is two bytes)

### Decode

1. Split instruction into 4 bytes
   - X: The second byte. Used to look up one of the 16 registers (VX) from V0 through VF.
   - Y: The third byte. Also used to look up one of the 16 registers (VY) from V0 through VF.
   - N: The fourth byte. A 4-bit number.
   - NN: The second byte (third and fourth bytes). An 8-bit immediate number.
   - NNN: The second, third and fourth bytes. A 12-bit immediate memory address.

### Execute

1. Execute instruction

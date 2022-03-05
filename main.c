#include "emu.h"

// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

int main()
{
	// Error is printed if one is raised
	int err = start_emulation();
	return err;
}

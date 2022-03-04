#include "emu.h"

int main()
{
	// Error is printed if one is raised
	int err = start_emulation();
	return err;
}

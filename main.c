#include "emu.h"

int main(int argc, char** argv)
{
	// Error is printed if one is raised
	int err = start_emulation();
	return err;
}

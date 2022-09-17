
#pragma once

#include <dev/types.h>
#include <dev/mnemonic.h>

udword	get_instructions(instruction_t dest[], uqword nb, const ubyte** bytecode);
void	clear_instructions(instruction_t insts[], uqword nb);

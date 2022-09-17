
#pragma once

#include <evm_disassembler.h>

#include <stdio.h>

#define PRINT_DESTRUCTIVE_FORM
#define PRINT_OUTPUT
#define PRINT_STATIC_GAS

extern void fprint_instruction(FILE* where, instruction_t* const target);

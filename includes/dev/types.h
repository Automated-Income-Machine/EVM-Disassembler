
#pragma once

#include <stdint.h>

/*
*	NOTE: 'word' meanning in this program context
* 	is a 16-bits integer in the EVM is a 256-bit integer.
*/

typedef int8_t		byte;
typedef int16_t		word;
typedef int32_t		dword;
typedef int64_t		qword;

typedef uint8_t		ubyte;
typedef uint16_t	uword;
typedef uint32_t	udword;
typedef uint64_t	uqword;

/*
*	Next defines 'OPERAND_X' and typedef 'operand_t' and 'mnemonic_t
*	exist to avoid the creation of an enum (which size is 32-bits)
*/

#define OPERAND_NONE 0x0
#define OPERAND_STACK 0x1
#define OPERAND_IMM 0x2

typedef ubyte operand_t;
typedef ubyte mnemonic_t;

typedef struct
{
    mnemonic_t	mnemonic;
	ubyte		opcode;
	operand_t	input_type:2;
	ubyte		input_len:6;
	operand_t	output_type;
	dword		static_gas;
	ubyte*		immediate;
} instruction_t;

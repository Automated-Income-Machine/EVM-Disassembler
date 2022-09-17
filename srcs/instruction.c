
#include <dev/instruction.h>
#include <dev/portability.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TRUE 0
#define FALSE 1

// #define DEBUG(x...) (fprintf(stderr, "[DEBUG] " x))

static udword	get_instruction(instruction_t* const dest, const ubyte** bytecode)
{
	const ubyte					opcode = *((*bytecode)++);
	const instruction_data_t	found = lookup_table[opcode];

	/* Don't try this at home ! I do this because i know i can do
	*	it without risks since:
	*	- instruction_data_t : packed by default on 8-bytes.
	*	- instruction_t : packed by default on 16-bytes.
	*	- both have the same members at the same location on the 8 first bytes.
	*/
	*(uqword*)dest = *(uqword*)&found;
	dest->opcode = opcode;

	if (found.input_type == OPERAND_IMM)
	{
		dest->immediate = (ubyte*)malloc(sizeof(ubyte) * found.input_len);
		if (dest->immediate == NULL)
		{
			perror("malloc");
			return FALSE;
		}

		memcpy(dest->immediate, *bytecode, found.input_len);
		*bytecode += found.input_len;
	}

	return TRUE;
}

/**
 * @brief Parses @p 'nb' EVM instructions from @p 'bytcode'
 * 
 * @param dest Destination struct array in which an entity represents an EVM instruction.
 * @param nb The amount of instructions to parse.
 * @param bytecode A reference to a pointer pointing to the souce bytecode.
 * The pointer is incremented by the lenght of the instruction.
 * @return 0 on success
 * NOTE: some instruction may allocate memory and @p dest might be freed using 'clear_instructions'
 */
udword			get_instructions(instruction_t dest[], uqword nb, const ubyte** bytecode)
{
	udword st = 0;

	for (uqword i = 0 ; !st && i < nb ; i++)
		st = get_instruction(&dest[i], bytecode);

	return st;
}

/**
 * @brief Freed allocated data from an array of instructions.
 * 
 * @param insts An array of struct of instructions which may contain allocated memory.
 * @param nb The lenght of the array.
 */
void			clear_instructions(instruction_t insts[], uqword nb)
{
	for (uqword i = 0 ; i < nb ; i++)
	{
		if (insts[i].input_type == OPERAND_IMM)
			free(insts[i].immediate);
	}
}

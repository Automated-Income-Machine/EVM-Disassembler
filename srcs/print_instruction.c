
#include <dev/portability.h>
#include <dev/style.h>
#include <print_instruction.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define ISNEG(x) ((x) < 0)

__always_inline
static uqword get_instruction_size(instruction_t* const target)
{
	return target->input_type == OPERAND_IMM ? target->input_len + 1 : 1;
}

__always_inline
static void fprint_bin(FILE* where, instruction_t* const target)
{
	static uqword offset;
	const uqword size = get_instruction_size(target);

	fprintf(where, ANSI_COLOR_CYAN "%08"PRIXq":\t%02"PRIXb"\t" ANSI_COLOR_RESET, offset, target->opcode);
	offset += size;
}

__always_inline
static void	fprint_mnemonic(FILE* where, instruction_t* const target)
{
    static const char* const mnmonics[] = {
		"(BAD)",
		"STOP",				// Halts execution
		"ADD",				// Addition operation
		"MUL",				// Multiplication operation
		"SUB",				// Subtraction operation
		"DIV",				// Integer division operation
		"SDIV",				// Signed integer division operation (truncated)
		"MOD",				// Modulo remainder operation
		"SMOD",				// Signed modulo remainder operation
		"ADDMOD",			// Modulo addition operation
		"MULMOD",			// Modulo multiplication operation
		"EXP",				// Exponential operation
		"SIGNEXTEND",		// Extend length of two’s complement signed integer
		"LT",				// Less-than comparison
		"GT",				// Greater-than comparison
		"SLT",				// Signed less-than comparison
		"SGT",				// Signed greater-than comparison
		"EQ",				// Equality comparison
		"ISZERO",			// Simple not operator
		"AND",				// Bitwise AND operation
		"OR",				// Bitwise OR operation
		"XOR",				// Bitwise XOR operation
		"NOT",				// Bitwise NOT operation
		"BYTE",				// Retrieve single byte from word
		"SHL",				// Left shift operation
		"SHR",				// Logical right shift operation
		"SAR",				// Arithmetic (signed) right shift operation
		"SHA3",				// Compute Keccak-256 hash
		"ADDRESS",			// Get address of currently executing account
		"BALANCE",			// Get balance of the given account
		"ORIGIN",			// Get execution origination address
		"CALLER",			// Get caller address
		"CALLVALUE",		// Get deposited value by the instruction/transaction responsible for this execution
		"CALLDATALOAD",		// Get input data of current environment
		"CALLDATASIZE",		// Get size of input data in current environment
		"CALLDATACOPY",		// Copy input data in current environment to memory
		"CODESIZE",			// Get size of code running in current environment
		"CODECOPY",			// Copy code running in current environment to memory
		"GASPRICE",			// Get price of gas in current environment
		"EXTCODESIZE",		// Get size of an account’s code
		"EXTCODECOPY",		// Copy an account’s code to memory
		"RETURNDATASIZE",	// Get size of output data from the previous call from the current environment
		"RETURNDATACOPY",	// Copy output data from the previous call to memory
		"EXTCODEHASH",		// Get hash of an account’s code
		"BLOCKHASH",		// Get the hash of one of the 256 most recent complete blocks
		"COINBASE",			// Get the block’s beneficiary address
		"TIMESTAMP",		// Get the block’s timestamp
		"NUMBER",			// Get the block’s number
		"DIFFICULTY",		// Get the block’s difficulty
		"GASLIMIT",			// Get the block’s gas limit
		"CHAINID",			// Get the chain ID
		"SELFBALANCE",		// Get balance of currently executing account
		"BASEFEE",			// Get the base fee
		"POP",				// Remove item from stack
		"MLOAD",			// Load word from memory
		"MSTORE",			// Save word to memory
		"MSTORE8",			// Save byte to memory
		"SLOAD",			// Load word from storage
		"SSTORE",			// Save word to storage
		"JUMP",				// Alter the program counter
		"JUMPI",			// Conditionally alter the program counter
		"PC",				// Get the value of the program counter prior to the increment corresponding to this instruction
		"MSIZE",			// Get the size of active memory in bytes
		"GAS",				// Get the amount of available gas", including the corresponding reduction for the cost of this instruction
		"JUMPDEST",			// Mark a valid destination for jumps
		"PUSH1",			// Place 1 byte item on stack
		"PUSH2",			// Place 2 byte item on stack
		"PUSH3",			// Place 3 byte item on stack
		"PUSH4",			// Place 4 byte item on stack
		"PUSH5",			// Place 5 byte item on stack
		"PUSH6",			// Place 6 byte item on stack
		"PUSH7",			// Place 7 byte item on stack
		"PUSH8",			// Place 8 byte item on stack
		"PUSH9",			// Place 9 byte item on stack
		"PUSH10",			// Place 10 byte item on stack
		"PUSH11",			// Place 11 byte item on stack
		"PUSH12",			// Place 12 byte item on stack
		"PUSH13",			// Place 13 byte item on stack
		"PUSH14",			// Place 14 byte item on stack
		"PUSH15",			// Place 15 byte item on stack
		"PUSH16",			// Place 16 byte item on stack
		"PUSH17",			// Place 17 byte item on stack
		"PUSH18",			// Place 18 byte item on stack
		"PUSH19",			// Place 19 byte item on stack
		"PUSH20",			// Place 20 byte item on stack
		"PUSH21",			// Place 21 byte item on stack
		"PUSH22",			// Place 22 byte item on stack
		"PUSH23",			// Place 23 byte item on stack
		"PUSH24",			// Place 24 byte item on stack
		"PUSH25",			// Place 25 byte item on stack
		"PUSH26",			// Place 26 byte item on stack
		"PUSH27",			// Place 27 byte item on stack
		"PUSH28",			// Place 28 byte item on stack
		"PUSH29",			// Place 29 byte item on stack
		"PUSH30",			// Place 30 byte item on stack
		"PUSH31",			// Place 31 byte item on stack
		"PUSH32",			// Place 32 byte item on stack
		"DUP1",				// Duplicate 1st stack item
		"DUP2",				// Duplicate 2nd stack item
		"DUP3",				// Duplicate 3rd stack item
		"DUP4",				// Duplicate 4th stack item
		"DUP5",				// Duplicate 5th stack item
		"DUP6",				// Duplicate 6th stack item
		"DUP7",				// Duplicate 7th stack item
		"DUP8",				// Duplicate 8th stack item
		"DUP9",				// Duplicate 9th stack item
		"DUP10",			// Duplicate 10th stack item
		"DUP11",			// Duplicate 11th stack item
		"DUP12",			// Duplicate 12th stack item
		"DUP13",			// Duplicate 13th stack item
		"DUP14",			// Duplicate 14th stack item
		"DUP15",			// Duplicate 15th stack item
		"DUP16",			// Duplicate 16th stack item
		"SWAP1",			// Exchange 1st and 2nd stack items
		"SWAP2",			// Exchange 1st and 3rd stack items
		"SWAP3",			// Exchange 1st and 4th stack items
		"SWAP4",			// Exchange 1st and 5th stack items
		"SWAP5",			// Exchange 1st and 6th stack items
		"SWAP6",			// Exchange 1st and 7th stack items
		"SWAP7",			// Exchange 1st and 8th stack items
		"SWAP8",			// Exchange 1st and 9th stack items
		"SWAP9",			// Exchange 1st and 10th stack items
		"SWAP10",			// Exchange 1st and 11th stack items
		"SWAP11",			// Exchange 1st and 12th stack items
		"SWAP12",			// Exchange 1st and 13th stack items
		"SWAP13",			// Exchange 1st and 14th stack items
		"SWAP14",			// Exchange 1st and 15th stack items
		"SWAP15",			// Exchange 1st and 16th stack items
		"SWAP16",			// Exchange 1st and 17th stack items
		"LOG0",				// Append log record with no topics
		"LOG1",				// Append log record with one topic
		"LOG2",				// Append log record with two topics
		"LOG3",				// Append log record with three topics
		"LOG4",				// Append log record with four topics
		"CREATE",			// Create a new account with associated code
		"CALL",				// Message-call into an account
		"CALLCODE",			// Message-call into this account with alternative account’s code
		"RETURN",			// Halt execution returning output data
		"DELEGATECALL",		// Message-call into this account with an alternative account’s code", but persisting the current values for sender and value
		"CREATE2",			// Create a new account with associated code at a predictable address
		"STATICCALL",		// Static message-call into an account
		"REVERT",			// Halt execution reverting state changes but returning data and remaining gas
		"INVALID",			// Designated invalid instruction
		"SELFDESTRUCT"		// Halt execution and register account for later deletion
    };

    fprintf(where, ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, mnmonics[target->mnemonic]);
}

__always_inline
static void	fprint_operands(FILE* where, instruction_t* const target)
{
	if (target->input_type != OPERAND_NONE)
	{
		fprintf(where, " ");

		if (target->input_type == OPERAND_STACK)
		{
			if (ISGROUP_DUP(target->mnemonic))
				fprintf(where, ANSI_COLOR_YELLOW "st(" ANSI_COLOR_RESET ANSI_COLOR_CYAN \
					"%"PRIud ANSI_COLOR_RESET ANSI_COLOR_YELLOW ")" ANSI_COLOR_RESET,
					target->mnemonic - MN_DUP1 + 1);
			else if (ISGROUP_XCHG(target->mnemonic))
				fprintf(where, ANSI_COLOR_YELLOW "st(" ANSI_COLOR_RESET ANSI_COLOR_CYAN "0" \
				ANSI_COLOR_RESET ANSI_COLOR_YELLOW ")" ANSI_COLOR_RESET ANSI_COLOR_CYAN " <=> " ANSI_COLOR_RESET  \
				ANSI_COLOR_YELLOW "st(" ANSI_COLOR_RESET ANSI_COLOR_CYAN "%"PRIud  \
				ANSI_COLOR_RESET ANSI_COLOR_YELLOW ")" ANSI_COLOR_RESET,
				target->mnemonic - MN_SWAP1 + 1);
			else
			{
				for (uqword i = 0 ; i < target->input_len ; i++)
				fprintf(where, 
#ifdef PRINT_DESTRUCTIVE_FORM
					ANSI_COLOR_RED "{" ANSI_COLOR_RESET
#endif
					ANSI_COLOR_YELLOW "st(" ANSI_COLOR_RESET ANSI_COLOR_CYAN "%"PRIuq \
					ANSI_COLOR_RESET ANSI_COLOR_YELLOW ")" ANSI_COLOR_RESET
#ifdef PRINT_DESTRUCTIVE_FORM
					ANSI_COLOR_RED "}" ANSI_COLOR_RESET
#endif
					"%s", i, (ubyte)i == target->input_len - 1 ? ""
						: ANSI_COLOR_CYAN ", " ANSI_COLOR_RESET);
			}
		}
		else
		{
			fprintf(where, ANSI_COLOR_BLUE "0x");
			for (uqword i = 0 ; i < target->input_len ; i++)	
				fprintf(where, "%02"PRIXb, target->immediate[i]);
			fprintf(where, "%s", ANSI_COLOR_RESET);
		}
	}

#ifdef PRINT_OUTPUT
	if (target->output_type == OPERAND_STACK && !ISGROUP_XCHG(target->mnemonic))
			fprintf(where, ANSI_COLOR_CYAN " => " ANSI_COLOR_RESET ANSI_COLOR_YELLOW "st("  \
			ANSI_COLOR_RESET ANSI_COLOR_CYAN "0" ANSI_COLOR_RESET ANSI_COLOR_YELLOW ")" ANSI_COLOR_RESET);
#endif
}

#ifdef PRINT_STATIC_GAS

__always_inline
static void fprint_gas(FILE* where, instruction_t* const target)
{
	if (target->mnemonic != MN_NONE)
		fprintf(where, ANSI_COLOR_YELLOW " (" ANSI_COLOR_RESET ANSI_COLOR_BLUE "GAS: " \
			ANSI_COLOR_RESET ANSI_COLOR_RED "%"PRIdd"%s" ANSI_COLOR_RESET ANSI_COLOR_YELLOW ")" \
			ANSI_COLOR_RESET, ABS(target->static_gas), ISNEG(target->static_gas) ? "*" : "");
}

#endif

__always_inline
void	fprint_instruction(FILE* where, instruction_t* const target)
{
	fprint_bin(where, target);
	fprint_mnemonic(where, target);
	fprint_operands(where, target);

#ifdef PRINT_STATIC_GAS
	fprint_gas(where, target);
#endif

	fprintf(where, "\n");
}

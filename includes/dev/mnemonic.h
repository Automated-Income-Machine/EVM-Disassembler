
#pragma once

typedef enum
{
	MN_NONE,			// RESERVED
	MN_STOP,			// Halts execution
	MN_ADD,				// Addition operation
	MN_MUL,				// Multiplication operation
	MN_SUB,				// Subtraction operation
	MN_DIV,				// Integer division operation
	MN_SDIV,			// Signed integer division operation (truncated)
	MN_MOD,				// Modulo remainder operation
	MN_SMOD,			// Signed modulo remainder operation
	MN_ADDMOD,			// Modulo addition operation
	MN_MULMOD,			// Modulo multiplication operation
	MN_EXP,				// Exponential operation
	MN_SIGNEXTEND,		// Extend length of two’s complement signed integer
	MN_LT,				// Less-than comparison
	MN_GT,				// Greater-than comparison
	MN_SLT,				// Signed less-than comparison
	MN_SGT,				// Signed greater-than comparison
	MN_EQ,				// Equality comparison
	MN_ISZERO,			// Simple not operator
	MN_AND,				// Bitwise AND operation
	MN_OR,				// Bitwise OR operation
	MN_XOR,				// Bitwise XOR operation
	MN_NOT,				// Bitwise NOT operation
	MN_BYTE,			// Retrieve single byte from word
	MN_SHL,				// Left shift operation
	MN_SHR,				// Logical right shift operation
	MN_SAR,				// Arithmetic (signed) right shift operation
	MN_SHA3,			// Compute Keccak-256 hash
	MN_ADDRESS,			// Get address of currently executing account
	MN_BALANCE,			// Get balance of the given account
	MN_ORIGIN,			// Get execution origination address
	MN_CALLER,			// Get caller address
	MN_CALLVALUE,		// Get deposited value by the instruction/transaction responsible for this execution
	MN_CALLDATALOAD,	// Get input data of current environment
	MN_CALLDATASIZE,	// Get size of input data in current environment
	MN_CALLDATACOPY,	// Copy input data in current environment to memory
	MN_CODESIZE,		// Get size of code running in current environment
	MN_CODECOPY,		// Copy code running in current environment to memory
	MN_GASPRICE,		// Get price of gas in current environment
	MN_EXTCODESIZE,		// Get size of an account’s code
	MN_EXTCODECOPY,		// Copy an account’s code to memory
	MN_RETURNDATASIZE,	// Get size of output data from the previous call from the current environment
	MN_RETURNDATACOPY,	// Copy output data from the previous call to memory
	MN_EXTCODEHASH,		// Get hash of an account’s code
	MN_BLOCKHASH,		// Get the hash of one of the 256 most recent complete blocks
	MN_COINBASE,		// Get the block’s beneficiary address
	MN_TIMESTAMP,		// Get the block’s timestamp
	MN_NUMBER,			// Get the block’s number
	MN_DIFFICULTY,		// Get the block’s difficulty
	MN_GASLIMIT,		// Get the block’s gas limit
	MN_CHAINID,			// Get the chain ID
	MN_SELFBALANCE,		// Get balance of currently executing account
	MN_BASEFEE,			// Get the base fee
	MN_POP,				// Remove item from stack
	MN_MLOAD,			// Load word from memory
	MN_MSTORE,			// Save word to memory
	MN_MSTORE8,			// Save byte to memory
	MN_SLOAD,			// Load word from storage
	MN_SSTORE,			// Save word to storage
	MN_JUMP,			// Alter the program counter
	MN_JUMPI,			// Conditionally alter the program counter
	MN_PC,				// Get the value of the program counter prior to the increment corresponding to this instruction
	MN_MSIZE,			// Get the size of active memory in bytes
	MN_GAS,				// Get the amount of available gas, including the corresponding reduction for the cost of this instruction
	MN_JUMPDEST,		// Mark a valid destination for jumps
	MN_PUSH1,			// Place 1 byte item on stack
	MN_PUSH2,			// Place 2 byte item on stack
	MN_PUSH3,			// Place 3 byte item on stack
	MN_PUSH4,			// Place 4 byte item on stack
	MN_PUSH5,			// Place 5 byte item on stack
	MN_PUSH6,			// Place 6 byte item on stack
	MN_PUSH7,			// Place 7 byte item on stack
	MN_PUSH8,			// Place 8 byte item on stack
	MN_PUSH9,			// Place 9 byte item on stack
	MN_PUSH10,			// Place 10 byte item on stack
	MN_PUSH11,			// Place 11 byte item on stack
	MN_PUSH12,			// Place 12 byte item on stack
	MN_PUSH13,			// Place 13 byte item on stack
	MN_PUSH14,			// Place 14 byte item on stack
	MN_PUSH15,			// Place 15 byte item on stack
	MN_PUSH16,			// Place 16 byte item on stack
	MN_PUSH17,			// Place 17 byte item on stack
	MN_PUSH18,			// Place 18 byte item on stack
	MN_PUSH19,			// Place 19 byte item on stack
	MN_PUSH20,			// Place 20 byte item on stack
	MN_PUSH21,			// Place 21 byte item on stack
	MN_PUSH22,			// Place 22 byte item on stack
	MN_PUSH23,			// Place 23 byte item on stack
	MN_PUSH24,			// Place 24 byte item on stack
	MN_PUSH25,			// Place 25 byte item on stack
	MN_PUSH26,			// Place 26 byte item on stack
	MN_PUSH27,			// Place 27 byte item on stack
	MN_PUSH28,			// Place 28 byte item on stack
	MN_PUSH29,			// Place 29 byte item on stack
	MN_PUSH30,			// Place 30 byte item on stack
	MN_PUSH31,			// Place 31 byte item on stack
	MN_PUSH32,			// Place 32 byte item on stack
	MN_DUP1,			// Duplicate 1st stack item
	MN_DUP2,			// Duplicate 2nd stack item
	MN_DUP3,			// Duplicate 3rd stack item
	MN_DUP4,			// Duplicate 4th stack item
	MN_DUP5,			// Duplicate 5th stack item
	MN_DUP6,			// Duplicate 6th stack item
	MN_DUP7,			// Duplicate 7th stack item
	MN_DUP8,			// Duplicate 8th stack item
	MN_DUP9,			// Duplicate 9th stack item
	MN_DUP10,			// Duplicate 10th stack item
	MN_DUP11,			// Duplicate 11th stack item
	MN_DUP12,			// Duplicate 12th stack item
	MN_DUP13,			// Duplicate 13th stack item
	MN_DUP14,			// Duplicate 14th stack item
	MN_DUP15,			// Duplicate 15th stack item
	MN_DUP16,			// Duplicate 16th stack item
	MN_SWAP1,			// Exchange 1st and 2nd stack items
	MN_SWAP2,			// Exchange 1st and 3rd stack items
	MN_SWAP3,			// Exchange 1st and 4th stack items
	MN_SWAP4,			// Exchange 1st and 5th stack items
	MN_SWAP5,			// Exchange 1st and 6th stack items
	MN_SWAP6,			// Exchange 1st and 7th stack items
	MN_SWAP7,			// Exchange 1st and 8th stack items
	MN_SWAP8,			// Exchange 1st and 9th stack items
	MN_SWAP9,			// Exchange 1st and 10th stack items
	MN_SWAP10,			// Exchange 1st and 11th stack items
	MN_SWAP11,			// Exchange 1st and 12th stack items
	MN_SWAP12,			// Exchange 1st and 13th stack items
	MN_SWAP13,			// Exchange 1st and 14th stack items
	MN_SWAP14,			// Exchange 1st and 15th stack items
	MN_SWAP15,			// Exchange 1st and 16th stack items
	MN_SWAP16,			// Exchange 1st and 17th stack items
	MN_LOG0,			// Append log record with no topics
	MN_LOG1,			// Append log record with one topic
	MN_LOG2,			// Append log record with two topics
	MN_LOG3,			// Append log record with three topics
	MN_LOG4,			// Append log record with four topics
	MN_CREATE,			// Create a new account with associated code
	MN_CALL,			// Message-call into an account
	MN_CALLCODE,		// Message-call into this account with alternative account’s code
	MN_RETURN,			// Halt execution returning output data
	MN_DELEGATECALL,	// Message-call into this account with an alternative account’s code, but persisting the current values for sender and value
	MN_CREATE2,			// Create a new account with associated code at a predictable address
	MN_STATICCALL,		// Static message-call into an account
	MN_REVERT,			// Halt execution reverting state changes but returning data and remaining gas
	MN_INVALID,			// Designated invalid instruction
	MN_SELFDESTRUCT		// Halt execution and register account for later deletion
} e_mnemonic_t;

#define RANGE(hls, hrs, x) ((x) >= (hls) && (x) <= (hrs))
#define ISGROUP_ARITHMETIC(mn) (RANGE(MN_STOP, MN_SIGNEXTEND mn))
#define ISGROUP_COMP(mn) (RANGE(MN_LT, MN_ISZERO, mn))
#define ISGROUP_BITWISE(mn) (RANGE(MN_AND, MN_SAR, mn))
#define ISGROUP_SHA3(mn) ((mn) == MN_SHA3)
#define ISGROUP_ENVINFO(mn) (RANGE(MN_ADDRESS, EXTCODEHASH, mn))
#define ISGROUP_BLOCKINFO(mn) (RANGE(MN_BLOCKHASH, BASEFEE, mn))
#define ISFROUP_STACKMEMSTORFLOW(mn) (RANGE(MN_POP, JUMPDEST, mn))
#define ISGROUP_PUSH(mn) (RANGE(MN_PUSH1, MN_PUSH32, mn))
#define ISGROUP_DUP(mn) (RANGE(MN_DUP1, MN_DUP16, mn))
#define ISGROUP_XCHG(mn) (RANGE(MN_SWAP1, MN_SWAP16, mn))
#define ISGROUP_LOGGING(mn) (RANGE(MN_LOG0, MN_LOG4, mn))
#define ISGROUP_SYSTE(mn) ((mn) >= MN_CREATE)

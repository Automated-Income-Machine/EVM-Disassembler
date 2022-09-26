# EVM-Disassembler

EVM bilateral instructions tokenizer implemented in C. With which a disassembler has been implemented in order to ease testing. 

### Downloading and compilation
```sh
git clone https://github.com/Automated-Income-Machine/EVM-Disassembler ~/EVM-Disassembler && \
cd ~/EVM-Disassembler && \
make
```
### Usage
The disassembler only reads input from stdin.
```sh
echo -ne "\x60\x69\x60\x77\x01\x51" | ./evm-disassembler | less
```
Will display:
```
00000000:       60      PUSH1 0x69 => st(0) (GAS: 3)
00000002:       60      PUSH1 0x77 => st(0) (GAS: 3)
00000004:       01      ADD {st(0)}, {st(1)} => st(0) (GAS: 3)
00000005:       51      MLOAD {st(0)} => st(0) (GAS: 3*)
```
NOTE: It has been implemented and tested on Ubuntu 20.04.4.

### Disassembler format
Each instruction follows the following format:
```
<offset>: <opcode> <mnemonic> [ ['{'] <input operand(s)> ['}'] | <immediate> ] => [output operand] <gas ['*']>
```
- When `<input operands>` is between curly braces (`{`,`}`) the operation is destructive.
- When `<gas>` is followded by a wildcard (`*`) the operation consumes an addon of dynamic gas.
- `st` stands for `stack`, since the EVM has no registers all instruction use either the stack or immediate data.
- In `st(N)` `N` is the depth of the stack.

### Instruction token
Each instruction is tokenized in form of struct `instruction_t`:
```c
// includes/dev/types.h

typedef uint8_t ubyte;

/* ... */

typedef ubyte operand_t;
typedef ubyte mnemonic_t;

typedef struct
{
  mnemonic_t  mnemonic;     // The mnemonic code (includes/dev/mnemonic.h)
  ubyte       opcode;       // The opcode of the instruction
  operand_t   input_type:2; // The kind of input the instruction takes (either STACK, IMMEDIATE or NONE)
  ubyte       input_len:6;  // For IMMEDIATE: the lenght in bytes ; For STACK: the amount of arguments
  operand_t   output_type;  // Same as 'input_type'
  dword       static_gas;   // The cost of the instruction in GAS (negative values indicate than there is a dynamic addon)
  ubyte*      immediate;    // A pointer to the immediate (must be freed if non nul)
} instruction_t;

```

### The (mini) Lib
- The function `get_instructions` converts N instructions from bytecode to `instruction_t` tokens. Return 0 on success.
- The function `clear_instructions` automatically frees all immediates from a given set of tokens.

Their prototypes:
```c
// includes/evm_disassembler.h
// see types in includes/dev/types.h

udword	get_instructions(instruction_t dest[], uqword nb, const ubyte** bytecode);
void	clear_instructions(instruction_t insts[], uqword nb);
```

---

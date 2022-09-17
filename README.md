# EVM-Disassembler

The main purpose of this project is the EVM bytecodes parsing. However, a disassembler has been implemented for testing.

### Downloading and compilation
```sh
git clone https://github.com/Automated-Money-Machine/EVM-Disassembler ~/EVM-Disassembler && \
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
When `<input operands>` is between curly braces (`{`,`}`) the operation is destructive.
When `<gas>` is followded by a wildcard (`*`) the operation consumes an addon of dynamic gas.
`st` stands for `stack` since the EVM has no registers all instruction use either the stack or immediate data.
In `st(N)` `N` is the depth of the stack.

---

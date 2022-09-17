
#include <dev/portability.h>
#include <evm_disassembler.h>
#include <print_instruction.h>

#include <unistd.h>

#define ARRLEN(x) (sizeof(x) / sizeof(*x))

#define INSTRUCTION_NB 0x100
#define BUFFSIZE 0x1000
#define STOP_RATE 0x8

__always_inline
static int has_reach_stop_point(instruction_t insts[])
{
	uqword count = 0;

	for (uqword i = 0 ; i < STOP_RATE ; i++)
	{
		if (insts[i].mnemonic == MN_STOP)
			count++;
	}

	return count == STOP_RATE;
}

int main()
{
    static instruction_t	insts[INSTRUCTION_NB];
    static ubyte			buff[BUFFSIZE];
	const ubyte*			pbuff = (const ubyte*)buff;
	udword					st = 0;
	qword					rbytes;

	do
	{
		if ((rbytes = read(STDIN_FILENO, buff, BUFFSIZE)) < 0
		|| (st = get_instructions(insts, ARRLEN(insts), &pbuff)) != 0)
			goto error;

		for (uqword i = 0 ; i < ARRLEN(insts) ; i++)
		{
			if (i < ARRLEN(insts) - STOP_RATE && has_reach_stop_point(&insts[i]))
				break ;
			fprint_instruction(stdout, &insts[i]);
		}

		clear_instructions(insts, ARRLEN(insts));
	}
	while (rbytes != 0);

error:
	return st;
}

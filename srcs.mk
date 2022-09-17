INCDIR	=	includes
SRCDIR	=	srcs

HDRS	=\
$(addprefix includes/,\
	$(addprefix dev/,\
		gas.h\
		instruction.h\
		mnemonic.h\
		portability.h\
		types.h\
	)\
	print_instruction.h\
	evm_disassembler.h\
)
SRCS	=\
$(addprefix srcs/,\
	instruction.c\
	main.c\
	print_instruction.c\
)


#pragma once

#define DISABLE_STYLE
#undef DISABLE_STYLE

#ifndef DISABLE_STYLE

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

#else

# define ANSI_COLOR_RED     ""
# define ANSI_COLOR_GREEN   ""
# define ANSI_COLOR_YELLOW  ""
# define ANSI_COLOR_BLUE    ""
# define ANSI_COLOR_MAGENTA ""
# define ANSI_COLOR_CYAN    ""
# define ANSI_COLOR_RESET   ""

#endif

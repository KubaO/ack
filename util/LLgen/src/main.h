/* Copyright (c) 1991 by the Vrije Universiteit, Amsterdam, the Netherlands.
 * For full copyright and restrictions on use see the file COPYING in the top
 * level of the LLgen tree.
 */

#ifndef LLGEN_MAIN_H
#define LLGEN_MAIN_H

#include "types.h"

// main.c
extern void	error(int lineno, string fmt, ...);
extern void	warning(int lineno, string fmt, ...);
extern void	fatal(int lineno, string fmt, ...);
extern void	comfatal(void);
extern void	copyfile(cstring);
extern void	install(cstring target, cstring source);
extern void p_init(void);

// alloc.c
extern p_mem alloc(unsigned size);
extern p_mem ralloc(p_mem p, unsigned size);
extern p_mem new_mem(p_info p);

// checks.c
extern void conflchecks(void);

// compute.c
extern void	do_compute(void);
extern int	empty(p_gram);

// gencode.c
extern void gencode(int argc);

// Lpars.c
void LLparse(void);

// machdep.c
extern void		UNLINK(cstring);
extern void		RENAME(cstring, cstring);
extern string	libpath(cstring);

// name.c
extern string	store(cstring);
extern void		name_init(void);
extern p_gram	search(int, cstring, int);

// reach.c
extern void co_reach(void);

#endif // LLGEN_MAIN_H

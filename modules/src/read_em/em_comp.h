/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header$ */

struct e_arg {
	int	ems_argtype;		/* type of this argument */
	union e_simple_arg {
		arith	emu_cst;	/* a cst */
		label	emu_dlb;	/* a numeric data label */
		label	emu_ilb;	/* an instruction label */
		char	*emu_dnam;	/* a data label */
		char	*emu_pnam;	/* a procedure name */
		char	*emu_string;	/* a string (fcon,icon,ucon,scon) */
	}	ems_arg;
	arith	ems_szoroff;
};
#define ema_cst 	ems_arg.emu_cst
#define ema_dlb 	ems_arg.emu_dlb
#define ema_ilb 	ems_arg.emu_ilb
#define ema_dnam	ems_arg.emu_dnam
#define ema_pnam	ems_arg.emu_pnam
#define ema_string	ems_arg.emu_string


struct e_instr {
	int     	em_type;	/* Type of this instr */
#define EM_MNEM 	256		/* A machine instruction */
#define EM_PSEU 	257		/* A pseudo */
#define EM_STARTMES	258		/* Start of a MES pseudo */
#define EM_MESARG	259		/* A member in a MES list */
#define EM_ENDMES	260		/* End of a MES pseudo */
#define EM_DEFILB	261		/* An instruction label definition */
#define EM_DEFDLB	262		/* A numeric data label definition */
#define EM_DEFDNAM	263		/* A non-numeric data label def */
#define EM_ERROR	264		/* Recoverable error */
#define EM_FATAL	265		/* Unrecoverable error */
#define EM_EOF  	266		/* End of file */
	int     	em_opcode;
	struct e_arg	em_arg;
};

extern arith
	EM_holsize, EM_bsssize;
extern int
	EM_holinit, EM_bssinit;

#define em_ilb  	em_arg.ema_ilb
#define em_dlb  	em_arg.ema_dlb
#define em_dnam 	em_arg.ema_dnam
#define em_argtype	em_arg.ems_argtype
#define em_cst  	em_arg.ema_cst
#define em_pnam 	em_arg.ema_pnam
#define em_string	em_arg.ema_string
#define em_off  	em_arg.ems_szoroff
#define em_size 	em_arg.ems_szoroff

/* Arguments for EXC pseudo: */
#define em_exc1 	em_arg.ema_cst
#define em_exc2 	em_arg.ems_szoroff

extern char
	*EM_error, *EM_filename;
extern unsigned int
	EM_lineno;
extern int
	EM_wordsize, EM_pointersize;

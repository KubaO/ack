/* $Header$ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*	makecalls: expand a datastructure as delivered by "EM_getline"
	into calls to the procedural interface.
	Exported routine:
		EM_mkcalls
*/

#include <em_spec.h>
#include <em_mnem.h>
#include <em_pseu.h>
#include <em_flag.h>
#include "em_ptyp.h"
#include <em.h>
#include "em_comp.h"
#include <assert.h>

extern char em_flag[];	/* One per EM instruction: indicates parameter kind */
extern short em_ptyp[];	/* One per parameter kind: indicates parameter type */

#include "C_funcs"

static int listtype = 0;	/* indicates pseudo when generating code for
				   variable length argument lists
				   (only for MES)
				*/

#ifdef CHECKING
/*	c_getarg: Check the argument indicated by "args".
	The argument must be of a type allowed by "typset".
	Return a pointer to the next argument.
*/
PRIVATE
checkarg(arg, typset)
	register struct e_arg *arg;
{

	if (((!typset) && arg->ems_argtype) ||
	    ((!arg->ems_argtype) && typset)) {
		/* End of arguments expected, but there are more, or
		   an argument expected, but there is none
		*/
		EM_error = "Illegal number of parameters";
		return;
	}

	if (!(arg->ems_argtype & typset)) {
		/* Type error */
		EM_error = "Illegal parameter type";
	}
}
#else not CHECKING
#define c_getarg(arg, x)
#endif CHECKING

/*	EM_doinstr: An EM instruction
*/
PRIVATE
EM_doinstr(p)
	register struct e_instr *p;
{
	register int parametertype;	/* parametertype of the instruction */

	parametertype = em_flag[p->em_opcode-sp_fmnem] & EM_PAR;
#ifdef CHECKING
	if (parametertype != PAR_NO && parametertype != PAR_W) {
		if (p->em_argtype == 0) {
			EM_error = "Illegal number of parameters";
			return;
		}
	}
#endif CHECKING
	switch(parametertype) {
		case PAR_NO:
			break;
		default:
			checkarg(&(p->em_arg), em_ptyp[parametertype]);
			break;
		case PAR_W:
			if (p->em_argtype != 0) {
				checkarg(&(p->em_arg), cst_ptyp);
			}
			else {
#include "C_mnem_narg"
				return;
			}
			break;
	}
#include "C_mnem"
}

PRIVATE
EM_dopseudo(p)
	register struct e_instr *p;
{

	switch(p->em_opcode) {
		case ps_exc: {
			C_exc(p->em_exc1, p->em_exc2);
			break;
		}
		case ps_hol: {
			checkarg(&(p->em_arg), par_ptyp);
			switch(p->em_argtype) {
			    case cst_ptyp:
				C_hol_cst(EM_holsize,
					  p->em_cst,
					  EM_holinit);
				break;
			    case ico_ptyp:
				C_hol_icon(EM_holsize,
					   p->em_string,
					   p->em_size, 
					   EM_holinit);
				break;
			    case uco_ptyp:
				C_hol_ucon(EM_holsize,
					   p->em_string,
					   p->em_size,
					   EM_holinit);
				break;
			    case fco_ptyp:
				C_hol_fcon(EM_holsize,
					   p->em_string,
					   p->em_size, 
					   EM_holinit);
				break;
			    case sof_ptyp:
				C_hol_dnam(EM_holsize,
					   p->em_dnam,
					   p->em_off, 
					   EM_holinit);
				break;
			    case nof_ptyp:
				C_hol_dlb(EM_holsize,
					  p->em_dlb,
					  p->em_off, 
					  EM_holinit);
				break;
			    case ilb_ptyp:
				C_hol_ilb(EM_holsize,
					  p->em_ilb, 
					  EM_holinit);
				break;
			    case pro_ptyp:
				C_hol_pnam(EM_holsize,
					   p->em_pnam, 
					   EM_holinit);
				break;
			    default:
				EM_error = "Illegal parameter type";
				break;
			}
			break;
		}
		case ps_bss: {
			checkarg(&(p->em_arg), par_ptyp);
			switch(p->em_argtype) {
			    case cst_ptyp:
				C_bss_cst(EM_bsssize,
					  p->em_cst,
					  EM_bssinit);
				break;
			    case ico_ptyp:
				C_bss_icon(EM_bsssize,
					   p->em_string,
					   p->em_size, 
					   EM_bssinit);
				break;
			    case uco_ptyp:
				C_bss_ucon(EM_bsssize,
					   p->em_string,
					   p->em_size,
					   EM_bssinit);
				break;
			    case fco_ptyp:
				C_bss_fcon(EM_bsssize,
					   p->em_string,
					   p->em_size, 
					   EM_bssinit);
				break;
			    case sof_ptyp:
				C_bss_dnam(EM_bsssize,
					   p->em_dnam,
					   p->em_off, 
					   EM_bssinit);
				break;
			    case nof_ptyp:
				C_bss_dlb(EM_bsssize,
					  p->em_dlb,
					  p->em_off, 
					  EM_bssinit);
				break;
			    case ilb_ptyp:
				C_bss_ilb(EM_bsssize,
					  p->em_ilb, 
					  EM_bssinit);
				break;
			    case pro_ptyp:
				C_bss_pnam(EM_bsssize, 
					   p->em_pnam, 
					   EM_bssinit);
				break;
			    default:
				EM_error = "Illegal parameter type";
				break;
			}
			break;
		}
		case ps_end:
			if (p->em_argtype != 0) {
				checkarg(&(p->em_arg), cst_ptyp);
				C_end(p->em_cst);
				break;
			}
			C_end_narg();
			break;
		case ps_exa:
		case ps_ina:
			checkarg(&(p->em_arg), lab_ptyp);
			if (p->em_argtype == nof_ptyp) {
				if (p->em_opcode == ps_exa) {
					C_exa_dlb(p->em_dlb);
				}
				else	C_ina_dlb(p->em_dlb);
				break;
			}
			if (p->em_opcode == ps_exa) {
				C_exa_dnam(p->em_dnam);
			}
			else	C_ina_dnam(p->em_dnam);
			break;
		case ps_exp:
			checkarg(&(p->em_arg), pro_ptyp);
			C_exp(p->em_pnam);
			break;
		case ps_inp:
			checkarg(&(p->em_arg), pro_ptyp);
			C_inp(p->em_pnam);
			break;
		case ps_pro:
			checkarg(&(p->em_arg), pro_ptyp);
			if (p->em_size >= 0) {
				C_pro(p->em_pnam, p->em_size);
			}
			else	C_pro_narg(p->em_pnam);
			break;
		case ps_con:
			checkarg(&(p->em_arg), val_ptyp);
			switch(p->em_argtype) {
				case ilb_ptyp:
					C_con_ilb(p->em_ilb);
					break;
				case nof_ptyp:
					C_con_dlb(p->em_dlb, p->em_off);
					break;
				case sof_ptyp:
					C_con_dnam(p->em_dnam, p->em_off);
					break;
				case cst_ptyp:
					C_con_cst(p->em_cst);
					break;
				case pro_ptyp:
					C_con_pnam(p->em_pnam);
					break;
				case str_ptyp:
					C_con_scon(p->em_string, p->em_size);
					break;
				case ico_ptyp:
					C_con_icon(p->em_string, p->em_size);
					break;
				case uco_ptyp:
					C_con_ucon(p->em_string, p->em_size);
					break;
				case fco_ptyp:
					C_con_fcon(p->em_string, p->em_size);
					break;
				default:
					EM_error = "Illegal argument type";
					return;
			}
			break;
		case ps_rom:
			checkarg(&(p->em_arg), val_ptyp);
			switch(p->em_argtype) {
				case ilb_ptyp:
					C_rom_ilb(p->em_ilb);
					break;
				case nof_ptyp:
					C_rom_dlb(p->em_dlb, p->em_off);
					break;
				case sof_ptyp:
					C_rom_dnam(p->em_dnam, p->em_off);
					break;
				case cst_ptyp:
					C_rom_cst(p->em_cst);
					break;
				case pro_ptyp:
					C_rom_pnam(p->em_pnam);
					break;
				case str_ptyp:
					C_rom_scon(p->em_string, p->em_size);
					break;
				case ico_ptyp:
					C_rom_icon(p->em_string, p->em_size);
					break;
				case uco_ptyp:
					C_rom_ucon(p->em_string, p->em_size);
					break;
				case fco_ptyp:
					C_rom_fcon(p->em_string, p->em_size);
					break;
				default:
					EM_error = "Illegal argument type";
					return;
			}
			break;
		default: 
			EM_error = "Illegal pseudo instruction";
			break;
	}
}

PRIVATE
EM_docon(p)
	register struct e_instr *p;
{
	checkarg(&(p->em_arg), val_ptyp);
	switch(p->em_argtype) {
		case ilb_ptyp:
			C_ilb(p->em_ilb);
			break;
		case nof_ptyp:
			C_dlb(p->em_dlb, p->em_off);
			break;
		case sof_ptyp:
			C_dnam(p->em_dnam, p->em_off);
			break;
		case cst_ptyp:
			C_cst(p->em_cst);
			break;
		case pro_ptyp:
			C_pnam(p->em_pnam);
			break;
		case str_ptyp:
			C_scon(p->em_string, p->em_size);
			break;
		case ico_ptyp:
			C_icon(p->em_string, p->em_size);
			break;
		case uco_ptyp:
			C_ucon(p->em_string, p->em_size);
			break;
		case fco_ptyp:
			C_fcon(p->em_string, p->em_size);
			break;
		default:
			EM_error = "Illegal argument type";
			break;
	}
}

PRIVATE
EM_dostartmes(p)
	register struct e_instr *p;
{

	if (listtype) {
		EM_error = "Message not ended";
		return;
	}
	checkarg(&(p->em_arg), cst_ptyp);
	C_mes_begin((int) (p->em_cst));
	listtype = ps_mes;
}

EXPORT int
EM_mkcalls(line)
	register struct e_instr *line;
{

#ifdef CHECKING
	if (listtype && line->em_type != EM_MESARG && line->em_type != EM_ENDMES) {
		EM_error = "Message not ended";
		return 0;
	}
#endif CHECKING
	EM_error = 0;
	switch(line->em_type) {
		default:
			EM_error = "Illegal EM line";
			break;
		case EM_MNEM:
			/* normal instruction */
			EM_doinstr(line);
			break;
		case EM_DEFILB:
			/* defining occurrence of an instruction label */
			C_df_ilb(line->em_ilb);
			break;
		case EM_DEFDLB:
			/* defining occurrence of a global data label */
			C_df_dlb(line->em_dlb);
			break;
		case EM_DEFDNAM:
			/* defining occurrence of a non-numeric data label */
			C_df_dnam(line->em_dnam);
			break;
		case EM_PSEU:
			/* pseudo */
			EM_dopseudo(line);
			break;
		case EM_STARTMES:
			/* start of a MES pseudo */
			EM_dostartmes(line);
			break;
		case EM_MESARG:
		case EM_ENDMES:
#ifdef CHECKING
			if (!listtype) {
				EM_error = "Message not started";
				return 0;
			}
#endif
			if (line->em_type == EM_MESARG) {
				EM_docon(line);
				break;
			}
			C_mes_end();
			listtype = 0;
			break;
	}
	if (EM_error) return 0;
	return 1;
}

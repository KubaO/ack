/*
 * tmpfile.c - create and open a temporary file
 */
/* $Header$ */

#include	<stdio.h>
#include	<string.h>
#include	"loc_incl.h"

unsigned int getpid(void);

FILE *
tmpfile(void) {
	static char name_buffer[L_tmpnam] = "/tmp/tmp." ;
	static char *name = NULL;
	FILE *file;

	if (!name) {
		name = name_buffer + strlen(name_buffer);
		i_compute(getpid(), 10, name, 5);
		name += strlen(name);
		*name++ = '\0';
	}

	file = fopen(name_buffer,"wb+");
	if (!file) return (FILE *)NULL;
	if (remove(name_buffer)) return (FILE *)NULL;
	return file;
}

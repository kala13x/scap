/*
 * src/info.h
 * Copyleft (C) 2015  Sun Dro (a.k.a 7th Ghost)
 *
 * Get and print additional information about program.
 */


#include "stdinc.h"


#define VERSION_MAX     1
#define VERSION_MIN     0
#define BUILD_NUMBER    31


/* 
 * Get version. Function returns version and build number of 
 * application. Return value is static char pointer.
 */
const char* get_version();


/* 
 * greet - Print greeting message. Function returns program 
 * name, version, build number and build date. Argument 
 * p_name is program name from which we want to greet users. 
 */
void greet(char *p_name);


/*
 * Usage - Print usage information of compilator.
 * Argument fname is name of executable application. 
 */
void usage(char *fname);

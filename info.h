/*
 * info.h
 * Copyleft (C) 2015  Sun Dro (a.k.a 7th Ghost)
 *
 * Get and print additional information
 */


#include "stdinc.h"

/* Version and build number */
#define VERSION "1.0.5 Snapshot"
#define BUILD 23


/* 
 * Get version. Function returns version and build number of 
 * application. Return value is static char pointer.
 */
const char* get_version();


/*
 * Greet users. Function prints application name, version and
 * build number.
 */
void greet(void);


/*
 * Print help and usage
 */
void usage(void);

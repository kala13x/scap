/*
 * info.c
 * Copyleft (C) 2015  Sun Dro (a.k.a 7th Ghost)
 *
 * Get and print additional information
 */


#include "stdinc.h"
#include "info.h"


/* 
 * Get version. Function returns version and build number of 
 * application. Return value is static char pointer.
 */
const char* get_version()
{
    static char version[128];
    sprintf(version, "%s Build %d (%s)", VERSION, BUILD, __DATE__);
    return version;
}


/*
 * Greet users. Function prints application name, version and
 * build number.
 */
void greet(void) 
{
    printf("============================================\n");
    printf("sCap: %s\n", get_version());
    printf("============================================\n");
} 


/*
 * Print help and usage
 */
void usage(void) 
{
    printf("Usage: scap [-i] [-d] [-h]\n");
    printf("options are:\n");
    printf(" -i         # dump header info in file\n");
    printf(" -d         # dump data in file\n");
    printf(" -h         # print help and usage\n");
    printf("\n");
}

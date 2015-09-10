/*
 * src/info.c
 * Copyleft (C) 2015  Sun Dro (a.k.a 7th Ghost)
 *
 * Get and print additional information about program.
 */


#include "stdinc.h"
#include "info.h"


/* 
 * get_version - Get spartaca version. Function returns 
 * version, build number and build date of application. 
 * Return value is char pointer.
 */
const char* get_version()
{
    static char str[128];
    sprintf(str, "%d.%d build %d (%s)", 
        VERSION_MAX, VERSION_MIN, BUILD_NUMBER, __DATE__);

    return str;
}


/* 
 * greet - Print greeting message. Function returns program 
 * name, version, build number and build date. Argument 
 * p_name is program name from which we want to greet users. 
 */
void greet(char *p_name)
{
    printf("=========================================\n");
    printf("%s Version: %s\n", p_name, get_version());
    printf("=========================================\n");
}


/*
 * Usage - Print usage information of compilator.
 * Argument fname is name of executable application. 
 */
void usage(char *fname)
{
    printf("\nUsage: %s [-i] [-d] [-h]\n", fname);
    printf("Options are:\n");
    printf("   -i         # dump header info in file\n");
    printf("   -d         # dump data in file\n");
    printf("   -h         # print help and usage\n");
    printf("\n");
}

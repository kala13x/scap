/*-----------------------------------------------------
Name: info.c
Date: 2015.05.09
Auth: kala13x (a.k.a 7th Ghost / kala13x)
Desc: Get and print additional information
-----------------------------------------------------*/


#include "stdinc.h"
#include "info.h"


/*---------------------------------------------
| Get application version
---------------------------------------------*/
const char* get_version()
{
    static char version[128];
    sprintf(version, "%s Build %d (%s)", VERSION, BUILD, __DATE__);
    return version;
}


/*---------------------------------------------
| Greet users
---------------------------------------------*/
void greet(void) 
{
    printf("============================================\n");
    printf("sCap: %s\n", get_version());
    printf("============================================\n");
} 


/*---------------------------------------------
| Print usage
---------------------------------------------*/
void usage(void) 
{
    printf("Usage: sCap\n");
    printf("options are:\n");
    printf(" No options right now\n");
    printf("\n");
}

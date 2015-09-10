/*
 *  utils/errex.c
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * Functions for clean memory before exit from application.
 */


#include "stdinc.h"
#include "errex.h"
#include "../slog/slog.h"

/* Max buffer size of message */
#define MAXMSG 8196


/*
 * exit_prog - Exit from program with error message. Function 
 * exits with error message if argument msg is 1, if argument 
 * msg is 0 exit message would not printed. Argument errmsg is 
 * error message which is generated with the various list.
 */
void exit_prog(int msg, char * errmsg, ...) 
{
    char string[MAXMSG];

    /* Read args */
    va_list args;
    va_start(args, errmsg);
    vsprintf(string, errmsg, args);
    va_end(args);

    /* Print message */
    if (msg)
        slog(0, SLOG_ERROR, "%s", string);

/*
    slog(0, SLOG_INFO, "Press enter to exit");
    char c = getchar();
    while (c != '\n')
        c = getchar();
*/
 
    exit(-1);
}


/* 
 * clean_prog - Cleanup on exit. Function handles exit signal
 * and terminates the program. Argument sig is signal value.
 */
void clean_prog(int sig)
{
    /* Handle signals */
    if (sig == SIGILL || sig == SIGSEGV) 
        slog(0, SLOG_FATAL, "Incorrect data!");

    slog(0, SLOG_LIVE, "Cleaning up...");
    exit(-1);
}

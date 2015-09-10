/*
 *  utils/errex.h
 * 
 *  Copyleft (C) 2015  Sun Dro (a.k.a. kala13x)
 *
 * Functions for clean memory before exit from application.
 */


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif


/*
 * exit_prog - Exit from program with error message. Function 
 * exits with error message if argument msg is 1, if argument 
 * msg is 0 exit message would not printed. Argument errmsg is 
 * error message which is generated with the various list.
 */
void exit_prog(int msg, char * errmsg, ...);


/* 
 * clean_prog - Cleanup on exit. Function handles exit signal
 * and terminates the program. Argument sig is signal value.
 */
void clean_prog(int sig);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif
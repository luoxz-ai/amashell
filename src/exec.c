/*!
   \file exec.c
   \brief Contains subroutines for executing parsed input.
 */
#include "amash.h"
#include <sys/wait.h>
//TODO finish this
void set_redirects(Executable *e)
{
    
}

void exec_program(Executable *e)
{
    log_debug("\tPath : %s", e->exec_path);
    log_debug("\tArguments : ");
    int i;
    for (i = 0; i < e->argc; i++)
    {
        log_debug("\t\t%s ", e->argv[i]);
    }

    if (startsWith("quit", e->exec_path))
    {
        do_quit(e);
    }
    else if (strcmp(e->exec_path, "cd") == 0)
    {
        do_cd(e);
    }
    else if (strcmp(e->exec_path, "pwd") == 0)
    {
        do_pwd(e);
    }
    else if (fork() == 0)
    {
        /*child*/
        log_trace("\tFork Successful");
        printf(KMAG "\n__________________________________________________________________________________________________________________________\n");
        printf(KCYN "\n");
        //set_redirects(e);
        if (execvp(e->exec_path, e->argv) != 0)
        {
            log_error("Exec error(error %d)", errno);
            printf(KGRN "\nCommand not found");
            printf(KRED "\n");
        }
        abort();
    }
    wait(NULL);
    printf(KMAG "\n__________________________________________________________________________________________________________________________\n");
    printf(KCYN "\n");
    log_trace("Process Returned\n");
}

/*
   void exec_input(ParsedInput* i)
   {
        assert(false);
        //TODO make this work for pipelined programs
        assert(i->exec_strings_count == 1);
   }
 */


void dump_executable(Executable *e)
{
    log_debug("Beginning dump:");
    log_debug("\tExec path: %s", e->exec_path);
    for (int i = 0; i < e->argc; i++)
    {
        log_debug("Argument %d: %s", i, e->argv[i]);
    }
}

void do_cd(Executable *e)
{
    if (e->argv[1] == NULL)
    {
        chdir("/");
    }
    else
    {
        chdir(e->argv[1]);
    }
}

void do_pwd(Executable *e)
{
    printf("%s\n", get_current_dir_name());
}

void do_quit(Executable *e)
{
    printf("\nBye bye.");
    exit(0);
}

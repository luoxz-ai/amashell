/*!
   \file amash.c
   \brief Contains the main function, and other control structures
   \author "Your name"
   \date "DD"/"Month"/"Year"
*/
#include "amash.h"
#include <string.h>

/**
 *  Basic prefix matching utility function
 *  @param  pre Prefix to test for
 *  @param  str Target string to test
 *  @return     boolean
 */
bool startsWith(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

int run_event_loop(){
    char input[1000];
    do{
        fgets(input, 1000, stdin);
        //ParsedInput* p = parse(input);
        //exec_input(p);
        Executable* e = parse_single(input);
        exec_program(e);

    }while(!startsWith("quit",input));
}

//TODO add something cool here
void print_intro_screen(){

}

int main(){
    print_intro_screen();
    run_event_loop();
}

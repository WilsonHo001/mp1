/******************************************************************
*
*   file:   cmds.c
*   author: wilson ho  
*   date:   2/26/18
*
*   semantic actions for commands called by tutor (cs341, hw2)
*
*   revisions:
*      9/90  eb   cleanup, convert function declarations to ansi
*      9/91  eb   changes so that this can be used for hw1
*      9/02  re   minor changes to quit command
*/
/* the Makefile arranges that #include <..> searches in the right
   places for these headers-- 200920*/

#include <stdio.h>
#include "slex.h"

/*===================================================================*
*
*   Command table for tutor program -- an array of structures of type
*   cmd -- for each command provide the token, the function to call when
*   that token is found, and the help message.
*
*   slex.h contains the typdef for struct cmd, and declares the
*   cmds array as extern to all the other parts of the program.
*   Code in slex.c parses user input command line and calls the
*   requested semantic action, passing a pointer to the cmd struct
*   and any arguments the user may have entered.
*
*===================================================================*/

PROTOTYPE int stop(Cmd *cp, char *arguments);
PROTOTYPE int mem_display(Cmd *cp, char *arguments);
PROTOTYPE int mem_set(Cmd *cp, char *arguments);
PROTOTYPE int help(Cmd *cp, char *arguments);

/* command table */

Cmd cmds[] = {{"md",  mem_display, "Memory display: MD <addr>"},
              {"ms",  mem_set, "Memory set: MS <addr> <value> "},
	      {"h",   help, "Help: H <command>"},
	      {"s",   stop,        "Stop"},
              {NULL,  NULL,        NULL}};  /* null cmd to flag end of table */

char xyz = 6;  /* test global variable  */
char *pxyz = &xyz;  /* test pointer to xyz */
/*===================================================================*
*		command			routines
*
*   Each command routine is called with 2 args, the remaining
*   part of the line to parse and a pointer to the struct cmd for this
*   command. Each returns 0 for continue or 1 for all-done.
*
*===================================================================*/

int stop(Cmd *cp, char *arguments)
{
  return 1;			/* all done flag */
}

/*===================================================================*
*
*   mem_display: display contents of 16 bytes in hex
*
*/

int mem_display(Cmd *cp, char *arguments)
{
  int numprint = 0, address;
  unsigned char *address_ptr;
 
  sscanf(arguments, "%x", &address); 
  address_ptr = (char *)address;
 // printf("addressptr is ", address_ptr);
 
  printf("Here is the address: %08x \n", address);
  for(numprint = 0; numprint < 16; numprint++)
	printf("%02x ", *address_ptr++);

  address_ptr = (unsigned char *)address;
  
  for(numprint = 0; numprint < 16; numprint++)
  {
	if(*address_ptr > 0x20 && *address_ptr < 0x7f)
		printf("%c", *address_ptr++);
	else
	{
		printf(".");
		address_ptr++;
	}
  }

  printf("\n");	  
  printf("Reached mem_display, passed argument string: |%s|\n", arguments);
  printf("        help message: %s\n", cp->help);
  return 0;			/* not done */
}
int mem_set(Cmd *cp, char *arguments)
{
  int value = 0, address;
  char *address_ptr;
  sscanf(arguments,"%x %x", &address, &value );
  address_ptr = (char *)address;
  *address_ptr = value;
  return 0;
}
int help(Cmd *cp, char *arguments)
{
  char size[2];
  int num = 0;
  int length = sizeof(cmds)/sizeof(Cmd);
  
  sscanf(arguments, "%s", size);

  for(num = 0; num < length -1; num++)
	if((strcmp(cmds[num].cmdtoken, size)) ==0)
		printf("%s\n", cmds[num].help);
  return 0;
}


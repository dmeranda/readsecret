/* testpass.c
 */
#include <stdio.h>
#include <string.h>

#include "readsecret.h"

int main( int argc, char** argv )
{
    unsigned char pw[ 16 ];
    int rc;
    int i;
    struct timespec idle_timer;
    struct timespec* idle_timer_ptr = NULL;

    memset(pw, 0xfe, sizeof(pw));

    if( argc > 1 && strcmp(argv[1],"-t")==0 ) {
	idle_timer.tv_sec = 10;
	idle_timer.tv_nsec = 0;
	idle_timer_ptr = & idle_timer;
    }

    rc = rsecret_get_secret_from_tty_timed(
	pw, sizeof(pw)-1,
	"Password: ",
	idle_timer_ptr );

    if( rc == 0 ) {
	printf("Pass was %d characters = [%s]\n", strlen(pw), pw );
    }
    else {
	printf("\nFailed to read password (rc=%d): %s\n",
	       rc, rsecret_strerror(rc) );
    }

    printf("Password buffer is:\n");
    for( i=0; i < sizeof(pw)/2; ++i ) {
	printf("     pw[%2d] = %02x        pw[%2d] = %02x\n",
	       i, pw[i], i+sizeof(pw)/2, pw[i+sizeof(pw)/2] );
    }
    return rc;
}

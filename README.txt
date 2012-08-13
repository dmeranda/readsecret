About "readsecret" by Deron Meranda

Version 1.0  (November 2011)
Homepage: http://deron.meranda.us/computing/c/readsecret/
Author: Deron Meranda <http://deron.meranda.us/

This is free software. See the included LICENSE.txt file for details.


====================
About readsecret
====================

Readsecret is a simple self-contained C (or C++) library intended to
be used on Unix and Unix-like operating systems that need to read a
password or other textual secret typed in by the user while in a
text-mode environment, such as from a console or shell.

It is similar in purpose to the GNU getpass() function but it has
more features, is more secure, and more robust against failures.
For more about GNU getpass, see
    <http://www.gnu.org/s/hello/manual/libc/getpass.html>

  * Can manage timed inputs
  * Handles interrupts and signals more robustly
  * Can prevent core-file dumping during entry to avoid secret disclosure
  * Securely overwrites memory, better than memset()
  * Reentrant and state-free
  * Conservative error handling and reporting



====================
Compiling
====================

It is assumed you have an ANSI C compiler, as well as a POSIX
operating system environment (e.g., Linux or Unix compatible
environment).

The included "build script" uses the SCons tool. The Makefile is just
a front-end to SCons, so you will need SCons to use the Makefile.  You
can obtain SCons from <http://www.scons.org/>.  Most Linux
distributions will provide SCons as an (optional) installable package.

To compile, type one of:

    scons -Q

To install the "libreadsecret" library and associated header file use
one of:

    scons -Q install

or to install to a location other that "/usr/local", use one of:

    scons -Q prefix=/some/directory install


====================
Using
====================

For your programs, you can just include the readsecret source code
into your own sources. But if you wish to use readsecret as a library
you will need to install the library and header file as noted above.
Your C source code should include the readsecret.h header file,

    #include "readsecret.h"

Then you just need to link with the libreadsecret library.  On some
platforms you may also need to link against additional system
libraries (to get access to the POSIX real-time timers). Under Linux
you will need to link with "librt".  For example:

    $ gcc -o myprogram myprogram.c \
          -I /usr/local/include
          -L /usr/local/lib -l readsecret -l rt


====================
Quick Example
====================

#include <stdio.h>
#include "readsecret.h"

int main()
{
    char pass[ 40 ];
    rsecret_error_ty rc;

    rc = rsecret_get_secret_from_tty( pass, sizeof(pass),
                                      "Enter password: " );
    if( rc == RSECRET_SUCCESS ) {
        /* Do something with the password */
        printf( "Your password is: %s\n", pass );
    }
    return 0;
}



====================
Detailed Example
====================
This next example shows a more involved use, and is also more secure
in that it tries to prevent accidental leakage of the password.


#include <stdio.h>
#include <time.h>
#include "readsecret.h"

int main( int argc, char* argv[] )
{
    void* corefile_state;
    struct timespec timeout;

    timeout.tv_sec = 30;  /* A 30.0 second timeout */
    timeout.tv_nsec = 0;

    corefile_state = rsecret_inhibit_corefiles();
    {
        char pass[ 40 ];
        rsecret_error_ty rc;

        rc = rsecret_get_pass_from_tty_timed(
                 pass, sizeof(pass),
                 "Enter password: ",
                 timeout );
        if( rc == RSECRET_SUCCESS ) {
            /* Do something with the password */
            void* hash = hash_password( pass );
        }
        else {
            printf( "Could not read password: %s\n",
                    rsecret_strerror( rc ) );
        }
        rsecret_overwrite_buffer( pass, sizeof(pass) );
    }
    rsecret_restore_corefiles( corefile_state );
    return 0;
}



====================
Signal handling
====================

These signals may be used: SIGINT, SIGTERM, SIGALRM

The functions that get secrets or passwords,
rsecret_get_secret_from_tty() and rsecret_get_secret_from_tty_timed(),
will attempt to catch signals typically used to interrupt or terminate
the process, namely SIGINT and SIGTERM.  These are often raised by the
user aborting the process, for example by entering Control-C.

If these signals occur, the functions will insure that no
partially-entered secret or password still resides in memory or in the
terminal I/O buffers, and then return with a RSECRET_ERROR_INTERRUPTED
error code.  However if either SIGINT or SIGTERM have been ignored
with SIG_IGN prior to calling these functions, then those signals will
continue to ignored and will not abort the text entry.

If you have established your own signal handlers, understand that
while one of these function is operating your handlers will not be
called. However your handlers will be re-established as you had left
them when these functions do return.

When using timed text entry, the SIGALRM signal is also diverted and
used internally. Again, upon exit the original handler for that signal
will be restored.



====================
Terminal device
====================

The functions that get secrets or passwords from the user will open
the process's controling terminal device, typically /dev/tty but may
be different under some operating systems.  It will not read from
stdin.

While the function is active it will disable the echoing of characters
to the terminal, and will restore the terminal line disipline upon
completion. The terminal is kept in cooked icannon line mode rather
than raw character mode, so terminal controls such as backspace work
as configured (see stty(1) man page). Also note these functions will
attempt to flush the terminal I/O buffers at appropriate points to
help prevent accidental keystroke leakage.

Nothing special is done regarding character sets. Under Linux usually
the IUTF8 input mode flag is set so that the returned byte string will
be encoded in UTF-8, but this is outside of the responsibility of this
library.

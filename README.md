<!-- -*- coding: utf-8 -*-
****
****   This file is in Markdown format. It is primarily used to
****   display a top-level project page in the Github repository.
****
****   For a more detailed README, see the "README.txt" file.
****
-->
readsecret
==========

Readsecret is a simple self-contained C (or C++) library intended to
be used on Unix and Unix-like operating systems that need to read a
password or other textual secret typed in by the user while in a
text-mode environment, such as from a console or shell.

It is similar in purpose to the GNU getpass() function but it has
more features, is more secure, and more robust against failures.
For more about GNU getpass, see
http://www.gnu.org/s/hello/manual/libc/getpass.html

  * Can manage timed inputs
  * Handles interrupts and signals more robustly
  * Can prevent core-file dumping during entry to avoid secret disclosure
  * Securely overwrites memory, better than memset()
  * Reentrant and state-free
  * Conservative error handling and reporting


More information
================
Complete documentation and additional information is available on the
[readsecret project homepage](http://deron.meranda.us/computing/c/readsecret/).

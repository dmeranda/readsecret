# Makefile for readsecret
# By Deron Meranda <http://deron.meranda.us/>
#
# All the real work is done by scons.  See the file "SConstruct".

prefix=/usr/local

all:
	scons -Q

install:
	scons -Q prefix=$(prefix) install

clean:
	scons -Q -c
	-rm -f config.log

realclean:
	scons -Q -c
	-rm -f config.log
	-rm -fr .sconf_temp
	-rm -fr .sconsign.dblite

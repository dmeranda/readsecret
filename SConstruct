# SConstruct for readsecret                        -*- python -*-
# By Deron Meranda <http://deron.meranda.us/>
#
# This is a "build" script. It uses the SCons build tool. See http://www.scons.org/
#
# To build the library:
#
#      scons -Q
#
# To install it, one of:
#
#      scons -Q install
#      scons -Q prefix=/usr/local install
#
import os

prefix = ARGUMENTS.get("prefix","/usr/local")
includedir = os.path.join(prefix, "include")
libdir = os.path.join(prefix, "lib")


env = Environment()
conf = Configure(env)
have_librt =  conf.CheckLib('rt')
env = conf.Finish()

LIBS=["readsecret"]
if have_librt:
    LIBS.append("rt")

libreadsecret = env.SharedLibrary( target='readsecret', source=['readsecret.c'] )
testprogram = env.Program( [ 'testpass.c' ], LIBS=LIBS, LIBPATH='.' )

install = env.Alias('install',
                    [ env.Install(includedir, "readsecret.h"),
                      env.Install(libdir, libreadsecret) ] )

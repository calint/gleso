#NDK_TOOLCHAIN_VERSION:=clang
APP_STL:=stlport_static
APP_CPPFLAGS+=-fexceptions -std=c++11 -Wfatal-errors #-Wall -Wextra -pedantic

// included from gleso.h  supplies adaptation for android
#ifndef GLES_H
#include<GLES2/gl2.h>
#include<GLES2/gl2ext.h>
#include<android/log.h>
#define p(...)__android_log_print(ANDROID_LOG_INFO,"gleso",__VA_ARGS__)
#define GLESO_EMBEDDED
#define GLES_H
#endif

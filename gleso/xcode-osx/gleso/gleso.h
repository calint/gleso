// cross platform interface
#ifndef GLESO_H
int gleso_argc;
char**gleso_argv;
#ifdef __cplusplus
#include"gles.h"
extern "C" {
#endif
    int gleso_init();// called when opengl context needs reload
    void gleso_step();// called when opengl ready for render
    void gleso_on_viewport_change(const int width,const int height);// called when screen size changes
#ifdef __cplusplus
}
#endif
#define GLESO_H
#endif

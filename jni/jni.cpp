#include<jni.h>
#include"gleso.cpp"
extern"C"{
    JNIEXPORT int JNICALL Java_a_gleso_jni_glesoinit(JNIEnv*env,jobject obj){return gleso_init();}
    JNIEXPORT void JNICALL Java_a_gleso_jni_glesoonviewportchange(JNIEnv*env,jobject obj,jint width,jint height){gleso_on_viewport_change(width,height);}
    JNIEXPORT void JNICALL Java_a_gleso_jni_glesostep(JNIEnv*env,jobject obj){gleso_step();}
}

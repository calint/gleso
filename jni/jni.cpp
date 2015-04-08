#include<jni.h>
#include"gleso.cpp"
extern"C"{
	JNIEXPORT int JNICALL Java_a_gleso_jni_glesoinit(JNIEnv*env,jobject obj){return gleso_init();}
	JNIEXPORT void JNICALL Java_a_gleso_jni_glesoviewport(JNIEnv*env,jobject obj,jint width,jint height){gleso_viewport(width,height);}
	JNIEXPORT void JNICALL Java_a_gleso_jni_glesostep(JNIEnv*env,jobject obj){gleso_step();}
	JNIEXPORT void JNICALL Java_a_gleso_jni_glesokey(JNIEnv*env,jobject obj,jint key,jint scancode,jint action,jint mod){gleso_key(key,scancode,action,mod);}
	JNIEXPORT void JNICALL Java_a_gleso_jni_glesotouch(JNIEnv*env,jobject obj,jfloat x,jfloat y,jint action){gleso_touch(x,y,action);}
}

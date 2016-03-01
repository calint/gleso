package a.gleso;
public class jni{
     static{System.loadLibrary("jni");}
     public static native int glesoinit();
     public static native void glesoviewport(int width, int height);
     public static native void glesostep();
     public static native void glesokey(int key,int scancode,int action,int mod);
     public static native void glesotouch(float x,float y,int action);
}

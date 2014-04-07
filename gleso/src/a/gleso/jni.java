package a.gleso;
public class jni{
     static{System.loadLibrary("jni");}
     public static native int glesoinit();
     public static native void glesoonviewportchange(int width, int height);
     public static native void glesostep();
}

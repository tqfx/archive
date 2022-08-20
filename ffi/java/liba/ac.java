package liba;

public class ac {
    static {
        System.loadLibrary("ac");
    }

    public native String version();
    public native int version_major();
    public native int version_minor();
    public native int version_patch();

    public native float int_sqrt(float x);
}

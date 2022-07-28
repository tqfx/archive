package liba;

public class a {
    static {
        System.loadLibrary("a");
    }

    public native String version();
    public native int version_major();
    public native int version_minor();
    public native int version_patch();

    public native float int_sqrt(float x);
}

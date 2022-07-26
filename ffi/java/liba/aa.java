package liba;

public class aa {
    static {
        System.loadLibrary("aa");
    }

    public native String version();
    public native int version_major();
    public native int version_minor();
    public native int version_patch();
}

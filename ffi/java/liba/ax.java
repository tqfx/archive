package liba;

public class ax {
    static {
        System.loadLibrary("ax");
    }

    public native String version();
    public native int version_major();
    public native int version_minor();
    public native int version_patch();
}

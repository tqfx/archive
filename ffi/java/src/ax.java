package liba;

public class ax {
    static {
        System.loadLibrary("ax");
    }
    public final static native String version();
    public final static native int version_major();
    public final static native int version_minor();
    public final static native int version_patch();
}

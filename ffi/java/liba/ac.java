package liba;

public class ac {
    static {
        System.loadLibrary("ac");
    }
    public final static native String version();
    public final static native int version_major();
    public final static native int version_minor();
    public final static native int version_patch();

    public final static native float int_sqrt(float x);
}

public class aa {
    static {
        System.loadLibrary("aa-jni");
    }

    public native String version();

    public static void main(String[] args) {
        aa obj = new aa();
        System.out.println("version " + obj.version());
    }
}

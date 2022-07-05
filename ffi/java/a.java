public class a {
    static {
        System.loadLibrary("a-jni");
    }

    public native String version();

    public static void main(String[] args) {
        a obj = new a();
        System.out.println("version " + obj.version());
    }
}

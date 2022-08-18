import liba.ax;

public class axTest {
    public static void main(String[] args) {
        ax obj = new ax();
        System.out.println("version " + obj.version());
        System.out.println("major " + obj.version_major());
        System.out.println("minor " + obj.version_minor());
        System.out.println("patch " + obj.version_patch());
    }
}

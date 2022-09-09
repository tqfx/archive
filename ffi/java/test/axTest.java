import liba.ax;

public class axTest {
    public static void main(String[] args) {
        System.out.println("version " + ax.version());
        System.out.println("major " + ax.version_major());
        System.out.println("minor " + ax.version_minor());
        System.out.println("patch " + ax.version_patch());
    }
}

import liba.aa;

public class aaTest {
    public static void main(String[] args) {
        aa obj = new aa();
        System.out.println("version " + obj.version());
        System.out.println("major " + obj.version_major());
        System.out.println("minor " + obj.version_minor());
        System.out.println("patch " + obj.version_patch());
    }
}

import liba.a;

public class aTest {
    public static void main(String[] args) {
        a obj = new a();
        System.out.println("version " + obj.version());
        System.out.println("major " + obj.version_major());
        System.out.println("minor " + obj.version_minor());
        System.out.println("patch " + obj.version_patch());
    }
}

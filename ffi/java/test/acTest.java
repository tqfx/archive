import liba.ac;

public class acTest {
    public static void main(String[] args) {
        ac obj = new ac();
        System.out.println("version " + obj.version());
        System.out.println("major " + obj.version_major());
        System.out.println("minor " + obj.version_minor());
        System.out.println("patch " + obj.version_patch());
    }
}

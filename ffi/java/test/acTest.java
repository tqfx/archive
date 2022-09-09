import liba.ac;

public class acTest {
    public static void main(String[] args) {
        System.out.println("version " + ac.version());
        System.out.println("major " + ac.version_major());
        System.out.println("minor " + ac.version_minor());
        System.out.println("patch " + ac.version_patch());
        test_pid();
    }
    public static void test_pid() {
        ac.pid pid = new ac.pid(1, -10, 10);
        System.out.print(pid.proc(1, 0) + " ");
        pid.off().inc().pos(10);
        pid.kpid(10, 0.1, 1);
        pid.mode(ac.pid.INC);
        pid.time(0.1).done();
        System.out.println(pid.proc(1, 0));
    }
}

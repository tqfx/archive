import liba.ac;

public class acTest {
    public static void main(String[] args) {
        System.out.println("version " + ac.version());
        System.out.println("major " + ac.version_major());
        System.out.println("minor " + ac.version_minor());
        System.out.println("patch " + ac.version_patch());
        test_pid();
        test_polytrack3();
        test_polytrack5();
        test_polytrack7();
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

    public static void test_polytrack3() {
        double[] source = { 0, 0, 0 };
        double[] target = { 1, 1, 1 };
        ac.polytrack3 obj = new ac.polytrack3(source, target);
        double[] out = obj.all(0.5);
        System.out.print(obj.pos(0.5) + "," + obj.vec(0.5) + "," + obj.acc(0.5));
        System.out.println(" " + out[0] + "," + out[1] + "," + out[2]);
    }

    public static void test_polytrack5() {
        double[] source = { 0, 0, 0, 0 };
        double[] target = { 1, 1, 1, 1 };
        ac.polytrack5 obj = new ac.polytrack5(source, target);
        double[] out = obj.all(0.5);
        System.out.print(obj.pos(0.5) + "," + obj.vec(0.5) + "," + obj.acc(0.5));
        System.out.println(" " + out[0] + "," + out[1] + "," + out[2]);
    }

    public static void test_polytrack7() {
        double[] source = { 0, 0, 0, 0, 0 };
        double[] target = { 1, 1, 1, 1, 1 };
        ac.polytrack7 obj = new ac.polytrack7(source, target);
        double[] out = obj.all(0.5);
        System.out.print(obj.pos(0.5) + "," + obj.vec(0.5) + "," + obj.acc(0.5) + "," + obj.jer(0.5));
        System.out.println(" " + out[0] + "," + out[1] + "," + out[2] + "," + out[3]);
    }
}

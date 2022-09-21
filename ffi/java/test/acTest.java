import liba.ac;

public class acTest {
    public static void main(String[] args) {
        System.out.println("version " + ac.version());
        System.out.println("major " + ac.version_major());
        System.out.println("minor " + ac.version_minor());
        System.out.println("patch " + ac.version_patch());
        test_mf();
        test_pid();
        test_fpid();
        test_polytrack3();
        test_polytrack5();
        test_polytrack7();
    }

    public static void test_mf() {
        ac.mf.gauss(0, 0, 0);
        ac.mf.gbell(0, 0, 0, 0);
        ac.mf.sig(0, 0, 0);
        ac.mf.trap(0, 0, 0, 0, 0);
        ac.mf.tri(0, 0, 0, 0);
        ac.mf.z(0, 0, 0);
    }

    public static void test_pid() {
        ac.pid pid = new ac.pid(1, -10, +10);
        System.out.print(pid.proc(1, 0) + " ");
        pid.off().inc().pos(10);
        pid.kpid(10, 0.1, 1);
        pid.mode(ac.pid.INC);
        pid.time(0.1).done();
        System.out.println(pid.proc(1, 0));
    }

    public static void test_fpid() {
        final int NB = -3;
        final int NM = -2;
        final int NS = -1;
        final int ZO = 0;
        final int PS = +1;
        final int PM = +2;
        final int PB = +3;
        double[][] mkp = {
                { NB, NB, NM, NM, NS, ZO, ZO },
                { NB, NB, NM, NS, NS, ZO, PS },
                { NM, NM, NM, NS, ZO, PS, PS },
                { NM, NM, NS, ZO, PS, PM, PM },
                { NS, NS, ZO, PS, PS, PM, PM },
                { NS, ZO, PS, PM, PM, PM, PB },
                { ZO, ZO, PM, PM, PM, PB, PB },
        };
        double[][] mki = {
                { PB, PB, PM, PM, PS, ZO, ZO },
                { PB, PB, PM, PS, PS, ZO, ZO },
                { PB, PM, PS, PS, ZO, NS, NS },
                { PM, PM, PS, ZO, NS, NM, NM },
                { PM, PS, ZO, NS, NS, NM, NB },
                { ZO, ZO, NS, NS, NM, NB, NB },
                { ZO, ZO, NS, NM, NM, NB, NB },
        };
        double[][] mkd = {
                { NS, PS, PB, PB, PB, PM, NS },
                { NS, PS, PB, PM, PM, PS, ZO },
                { ZO, PS, PM, PM, PS, PS, ZO },
                { ZO, PS, PS, PS, PS, PS, ZO },
                { ZO, ZO, ZO, ZO, ZO, ZO, ZO },
                { NB, NS, NS, NS, NS, NS, NB },
                { NB, NM, NM, NM, NS, NS, NB },
        };
        double[][] mma = {
                { ac.mf.TRI, -3, -3, -2 },
                { ac.mf.TRI, -3, -2, -1 },
                { ac.mf.TRI, -2, -1, +0 },
                { ac.mf.TRI, -1, +0, +1 },
                { ac.mf.TRI, +0, +1, +2 },
                { ac.mf.TRI, +1, +2, +3 },
                { ac.mf.TRI, +2, +3, +3 },
                { ac.mf.NUL },
        };
        ac.fpid fpid = new ac.fpid(0, 1, mma, mkp, mki, mkd, -3, 3, -10, +10);
        System.out.print(fpid.proc(1, 0) + " ");
        fpid.off().inc().pos(10).buff(2);
        fpid.kpid(10, 0.1, 1);
        fpid.mode(ac.pid.INC);
        fpid.time(0.1).done();
        System.out.println(fpid.proc(1, 0));
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

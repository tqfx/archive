import liba.a;

public class aTest {
    public static void main(String[] args) {
        System.out.println("version " + a.version());
        System.out.println("major " + a.version_major());
        System.out.println("minor " + a.version_minor());
        System.out.println("patch " + a.version_patch());
        test_mf();
        test_tf();
        test_pid();
        test_fpid();
        test_polytrack3();
        test_polytrack5();
        test_polytrack7();
    }

    public static void test_mf() {
        a.mf.gauss(0, 0, 0);
        a.mf.gbell(0, 0, 0, 0);
        a.mf.sig(0, 0, 0);
        a.mf.trap(0, 0, 0, 0, 0);
        a.mf.tri(0, 0, 0, 0);
        a.mf.z(0, 0, 0);
    }

    public static void test_tf() {
        double num[] = { 6.59492796e-05, 6.54019884e-05 };
        double den[] = { -1.97530991, 0.97530991 };
        a.tf tf = new a.tf(num, den);
        System.out.println(tf.proc(1));
        tf.zero();
    }

    public static void test_pid() {
        a.pid pid = new a.pid(1, -10, +10);
        System.out.print(pid.proc(1, 0) + " ");
        pid.off().inc().pos(10);
        pid.kpid(10, 0.1, 1);
        pid.mode(a.pid.INC);
        pid.time(0.1).zero();
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
        double[][] mmp = {
                { a.mf.TRI, NB, NB, NM },
                { a.mf.TRI, NB, NM, NS },
                { a.mf.TRI, NM, NS, ZO },
                { a.mf.TRI, NS, ZO, PS },
                { a.mf.TRI, ZO, PS, PM },
                { a.mf.TRI, PS, PM, PB },
                { a.mf.TRI, PM, PB, PB },
                { a.mf.NUL },
        };
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
        a.fpid fpid = new a.fpid(0, 1, mmp, mkp, mki, mkd, -3, 3, -10, +10);
        System.out.print(fpid.proc(1, 0) + " ");
        fpid.off().inc().pos(10).buff(2);
        fpid.kpid(10, 0.1, 1);
        fpid.mode(a.pid.INC);
        fpid.time(0.1).zero();
        System.out.println(fpid.proc(1, 0));
    }

    public static void test_polytrack3() {
        double[] t = { 0, 1 };
        double[] q = { 0, 1 };
        double[] v = { 0, 1 };
        double[] source = { 0, 0, 0 };
        double[] target = { 1, 1, 1 };
        a.polytrack3 obj = new a.polytrack3(0, 1, 0, 1, 0, 1);
        obj.init(t, q, v);
        obj.init(source, target);
        double[] out = obj.out(0.5);
        System.out.print(obj.pos(0.5) + "," + obj.vec(0.5) + "," + obj.acc(0.5));
        System.out.println(" " + out[0] + "," + out[1] + "," + out[2]);
    }

    public static void test_polytrack5() {
        double[] t = { 0, 1 };
        double[] q = { 0, 1 };
        double[] v = { 0, 1 };
        double[] a = { 0, 1 };
        double[] source = { 0, 0, 0, 0 };
        double[] target = { 1, 1, 1, 1 };
        a.polytrack5 obj = new a.polytrack5(0, 1, 0, 1, 0, 1, 0, 1);
        obj.init(t, q, v, a);
        obj.init(source, target);
        double[] out = obj.out(0.5);
        System.out.print(obj.pos(0.5) + "," + obj.vec(0.5) + "," + obj.acc(0.5));
        System.out.println(" " + out[0] + "," + out[1] + "," + out[2]);
    }

    public static void test_polytrack7() {
        double[] t = { 0, 1 };
        double[] q = { 0, 1 };
        double[] v = { 0, 1 };
        double[] a = { 0, 1 };
        double[] j = { 0, 1 };
        double[] source = { 0, 0, 0, 0, 0 };
        double[] target = { 1, 1, 1, 1, 1 };
        a.polytrack7 obj = new a.polytrack7(0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
        obj.init(t, q, v, a, j);
        obj.init(source, target);
        double[] out = obj.out(0.5);
        System.out.print(obj.pos(0.5) + "," + obj.vec(0.5) + "," + obj.acc(0.5) + "," + obj.jer(0.5));
        System.out.println(" " + out[0] + "," + out[1] + "," + out[2] + "," + out[3]);
    }
}

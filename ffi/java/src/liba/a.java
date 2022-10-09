package liba;

public class a {
    static {
        System.loadLibrary("a");
    }

    public final static native String version();

    public final static native int version_major();

    public final static native int version_minor();

    public final static native int version_patch();

    public final static native float sqrt_inv(float x);

    public final static class mf {
        public final static int NUL = 0;
        public final static int GAUSS = 1;
        public final static int GBELL = 2;
        public final static int SIG = 3;
        public final static int TRAP = 4;
        public final static int TRI = 5;
        public final static int Z = 6;

        public final static native double gauss(double x, double sigma, double c);

        public final static native double gbell(double x, double a, double b, double c);

        public final static native double sig(double x, double a, double c);

        public final static native double trap(double x, double a, double b, double c, double d);

        public final static native double tri(double x, double a, double b, double c);

        public final static native double z(double x, double a, double b);
    }

    public final static class tf {
        public double num[];
        public double den[];
        double u[];
        double v[];

        public tf(double num[], double den[]) {
            this.init(num, den);
        }

        public final native tf init(double num[], double den[]);

        public final native double proc(double x);

        public final native tf zero();
    }

    public final static class pid {
        public final static int OFF = 0;
        public final static int POS = 1;
        public final static int INC = 2;
        public double dt;
        public double kp;
        public double ki;
        public double kd;
        public double summax;
        public double outmax;
        public double outmin;
        public double out;
        public double sum;
        public double fdb;
        public double ec;
        public double e;
        int num;
        int reg;

        public pid(double dt, double min, double max) {
            this.init(dt, min, max).inc();
        }

        public pid(double dt, double min, double max, double sum) {
            this.init(dt, min, max).pos(sum);
        }

        public pid(double dt, double kp, double ki, double kd, double min, double max) {
            this.init(dt, min, max).kpid(kp, ki, kd).inc();
        }

        public pid(double dt, double kp, double ki, double kd, double min, double max, double sum) {
            this.init(dt, min, max).kpid(kp, ki, kd).pos(sum);
        }

        public final native pid inc();

        public final native pid off();

        public final native pid pos(double max);

        public final native pid mode(int mode);

        public final native pid time(double dt);

        public final native pid kpid(double kp, double ki, double kd);

        public final native pid init(double dt, double min, double max);

        public final native double proc(double set, double fdb);

        public final native pid zero();
    }

    public final static class fpid {
        public pid pid;
        double[] mmp;
        double[] mkp;
        double[] mki;
        double[] mkd;
        double[] mat;
        double[] mms;
        int[] idx;
        double sigma;
        double alpha;
        public double kp;
        public double ki;
        public double kd;
        long op;

        public fpid(int num, double dt, double[][] mmp,
                double[][] mkp, double[][] mki, double[][] mkd,
                double imin, double imax, double omin, double omax) {
            this.pid = new pid(dt, omin, omax);
            this.init(dt, mmp, mkp, mki, mkd, imin, imax, omin, omax).buff(num);
        }

        public fpid(int num, double dt, double[][] mmp,
                double[][] mkp, double[][] mki, double[][] mkd,
                double imin, double imax, double omin, double omax, double sum) {
            this.pid = new pid(dt, omin, omax, sum);
            this.init(dt, mmp, mkp, mki, mkd, imin, imax, omin, omax).buff(num);
        }

        public final native fpid inc();

        public final native fpid off();

        public final native fpid pos(double max);

        public final native fpid mode(int reg);

        public final native fpid time(double dt);

        public final native fpid ilim(double min, double max);

        public final native fpid olim(double min, double max);

        public final native fpid kpid(double kp, double ki, double kd);

        public final native fpid buff(int num);

        public final native fpid base(double[][] mmp, double[][] mkp, double[][] mki, double[][] mkd);

        public final native fpid init(double dt, double[][] mmp,
                double[][] mkp, double[][] mki, double[][] mkd,
                double imin, double imax, double omin, double omax);

        public final native double proc(double set, double fdb);

        public final native fpid zero();

    }

    public final static class polytrack3 {
        public double[] k;
        public double[] t;
        public double[] q;
        public double[] v;

        private polytrack3() {
            this.k = new double[4];
            this.t = new double[2];
            this.q = new double[2];
            this.v = new double[2];
        }

        public polytrack3(double[] source, double[] target) {
            this();
            this.init(source, target);
        }

        public polytrack3(double[] t, double[] q, double[] v) {
            this();
            this.init(t, q, v);
        }

        public polytrack3(double t0, double t1, double q0, double q1) {
            this();
            this.init(t0, t1, q0, q1);
        }

        public polytrack3(double t0, double t1, double q0, double q1, double v0, double v1) {
            this();
            this.init(t0, t1, q0, q1, v0, v1);
        }

        public final native polytrack3 init(double t0, double t1, double q0, double q1, double v0, double v1);

        public final native polytrack3 init(double t0, double t1, double q0, double q1);

        public final native polytrack3 init(double[] t, double[] q, double[] v);

        public final native polytrack3 init(double[] source, double[] target);

        public final native double[] out(double ts);

        public final native double pos(double ts);

        public final native double vec(double ts);

        public final native double acc(double ts);
    }

    public final static class polytrack5 {
        public double[] k;
        public double[] t;
        public double[] q;
        public double[] v;
        public double[] a;

        private polytrack5() {
            this.k = new double[6];
            this.t = new double[2];
            this.q = new double[2];
            this.v = new double[2];
            this.a = new double[2];
        }

        public polytrack5(double[] source, double[] target) {
            this();
            this.init(source, target);
        }

        public polytrack5(double[] t, double[] q, double[] v) {
            this();
            this.init(t, q, v);
        }

        public polytrack5(double[] t, double[] q, double[] v, double[] a) {
            this();
            this.init(t, q, v, a);
        }

        public polytrack5(double t0, double t1, double q0, double q1) {
            this();
            this.init(t0, t1, q0, q1);
        }

        public polytrack5(double t0, double t1, double q0, double q1, double v0, double v1) {
            this();
            this.init(t0, t1, q0, q1, v0, v1);
        }

        public polytrack5(double t0, double t1, double q0, double q1, double v0, double v1,
                double a0, double a1) {
            this();
            this.init(t0, t1, q0, q1, v0, v1, a0, a1);
        }

        public final native polytrack5 init(double t0, double t1, double q0, double q1, double v0, double v1,
                double a0, double a1);

        public final native polytrack5 init(double t0, double t1, double q0, double q1, double v0, double v1);

        public final native polytrack5 init(double t0, double t1, double q0, double q1);

        public final native polytrack5 init(double[] t, double[] q, double[] v, double[] a);

        public final native polytrack5 init(double[] t, double[] q, double[] v);

        public final native polytrack5 init(double[] source, double[] target);

        public final native double[] out(double ts);

        public final native double pos(double ts);

        public final native double vec(double ts);

        public final native double acc(double ts);
    }

    public final static class polytrack7 {
        public double[] k;
        public double[] t;
        public double[] q;
        public double[] v;
        public double[] a;
        public double[] j;

        private polytrack7() {
            this.k = new double[8];
            this.t = new double[2];
            this.q = new double[2];
            this.v = new double[2];
            this.a = new double[2];
            this.j = new double[2];
        }

        public polytrack7(double[] source, double[] target) {
            this();
            this.init(source, target);
        }

        public polytrack7(double[] t, double[] q, double[] v) {
            this();
            this.init(t, q, v);
        }

        public polytrack7(double[] t, double[] q, double[] v, double[] a) {
            this();
            this.init(t, q, v, a);
        }

        public polytrack7(double[] t, double[] q, double[] v, double[] a, double[] j) {
            this();
            this.init(t, q, v, a, j);
        }

        public polytrack7(double t0, double t1, double q0, double q1) {
            this();
            this.init(t0, t1, q0, q1);
        }

        public polytrack7(double t0, double t1, double q0, double q1, double v0, double v1) {
            this();
            this.init(t0, t1, q0, q1, v0, v1);
        }

        public polytrack7(double t0, double t1, double q0, double q1, double v0, double v1,
                double a0, double a1) {
            this();
            this.init(t0, t1, q0, q1, v0, v1, a0, a1);
        }

        public polytrack7(double t0, double t1, double q0, double q1, double v0, double v1,
                double a0, double a1, double j0, double j1) {
            this();
            this.init(t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
        }

        public final native polytrack7 init(double t0, double t1, double q0, double q1, double v0, double v1,
                double a0, double a1, double j0, double j1);

        public final native polytrack7 init(double t0, double t1, double q0, double q1, double v0, double v1,
                double a0, double a1);

        public final native polytrack7 init(double t0, double t1, double q0, double q1, double v0, double v1);

        public final native polytrack7 init(double t0, double t1, double q0, double q1);

        public final native polytrack7 init(double[] t, double[] q, double[] v, double[] a, double[] j);

        public final native polytrack7 init(double[] t, double[] q, double[] v, double[] a);

        public final native polytrack7 init(double[] t, double[] q, double[] v);

        public final native polytrack7 init(double[] source, double[] target);

        public final native double[] out(double ts);

        public final native double pos(double ts);

        public final native double vec(double ts);

        public final native double acc(double ts);

        public final native double jer(double ts);
    }
}

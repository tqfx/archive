package liba;

public class ac {
    static {
        System.loadLibrary("ac");
    }

    public final static native String version();

    public final static native int version_major();

    public final static native int version_minor();

    public final static native int version_patch();

    public final static native float int_sqrt(float x);

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
        public double ts;
        public double kp;
        public double ki;
        public double kd;
        public double out;
        public double outmin;
        public double outmax;
        public double summax;
        public double sum;
        public double ref;
        public double ec;
        public double e;
        int mode;
        int num;

        public pid(double ts, double min, double max) {
            this.init(ts, min, max);
        }

        public final native pid inc();

        public final native pid off();

        public final native pid pos(double max);

        public final native pid mode(int mode);

        public final native pid time(double ts);

        public final native pid kpid(double kp, double ki, double kd);

        public final native pid init(double ts, double min, double max);

        public final native double proc(double set, double ref);

        public final native pid zero();
    }

    public final static class fpid {
        public pid pid;
        double[] mkp;
        double[] mki;
        double[] mkd;
        double[] mma;
        double[] mat;
        double[] mms;
        int[] idx;
        double sigma;
        double alpha;
        public double kp;
        public double ki;
        public double kd;
        long op;

        public fpid(int num, double ts, double[][] mma,
                double[][] mkp, double[][] mki, double[][] mkd,
                double imin, double imax, double omin, double omax) {
            this.pid = new pid(ts, omin, omax);
            this.init(ts, mma, mkp, mki, mkd, imin, imax, omin, omax).buff(num);
        }

        public final native fpid inc();

        public final native fpid off();

        public final native fpid pos(double max);

        public final native fpid mode(int mode);

        public final native fpid time(double ts);

        public final native fpid ilim(double min, double max);

        public final native fpid olim(double min, double max);

        public final native fpid kpid(double kp, double ki, double kd);

        public final native fpid buff(int num);

        public final native fpid base(double[][] mma, double[][] mkp, double[][] mki, double[][] mkd);

        public final native fpid init(double ts, double[][] mma,
                double[][] mkp, double[][] mki, double[][] mkd,
                double imin, double imax, double omin, double omax);

        public final native double proc(double set, double ref);

        public final native fpid zero();

    }

    public final static class polytrack3 {
        public double[] t;
        public double[] q;
        public double[] v;
        public double[] k;

        public polytrack3(double[] source, double[] target) {
            this.t = new double[2];
            this.q = new double[2];
            this.v = new double[2];
            this.k = new double[4];
            this.init(source, target);
        }

        public final native polytrack3 init(double[] source, double[] target);

        public final native double[] all(double ts);

        public final native double pos(double ts);

        public final native double vec(double ts);

        public final native double acc(double ts);
    }

    public final static class polytrack5 {
        public double[] t;
        public double[] q;
        public double[] v;
        public double[] a;
        public double[] k;

        public polytrack5(double[] source, double[] target) {
            this.t = new double[2];
            this.q = new double[2];
            this.v = new double[2];
            this.a = new double[2];
            this.k = new double[6];
            this.init(source, target);
        }

        public final native polytrack5 init(double[] source, double[] target);

        public final native double[] all(double ts);

        public final native double pos(double ts);

        public final native double vec(double ts);

        public final native double acc(double ts);
    }

    public final static class polytrack7 {
        public double[] t;
        public double[] q;
        public double[] v;
        public double[] a;
        public double[] j;
        public double[] k;

        public polytrack7(double[] source, double[] target) {
            this.t = new double[2];
            this.q = new double[2];
            this.v = new double[2];
            this.a = new double[2];
            this.j = new double[2];
            this.k = new double[8];
            this.init(source, target);
        }

        public final native polytrack7 init(double[] source, double[] target);

        public final native double[] all(double ts);

        public final native double pos(double ts);

        public final native double vec(double ts);

        public final native double acc(double ts);

        public final native double jer(double ts);
    }
}

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
        public final native pid done();
    }
}

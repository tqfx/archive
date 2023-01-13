package liba;

/** cubic polynomial trajectory */
public final class polytrack3 {
    /** quantity */
    public double[] k = new double[4];
    /** time */
    public double[] t = new double[2];
    /** position */
    public double[] q = new double[2];
    /** velocity */
    public double[] v = new double[2];

    /**
     * construct a new {@link polytrack3} object
     *
     * @param source source for trajectory
     * @param target target for trajectory
     */
    public polytrack3(double[] source, double[] target) {
        this.init(source, target);
    }

    /**
     * construct a new {@link polytrack3} object
     *
     * @param t time
     * @param q position
     * @param v velocity
     */
    public polytrack3(double[] t, double[] q, double[] v) {
        this.init(t, q, v);
    }

    /**
     * construct a new {@link polytrack3} object
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     */
    public polytrack3(double t0, double t1, double q0, double q1) {
        this.init(t0, t1, q0, q1);
    }

    /**
     * construct a new {@link polytrack3} object
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     */
    public polytrack3(double t0, double t1, double q0, double q1, double v0, double v1) {
        this.init(t0, t1, q0, q1, v0, v1);
    }

    /**
     * initialize function for cubic polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @param v0 velocity for source
     * @param v1 velocity for target
     * @return {@link polytrack3}
     */
    public final native polytrack3 init(double t0, double t1, double q0, double q1, double v0, double v1);

    /**
     * initialize function for cubic polynomial trajectory
     *
     * @param t0 time for source
     * @param t1 time for target
     * @param q0 position for source
     * @param q1 position for target
     * @return {@link polytrack3}
     */
    public final native polytrack3 init(double t0, double t1, double q0, double q1);

    /**
     * initialize function for cubic polynomial trajectory
     *
     * @param t time
     * @param q position
     * @param v velocity
     * @return {@link polytrack3}
     */
    public final native polytrack3 init(double[] t, double[] q, double[] v);

    /**
     * initialize function for cubic polynomial trajectory
     *
     * @param source source for trajectory
     * @param target target for trajectory
     * @return {@link polytrack3}
     */
    public final native polytrack3 init(double[] source, double[] target);

    /**
     * process function for cubic polynomial trajectory
     *
     * @param ts current time unit(s)
     * @return current output
     */
    public final native double[] out(double ts);

    /**
     * process function for cubic polynomial trajectory position
     *
     * @param ts current time unit(s)
     * @return position output
     */
    public final native double pos(double ts);

    /**
     * process function for cubic polynomial trajectory velocity
     *
     * @param ts current time unit(s)
     * @return velocity output
     */
    public final native double vec(double ts);

    /**
     * process function for cubic polynomial trajectory acceleration
     *
     * @param ts current time unit(s)
     * @return acceleration output
     */
    public final native double acc(double ts);
}

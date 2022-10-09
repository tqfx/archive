#include "lib.h"
#include "a/math.h"
#include "a/version.h"

emscripten::val version()
{
    return emscripten::val(a_version());
}

#include "a/pid.h"

class pid
{
    a_pid_s ctx[1];

public:
    pid(double jdt, double jmin, double jmax)
    {
        a_pid_init(this->ctx, jdt, jmin, jmax);
    }
    ~pid() { a_pid_exit(this->ctx); }
    double proc(double jset, double jfdb)
    {
        return a_pid_cc_x(this->ctx, jset, jfdb);
    }
    void zero() { a_pid_zero(this->ctx); }
    void kpid(double jkp, double jki, double jkd)
    {
        a_pid_kpid(this->ctx, jkp, jki, jkd);
    }
    void time(double jdt) { a_pid_time(this->ctx, jdt); }
    void pos(double jmax) { a_pid_pos(this->ctx, jmax); }
    void inc() { a_pid_inc(this->ctx); }
    void off() { a_pid_off(this->ctx); }
};

#include "a/fpid.h"

class fpid
{
    a_fpid_s ctx[1];
    double *mmp;
    double *mkp;
    double *mki;
    double *mkd;
    void *buf;
    double *from(emscripten::val x)
    {
        x = emscripten::val::array()["concat"].call<emscripten::val>("apply", emscripten::val::array(), x);
        unsigned int num = x["length"].as<unsigned int>();
        double *ptr = new double[num];
        for (unsigned int i = 0; i < num; ++i)
        {
            ptr[i] = x[i].as<double>();
        }
        return ptr;
    }

public:
    fpid(a_uint_t jmax, double jdt, emscripten::val jmmp,
         emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd,
         double jimin, double jimax, double jomin, double jomax)
    {
        this->mmp = from(jmmp);
        this->mkp = from(jmkp);
        this->mki = from(jmki);
        this->mkd = from(jmkd);
        unsigned int num = jmkp["length"].as<unsigned int>();
        a_fpid_init(this->ctx, jdt, num, this->mmp,
                    this->mkp, this->mki, this->mkd,
                    jimin, jimax, jomin, jomax);
        this->buf = malloc(A_FPID_BUF1(jmax));
        a_fpid_buf1(this->ctx, this->buf, jmax);
    }
    ~fpid()
    {
        a_fpid_exit(this->ctx);
        delete[] this->mmp;
        delete[] this->mkp;
        delete[] this->mki;
        delete[] this->mkd;
        free(this->buf);
    }
    void buff(a_uint_t jmax)
    {
        this->buf = realloc(this->buf, A_FPID_BUF1(jmax));
        a_fpid_buf1(this->ctx, this->buf, jmax);
    }
    void base(emscripten::val jmmp, emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd)
    {
        this->mmp = from(jmmp);
        this->mkp = from(jmkp);
        this->mki = from(jmki);
        this->mkd = from(jmkd);
        unsigned int num = jmkp["length"].as<unsigned int>();
        a_fpid_base(this->ctx, num, this->mmp, this->mkp, this->mki, this->mkd);
    }
    double proc(double jset, double jfdb)
    {
        return a_fpid_cc_x(this->ctx, jset, jfdb);
    }
    void zero() { a_fpid_zero(this->ctx); }
    void kpid(double jkp, double jki, double jkd)
    {
        a_fpid_kpid(this->ctx, jkp, jki, jkd);
    }
    void time(double jdt) { a_fpid_time(this->ctx, jdt); }
    void pos(double jmax) { a_fpid_pos(this->ctx, jmax); }
    void inc() { a_fpid_inc(this->ctx); }
    void off() { a_fpid_off(this->ctx); }
};

#include "a/polytrack.h"

class polytrack3
{
    a_polytrack3_s ctx[1];

public:
    polytrack3(emscripten::val jsource, emscripten::val jtarget)
    {
        double source[3];
        double target[3];
        for (int i = 0; i != 3; ++i)
        {
            source[i] = jsource[i].as<double>();
            target[i] = jtarget[i].as<double>();
        }
        a_polytrack3_init(this->ctx, source, target);
    }
    double pos(double jts)
    {
        return a_polytrack3_pos(this->ctx, jts);
    }
    double vec(double jts)
    {
        return a_polytrack3_vec(this->ctx, jts);
    }
    double acc(double jts)
    {
        return a_polytrack3_acc(this->ctx, jts);
    }
    emscripten::val all(double jts)
    {
        double out[3];
        a_polytrack3_all(this->ctx, jts, out);
        return emscripten::val(emscripten::typed_memory_view(3, out));
    }
};

class polytrack5
{
    a_polytrack5_s ctx[1];

public:
    polytrack5(emscripten::val jsource, emscripten::val jtarget)
    {
        double source[4];
        double target[4];
        for (int i = 0; i != 4; ++i)
        {
            source[i] = jsource[i].as<double>();
            target[i] = jtarget[i].as<double>();
        }
        a_polytrack5_init(this->ctx, source, target);
    }
    double pos(double jts)
    {
        return a_polytrack5_pos(this->ctx, jts);
    }
    double vec(double jts)
    {
        return a_polytrack5_vec(this->ctx, jts);
    }
    double acc(double jts)
    {
        return a_polytrack5_acc(this->ctx, jts);
    }
    emscripten::val all(double jts)
    {
        double out[3];
        a_polytrack5_all(this->ctx, jts, out);
        return emscripten::val(emscripten::typed_memory_view(3, out));
    }
};

class polytrack7
{
    a_polytrack7_s ctx[1];

public:
    polytrack7(emscripten::val jsource, emscripten::val jtarget)
    {
        double source[5];
        double target[5];
        for (int i = 0; i != 5; ++i)
        {
            source[i] = jsource[i].as<double>();
            target[i] = jtarget[i].as<double>();
        }
        a_polytrack7_init(this->ctx, source, target);
    }
    double pos(double jts)
    {
        return a_polytrack7_pos(this->ctx, jts);
    }
    double vec(double jts)
    {
        return a_polytrack7_vec(this->ctx, jts);
    }
    double acc(double jts)
    {
        return a_polytrack7_acc(this->ctx, jts);
    }
    double jer(double jts)
    {
        return a_polytrack7_jer(this->ctx, jts);
    }
    emscripten::val all(double jts)
    {
        double out[4];
        a_polytrack7_all(this->ctx, jts, out);
        return emscripten::val(emscripten::typed_memory_view(4, out));
    }
};

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("sqrt_inv", a_sqrt_inv);
    emscripten::constant("MF_NUL", 0);
    emscripten::function("mf_gauss", a_mf_gauss);
    emscripten::constant("MF_GAUSS", 1);
    emscripten::function("mf_gbell", a_mf_gbell);
    emscripten::constant("MF_GBELL", 2);
    emscripten::function("mf_sig", a_mf_sig);
    emscripten::constant("MF_SIG", 3);
    emscripten::function("mf_trap", a_mf_trap);
    emscripten::constant("MF_TRAP", 4);
    emscripten::function("mf_tri", a_mf_tri);
    emscripten::constant("MF_TRI", 5);
    emscripten::function("mf_z", a_mf_z);
    emscripten::constant("MF_Z", 6);
    emscripten::constant("PID_OFF", 0);
    emscripten::constant("PID_POS", 1);
    emscripten::constant("PID_INC", 2);
    emscripten::class_<pid>("pid")
        .constructor<double, double, double>()
        .function("proc", &pid::proc)
        .function("zero", &pid::zero)
        .function("kpid", &pid::kpid)
        .function("time", &pid::time)
        .function("pos", &pid::pos)
        .function("inc", &pid::inc)
        .function("off", &pid::off);
    emscripten::class_<fpid>("fpid")
        .constructor<a_uint_t, double, emscripten::val,
                     emscripten::val, emscripten::val, emscripten::val,
                     double, double, double, double>()
        .function("proc", &fpid::proc)
        .function("zero", &fpid::zero)
        .function("buff", &fpid::buff)
        .function("base", &fpid::base)
        .function("kpid", &fpid::kpid)
        .function("time", &fpid::time)
        .function("pos", &fpid::pos)
        .function("inc", &fpid::inc)
        .function("off", &fpid::off);
    emscripten::class_<polytrack3>("polytrack3")
        .constructor<emscripten::val, emscripten::val>()
        .function("pos", &polytrack3::pos)
        .function("vec", &polytrack3::vec)
        .function("acc", &polytrack3::acc)
        .function("all", &polytrack3::all);
    emscripten::class_<polytrack5>("polytrack5")
        .constructor<emscripten::val, emscripten::val>()
        .function("pos", &polytrack5::pos)
        .function("vec", &polytrack5::vec)
        .function("acc", &polytrack5::acc)
        .function("all", &polytrack5::all);
    emscripten::class_<polytrack7>("polytrack7")
        .constructor<emscripten::val, emscripten::val>()
        .function("pos", &polytrack7::pos)
        .function("vec", &polytrack7::vec)
        .function("acc", &polytrack7::acc)
        .function("jer", &polytrack7::jer)
        .function("all", &polytrack7::all);
    emscripten::constant("VERSION_MAJOR", A_VERSION_MAJOR);
    emscripten::constant("VERSION_MINOR", A_VERSION_MINOR);
    emscripten::constant("VERSION_PATCH", A_VERSION_PATCH);
    emscripten::function("version", version);
}

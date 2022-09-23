#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#include "lib.h"

#include "a/pid.h"

class pid
{
    a_pid_s ctx[1];

public:
    pid(double jts, double jmin, double jmax)
    {
        a_pid_init(this->ctx, jts, jmin, jmax);
    }
    double proc(double jset, double jref)
    {
        return a_pid_proc(this->ctx, jset, jref);
    }
    void done() { a_pid_done(this->ctx); }
    void kpid(double jkp, double jki, double jkd)
    {
        a_pid_kpid(this->ctx, jkp, jki, jkd);
    }
    void time(double jts) { a_pid_time(this->ctx, jts); }
    void pos(double jmax) { a_pid_pos(this->ctx, jmax); }
    void inc() { a_pid_inc(this->ctx); }
    void off() { a_pid_off(this->ctx); }
};

#include "a/fpid.h"

class fpid
{
    a_fpid_s ctx[1];
    double *mkp;
    double *mki;
    double *mkd;
    double *mma;
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
    fpid(a_uint_t jmax, double jts, emscripten::val jmma,
         emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd,
         double jimin, double jimax, double jomin, double jomax)
    {
        this->mkp = from(jmkp);
        this->mki = from(jmki);
        this->mkd = from(jmkd);
        this->mma = from(jmma);
        unsigned int num = jmkp["length"].as<unsigned int>();
        a_fpid_init(this->ctx, jts, num, this->mma,
                    this->mkp, this->mki, this->mkd,
                    jimin, jimax, jomin, jomax);
        this->buf = malloc(A_FPID_BUF1(jmax));
        a_fpid_buf1(this->ctx, this->buf, jmax);
    }
    ~fpid()
    {
        delete[] this->mkp;
        delete[] this->mki;
        delete[] this->mkd;
        delete[] this->mma;
        free(this->buf);
    }
    void buff(a_uint_t jmax)
    {
        this->buf = realloc(this->buf, A_FPID_BUF1(jmax));
        a_fpid_buf1(this->ctx, this->buf, jmax);
    }
    void base(emscripten::val jmma, emscripten::val jmkp, emscripten::val jmki, emscripten::val jmkd)
    {
        this->mkp = from(jmkp);
        this->mki = from(jmki);
        this->mkd = from(jmkd);
        this->mma = from(jmma);
        unsigned int num = jmkp["length"].as<unsigned int>();
        a_fpid_base(this->ctx, num, this->mma, this->mkp, this->mki, this->mkd);
    }
    double proc(double jset, double jref)
    {
        return a_fpid_proc(this->ctx, jset, jref);
    }
    void done() { a_fpid_done(this->ctx); }
    void kpid(double jkp, double jki, double jkd)
    {
        a_fpid_kpid(this->ctx, jkp, jki, jkd);
    }
    void time(double jts) { a_fpid_time(this->ctx, jts); }
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

#include "a/math.h"
#include "a/version.h"

emscripten::val version()
{
    return emscripten::val(a_version());
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("inv_sqrt", a_inv_sqrt);
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
        .function("done", &pid::done)
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
        .function("done", &fpid::done)
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

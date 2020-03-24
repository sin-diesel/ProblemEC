#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#define VISUALIZE

typedef double (*func_t)(double x, double a, double b, double c);

double f(double x, double a, double b, double c) {
    return a * x * x * sin(x) + b * x * cos(x) + c;
}

double fsgn(double x) {
    return signbit(x) ? -1.0 : 1.0;
}

int SC(func_t f, double xleft, double xright, double a, double b, double c, double prec) {

    double xmid = 0;
    double fl = 0;
    double fr = 0;
    double fm = 0;
    double xnew = 0;
    int iter = 0;

    if (signbit(f(xleft, a, b, c)) == signbit(f(xright, a, b, c))) {
        printf("0 0");
        exit(0);
    }

    do {

        xmid = (xleft + xright) / 2.0;
        fl = f(xleft, a, b, c);
        fr = f(xright, a, b, c);
        fm = f(xmid, a, b, c);
        xnew = xmid + (xmid - xleft) * fsgn(fl - fr) * fm / sqrt(fm * fm - fl * fr);

        if (signbit(f(xnew, a, b, c)) < 0) {
            xleft = xnew; // change xleft or xright depending on sign of f(xnew)
        } else {
            xright = xnew;
        }

        ++iter;
    } while (fabs(f(xnew, a, b, c)) > prec);

#ifdef VISUALIZE
    printf("SC: %f\n", xnew);
#endif

    return iter;
}

int DH(double start, double end, double a, double b, double c, double prec) {

    double pivot = 0;
    int iter = 0;

    if (signbit(f(start, a, b, c)) == signbit(f(end, a, b, c))) {
        printf("0 0");
        exit(0);
    }

    pivot = (start + end) / 2;
    while (fabs(f(pivot, a, b, c)) > prec) {

        pivot = (start + end) / 2;

        if (f(pivot, a, b, c) * f(start, a, b, c) < 0) {
            end = pivot;
        }

        if (f(pivot, a, b, c) * f(end, a, b, c) < 0) {
            start = pivot;
        }

        ++iter;
    }

#ifdef VISUALIZE
    printf("DH: %f\n", pivot);
#endif

    return iter;
}

int main() {

    int res = 0;
    double a = 0;
    double b = 0;
    double c = 0;
    double N = 0;
    double prec = 0;
    unsigned DH_iter = 0;
    unsigned SC_iter = 0;

    res = scanf("%lf %lf %lf %lf %lf", &a, &b, &c, &N, &prec);
    assert(res == 5);
    assert(N > 0);

    DH_iter = DH(-N, N, a, b, c, prec);
    SC_iter = SC(f, -N, N, a, b, c, prec);

    printf("%u %u", DH_iter, SC_iter);


    return 0;
}
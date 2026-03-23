#include <stdio.h>
#include <math.h>

double f(double x) {
    return x*x*x - x - 1;
}

double g1(double x) { return cbrt(x + 1); }
double g2(double x) { return 1.0 / (x*x - 1); }
double g3(double x) { return x*x*x - 1; }
double g4(double x) { return (cbrt(x + 1) + x) / 2; }

double (*g)(double);

int lap(double x0) {
    double x, y;
    int i = 0;
    double eps = 0.0001;

    printf("\n%5s | %12s | %12s\n", "k", "x", "f(x)");

    do {
        y = x0;
        x0 = g(y);
        x = x0;
        i++;

        if (isnan(x) || isinf(x)) {
            printf("\nKhong xac dinh!\n");
            return 0;
        }

        printf("%5d | %12.6lf | %12.6lf\n", i, x, f(x));

        if (i > 1000) {
            printf("\nKhong hoi tu!\n");
            return 0;
        }

    } while (fabs(x - y) > eps);

    printf("\nNghiem gan dung: x = %.6lf\n", x);
    return 1;
}

int main() {
    int choice;
    double x0;

    printf("Chon g(x):\n");
    printf("1. (x+1)^(1/3)\n");
    printf("2. 1/(x^2-1)\n");
    printf("3. x^3-1\n");
    printf("4. (cbrt(x+1)+x)/2\n");
    printf("Nhap: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: g = g1; break;
        case 2: g = g2; break;
        case 3: g = g3; break;
        case 4: g = g4; break;
        default: return 0;
    }

    printf("Nhap x0: ");
    scanf("%lf", &x0);

    lap(x0);

    return 0;
}

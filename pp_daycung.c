#include <stdio.h>
#include <math.h>

#define MAX 1000
#define EPS 0.0001
#define MAX_ITER 1000

double fx[MAX];

double f_mau(int n, double x);
double f_dathuc(int n, double x);
void create_hamdathuc(int *n);
void inp_khoangnghiem(double *a, double *b);
void nghiem(double a, double b, int n);
char choose();


double (*f_x)(int n, double x);


int main()
{
    double a, b;
    char c;
    int n = 0;

    while (1)
    {
        printf("\nChon ham can tinh:\n");
        printf("[1] Ham mau\n");
        printf("[2] Ham da thuc bac n\n");
        printf("Choose: ");
        scanf(" %c", &c);  

        if (c == '1') {
            f_x = f_mau;
            n = 0;
        }
        else if (c == '2') {
            f_x = f_dathuc;
            create_hamdathuc(&n);
        }
        else break;

        while (1)
        {
            inp_khoangnghiem(&a, &b);
            nghiem(a, b, n);

            c = choose();
            if (c != '2') break;
        }

        if (c != '1') break;
    }

    return 0;
}

char choose()
{
    char x;
    printf("\n----------------------------------------\n");
    printf("[1] Doi ham\n");
    printf("[2] Doi khoang\n");
    printf("[3] Ket thuc\n");
    printf("Choose: ");
    scanf(" %c", &x);
    return x;
}

void nghiem(double a, double b, int n)
{
    double f_a, f_b, f, x;
    int count = 0;

    f_a = f_x(n, a);
    f_b = f_x(n, b);

    if (f_a * f_b > 0) {
        printf("Khoang khong hop le!\n");
        return;
    }

    printf("\n%10s%10s%10s%15s\n", "a", "b", "x", "f(x)");

    do {
        f_a = f_x(n, a);
        f_b = f_x(n, b);

        if (fabs(f_b - f_a) < 1e-12) {
            printf("Loi chia cho 0!\n");
            return;
        }

        x = a - (b - a) * f_a / (f_b - f_a);
        f = f_x(n, x);

        printf("%10.4lf%10.4lf%10.4lf%15.4lf\n", a, b, x, f);

        if (f * f_a < 0)
            b = x;
        else
            a = x;

        count++;

    } while (fabs(f) >= EPS && count < MAX_ITER);

    if (count >= MAX_ITER)
        printf("Khong hoi tu!\n");
    else
        printf("Nghiem: %.6lf\n", x);
}

void inp_khoangnghiem(double *a, double *b)
{
    printf("Nhap khoang [a, b]: ");
    scanf("%lf %lf", a, b);
}

double f_dathuc(int n, double x)
{
    double f = fx[0];
    for (int i = 1; i <= n; i++)
        f = f * x + fx[i];
    return f;
}

void create_hamdathuc(int *n)
{
    printf("Nhap bac: ");
    scanf("%d", n);

    printf("Nhap he so:\n");
    for (int i = 0; i <= *n; i++) {
        scanf("%lf", &fx[i]);
    }
}
double f_mau(int n, double x)
{
    return pow(2, x) + x - 4;
}
#include <stdio.h>
#include <math.h>

#define MAX 1000
#define eps 0.0001

double fx[MAX];


double f_mau(int n, double x);
double f_dathuc(int n, double x);
void create_hamdathuc(int *n);
double (*f_x)(int n, double x);
void inp_khoangnghiem(double *a, double *b);
void nghiem(double a, double b, int n);
char choose()
{
    printf ("\n____________________________________________________\n");
    printf ("[1] Doi ham\n");
    printf ("[2] Doi khoang nghiem\n");
    printf ("[3] Ket thuc\n");
    printf ("Choose: ");
    char x;
    scanf ("%c", &x);
    return x;
}


int main()
{
    double a, b, x;
    char c;
    int n;
    while (1)
    {
        printf ("Chon ham can tinh:");
        printf ("\n[1] - Ham mau.");
        printf ("\n[2] - Ham da thuc bac n.");

        printf ("\nChoose: ");
        scanf ("%c", &c);
        
        if (c == '1') f_x = &f_mau;
        else 
        {
            f_x = &f_dathuc;
            create_hamdathuc(&n);
        }

        while (1)
        {
            inp_khoangnghiem(&a, &b);
            printf ("\n");
            nghiem(a, b, n);
            getchar();
            c = choose();
            getchar();
            if (c != '2') break;
        }
        if (c != '1') break;
    }
}

void nghiem(double a, double b, int n)
{
    double f_a, f_b, f, x, delta;
    int count = 0;
    printf ("%*c%*c%*c%*c%*c%*c%*s\n", 10, 'a', 10, '|', 10, 'b', 10, '|', 10, 'x', 10, '|', 13, "f(x)");
    do {
        f_a = f_x(n, a);
        f_b = f_x(n, b);
        printf ("%*.*lf%*c%*.*lf%*c", 10, 4, a, 10, '|', 10, 4, b, 10, '|');

        x = a - (b - a) * f_a / (f_b - f_a);
        f = f_x(n, x);
        if (f*f_a < 0) b = x;
        else a = x;
        printf ("%*.*lf%*c%*.*lf\n", 10, 4, x, 10, '|', 13, 4, f);
        count++;
    }   while (fabs(f) >= eps && count < 100);
    if (count > 100) printf ("khong co nghiem trong khoang.");
    else printf ("nghiem cua phuong trinh la %.4lf", x);
}

void inp_khoangnghiem(double *a, double *b)
{
    printf ("Nhap khoang nghiem: ");
    scanf ("%lf %lf", a, b);
}

double f_dathuc(int n, double x)
{
    double f = fx[0];
    for (int i = 1; i <= n; i++)
        f = f * x + fx[i];
    return f;
}

void create_hamdathuc (int *n)
{
    printf ("Nhap bac cua ham: ");
    scanf ("%d", n);

    printf ("Nhap he so cua da thuc: ");
    for (int i = 0; i <= (*n); i++)
        scanf ("%lf", &fx[i]);
}

double f_mau (int n, double x)
{
    double f;
    f = pow(2, x) + x - 4;
    return f;
}
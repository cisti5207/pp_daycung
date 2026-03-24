#include <stdio.h>

#define MAX_LEVEL 50

void inp(int *n, float *f_x);
void out(int i, int n, float *f_x);
void Tinh(int n, float *f_x, float c);
char choice_func();

int main()
{
    int n;
    float c;
    float f_x[MAX_LEVEL];
    char choice;

    do{
        inp(&n, f_x);
        do{
            printf ("Nhap c: ");
            scanf (" %f", &c);

            Tinh(n, f_x, c);
            choice = choice_func();
        }   while (choice == '2');
    }   while (choice == '1');

    printf (".....");
    return 0;
}

char choice_func()
{
    printf ("\n[1] Thay doi da thuc.");
    printf ("\n[2] Thay doi c.");
    printf ("\n[3] Exit.");
    printf ("\nchoice: ");

    char choice;
    scanf (" %c", &choice);
    return choice;
}

void inp(int *n, float *f_x)
{
    printf ("Nhap bac cua ham: ");
    scanf ("%d", n);

    printf ("Nhap he so cua ham: ");
    for (int i = 0; i <= (*n); i++)
        scanf ("%f", &f_x[i]);
}

void out(int i, int n, float *f_x)
{
    for (; i <= n; i++)
        printf ("%-20.6f", f_x[i]);
}

void Tinh(int n, float *f_x, float c)
{
    float f_p[n + 1];
    f_p[0] = f_x[0];
    float tmp, f_c = f_x[0];
    f_p[0] = 0;

    out(0, n, f_x);
    printf ("\n %19s", "");

    for (int i = 1; i <= n; i++)
    {
        tmp = f_c * c;
        f_p[i] = tmp;
        f_c = tmp + f_x[i];
    }

    out(1, n, f_p);
    printf ("\n");
    for (int i = 0; i <= 2*n; i++)
        printf ("__________");
    printf ("\n");
    
    for (int i = 0; i <= n; i++)
        printf ("%-20.6f", f_x[i] + f_p[i]);
    
    printf ("\nGia tri cua da thuc (x = %.6f) la %.6f", c, f_c);
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1000
#define TRUE  1
#define FALSE 0

double f_dathuc[MAX];

void inp_dathuc(int n);
void Arr_cpy(double *f_org, double *f_tmp, int n);
void Arr_add(double *f_org, double *f_tmp, int n);

// Tinh gia tri da thuc khi biet c
void main_giatriham();
void Tinh_giatriham(double c, int n);
void out_giatriham(int pos, int n, double *fx);
char choice_giatriham();

//So do hoocner tong quat
char choice_sodohoocner();
void main_sodohoocner();
void Tinh_sodohoocner(int n, double c);
void out_sodohoocner(int n, int i, double *f_org, double *f_tmp);
void out_hamdathuc(int n, int i, double *fx);


int main()
{
    char choose_menu;
    printf ("════════════════════════Menu════════════════════════\n");
    do {
        printf ("====================================================\n");
        printf ("[1] Tinh gia tri da thuc.\n");
        printf ("[2] So do hoocner tong quat.\n");
        printf ("[3] Tim nghiem.\n");
        printf ("[4] Exit.\n");

        printf ("Choose: ");
        scanf (" %c", &choose_menu);
        
        switch (choose_menu)
        {
            case '1':
                main_giatriham();
                break;
            case '2':
                main_sodohoocner();
                break;
            case '3':
            case '4': return 0;
            default:
                printf ("Lua chon khong hop le!");
                break;
        }
    }   while (1);
}

void inp_dathuc(int n)
{
    printf ("Nhap he so cua da thuc: ");
    for (int i = 0; i <= n; i++)
        scanf (" %lf", &f_dathuc[i]);
}
void Arr_cpy(double *f_org, double *f_tmp, int n)
{
    for (int i = 0; i <= n; i++)
        f_tmp[i] = f_org[i];
}
void Arr_add(double *f_org, double *f_tmp, int n)
{
    for (int i = 0; i <= n; i++)
        f_org[i] += f_tmp[i];
}
// tinh gia tri da thuc
void main_giatriham()
{
    char choose;
    do {
        int n;
        printf ("Nhap bac cua ham (n): ");
        scanf (" %d", &n);
        inp_dathuc(n);
        do {
            double c;
            printf ("Nhap c: ");
            scanf (" %lf", &c);

            Tinh_giatriham(c, n);

            choose = choice_giatriham();
        }   while (choose == '2');
    }   while (choose == '1');
}
char choice_giatriham(){
    printf ("====================================================\n");
    printf ("[1] Doi ham.\n");
    printf ("[2] Doi gia tri.\n");
    printf ("[3] Quay lai menu,\n");
    
    printf ("choose: ");
    char choose;
    scanf (" %c", &choose);
    return choose;
}
void Tinh_giatriham(double c, int n)
{
    double *f_tmp = (double*) malloc (sizeof(double) * MAX);
    f_tmp[0] = 0;
    double f_c = f_dathuc[0];

     out_giatriham(0, n, f_dathuc);

    for (int i = 1; i <= n; i++)
    {
        f_tmp[i] = f_c * c;
        f_c = f_tmp[i] + f_dathuc[i];
    }

    printf ("%15s", "");
     out_giatriham(1, n, f_tmp);

    Arr_add(f_tmp, f_dathuc, n);
    for (int i = 0; i <= n; i++) 
        printf ("---------------");
    printf ("\n");

     out_giatriham(0, n, f_tmp);
    printf ("Vay gia tri cua f(%.3lf) = %.3lf\n", c, f_tmp[n]);
    free(f_tmp);
}
void out_giatriham (int pos, int n, double *fx)
{
    for (int i = pos; i <= n; i++)
        printf ("%15.3lf", fx[i]);
    printf ("\n");
}

//So do hoocner tong quat
char choice_sodohoocner()
{
    printf ("====================================================\n");
    printf ("[1] Doi ham.\n");
    printf ("[2] Doi gia tri.\n");
    printf ("[3] Quay lai menu,\n");
    
    printf ("choose: ");
    char choose;
    scanf (" %c", &choose);
    return choose;
}
void main_sodohoocner()
{
    int n;
    char choose;
    double c;
    do  {
        printf ("Nhap bac cua ham (n): ");
        scanf (" %d", &n);

        inp_dathuc(n);
        do  {
            printf ("Nhap gia tri c [f(x + c)]: ");
            scanf (" %lf", &c);

            Tinh_sodohoocner(n, c);

            choose = choice_sodohoocner();
        }   while (choose == '2');
    }   while (choose == '1');
}
void Tinh_sodohoocner(int n, double c)
{
    double *f_org = (double*) malloc (sizeof(double) * MAX);
    double *f_tmp = (double*) malloc (sizeof(double) * MAX);

    Arr_cpy(f_dathuc, f_org, n);
    out_hamdathuc(n, 0, f_org);

    int i;
    f_tmp[0] = 0;

    for (int i = 1; i <= n - 1; i++)
    {
        double f_c = f_org[0];

        for (int j = 1; j <= n - i + 1; j++){
            f_tmp[j] = f_c * c;
            f_c = f_tmp[j] + f_org[j];
        }

        Arr_add(f_org, f_tmp, n);
        out_sodohoocner(n, i, f_org, f_tmp);
    }

    printf ("f(x + %lf) = ", c);
    for (int i = 0; i <= n; i++)
    {
        if (n - i == 0) printf ("%12.3lf", f_org[i]);
        else printf ("%12.3lf*x^%d", f_org[i], n - i);
    }
    printf ("\n");

    free (f_org);
    free (f_tmp);
}
void out_sodohoocner(int n, int i, double *f_org, double *f_tmp)
{
    printf ("%25s", "");
    for (int j = 1; j <= n - i + 1; j++)
        printf ("%-15.3lf", f_tmp[j]);


    printf ("\n");
    printf ("%10s", "");
    
    for (int j = 0; j <= n - i + 1; j++)
        printf ("---------------");
    
    printf ("\n");
    out_hamdathuc(n - i + 1, i, f_org);
}
void out_hamdathuc(int n, int i, double *fx)
{
    if (i == 0) printf ("P(x) %5s", "");
    else printf ("P%d(x) %4s", i, "");

    for (int i = 0; i <= n; i++)
        printf ("%-15.3lf", fx[i]);
    printf ("\n");
}

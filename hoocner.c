#include <stdio.h>
#include <math.h> 

#define MAX 1000

void sodohoocner(double a[], int n, double c);
int main() {
    int luachon;
    int n;
    double a[MAX + 1];
    double c;
    char tieptuc;
    double mau[] = {2, 4, 0, 0, -1, 1, 2};

    do {
        printf ("\n ==========CHUONG TRINH SO DO HOOCNER==========");
        printf ("\n[1]. Nhap ham mau");
        printf ("\n[2]. Nhap ham tu chon");
        printf ("\n[3]. Exit");
        printf ("\nNhap lua chon cua ban : ");
        scanf ("%d", &luachon);

        if (luachon > 3 || luachon <1) 
        { 
        printf ("Lua chon khong dung, hay nhap lai");
        continue;
        }

        if (luachon == 3) break;
        
        if (luachon == 1) 
        {
            n = 6;
            for (int i = 0; i <= n; i++)
                { a[i] = mau[i]; }

        }
        if (luachon == 2) 
            {printf ("\nnhap bac cua phuong trinh :"); 
            scanf ("%d", &n);
            printf ("\nnhap he so duoi day\n");
            for (int i = 0; i <= n; i++)
            {
                printf ("x^%d = ", n - i);
                scanf ("%lf", &a[i]);
            }
            }
        do {
            printf ("\nnhap c : ");
            scanf ("%lf", &c);
            sodohoocner (a, n, c);
            printf ("\nban co muon nhap thu gia tri c khac khong (Y de tiep tuc, cac nut khac de dung chuong trinh) : ");
            scanf (" %d", &luachon);
        } while (luachon == 'y' || luachon == 'Y');
    printf ("ban co muon quay ve menu khong (Y de tiep tuc, cac nut khac de dung chuong trinh) : ");
    scanf (" %c", &luachon);
    }while (luachon == 'y' || luachon == 'Y');
    printf ("Chuong trinh da dung, tam biet");

    return 0;
}


void sodohoocner(double a[], int n, double c){
    double b[MAX + 1];
    double hamKQ [MAX + 1];

    printf ("\n------So do Hoocner------\n");
   
    for (int i = 0; i <=n; i++) 
    {
        b[i] = a[i];
        printf ("%+15.3f ", b[i]);
    }
    printf ("(Phuong Trinh Ban Dau)");
    printf ("\n");
    
    for (int k = n; k >= 0; k--)
    {
        printf ("%+15.3f ", b[0]);
        for (int i = 1; i <= k; i++)
        {
            b[i] = b[i - 1] * c + b[i];
            printf ("%+15.3f ", b[i]);
        }
        printf (" (y^%d)", n - k); 
        printf ("\n");
        
        hamKQ[k] = b[k];
    }
    printf ("Ham so can tim la P(y %+.3lf) = ", c);
    for (int k = 0; k <= n; k++ )
        {
            printf (" %+fy^%d ", hamKQ[k], n - k);
        }
}
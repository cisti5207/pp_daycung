#include <stdio.h>
#include <math.h>
#define EPS 1e-6

float a[100];
int n;
float (*f_x)(float);
float (*df_x)(float);

float f0(float x){
    return exp(x) - 10*x + 7;
}

float df0(float x){
    return exp(x) - 10;
}

float f(float x){
    float p = a[0];
    for(int i = 1; i <= n; i++)
        p = p*x + a[i];
    return p;
}

float df(float x){
    float p = a[0]*n;
    for(int i = 1; i < n; i++)
        p = p*x + a[i]*(n - i);
    return p;
}

void nhap_dathuc(){
    printf("Nhap bac cua da thuc : ");
    scanf("%d",&n);
    printf("Nhap he so tư bac cao đen thap :\n");
    for(int i = 0; i <= n; i++)
        scanf("%f",&a[i]);
}

float tieptuyen(float x0){
    float x = x0, y;
    int dem = 0;

    do{
        y = x;
        if(fabs(df_x(y)) < EPS){
            printf("Dao ham bang 0 tai x = %.6f\n", y);
            return 1e9;
        }
        x = y - f_x(y)/df_x(y);
        dem++;
        if(dem > 1000){
            printf("Khong hoi tu!\n");
            return 1e9;
        }

    } while(fabs(x - y) >= EPS);
    return x;
}
int menu(){
    int chon;
    printf("\n-----------------------------\n");
    printf("1. Doi ham\n");
    printf("2. Doi xap xi ban dau x0\n");
    printf("3. Thoat\n");
    printf("Chon : ");
    scanf("%d",&chon);
    return chon;
}
int main(){
    char ham;
    int chon;
    float x0;

    while(1){
        printf("\n[1] Ham nguon");
        printf("\n[2] Ham da thuc");
        printf("\nChon ham can tinh : ");
        scanf(" %c",&ham);

        if(ham == '1'){
            f_x = &f0;
            df_x = &df0;
        }
        else{
            nhap_dathuc();
            f_x = &f;
            df_x =& df;
        }

        while(1){
            printf("\nNhap xap xi ban dau x0: ");
            scanf("%f",&x0);
            float nghiem = tieptuyen(x0);
           if(fabs(nghiem - 1e9) < EPS){
                chon=menu();
                if(chon == 2) continue; 
                if(chon == 1) break;    
                if(chon == 3) return 0;
            }
            if(fabs(nghiem) < EPS) nghiem = 0;
            printf("Nghiem: %.6f\n", nghiem);
            chon = menu();
            if(chon==2) continue;
            if(chon==1) break;
            if(chon==3) return 0;
        }
    }
}
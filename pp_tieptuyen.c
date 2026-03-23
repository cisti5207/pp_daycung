#include <stdio.h>
#include <math.h>
#define EPS 1e-6

float f0(float x);
float df0(float x);
void nhap(float a[], int n);
float f(float a[], int n, float x);
float df(float a[], int n, float x);
float tieptuyen_f0(float x0);
float tieptuyen_f(float a[], int n, float x0);


int main(){
    int choice;
    char tt;

    /* Nếu ko sử dụng while ở trước lựa chọn hàm thì không thể thực hiện
       việc chọn hàm -> nhập hệ số -> giải pt -> back lại việc chọn hàm
    */
    printf("1.Ham nguon\n");
    printf("2.Ham da thuc\n");
    printf("Chon: ");  scanf("%d", &choice);
    /*Đoạn này dùng con trỏ hàm để trỏ 2 hàm cho tiện, mặc dù bữa thầy nói code dài ko sao
    nhưng code mà có thể gọn lại thì đừng nên làm dài.
    ví dụ choice == 1
            ptr_f = &f0
          choice == 2
            ptr_f = &f

        như vậy thì sử dụng hàm tinh (tieptuyen_f, hay tieptuyen_f0 chỉ cần gọp thành 1 hàm. này gợi ý v thooiiiii!!!!
    */
    if(choice == 1){
        float x0;
        while(1){
            printf("Nhap xap xi ban dau: ");
            scanf("%f",&x0);
            printf("Nghiem cua phuong trinh : %.6f\n", tieptuyen_f0(x0));
            printf("Ban muon tiep tuc khong ? (c/k): ");
            /*đoạn scanf choice này, cẩn thật nó bị lỗi (do bài toán này đã printf trước scanf nên k sao)
              khi scanf -> stdin : 'choice' '\n'   -- choice là giá trị bạn nhập
                                                   -- \n là khi bạn ấn enter nó sẽ xuất hiện
                                                   nên kieu_du_lieu nó chỉ nhận choice còn \n nó vẫn còn
                                                   nên khi printf thường tự xuống dòng là vậy.
                                                   Nếu 2 lần scanf liên tiếp thì scanf số 2 sẽ nhận giá trị \n -> lỗi
            */
        }
    }
    else{
        int n;
        float a[100], x0;
        printf("Nhap bac n: ");scanf("%d", &n);
        printf("Nhap he so tu bac cao den thap:\n");
        nhap(a, n);
        while(1){
            printf("\nNhap xap xi ban dau : "); scanf("%f", &x0);
            float nghiem=tieptuyen_f(a,n,x0);
            if(fabs(nghiem) < EPS) nghiem = 0;
            printf("Nghiem: %.6f\n", nghiem);
            printf("Ban muon tiep tuc khong ? (c/k): ");
            scanf(" %c", &tt);
            if(tt=='k'||tt=='K') break;
        }
    }
    return 0;
}

float f0(float x){
    return exp(x) - 10*x + 7 ;
}

float df0(float x){
    return exp(x) - 10;
}

void nhap(float a[], int n){
    for(int i = 0; i <= n; i++){
        printf("a[%d] = ", i);
        scanf("%f", &a[i]);
    }
}

float f(float a[], int n, float x){
    float p= a[0];
    for(int i = 1; i <= n; i++)
        p = p*x + a[i];
    return p;
}

float df(float a[], int n, float x){
    float p = a[0]*n;
    for(int i = 1; i < n; i++)
        p = p*x + a[i]*(n - i);
    return p;
}

float tieptuyen_f0(float x0){
    float x = x0, y;
    do{
        y = x;
        x = y - f0(y)/df0(y);
    } while(fabs(x - y) >= EPS);
    return x;
}

float tieptuyen_f(float a[], int n, float x0){
    float x = x0, y;
    do{
        /*bạn có thể cho thêm 1 số cách để thoát vòng lặp như nếu quá 200 lần lọc mà
        không tìm ra thì ghi ko có, còn 1 số cách nữa mà bạn có thể nghĩ thêm*/
        y = x;
        x = y - f(a,n,y)/df(a,n,y);
    } while(fabs(x - y) >= EPS);

    return x;
}
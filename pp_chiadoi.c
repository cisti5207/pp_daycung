#include <stdio.h>
#include <math.h>

#define MAX 100
#define eps 1e-6
#define MAX_LAP 100

double he_so[MAX];

double ham_mau(int bac, double x);
double ham_dathuc(int bac, double x);
void nhap_dathuc(int *bac);
void nhap_khoang(double *a, double *b);
void chia_doi(double a, double b, int bac, double (*ham)(int, double));
char chon_menu();

int main()
{
    double a, b;
    int bac = 0;
    char lua_chon;

    // có thể khai báo con trỏ ở quy mô toàn cục thì chia_doi ko cần gọi lại
    double (*ham)(int, double);

    while (1)
    {
        printf("\n=== CHON HAM ===\n");
        printf("1. Ham mau (2^x + x - 4)\n");
        printf("2. Ham da thuc\n");
        printf("Chon: ");
        scanf(" %c", &lua_chon);

        /* trong {} mà chỉ có 1 dòng code thì ko cần {}, chỉ cần viết lun cx đc
            if .....
                okeeee;
            else
            {
                oke;
                oke;
            }
        */
        if (lua_chon == '1')
        {
            ham = ham_mau;
        }
        else
        {
            ham = ham_dathuc;
            nhap_dathuc(&bac);
        }

        while (1)
        {
            nhap_khoang(&a, &b);
            chia_doi(a, b, bac, ham);

            /*Này cho biến thêm thôi:
            Nếu a minh scanf 2 lần liên tiếp sẽ lỗi ví dụ:
            scanf_1 -> stdin : 'gia_tri_vao' '\n'
            vì sao khi nhập a minh ấn enter nên std sẽ có cả '\n' nên scanf lần 2 sẽ nhận nó
            nếu trước scanf lần 2 có printf thì printf nó sẽ nhận \n giùm rồi*/
            lua_chon = chon_menu();
            if (lua_chon != '2') break;
        }

        if (lua_chon != '1') break;
    }

    return 0;
}

char chon_menu()
{
    char ch;
    printf("\n-----------------------------\n");
    printf("1. Doi ham\n");
    printf("2. Doi khoang\n");
    printf("3. Thoat\n");
    printf("Chon: ");
    scanf(" %c", &ch);
    return ch;
}

void nhap_khoang(double *a, double *b)
{
    printf("\nNhap khoang [a, b]: ");
    scanf("%lf %lf", a, b);
}

void nhap_dathuc(int *bac)
{
    printf("Nhap bac da thuc: ");
    scanf("%d", bac);

    printf("Nhap cac he so (tu bac cao den thap):\n");
    for (int i = 0; i <= *bac; i++)
    {
        printf("a[%d] = ", i);
        scanf("%lf", &he_so[i]);
    }
}

double ham_mau(int bac, double x)
{
    return pow(2, x) + x - 4;
}

double ham_dathuc(int bac, double x)
{
    double ket_qua = he_so[0];
    for (int i = 1; i <= bac; i++)
    {
        ket_qua = ket_qua * x + he_so[i];
    }
    return ket_qua;
}

void chia_doi(double a, double b, int bac, double (*ham)(int, double))
{
    double fa = ham(bac, a);
    double fb = ham(bac, b);

    if (fabs(fa) < eps) {
        printf("Nghiem chinh xac tai a: x = %.6lf\n", a);
        return;
    }
    if (fabs(fb) < eps) {
        printf("Nghiem chinh xac tai b: x = %.6lf\n", b);
        return;
    }
    if (fa * fb > 0) {
        printf("Khoang khong hop le (cung dau)!\n");
        return;
    }

    printf("\n%-5s %-12s %-12s %-12s %-15s\n", "Lap", "a", "b", "c", "f(c)");
    printf("------------------------------------------------------\n");

    double c, fc;
    int buoc = 0;

    while (fabs(b - a) > eps && buoc < MAX_LAP)
    {
        c = (a + b) / 2.0;
        fc = ham(bac, c);

        printf("%-5d %-12.6lf %-12.6lf %-12.6lf %-15.6lf\n", 
               buoc + 1, a, b, c, fc);

        if (fabs(fc) < eps) {
            printf("\n=> Nghiem chinh xac: x = %.6lf\n", c);
            return;
        }

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
        buoc++;
    }

    printf("\n=> Nghiem gan dung: x = %.6lf (sau %d lan lap)\n", (a + b) / 2.0, buoc);
}
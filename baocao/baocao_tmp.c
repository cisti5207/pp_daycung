#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// --- Khai bao hang so va bien toan cuc ---
#define MAX_LEVEL 50
#define MAX 1000
#define EPS 1e-6
#define MAX_LAP 500

double fx_global[MAX]; // Dung cho pp day cung
double he_so[MAX];     // Dung cho pp chia doi
float a_tieptuyen[100]; // Dung cho pp tiep tuyen
int n_global;

// --- Mau sac console ---
void reset_color() { printf("\033[0m"); }
void red() { printf("\033[1;31m"); }
void green() { printf("\033[1;32m"); }
void yellow() { printf("\033[1;33m"); }
void cyan() { printf("\033[1;36m"); }

// ======================================================
// [1.1] TINH GIA TRI DA THUC VOI SO DO HOOCNER (Source 1)
// ======================================================
void out_s1(int i, int n, float *f_x) {
    for (; i <= n; i++) printf("%-20.6f", f_x[i]);
}

char choice_func_s1() {
    printf("\n[1] Thay doi da thuc.");
    printf("\n[2] Thay doi c.");
    printf("\n[3] Exit (Ve menu).");
    printf("\nChoice: ");
    char choice;
    scanf(" %c", &choice);
    return choice;
}

void Tinh_s1(int n, float *f_x, float c) {
    float f_p[MAX_LEVEL] = {0};
    float f_c = f_x[0];
    out_s1(0, n, f_x);
    printf("\n %19s", "");
    for (int i = 1; i <= n; i++) {
        f_p[i] = f_c * c;
        f_c = f_x[i] + f_p[i];
    }
    out_s1(1, n, f_p);
    printf("\n");
    for (int i = 0; i <= 2 * n; i++) printf("________");
    printf("\n");
    for (int i = 0; i <= n; i++) printf("%-20.6f", f_x[i] + f_p[i]);
    printf("\nGia tri cua da thuc (x = %.6f) la %.6f\n", c, f_c);
}

void main_tinhdathuc_hoocner() {
    int n; float c; float f_x[MAX_LEVEL]; char choice;
    do {
        printf("Nhap bac cua ham: "); scanf("%d", &n);
        printf("Nhap he so cua ham: ");
        for (int i = 0; i <= n; i++) scanf("%f", &f_x[i]);
        do {
            printf("Nhap c: "); scanf(" %f", &c);
            Tinh_s1(n, f_x, c);
            choice = choice_func_s1();
        } while (choice == '2');
    } while (choice == '1');
}

// ======================================================
// [1.2] TINH SO DO HOOCNER TONG QUAT (Source 6)
// ======================================================
void sodohoocner_tongquat(double a[], int n, double c) {
    double b[MAX + 1], hamKQ[MAX + 1];
    printf("\n------So do Hoocner------\n");
    for (int i = 0; i <= n; i++) { b[i] = a[i]; printf("%+15.3f ", b[i]); }
    printf("(Phuong Trinh Ban Dau)\n");
    for (int k = n; k >= 0; k--) {
        printf("%+15.3f ", b[0]);
        for (int i = 1; i <= k; i++) {
            b[i] = b[i - 1] * c + b[i];
            printf("%+15.3f ", b[i]);
        }
        printf(" (y^%d)\n", n - k);
        hamKQ[k] = b[k];
    }
    printf("Ham so can tim la P(y %+.3lf) = ", c);
    for (int k = 0; k <= n; k++) printf(" %+.3fy^%d ", hamKQ[k], n - k);
    printf("\n");
}

void main_hoocner_tongquat() {
    int luachon, n; double a[MAX + 1], c, mau[] = {2, 4, 0, 0, -1, 1, 2}; char tieptuc;
    do {
        printf("\n[1]. Nhap ham mau\n[2]. Nhap ham tu chon\n[3]. Exit\nChon: ");
        scanf("%d", &luachon);
        if (luachon == 3) break;
        if (luachon == 1) { n = 6; for (int i = 0; i <= n; i++) a[i] = mau[i]; }
        else {
            printf("Nhap bac: "); scanf("%d", &n);
            for (int i = 0; i <= n; i++) { printf("x^%d = ", n - i); scanf("%lf", &a[i]); }
        }
        do {
            printf("Nhap c: "); scanf("%lf", &c);
            sodohoocner_tongquat(a, n, c);
            printf("\nNhap c khac? (Y/N): "); scanf(" %c", &tieptuc);
        } while (tieptuc == 'y' || tieptuc == 'Y');
        printf("Quay lai menu Hoocner? (Y/N): "); scanf(" %c", &tieptuc);
    } while (tieptuc == 'y' || tieptuc == 'Y');
}

// ======================================================
// [2.1] PHUONG PHAP CHIA DOI (Source 5)
// ======================================================
double ham_mau_chiadoi(int bac, double x) { return pow(2, x) + x - 4; }
double ham_dathuc_chiadoi(int bac, double x) {
    double kq = he_so[0];
    for (int i = 1; i <= bac; i++) kq = kq * x + he_so[i];
    return kq;
}

void main_pp_chiadoi() {
    double a, b; int bac = 0; char lc; double (*ham)(int, double);
    while (1) {
        printf("\n1. Ham mau\n2. Ham da thuc\nChon: "); scanf(" %c", &lc);
        ham = (lc == '1') ? ham_mau_chiadoi : ham_dathuc_chiadoi;
        if (lc == '2') {
            printf("Bac: "); scanf("%d", &bac);
            for (int i = 0; i <= bac; i++) { printf("a[%d]=", i); scanf("%lf", &he_so[i]); }
        }
        while (1) {
            printf("Nhap [a, b]: "); scanf("%lf %lf", &a, &b);
            double fa = ham(bac, a), fb = ham(bac, b), c, fc; int buoc = 0;
            if (fa * fb > 0) printf("Khoang sai!\n");
            else {
                while (fabs(b - a) > EPS && buoc < MAX_LAP) {
                    c = (a + b) / 2.0; fc = ham(bac, c);
                    if (fa * fc < 0) b = c; else { a = c; fa = fc; }
                    buoc++;
                }
                printf("Nghiem: %.6lf\n", (a + b) / 2.0);
            }
            printf("1. Doi ham, 2. Doi khoang, 3. Thoat: "); scanf(" %c", &lc);
            if (lc != '2') break;
        }
        if (lc != '1') break;
    }
}

// ======================================================
// [2.2] PHUONG PHAP LAP (Source 3)
// ======================================================
double f_lap(double x) { return x*x*x - x - 1; }
double g1(double x) { return cbrt(x + 1); }
void main_pp_lap() {
    int choice; double x0, x, y; int i = 0;
    printf("Chon g(x): 1. (x+1)^(1/3), 2. Khac...\nChon: "); scanf("%d", &choice);
    printf("Nhap x0: "); scanf("%lf", &x0);
    do {
        y = x0; x0 = g1(y); x = x0; i++;
        if (i > 1000) break;
    } while (fabs(x - y) > 0.0001);
    printf("Nghiem: %.6lf\n", x);
}

// ======================================================
// [2.3] PHUONG PHAP TIEP TUYEN (Source 2)
// ======================================================
float f_tt(float x) { 
    float p = a_tieptuyen[0];
    for(int i = 1; i <= n_global; i++) p = p*x + a_tieptuyen[i];
    return p;
}
float df_tt(float x) {
    float p = a_tieptuyen[0]*n_global;
    for(int i = 1; i < n_global; i++) p = p*x + a_tieptuyen[i]*(n_global - i);
    return p;
}

void main_pp_tieptuyen() {
    float x0, x, y; int dem = 0;
    printf("Nhap bac da thuc: "); scanf("%d", &n_global);
    for(int i=0; i<=n_global; i++) { printf("a[%d]=", i); scanf("%f", &a_tieptuyen[i]); }
    printf("Nhap x0: "); scanf("%f", &x0);
    x = x0;
    do {
        y = x; x = y - f_tt(y)/df_tt(y); dem++;
    } while(fabs(x - y) >= EPS && dem < 1000);
    printf("Nghiem: %.6f\n", x);
}

// ======================================================
// [2.4] PHUONG PHAP DAY CUNG (Source 4)
// ======================================================
double f_daycung(int n, double x) {
    double f = fx_global[0];
    for (int i = 1; i <= n; i++) f = f * x + fx_global[i];
    return f;
}

void main_pp_daycung() {
    double a, b, x, fa, fb, f; int n, count = 0;
    printf("Nhap bac: "); scanf("%d", &n);
    for (int i = 0; i <= n; i++) { printf("a[%d]=", i); scanf("%lf", &fx_global[i]); }
    printf("Nhap khoang [a, b]: "); scanf("%lf %lf", &a, &b);
    do {
        fa = f_daycung(n, a); fb = f_daycung(n, b);
        x = a - (b - a) * fa / (fb - fa); f = f_daycung(n, x);
        if (f * fa < 0) b = x; else a = x;
        count++;
    } while (fabs(f) >= 0.0001 && count < 1000);
    printf("Nghiem: %.4lf\n", x);
}

// ======================================================
// MENU CHINH VA DIEU KHIEN LUONG
// ======================================================
void ve_menu_chinh() {
    system("cls || clear");
    cyan();
    printf("====================================================\n");
    printf("      BAO CAO MON PHUONG PHAP TINH - NHOM 4        \n");
    printf("====================================================\n");
    reset_color();
    printf("[1] Chuong 3: Tinh gia tri ham\n");
    printf("[2] Chuong 4: Giai gan dung phuong trinh\n");
    red();
    printf("[3] Ket Thuc\n");
    reset_color();
    printf("----------------------------------------------------\n");
    printf("Lua chon cua ban: ");
}

void menu_chuong3() {
    int choice;
    while (1) {
        system("cls || clear");
        green();
        printf(">>> CHUONG 3: TINH GIA TRI HAM <<<\n");
        reset_color();
        printf("[1] Tinh gia tri da thuc voi so do Hoocner\n");
        printf("[2] Tinh so do Hoocner tong quat\n");
        printf("[3] Quay lai Menu Chinh\n");
        printf("Chon: ");
        scanf("%d", &choice);
        if (choice == 1) main_tinhdathuc_hoocner();
        else if (choice == 2) main_hoocner_tongquat();
        else if (choice == 3) break;
    }
}

void menu_chuong4() {
    int choice;
    while (1) {
        system("cls || clear");
        green();
        printf(">>> CHUONG 4: GIAI GAN DUNG PHUONG TRINH <<<\n");
        reset_color();
        printf("[1] Phuong phap chia doi\n");
        printf("[2] Phuong phap lap\n");
        printf("[3] Phuong phap tiep tuyen\n");
        printf("[4] Phuong phap day cung\n");
        printf("[5] Quay lai Menu Chinh\n");
        printf("Chon: ");
        scanf("%d", &choice);
        if (choice == 1) main_pp_chiadoi();
        else if (choice == 2) main_pp_lap();
        else if (choice == 3) main_pp_tieptuyen();
        else if (choice == 4) main_pp_daycung();
        else if (choice == 5) break;
        printf("\nAn phim bat ky de tiep tuc...");
        getchar(); getchar();
    }
}

int main() {
    int choice;
    while (1) {
        ve_menu_chinh();
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) menu_chuong3();
        else if (choice == 2) menu_chuong4();
        else if (choice == 3) {
            yellow();
            printf("Tam biet! Cam on ban da su dung.\n");
            reset_color();
            break;
        }
    }
    return 0;
}
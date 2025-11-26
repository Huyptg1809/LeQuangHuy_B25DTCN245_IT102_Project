#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PATIENTS 1000
#define MAX_RECORDS 5000

// Struct lưu bệnh nhân
struct patient {
    char cardId[15];
    char name[50];
    char phone[20];
    double debt;
    int visitDays;
};
struct patient patients[MAX_PATIENTS] = {
    {"033207014120", "Le Quang Huy", "0824692222", 2, 5},
    {"001234567890", "Nguyen Van A", "0912345678", 0.0, 2},
    {"001234567891", "Tran Thi B", "0987654321", 500000.0, 5},
    {"001234567892", "Le Van C",   "0901234567", 0.0, 1},
    {"001234567893", "Pham Thi D",  "0933333333", 250000.0, 3},
    {"001234567894", "Hoang Van E", "0977777777", 0.0, 7}
};
int patientCount = 6;

// Khai báo hàm
void printMenu();
void addPatient();
void updatePatient();
void inputString(char *dest, int size, const char *message);
int isIdExists(const char *id);
int isValidPhone(const char *phone);
void deletePatient();
void listPatients();
void listPatientsPaginate();
void findPatient();
void sortList();
void addVisitRecord();
void showPatientRecords();
int isPatientDischarged(const char *cardId);


// --- MAIN ---
int main() {
    int choice;
    while (1) {
        printMenu();
        printf("Nhap lua chon cua ban : ");
        // Check
        char line[64];
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Lua chon ko hop le, nhap lai !!!\n");
            continue;
        }
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        char *p = line;
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0') {
            printf("Lua chon ko hop le, nhap lai !!!\n");
            continue;
        }
        char *endptr = NULL;
        long val = strtol(p, &endptr, 10);
        while (endptr && *endptr && isspace((unsigned char)*endptr)) endptr++;
        if (p == endptr || (endptr && *endptr != '\0')) {
            printf("Lua chon ko hop le, nhap lai !!!\n");
            continue;
        }
        choice = (int)val;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: updatePatient(); break;
            case 3: deletePatient(); break;
            case 4: listPatientsPaginate(); break;
            case 5: findPatient(); break;
            case 6: sortList(); break;
            case 7: addVisitRecord(); break;
            case 8: showPatientRecords(); break;
            case 9:
                printf("Thoat chuong trinh\n");
                return 0;
            default:
                printf("Lua chon ko hop le, nhap lai !!!\n");
        }
        printf("\n");
    }
    return 0;
}

int isIdExists(const char *id) {
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, id) == 0) {
            return 1;
        }
    }
    return 0;
}

int isValidPhone(const char *phone) {
    if (strlen(phone) < 9) return 0;
    for (int i = 0; phone[i] != '\0'; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

// --- F01: THÊM BỆNH NHÂN ---
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("!!! Danh sach benh nhan da day, khong the them moi!\n");
        return;
    }

    struct patient p;
    printf("\n--- TIEP NHAN BENH NHAN MOI ---\n");

    // 2. Nhập NAME
    inputString(p.name, sizeof(p.name), "Nhap ten benh nhan: ");

    // 3. Nhập ID
    while (1) {
        inputString(p.cardId, sizeof(p.cardId), "Nhap ma ho so (CCCD): ");
        if (isIdExists(p.cardId)) {
            printf("!!! Loi: Ma ho so '%s' da ton tai. Vui long nhap ma khac.\n", p.cardId);
        } else {
            break;
        }
    }

    // 4. Nhập PHONE
    while (1) {
        inputString(p.phone, sizeof(p.phone), "Nhap so dien thoai: ");
        if (isValidPhone(p.phone)) {
            break;
        } else {
            printf("!!! Loi: SDT phai chua it nhat 9 ky tu so va khong co chu cai.\n");
        }
    }

    // 5. Nhập DEBT
    printf("Nhap cong no hien tai: ");
    while (scanf("%lf", &p.debt) != 1) {
        printf("!!! Loi: Vui long nhap mot con so hop le.\nNhap lai cong no: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    p.visitDays = 0;

    // Lưu vào mảng
    patients[patientCount++] = p;
    printf(">>> Da them benh nhan thanh cong! (Tong so: %d)\n", patientCount);
}

// --- F02: CẬP NHẬT ---
void updatePatient() {
    char id[15];
    char newPhone[20];

    // Nhap cardId
    inputString(id, sizeof(id), "Nhap ma ho so benh nhan can cap nhat: ");

    // Kiem tra ton tai
    int index = -1;
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, id) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Khong tim thay benh nhan co ma: %s\n", id);
        return;
    }

    // Kiem tra trang thai xuat vien
    int discharged = 0;
    if (discharged) {
        printf("Khong the cap nhat. Benh nhan da xuat vien.\n");
        return;
    }

    // Nhap so dien thoai moi va validate
    while (1) {
        inputString(newPhone, sizeof(newPhone), "Nhap SDT moi: ");
        if (!isValidPhone(newPhone)) {
            printf("!!! Loi: SDT phai chua it nhat 9 ky tu so va khong co chu cai.\n");
            continue;
        }
        break;
    }

    // Cap nhat
    strcpy(patients[index].phone, newPhone);
    printf(">>> Cap nhat SDT thanh cong!\n");
}

void printMenu() {
    printf("+-------------------------MENU-------------------------+\n");
    printf("|%-54s|\n","1. Tiep nhan benh nhan.");
    printf("|%-54s|\n","2. Cap nhat thong tin benh nhan.");
    printf("|%-54s|\n","3. Xuat vien");
    printf("|%-54s|\n","4. Hien thi danh sach benh nhan.");
    printf("|%-54s|\n","5. Tim kiem benh nhan.");
    printf("|%-54s|\n","6. Sap xep danh sach benh nhan.");
    printf("|%-54s|\n","7. Ghi nhan kham benh.");
    printf("|%-54s|\n","8. Xem lich su kham benh.");
    printf("|%-54s|\n","9. Thoat.");
    printf("+------------------------------------------------------+\n");
}

// Hàm nhập chuỗi
void inputString(char *dest, int size, const char *message) {
    while (1) {
        printf("%s", message);
        if (fgets(dest, size, stdin) != NULL) {
            // Xóa '\n'
            size_t len = strlen(dest);
            if (len > 0 && dest[len - 1] == '\n') {
                dest[len - 1] = '\0';
                len--;
            }
            // Kiểm tra rỗng
            if (len == 0) {
                printf("!!! Khong duoc de trong. Vui long nhap lai.\n");
            } else {
                break;
            }
        }
    }
}

int isPatientDischarged(const char *cardId) {
    (void)cardId;
    return 0;
}

void deletePatient() {
    if (patientCount == 0) {
        printf("Khong co benh nhan trong danh sach.\n");
        return;
    }

    char id[15];
    inputString(id, sizeof(id), "Nhap ma ho so (cardId) can xuat vien: ");

    int index = -1;
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay benh nhan.\n");
        return;
    }

    // Kiem tra debt
    if (patients[index].debt > 0) {
        printf("Benh nhan co cong no %.2f. Khong the xuat vien khi con no.\n", patients[index].debt);
        return;
    }

    // dich mang ve trai
    for (int j = index; j < patientCount - 1; j++) {
        patients[j] = patients[j + 1];
    }
    patientCount--;

    printf("Xuat vien thanh cong.\n");
}

void listPatients() {
    if (patientCount == 0) {
        printf("Chua co benh nhan nao\n");
        return;
    }
    // Header
    printf("+---------------+------------------------------+--------------------+------------+-------------+\n");
    printf("|%-15s|%-30s|%-20s|%-12s|%-13s|\n", "Ma ho so", "Ten benh nhan", "So dien thoai", "Cong no", "So ngay kham");
    printf("+---------------+------------------------------+--------------------+------------+-------------+\n");

    // Rows
    for (int i = 0; i < patientCount; i++) {
        printf("|%-15s|%-30s|%-20s|%12.0f|%13d|\n",
               patients[i].cardId,
               patients[i].name,
               patients[i].phone,
               patients[i].debt,
               patients[i].visitDays);
    }

    // Footer
    printf("+---------------+------------------------------+--------------------+------------+-------------+\n");
}

void listPatientsPaginate() {
    if (patientCount == 0) {
        printf("Chua co benh nhan nao.\n");
        return;
    }

    int page_size;
    char buffer[100];

    // --- Nhập số lượng dòng trên 1 trang ---
    while (1) {
        printf("Nhap so danh sach trong 1 trang (>0): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Xóa ký tự xuống dòng
            buffer[strcspn(buffer, "\n")] = 0;
            
            // Kiểm tra nhập rỗng
            if (strlen(buffer) == 0) {
                printf("Ban chua nhap gi ca. Vui long nhap lai.\n");
                continue;
            }

            // Kiểm tra xem có phải là số hợp lệ không
            if (sscanf(buffer, "%d", &page_size) == 1 && page_size > 0) {
                break;
            }
        }
        printf("Gia tri khong hop le. Thu lai.\n");
    }

    int total_page = (patientCount + page_size - 1) / page_size;
    int page_number = 1;

    // --- Vòng lặp hiển thị trang ---
    while (1) {
        // --- Nhập số trang ---
        while (1) {
            printf("Chon so trang can hien thi 1 -> %d : ", total_page);
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                buffer[strcspn(buffer, "\n")] = 0;

                if (strlen(buffer) == 0) continue;

                if (sscanf(buffer, "%d", &page_number) == 1) {
                    if (page_number >= 1 && page_number <= total_page) {
                        break; 
                    } else {
                        printf("So trang phai tu 1 den %d.\n", total_page);
                    }
                } else {
                    printf("Vui long nhap so, khong nhap chu.\n");
                }
            }
        }

        // --- Tính toán bắt đầu và kết thúc ---
        int start = (page_number - 1) * page_size;
        int end = start + page_size;
        if (end > patientCount) end = patientCount;

        // --- Header ---
        printf("\nTrang %d/%d: \n", page_number, total_page);
        printf("+---------------+------------------------------+--------------------+------------+-------------+\n");
        printf("|%-15s|%-30s|%-20s|%-12s|%-13s|\n", "Ma ho so", "Ten benh nhan", "So dien thoai", "Cong no", "So ngay kham");
        printf("+---------------+------------------------------+--------------------+------------+-------------+\n");

        for (int i = start; i < end; i++) {
            printf("|%-15s|%-30s|%-20s|%12.0f|%13d|\n",
                   patients[i].cardId,
                   patients[i].name,
                   patients[i].phone,
                   patients[i].debt,
                   patients[i].visitDays);
        }

        // --- Footer ---
        printf("+---------------+------------------------------+--------------------+------------+-------------+\n");
        printf("Ban co muon xem trang khac khong (Y/N)? ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char ch = buffer[0];
            if (ch == 'N' || ch == 'n') {
                break;
            }
        }
    }
}

void findPatient() {}
void sortList() {}
void addVisitRecord() {}
void showPatientRecords() {}


#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 1000
#define MAX_RECORDS 5000

// Mảng lưu bệnh nhân
struct patient {
    char cardId[15]; // CCCD / Mã hồ sơ
    char name[50];   // Tên bệnh nhân
    char phone[20];  // SDT
    double debt;     // Công nợ
    int visitDays;   // Số ngày khám
};
struct patient patients[MAX_PATIENTS];
int patientCount = 0;

// Mảng lưu lịch sử khám
struct record {
    char recId[20];
    char cardId[15];
    char date[20];
    char status[20];
};

// Khai báo hàm
void printMenu();
void addPatient();
void updatePatient();
void deletePatient();
void listPatients();
void findPatient();
void sortList();
void addVisitRecord();
void showPatientRecords();

int main() {
    int choice;
    while (1) {
        printMenu();
        printf("Nhap lua chon cua ban : ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: updatePatient(); break;
            case 3: deletePatient(); break;
            case 4: listPatients(); break;
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
    }
    return 0;
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

//===F01===

void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Danh sach benh nhan da day!\n");
        return;
    }

    struct patient p;
    printf("Nhap ma ho so (CCCD): ");
    fflush(stdin);
    fgets(p.cardId, sizeof(p.cardId), stdin);
    p.cardId[strcspn(p.cardId, "\n")] = 0;

    // Kiểm tra trùng mã
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, p.cardId) == 0) {
            printf("Ma ho so nay da ton tai!\n");
            return;
        }
    }

    printf("Nhap ten benh nhan: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Nhap so dien thoai: ");
    fgets(p.phone, sizeof(p.phone), stdin);
    p.phone[strcspn(p.phone, "\n")] = 0;

    printf("Nhap cong no hien tai: ");
    scanf("%lf", &p.debt);

    p.visitDays = 0;

    patients[patientCount++] = p;

    printf(">>> Da them benh nhan thanh cong!\n");
}

// F02 - CẬP NHẬT THÔNG TIN BỆNH NHÂN

void updatePatient() {
    char id[15];
    printf("Nhap ma ho so benh nhan can cap nhat: ");
    fflush(stdin);
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int index = -1;

    // Tìm kiếm bệnh nhân theo mã
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay benh nhan!\n");
        return;
    }

    struct patient *p = &patients[index];

    printf("Cap nhat ten (%s): ", p->name);
    fflush(stdin);
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = 0;

    printf("Cap nhat SDT (%s): ", p->phone);
    fgets(p->phone, sizeof(p->phone), stdin);
    p->phone[strcspn(p->phone, "\n")] = 0;

    printf("Cap nhat cong no (%.2f): ", p->debt);
    scanf("%lf", &p->debt);

    printf(">>> Cap nhat thanh cong!\n");
}

void deletePatient() {}
void listPatients() {}
void findPatient() {}
void sortList() {}
void addVisitRecord() {}
void showPatientRecords() {}

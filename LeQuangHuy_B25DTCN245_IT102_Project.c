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
    {"033207014120", "Le Quang Huy", "0824692222", 2000000.0, 0},
    {"1234567890", "Nguyen Van A", "0912345678", 0.0, 2},
    {"234567890", "Tran Thi B", "0987654321", 500000.0, 0},
    {"34567890", "Le Van C", "0901234567", 100000.0, 0},
    {"4567890", "Pham Thi D", "0933333333", 250000.0, 0},
    {"567890", "Hoang Van E", "0977777777", 0.0, 0}
};
int patientCount = 6;

// Struct lưu lịch sử khám bệnh
struct visitRecord {
    char cardId[15];
    char visitDate[15];
    char status[50];
};
struct visitRecord records[MAX_RECORDS] = {
    {"1234567890", "15/10/2024", "Theo Doi"},
    {"1234567890", "22/10/2024", "Tai kham"}
};
int recordCount = 2;


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
int findPatientIndex(const char *cardId);
int isRecordExists(const char *cardId, const char *visitDate);

// --- MAIN ---
int main() {
    int choice;
    char line[64];

    while (1) {
        printMenu();
        printf("Nhap lua chon cua ban: ");
        if (!fgets(line, sizeof(line), stdin))
            continue;
        line[strcspn(line, "\n")] = '\0';
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\0') {
            printf("Lua chon khong hop le, nhap lai !!!\n\n");
            continue;
        }
        char *t = p;
        while (*t) {
            if (!isdigit((unsigned char)*t)) {
                printf("Lua chon khong hop le, nhap lai !!!\n\n");
                break;
            }
            t++;
        }
        if (*t != '\0') continue;
        choice = atoi(p);
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
                printf("Lua chon khong hop le, nhap lai !!!\n");
        }

        printf("\n");
    }

    return 0;
}

// -- LOGIC --

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

int findPatientIndex(const char *cardId) {
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].cardId, cardId) == 0) {
            return i;
        }
    }
    return -1;
}

int isRecordExists(const char *cardId, const char *visitDate) {
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].cardId, cardId) == 0 && strcmp(records[i].visitDate, visitDate) == 0) {
            return 1;
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

    // 5. NHẬP DEBT
        char debt[50];
        while (1) {
            printf("Nhap cong no hien tai: ");
            fgets(debt, sizeof(debt), stdin);
            if (debt[0] == '\n') {
                printf("!!! Khong duoc de trong.\n");
                continue;
            }
            if (sscanf(debt, "%lf", &p.debt) == 1) {
                if (p.debt >= 0) {
                    break;
                } else {
                    printf("!!! Cong no khong duoc am.\n");
                }
            } else {
                printf("!!! Vui long nhap so hop le.\n");
            }
        }
    p.visitDays = 0;
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
    // Nhap so dien thoai moi
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

// F03 - Xoa benh nhan
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
        printf("Benh nhan co cong no %.0f VND,Can thanh toan truoc !!!\n", patients[index].debt);
        return;
    }

    // dich mang ve trai
    for (int j = index; j < patientCount - 1; j++) {
        patients[j] = patients[j + 1];
    }
    patientCount--;
    printf("Xuat vien thanh cong.\n");
}
// F04 - Danh Sach Benh Nhan
void listPatients() {
    if (patientCount == 0) {
        printf("Chua co benh nhan nao\n");
        return;
    }
    // Header
    printf("+---------------+------------------------------+--------------------+-------------+-------------+\n");
    printf("|%-15s|%-30s|%-20s|%-12s|%-13s|\n", "Ma ho so", "Ten benh nhan", "So dien thoai", "Cong no (VND)", "So ngay kham");
    printf("+---------------+------------------------------+--------------------+-------------+-------------+\n");
    // Rows
    for (int i = 0; i < patientCount; i++) {
        printf("|%-15s|%-30s|%-20s|%12.0f |%13d|\n",
               patients[i].cardId,
               patients[i].name,
               patients[i].phone,
               patients[i].debt,
               patients[i].visitDays);
    }
    // Footer
    printf("+---------------+------------------------------+--------------------+-------------+-------------+\n");
}
void listPatientsPaginate() {
    if (patientCount == 0) {
        printf("Chua co benh nhan nao.\n");
        return;
    }

    int page_size;
    char buffer[100];
    while (1) {
        printf("Nhap so phan tu trong 1 trang (>0): ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) == 0) {
                printf("Ban chua nhap gi ca. Vui long nhap lai.\n");
                continue;
            }
            if (sscanf(buffer, "%d", &page_size) == 1 && page_size > 0) {
                break;
            }
        }
        printf("Gia tri khong hop le. Thu lai.\n");
    }

    int total_page = (patientCount + page_size - 1) / page_size;
    int page_number = 1;
    while (1) {
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
        //--------------------------------------
        printf("\nTrang %d/%d: \n", page_number, total_page);
        printf("+---------------+------------------------------+--------------------+-------------+-------------+\n");
        printf("|%-15s|%-30s|%-20s|%-12s|%-13s|\n", "Ma ho so", "Ten benh nhan", "So dien thoai", "Cong no (VND)", "So ngay kham");
        printf("+---------------+------------------------------+--------------------+-------------+-------------+\n");

        for (int i = start; i < end; i++) {
            printf("|%-15s|%-30s|%-20s|%12.0f |%13d|\n",
                   patients[i].cardId,
                   patients[i].name,
                   patients[i].phone,
                   patients[i].debt,
                   patients[i].visitDays);
        }
        printf("+---------------+------------------------------+--------------------+-------------+-------------+\n");
        printf("Ban co muon xem trang khac khong (Y/N)? ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char ch = buffer[0];
            if (ch == 'N' || ch == 'n') {
                break;
            }
        }
    }
}
// --- F05: TÌM KIẾM BỆNH NHÂN ---
void findPatient() {
    char searchName[50];
    printf("\n--- TIM KIEM BENH NHAN ---\n");
    
    // Nhập 
    inputString(searchName, sizeof(searchName), "Nhap ten (hoac mot phan ten) can tim: ");

    int foundCount = 0;

    // Header
    printf("\nKET QUA TIM KIEM:\n");
    printf("+---------------+------------------------------+--------------------+-------------+-------------+\n");
    printf("|%-15s|%-30s|%-20s|%-12s|%-13s|\n", "Ma ho so", "Ten benh nhan", "So dien thoai", "Cong no (VND)", "So ngay kham");
    printf("+---------------+------------------------------+--------------------+-------------+-------------+\n");

    // Tìm kiếm
    for (int i = 0; i < patientCount; i++) {
        int nameLen = strlen(patients[i].name);
        int searchLen = strlen(searchName);
        int match = 0;

        for (int j = 0; j <= nameLen - searchLen; j++) {
            int k;
            for (k = 0; k < searchLen; k++) {
                char c1 = tolower(patients[i].name[j + k]);
                char c2 = tolower(searchName[k]);
                if (c1 != c2) break;
            }
            if (k == searchLen) {
                match = 1;
                break;
            }
        }
        if (match) {
            printf("|%-15s|%-30s|%-20s|%12.0f |%13d|\n",
                   patients[i].cardId,
                   patients[i].name,
                   patients[i].phone,
                   patients[i].debt,
                   patients[i].visitDays);
            foundCount++;
        }
    }

    printf("+---------------+------------------------------+--------------------+-------------+-------------+\n");

    if (foundCount == 0) {
        printf("!!! Khong tim thay benh nhan nao co ten chua '%s'.\n", searchName);
    } else {
        printf(">>> Tim thay %d benh nhan.\n", foundCount);
    }
}

// --- F06: SẮP XẾP DANH SÁCH ---
// swap
void bubbleSortPatients(int order) {
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - 1 - i; j++) {
            int needSwap = 0;

            if (order == 1 && patients[j].debt > patients[j+1].debt)
                needSwap = 1;
            else if (order == 2 && patients[j].debt < patients[j+1].debt)
                needSwap = 1;

            if (needSwap) {
                struct patient temp = patients[j];
                patients[j] = patients[j+1];
                patients[j+1] = temp;
            }
        }
    }
}
void sortList() {
    if (patientCount == 0) {
        printf("!!! Danh sach benh nhan hien dang trong.\n");
        return;
    }

    char temp[100];
    int choice = 0;

    // Nhận lựa chọn
    while (1) {
        printf("\n--- SAP XEP DANH SACH BENH NHAN ---\n");
        printf("Chon kieu sap xep:\n");
        printf("1. Sap xep Tang dan theo Cong no (Debt)\n");
        printf("2. Sap xep Giam dan theo Cong no (Debt)\n");
        printf("Nhap lua chon: ");

        if (fgets(temp, sizeof(temp), stdin) != NULL) {
            temp[strcspn(temp, "\n")] = 0;
            if (sscanf(temp, "%d", &choice) == 1 && (choice == 1 || choice == 2)) {
                break;
            }
        }
        printf("!!! Lua chon khong hop le. Vui long nhap 1 hoac 2.\n");
    }
    bubbleSortPatients(choice);
    // Thông báo
    if (choice == 1) {
        printf(">>> Da sap xep danh sach Tang dan theo Cong no.\n");
    } else {
        printf(">>> Da sap xep danh sach Giam dan theo Cong no.\n");
    }
    listPatients();
}
// --- F07: GHI NHẬN KHÁM BỆNH ---
// Hàm kiểm tra năm nhuận
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// Hàm kiểm tra ngày tháng
int isValidDate(const char *dateStr) {
    if (strlen(dateStr) != 10) return 0;
    int day, month, year;
    if (sscanf(dateStr, "%d/%d/%d", &day, &month, &year) != 3) return 0;
    if (year < 2024 || year > 2030  ) return 0;
    if (month < 1 || month > 12) return 0;
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        daysInMonth[2] = 29;
    }
    if (day < 1 || day > daysInMonth[month]) return 0;
    return 1;
}
void addVisitRecord() {
    if (recordCount >= MAX_RECORDS) {
        printf("!!! Danh sach lich su kham benh da day, khong the them moi!\n");
        return;
    }

    char id[15];
    char date[15];
    char statusBuffer[50];
    int typeChoice;
    char choiceBuff[10];
    printf("\n--- GHI NHAN KHAM BENH ---\n");
    // 1. Nhập và kiểm tra cardId
    inputString(id, sizeof(id), "Nhap ma ho so benh nhan (cardId): ");
    int patientIndex = findPatientIndex(id);
    if (patientIndex == -1) {
        printf("!!! Khong tim thay benh nhan co ma %s.\n", id);
        return;
    }

    // 2. Nhập và kiểm tra visitDate
    while (1) {
        inputString(date, sizeof(date), "Nhap ngay kham benh (dd/mm/yyyy): ");
        if (isValidDate(date)) {
            break;
        } else {
            printf("!!! Ngay thang khong hop le. Vui long nhap lai\n");
        }
    }

    // 3. Kiểm tra trùng lặp
    if (isRecordExists(id, date)) {
        printf("!!! Benh nhan %s da duoc ghi nhan lich kham vao ngay %s roi.\n", id, date);
        return;
    }

    // 4. NHẬP TRẠNG THÁI
    while (1) {
        printf("Chon trang thai ghi nhan:\n");
        printf("  1. Tai kham\n");
        printf("  2. Theo doi\n");
        printf("  3. Nhap ly do khac\n");
        printf("Nhap lua chon (1-3): ");
        
        if (fgets(choiceBuff, sizeof(choiceBuff), stdin)) {
            if (sscanf(choiceBuff, "%d", &typeChoice) == 1) {
                if (typeChoice == 1) {
                    strcpy(statusBuffer, "Tai kham");
                    break;
                } else if (typeChoice == 2) {
                    strcpy(statusBuffer, "Theo doi");
                    break;
                } else if (typeChoice == 3) {
                    inputString(statusBuffer, sizeof(statusBuffer), "Nhap trang thai/ly do: ");
                    break;
                }
            }
        }
        printf("!!! Lua chon khong hop le. Vui long chon 1, 2 hoac 3.\n");
    }
    
    patients[patientIndex].visitDays++;
    struct visitRecord newRecord;
    strcpy(newRecord.cardId, id);
    strcpy(newRecord.visitDate, date);
    strcpy(newRecord.status, statusBuffer);
    records[recordCount++] = newRecord;
    printf(">>> THANH CONG: Ghi nhan trang thai '%s' ngay %s cho benh nhan %s.\n", statusBuffer, date, id);
    printf("Tong so lan kham: %d\n", patients[patientIndex].visitDays);
}
// --- F08: XEM LỊCH SỬ KHÁM BỆNH---
void showPatientRecords() {
    char id[15];
    printf("\n--- XEM LICH SU KHAM BENH ---\n");
    inputString(id, sizeof(id), "Nhap ma ho so benh nhan can xem lich su (cardId): ");
    if (findPatientIndex(id) == -1) {
        printf("!!! Khong tim thay benh nhan co ma %s.\n", id);
        return;
    }
    
    printf("\n--- LICH SU KHAM BENH CUA BENH NHAN %s ---\n", id);
    printf("+-------+-----------------+---------------------------------+\n");
    printf("|%-7s|%-17s|%-33s|\n", "STT", "Ngay kham", "Trang thai");
    printf("+-------+-----------------+---------------------------------+\n");

    int foundCount = 0;
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].cardId, id) == 0) {
            printf("|%-7d|%-17s|%-33s|\n",
                   foundCount + 1,
                   records[i].visitDate,
                   records[i].status);
            foundCount++;
        }
    }
    
    printf("+-------+-----------------+---------------------------------+\n");

    if (foundCount == 0) {
        printf("!!! Benh nhan %s chua co lich su kham benh nao duoc ghi nhan.\n", id);
    } else {
        printf(">>> Tong cong %d lan kham benh.\n", foundCount);
    }
}

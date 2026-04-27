#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

// --- 1. KHAI BÁO CẤU TRÚC DỮ LIỆU ---

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[15];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node* link;
};

struct List {
    Node* first;
    Node* last;
};

// --- 2. CÁC HÀM CƠ BẢN ---

void Init(List& l) {
    l.first = l.last = NULL;
}

Node* CreateNode(SinhVien sv) {
    Node* p = new Node;
    if (p == NULL) return NULL;
    p->data = sv;
    p->link = NULL;
    return p;
}

void AddLast(List& l, Node* p) {
    if (l.first == NULL) {
        l.first = l.last = p;
    }
    else {
        l.last->link = p;
        l.last = p;
    }
}

// 3. TASK 2: NHẬP, SẮP XẾP VÀ CHÈN

// Hàm nhập thông tin 1 sinh viên
void Nhap1SV(SinhVien& sv) {
    cout << "Nhap ma SV: "; cin >> sv.maSV;
    cin.ignore(1000, '\n'); // Xóa bộ nhớ đệm
    cout << "Nhap ho ten: "; cin.getline(sv.hoTen, 50);
    cout << "Nhap ngay sinh (ngay thang nam): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cin.ignore();
}

// Sắp xếp danh sách hiện có theo mã SV
void SortList(List& l) {
    for (Node* p = l.first; p != NULL; p = p->link) {
        for (Node* q = p->link; q != NULL; q = q->link) {
            if (strcmp(p->data.maSV, q->data.maSV) > 0) {
                SinhVien temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
}

// Hàm chèn 1 SV mới vào danh sách đã sắp xếp
void InsertSorted(List& l, SinhVien sv) {
    Node* p = CreateNode(sv);
    if (l.first == NULL || strcmp(sv.maSV, l.first->data.maSV) < 0) {
        p->link = l.first;
        l.first = p;
        if (l.last == NULL) l.last = p;
        return;
    }
    Node* curr = l.first;
    while (curr->link != NULL && strcmp(curr->link->data.maSV, sv.maSV) < 0) {
        curr = curr->link;
    }
    p->link = curr->link;
    curr->link = p;
    if (p->link == NULL) l.last = p;
}

// --- 4. TASK 3 & 4: XỬ LÝ NGÀY SINH ---

bool laCungNgaySinh(Ngay n1, Ngay n2) {
    return (n1.ngay == n2.ngay && n1.thang == n2.thang && n1.nam == n2.nam);
}

void InSVTrungNgaySinh(List l) {
    bool found = false;
    for (Node* p = l.first; p != NULL; p = p->link) {
        bool duplicate = false;
        for (Node* q = l.first; q != NULL; q = q->link) {
            if (p != q && laCungNgaySinh(p->data.ngaySinh, q->data.ngaySinh)) {
                duplicate = true; break;
            }
        }
        if (duplicate) {
            cout << "SV trung ngay sinh: " << p->data.maSV << " - " << p->data.hoTen << endl;
            found = true;
        }
    }
    if (!found) cout << "khong tim thay sinh vien cung ngay sinh" << endl;
}

void XoaTrungNgaySinh(List& l) {
    Node* curr = l.first;
    Node* prev = NULL;
    while (curr != NULL) {
        bool hasDup = false;
        for (Node* t = l.first; t != NULL; t = t->link) {
            if (curr != t && laCungNgaySinh(curr->data.ngaySinh, t->data.ngaySinh)) {
                hasDup = true; break;
            }
        }
        if (hasDup) {
            Node* del = curr;
            if (prev == NULL) { l.first = curr->link; curr = l.first; }
            else { prev->link = curr->link; curr = prev->link; }
            if (del == l.last) l.last = prev;
            delete del;
        }
        else {
            prev = curr; curr = curr->link;
        }
    }
}

// --- 5. HÀM IN DANH SÁCH ---

void PrintList(List l) {
    cout << left << setw(15) << "Ma SV" << setw(20) << "Ho Ten" << "Ngay Sinh" << endl;
    for (Node* p = l.first; p != NULL; p = p->link) {
        cout << left << setw(15) << p->data.maSV << setw(20) << p->data.hoTen
            << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl;
    }
}

// --- CHƯƠNG TRÌNH CHÍNH ---

int main() {
    List ds;
    Init(ds);
    int n;

    cout << "Nhap so luong SV ban dau: "; cin >> n;
    for (int i = 0; i < n; i++) {
        SinhVien sv;
        cout << "\nNhap SV thu " << i + 1 << ":" << endl;
        Nhap1SV(sv);
        AddLast(ds, CreateNode(sv));
    }

    cout << "\n--- Danh sach ban dau ---" << endl;
    PrintList(ds);

    // Task 2: Sắp xếp
    SortList(ds);
    cout << "\n--- Danh sach sau khi sap xep tang dan theo Ma SV ---" << endl;
    PrintList(ds);

    // Chèn thêm 1 SV mới vào danh sách đã sắp xếp
    SinhVien svMoi;
    cout << "\nNhap 1 SV moi de chen vao danh sach:" << endl;
    Nhap1SV(svMoi);
    InsertSorted(ds, svMoi);
    cout << "\n--- Danh sach sau khi chen SV moi ---" << endl;
    PrintList(ds);

    // Task 3: In SV cùng ngày sinh
    cout << "\n--- Kiem tra sinh vien cung ngay sinh ---" << endl;
    InSVTrungNgaySinh(ds);

    // Task 4: Loại bỏ SV cùng ngày sinh
    cout << "\n--- Danh sach sau khi loai bo SV trung ngay sinh ---" << endl;
    XoaTrungNgaySinh(ds);
    PrintList(ds);

    cout << endl;
    system("pause");
    return 0;
}

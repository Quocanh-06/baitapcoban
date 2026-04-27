#include <iostream>
#include <string.h>
using namespace std;

// 1. Cấu trúc Ngày sinh [cite: 5-8]
struct Ngay {
    int ngay, thang, nam;
};

// 2. Cấu trúc thông tin Sinh viên [cite: 33-42]
struct SinhVien {
    char maSV[8];
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

void Init(List& l) {
    l.first = NULL;
    l.last = NULL;
}

int main() {
    List ds;
    Init(ds);
    cout << "Da khoi tao danh sach sinh vien!" << endl;
    return 0;
}
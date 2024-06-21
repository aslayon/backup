#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Book {
    string* title;
    int price;

public:
    Book(string title, int price);
    ~Book();
    void set(string title, int price);
    void show() { cout << *title << ' ' << price << "��" << endl; }
};

Book::Book(string title, int price) {
    this->price = price;
    this->title = new string(title);
}

Book::~Book() {
    if (title)
        delete title;
}

void Book::set(string title, int price) {
    

    this->price = price;
    this->title = new string(title);
}

int main() {
    Book cpp("��ǰC++", 10000);
    Book java = cpp;
    java.set("��ǰ�ڹ�", 12000);
    cpp.show();
    java.show();

    return 0;
}

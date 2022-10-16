#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <string>
#include <clocale>
#include <iomanip>

using namespace std;

class Useless
{
private:
    int n;
    char* pc;
    static int ct;
    void ShowObject() const;
public:
    Useless();  // Constructor
    explicit Useless(int k); // Constructor
    Useless(int k, char ch);  // Constructor
    Useless(const Useless& f);  // Copy constructor
    Useless(Useless&& f);  // Move constructor
    Useless operator=(const Useless& f);  // Assignment constructor
    Useless operator=(Useless&& f);  // Move assigment construtor
    ~Useless(); // Destructor
    Useless operator+(const Useless& f) const;
    void ShowData() const;
};

int Useless::ct = 0;

Useless::Useless() {
    ++ct;
    n = 0;
    pc = nullptr;
    cout << "Default constructor called; Number of objects: " << ct << endl;
    ShowObject();
}

Useless::Useless(int k) : n(k) {
    ++ct;
    pc = new char[n];
    cout << "Int constructor called; Number of objects: " << ct << endl;
    ShowObject();
}

Useless::Useless(int k, char ch) : n(k) {
    ++ct;
    pc = new char[n];
    for (char* p = pc; p < pc + n; p++)
        *p = ch;
    cout << "Int and char constructor called; Number of objects: " << ct << endl;
    ShowObject();
}

Useless::Useless(const Useless& f) : n(f.n) {
    ++ct;
    pc = new char[n];
    for (char* p = pc; p < pc + n; p++)
        *p = *f.pc;
    cout << "Copy constructor called; Number of objects: " << ct << endl;
    ShowObject();
}

Useless::Useless(Useless&& f) : n(f.n) {
    ++ct;
    pc = f.pc;
    f.pc = nullptr;
    f.n = 0;
    cout << "Move constructor called; Number of objects: " << ct << endl;
    ShowObject();
}

Useless Useless::operator=(const Useless& f) {
    if (this == &f)
        return *this;
    n = f.n;
    delete[] pc;
    pc = new char[n];
    for (char* p = pc; p < pc + n; p++)
        *p = *f.pc;
    cout << "= constructor called; Nuber of objects: " << ct << endl;
    ShowObject();
    return *this;
}

Useless Useless::operator=(Useless&& f) {
    if (this == &f)
        return *this;
    n = f.n;
    delete[] pc;
    pc = f.pc;
    f.n = 0;
    f.pc = nullptr;
    cout << "Move = constructor called; Nuber of objects: " << ct << endl;
    ShowObject();
    return *this;
}

Useless::~Useless() {
    cout << "Destructor called; Number of objects: " << --ct << endl;
    cout << "Deleted object: ";
    ShowObject();
    cout << endl;
    delete[] pc;
}

Useless Useless::operator+(const Useless& f) const {
    cout << "Entering operator+()\n";
    Useless temp = Useless(n + f.n);
    for (int i = 0; i < n; i++)
        temp.pc[i] = pc[i];
    for (int i = n; i < temp.n; i++)
        temp.pc[i] = f.pc[i - n];
    cout << "Temp object: " << endl;
    cout << "Leaving operator+()\n";
    return temp;
}

void Useless::ShowObject() const {
    cout << "Number of elements: " << n << endl;
    cout << "Data adress: " << (void*)pc << endl;
}

void Useless::ShowData() const {
    if (n == 0)
        cout << "Object is empty!";
    else
        for (auto p = pc; p < pc + n; p++)
            cout << *p;
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    {
        Useless one(10, 'x');
        Useless two;
        Useless three;
        two = one;
        three = one + two;
        cout << "\n\nObject 1: ";
        one.ShowData();
        cout << "\n\nObject 2: ";
        two.ShowData();
        cout << "\n\nObject 3: ";
        three.ShowData();
    }
    {
        Useless one(10, 'x');
        Useless two = one;
        Useless three(20, 'o');
        Useless four(two + three);
        cout << "Object ein: ";
        one.ShowData();
        cout << "Object zwei: ";
        two.ShowData();
        cout << "Object drei: ";
        three.ShowData();
        cout << "Object vier: ";
        four.ShowData();
        cout << endl;
    }
    system("pause>nul");
}
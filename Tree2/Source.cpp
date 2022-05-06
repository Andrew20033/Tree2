#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <math.h>

using namespace std;

#pragma warning(disable:4996)
#pragma warning(disable:26495)

struct LC { LC() { system("chcp 1251 > nul"); srand(time(0)); } ~LC() { cin.get(); cin.get(); } } _A_;

struct Tree
{
    Tree* left;
    Tree* right;
    int num;
    int pass;
    char* Name;
    char* Surname;

    void setPass(int pass_cnt) { pass = pass_cnt; }
    void setName(char* name) {
        Name = new char[strlen(name) + 1];
        strcpy(Name, name);
    }
    void setSurname(char* sur) {  Surname = new char[strlen(sur) + 1]; strcpy(Surname, sur); }

    Tree() :num(), left(), right(), pass(), Name(), Surname() {};
    Tree(int n) :num(n), left(), right() {};
    Tree(int n, int passa, char* tempname, char* tsurname) :num(n), left(), right(), pass(passa) { setName(tempname); setSurname(tsurname); };

    ~Tree() {
        if (Name) { delete Name; }
        if (Surname) { delete Surname; }
    }
};

class BTree
{
    Tree* root;

public:
    BTree() :root() {};

    Tree* getRoot() const { return root; }

    void add(Tree*& t, int n, int pass, char* nm, char* srn) {
        if (t == nullptr) {
            t = new Tree(n, pass, nm, srn);

        }
        else {

            if (n < t->num) {
                add(t->left, n, pass, nm, srn);

            }
            else {
                add(t->right, n, pass, nm, srn);
            }
        }

    }

    void sSearch(int key, Tree*& t)
    {
        if (t->num != key && t != nullptr) {

            inorder(t->left);
            inorder(t->right);

        }
    }




    void additem(int n, int pass, char* nm, char* srn) {
        add(root, n, pass, nm, srn);
    }
    static void inorder(Tree*& t)
    {

        if (t != nullptr) {

            inorder(t->left);
            cout << "Номер автобуса: " << t->num << " | " << " кол-во пассажиров: " << t->pass << " | " << "имя фамилия водителя: " << t->Name << " " << t->Surname << endl;
            inorder(t->right);

        }
    }
    void showtree() {
        inorder(root);
    }
    void showtree(Tree* root) {
        inorder(root);
    }

    friend ostream& operator<<(ostream& os, const BTree& A) {
        Tree* t = A.getRoot();

        if (t != nullptr) {

            BTree::inorder(t->left);
            BTree::inorder(t->right);

        }

        os << endl;
        return os;
    };

    BTree* fSearch(int key, const BTree& A) {
        Tree* t = A.getRoot();
        if (t->num == key) {
            showtree(t);
            return this;

        }
        else {

            if (key < t->num) {
                sSearch(key, t->left);

            }
            else {
                sSearch(key, t->right);
            }
        }
    };

};


int main()
{

    BTree bt;

    cout << "Значения до занесения в дерево:" << endl;
    int num;
    int pass;
    char buf_name[200];
    char buf_surname[200];

    for (int i = 0; i != 2; i++) {
        cout << "Введите номер автобуса - ";            cin >> num;             cout << endl;
        cout << "Введите кол-во пассажиров - ";           cin >> pass; cin.ignore();          cout << endl;
        cout << "Введите имя водителя - ";                cin.getline(buf_name, 200);        cout << endl;
        cout << "Введите фамилию водителя - ";        cin.getline(buf_surname, 200);  cout << endl;

        bt.additem(num, pass, buf_name, buf_surname);
    }
    cout << endl;
    cout << "Вывод дерева:" << endl;
    cout << bt;

    cout << "Введите номер автобуса который хотите найти - "; cin >> num;
    bt.fSearch(num, bt);


}
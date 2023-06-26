#include <string>
#include <iostream>
#include <regex>
#include <windows.h>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
using namespace std;

regex LC("(([АВЧ]{1})([0-9]{4})([-]{1})([0-9]{2}))");
regex C("(([\\d]{3})([.]{1})([\\d]{3}))");

struct Book {
    string Cipher;
    string Author;
    string Name;
    string Publisher;
    int YearPublication;
    int All = 0;
    int InPlace = 0;
};

struct tree {
    Book* book;
    tree* left;
    tree* right;
    int h = 1;
};

int compare(string cipher1, string cipher2) // 3 - равны, 1 - меньше, 2 - больше
{
    int i = 0;
    const char* ciph1 = cipher1.c_str();
    const char* ciph2 = cipher2.c_str();
    if (strcmp(ciph1, ciph2) == 0) {
        return 3;
    }
    while (i < cipher1.length()) {
        if (ciph1[i] == ciph2[i]) i++;
        else if (ciph1[i] < ciph2[i]) return 1;
        else return 2;
    }
}

unsigned char height(tree* R)
{
    return R ? R->h : 0;
}

// разность высот левого и правого поддеревьев
int bfactor(tree* R) {
    return height(R->right) - height(R->left);
}

//восстанавливает корректное значение поля height заданного узла
void fixheight(tree* R) {
    int hl = height(R->left);
    int hr = height(R->right);
    if (hl > hr) R->h = hl + 1;
    else R->h = hr + 1;
}

// правый поворот вокруг q
tree* right_rotate(tree* p) {
    tree* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

// левый поворот вокруг p
tree* left_rotate(tree* q) {
    tree* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

// балансировка узла
tree* balance(tree* R) {
    fixheight(R);
    if (bfactor(R) == 2) {
        if (bfactor(R->right) < 0)
            R->right = right_rotate(R->right); return left_rotate(R);
    }
    if (bfactor(R) == -2) {
        if (bfactor(R->left) > 0)
            R->left = left_rotate(R->left); return right_rotate(R);
    }
    return R; // балансировка не нужна
}

//поиск
tree* search(tree*& R, Book* books, int k) {
    if (compare(books->Cipher, R->book->Cipher) == 3) {
        //cout << "Кол-во шагов: " << k++ << endl;
        return R;
    }
    k++;
    if (compare(books->Cipher, R->book->Cipher) == 1) {
        if (R->left == NULL) {
            tree* R = new tree();
            return NULL;
        }
        search(R->left, books, k);
    }
    if (compare(books->Cipher, R->book->Cipher) == 2) {
        if (R->right == NULL) {
            tree* R = new tree();
            return NULL;
        }
        search(R->right, books, k);
    }
}

tree* find_min(tree* R) {
    if (R->left == NULL) return R;
    else find_min(R->left);
}

tree* remmin(tree* R) {
    if (R->left == NULL) return R->right;
    R->left = remmin(R->left);
    return balance(R);
}

string inputCipher()
{
    string key;
    cout << " Cтрока формата «NNN.MMM», где NNN – номер тематического раздела (цифры)\n"
        << " MMM – порядковый номер книги в разделе (цифры)\n";
    cin >> key;
    while (cin.fail() || (regex_match(key, C) == false)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << " Неверно!" << endl;
        cout << " Введите шифр книги: ";
        cin >> key;
    }
    return key;
}

bool checkAuthor(string author)
{
    int p = 0;
    for (int i = 0; i < author.length(); i++) {
        if ((author[i] <= 'Я' && author[i] >= 'А')) p++;
    }
    if (p != 3) return false;
    return true;
}

string inputAuthor()
{
    string author = " ";
    cout << " Введите автора книги: ";
    cin.ignore();
    getline(std::cin, author);
    while (cin.fail() || !(checkAuthor(author))) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << " Неверно!" << endl;
        cout << " Введите автора: ";
        getline(std::cin, author);
    }
    return author;
}

string inputPublisher()
{
    string publisher = " ";
    cout << " Введите издательство книги: ";
    cin.ignore();
    getline(std::cin, publisher);
    while (cin.fail()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << " Неверно!" << endl;
        cout << " Введите издательство: ";
        cin.ignore();
        getline(std::cin, publisher);
    }
    return publisher;
}

string inputName()
{
    string name = " ";
    cout << " Введите название книги: ";
    cin.ignore();
    getline(std::cin, name);
    while (cin.fail()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << " Неверно!" << endl;
        cout << " Введите название: ";
        cin.ignore();
        getline(std::cin, name);
    }
    return name;
}

bool checkYearPublication(int birthYear)
{
    if (birthYear > 2021) return false;
    return true;
}

int inputYearPublication()
{
    int YearPublication = 1;
    cout << " Введите год публикации книги: ";
    cin >> YearPublication;
    while (cin.fail() || !(checkYearPublication(YearPublication))) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << " Неверно!" << endl;
        cout << " Введите год публикации: ";
        cin >> YearPublication;
    }
    return YearPublication;
}

tree* remove(tree* R, string Cipher) {
    if (R == NULL) return 0;
    if (compare(Cipher, R->book->Cipher) == 1)
        R->left = remove(R->left, Cipher);
    else if (compare(Cipher, R->book->Cipher) == 2)
        R->right = remove(R->right, Cipher);
    else {
        tree* l = R->left; tree* r = R->right; delete R;
        if (r == NULL) return l; tree* min = find_min(r); min->right = remmin(r); min->left = l;
        return balance(min);
    }
    return balance(R);
}

//вывод дерева
void print_tree(tree* R, int l) {
    if (R != NULL) {
        print_tree(R->right, l + 1);
        for (int i = 1; i <= l; i++) cout << "   ";
        cout << R->book->Cipher << endl; 
        print_tree(R->left, l + 1);
    }
}

void print_tree1(tree* R) {
    if (R != NULL) {
        print_tree1(R->right);
        cout << R->book->Cipher << " / ";
        cout << R->book->Author << " / ";
        cout << R->book->Name << " / ";
        cout << R->book->Publisher << " / ";
        cout << R->book->YearPublication << " / ";
        cout << R->book->All << " / ";
        cout << R->book->InPlace << endl;
        print_tree1(R->left);
    }
}

void search1(tree*& R, string cipher) {
    if (compare(cipher, R->book->Cipher) == 3) {
        cout << R->book->Cipher << " / ";
        cout << R->book->Author << " / ";
        cout << R->book->Name << " / ";
        cout << R->book->Publisher << " / ";
        cout << R->book->YearPublication << endl;
        return;
    }
    if (compare(cipher, R->book->Cipher) == 1) {
        if (R->left == NULL) {
            tree* R = new tree();
            return;
        }
        search1(R->left, cipher);
    }
    if (compare(cipher, R->book->Cipher) == 2) {
        if (R->right == NULL) {
            tree* R = new tree();
            return;
        }
        search1(R->right, cipher);
    }
}

Book* add_book(Book* book1)//заполнение параметров книги
{
    book1->Cipher = inputCipher();
    book1->Author = inputAuthor();
    book1->Name = inputName();
    book1->Publisher = inputPublisher();
    book1->YearPublication = inputYearPublication();
    book1->All += 1;
    book1->InPlace += 1;
    return book1;
}

tree* insert(tree* p, Book* k) //добавление книги в сбалансированное дерево
{
    if (!p)
    {
        tree* T = new tree;
        T->book = k;
        T->left = T->right = 0;
        T->h = 1;
        return T;
    }
    if (k->Cipher < p->book->Cipher)
        p->left = insert(p->left, k);
    else if (k->Cipher > p->book->Cipher)
        p->right = insert(p->right, k);
    else//ключ уже есть в дереве
    {
        cout << "Книга не добавлена. Такой шифр уже есть!\n";
        return p;
    }
    return balance(p);
}

void delete_arr(tree* R) {
    if (R == NULL) { cout << "Удаление успешно завершилось\n";  return; }
    delete_arr(R->left);
    delete R;
    delete_arr(R->right);
}

class Reader {
private:
    string LibraryCard;
    string FIO;
    int BirthYear;
    string Address;
    string Workplace;
    bool flag;
public:
    Reader() {
        LibraryCard = " ";
        FIO = " ";
        BirthYear = 0;
        Address = " ";
        Workplace = " ";
        flag = false;
    }

    Reader(string a, string b, int c, string d, string e) {
        LibraryCard = a;
        FIO = b;
        BirthYear = c;
        Address = d;
        Workplace = e;
        flag = false;
    }

    string getkey()
    {
        return LibraryCard;
    }

    string getfio()
    {
        return FIO;
    }

    int getBirthYear()
    {
        return BirthYear;
    }

    string getAddress()
    {
        return Address;
    }

    string getWorkplace()
    {
        return Workplace;
    }

    void setkey(string k)
    {
        LibraryCard = k;
    }

    void setfio(string fio)
    {
        FIO = fio;
    }

    void setbirthyear(int birthyear)
    {
        BirthYear = birthyear;
    }

    void setaddress(string address)
    {
        Address = address;
    }

    void setworkplace(string workplace)
    {
        Workplace = workplace;
    }

    bool cellempty()
    {
        if ((LibraryCard == " ") && (flag == false)) { return true; }
        else { return false; }
    }

    bool delet()
    {
        if ((flag == true) && (LibraryCard == " ")) { return true; }
        else { return false; }
    }

    void setflag(bool f)
    {
        flag = f;
    }
};

class HashTable {
private:
    static const int default_size = 100;
    int size;
public:
    Reader* arr;

    HashTable()
    {
        size = default_size;
        arr = new Reader[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = Reader();
        }
    }

    void clear() {
        for (int i = 0; i < size; ++i) {
            if (arr[i].cellempty()) {
                arr[i].setkey(" ");
                arr[i].setfio(" ");
                arr[i].setbirthyear(0);
                arr[i].setaddress(" ");
                arr[i].setworkplace(" ");
                arr[i].setflag(true);
            }
        }
        delete[] arr;
    }

    int GetSize() { return size; };

    string inputKey()
    {
        string key;
        cout << " Cтрока формата «ANNNN-YY»\n"
            << " где A – буква, обозначающая права доступа читателя(А – только абонемент, Ч – только читальный зал, В – читальный зал и абонемент)\n"
            << " NNNN – порядковый номер регистрации(цифры)\n" // добавить счетчик
            << " YY – последние две цифры номера года регистрации\n"; // проверка чтобы не больше 21
        cout << " Введите номер читательского билета: ";
        cin >> key;
        while (cin.fail() || (regex_match(key, LC) == false)) {
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(), '/n');
            cout << " Неверно!" << endl;
            cout << " Введите номер читательского билета: ";
            cin >> key;
        }
        return key;
    }

    bool checkFIO(string fio)
    {
        int p = 0;
        for (int i = 0; i < fio.length(); i++) {
            if ((fio[i] <= 'Я' && fio[i] >= 'А')) p++;
        }
        if (p != 3) return false;
        return true;
    }

    string inputFIO()
    {
        string fio = " ";
        cout << " Введите ФИО читателя: ";
        cin.ignore();
        getline(std::cin, fio);
        while (cin.fail() || !(checkFIO(fio))) {
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(), '/n');
            cout << " Неверно!" << endl;
            cout << " Введите ФИО: ";
            getline(std::cin, fio);
        }
        return fio;
    }

    bool checkBirthYear(int birthYear)
    {
        if (birthYear > 2021 || birthYear < 1904) return false;
        return true;
    }

    int inputBirthYear()
    {
        int birthYear = 1;
        cout << " Введите год рождения читателя: ";
        cin >> birthYear; // перескакивает
        while (cin.fail() || !(checkBirthYear(birthYear))) {
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(), '/n');
            cout << " Неверно!" << endl;
            cout << " Введите год рождения: ";
            cin >> birthYear;
        }
        return birthYear;
    }

    bool checkAddress(string address)
    {
        return true; 
    }

    string inputAddress()
    {
        string address = " ";
        cout << " Введите адрес читателя: ";
        cin.ignore();
        getline(std::cin, address);
        while (cin.fail() || !(checkAddress(address))) {
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(), '/n');
            cout << " Неверно!\n";
            cout << " Введите адрес: ";
            cin.ignore();
            getline(std::cin, address);
        }
        return address;
    }

    bool checkWorkplace(string workplace)
    {
        return true; 
    }

    string inputWorkplace()
    {
        string workplace = " ";
        cout << " Введите место работы/учебы читателя: ";
        cin.ignore();
        getline(std::cin, workplace);
        while (cin.fail() || !(checkAddress(workplace))) {
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(), '/n');
            cout << " Неверно!" << endl;
            cout << " Введите место работы/учебы: ";
            cin.ignore();
            getline(std::cin, workplace);
        }
        return workplace;
    }

    int HashFunctionHorner(const string& s, int table_size, const int key)
    {
        int hash_result = 0;
        for (int i = 0; s[i] != 0; i++)
        {
            hash_result = (key * hash_result + s[i]) % table_size;
        }
        return hash_result;
    }

    void add(string LibraryCard, string FIO, int BirthYear, string Address, string Workplace)
    {
        int hashindex = HashFunctionHorner(LibraryCard, size, 5); //высчитываем номер ячейки где будет храниться ключ
        int numtry = 0;
        int fl = 0;
        while (fl != 1) {
            if (arr[hashindex].cellempty()) {
                arr[hashindex].setkey(LibraryCard);
                arr[hashindex].setfio(FIO);
                arr[hashindex].setbirthyear(BirthYear);
                arr[hashindex].setaddress(Address);
                arr[hashindex].setworkplace(Workplace);
                fl = 1;
                break;
            }
            else {
                numtry++;
                hashindex = static_cast<int>(hashindex + (round(2 * sqrt(numtry))) + numtry) % size;
            }
        }
    }

    void find()
    {
        int ch;
        cout << " Как вы хотите искать (1-по номеру читательского билета /2-по ФИО)?\n";
        cin >> ch;
        while (cin.fail() || (ch < 1) || (ch > 2)) {
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(), '/n');
            cout << " Неверно!\n";
            cout << " Введите заново: ";
            cin >> ch;
        }
        if (ch == 1) {
            string key = inputKey();
            int j = 0, m = 0;
            for (j; j < size; j++) {
                if (arr[j].getkey() == key) {
                    cout << " Элемент " << j << endl;
                    cout << arr[j].getkey() << " / ";
                    cout << arr[j].getfio() << " / ";
                    cout << arr[j].getBirthYear() << " / ";
                    cout << arr[j].getAddress() << " / ";
                    cout << arr[j].getWorkplace() << endl;
                    m++;
                    break;
                }
            }
            if (m == 0) cout << "Читатель с таким номером читательского билета не зарегистрирован.\n";
        }
        else if (ch == 2) {
            string fio = inputFIO();
            int i = 0, l = 0;
            for (i; i < size; i++) {
                if (arr[i].getfio() == fio) {
                    cout << " Элемент " << i << endl;
                    cout << arr[i].getkey() << " / ";
                    cout << arr[i].getfio() << " / ";
                    cout << arr[i].getBirthYear() << " / ";
                    cout << arr[i].getAddress() << " / ";
                    cout << arr[i].getWorkplace() << endl;
                    l++;
                    break;
                }
            }
            if (l == 0) cout << "Читатель с такими ФИО не зарегистрирован.\n";
        }
        system("pause");
    }

    void del()
    {
        cout << "Введите номер читательского билета, который хотите удалить.\n";
        string key = inputKey();
        int i = 0, l = 0;
        for (i; i < size; i++) {
            if (arr[i].getkey() == key) {
                arr[i].setkey(" ");
                arr[i].setfio(" ");
                arr[i].setbirthyear(0);
                arr[i].setaddress(" ");
                arr[i].setworkplace(" ");
                arr[i].setflag(true);
                cout << endl;
                cout << "Элемент удален" << endl;
                l++;
                break;
            }
        }
        if (l == 0) cout << "Читательский билет под таким номером не был найден.\n";
        system("pause");
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << "Элемент " << i << endl;
            if (arr[i].cellempty()) {
                cout << "Пусто" << endl;
            }
            else if (arr[i].delet()) { cout << "Элемент удален" << endl; }
            else {
                cout << arr[i].getkey() << " / ";
                cout << arr[i].getfio() << " / ";
                cout << arr[i].getBirthYear() << " / ";
                cout << arr[i].getAddress() << " / ";
                cout << arr[i].getWorkplace() << endl;
            }
        }
    }
};

struct BookActivities {
    Book* book;
    string LibraryCard0;
    string Issuance;
    string Receiving;
    struct BookActivities* next;
    struct BookActivities* prev;
};

struct BookActivities* init(string reader, Book* book1, string iss, string rec)
{
    struct BookActivities* lst = new BookActivities;
    lst->book = book1;
    lst->book->InPlace -= 1;
    lst->LibraryCard0 = reader; 
    lst->Issuance = iss;
    lst->Receiving = rec;
    lst->next = NULL;
    lst->prev = NULL;
    return (lst);
}

struct BookActivities* addelem(BookActivities* lst, string reader, Book* book1, string iss, string rec)
{
    struct BookActivities * p;
    struct BookActivities* temp = new BookActivities;
    p = lst->next; 
    lst->next = temp;
    temp->book = book1;
    temp->book->InPlace -= 1;
    temp->LibraryCard0 = reader; 
    temp->Issuance = iss; 
    temp->Receiving = rec;
    temp->next = p; 
    temp->prev = lst; 
    p->prev = temp;
    return temp;
}

struct BookActivities* deletelem(BookActivities* lst)
{
    struct BookActivities* prev, * next;
    prev = lst->prev; 
    next = lst->next; 
    lst->book->InPlace += 1;
    prev->next = lst->next; 
    next->prev = lst->prev; 
    free(lst);
    return(prev);
}

string Data() {
    string brt;
    cout << "Пример: 01.05.2001\n";
    cout << "Введите дату приема/возврата: ";
    cin >> brt;
    return brt;
}

Book* search2(tree*& R, string cipher) {
    int x = compare(cipher, R->book->Cipher);
    if (x == 3) {
        return R->book;
    }
    if (x == 1) {
        search2(R->left, cipher);
    }
    if (x == 2) {
        search2(R->right, cipher);
    }
}

void swapS(string* a, string* b)
{
    string t = *a; 
    *a = *b; 
    *b = t;
}

void swapB(Book* a, Book* b)
{
    Book t = *a;
    *a = *b;
    *b = t;
}

BookActivities* lastNode(BookActivities* root)
{
    while (root && root->next)
        root = root->next;
    return root;
}

BookActivities* partition(BookActivities* l, BookActivities* h)
{
    // установить поворот как элемент h
    string x = h->book->Cipher;
    // аналогично i = l-1 для реализации массива
    BookActivities* i = l->prev;
    // Аналогично "for (int j = l; j <= h- 1; j ++)"
    for (BookActivities* j = l; j != h; j = j->next)
    {
        if(compare(j->book->Cipher, x)==3 || compare(j->book->Cipher, x)==1)
        {
            // Аналогично i ++ для массива
            i = (i == NULL) ? l : i->next;
            swapB((i->book), (j->book));
            swapS(&(i->LibraryCard0), &(j->LibraryCard0));
            swapS(&(i->Issuance), &(j->Issuance));
            swapS(&(i->Receiving), &(j->Receiving));
        }
    }
    i = (i == NULL) ? l : i->next; // Аналогично i ++
    swapB((i->book), (h->book));
    swapS(&(i->LibraryCard0), &(h->LibraryCard0));
    swapS(&(i->Issuance), &(h->Issuance));
    swapS(&(i->Receiving), &(h->Receiving));
    return i;
}

void _quickSort(BookActivities* l, BookActivities* h)
{
    if (h != NULL && l != h && l != h->next)
    {
        BookActivities* p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}

void quickSort(BookActivities* head)
{
    // Найти последний узел
    BookActivities* h = lastNode(head);
    // Вызов рекурсивной быстрой сортировки
    _quickSort(head, h);
}

void printList(BookActivities* head)
{
    while (head)
    {
        cout << head->book->Cipher << " / ";
        cout << head->LibraryCard0 << " / ";
        cout << head->Issuance << " / ";
        cout << head->Receiving << endl;
        head = head->next;
    }
    cout << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    bool menu = true;
    int in;
    tree* root = NULL;
    BookActivities* head = NULL;
    HashTable H;
    BookActivities* cur;
    string istr, read, cipher3, iss, rec;
    while (menu) {
        do {
            system("cls");
            cout << "Меню:\n";
            cout << "1) Добавить читателя\n";
            cout << "2) Удалить читателя\n";
            cout << "3) Поиск читателя\n";
            cout << "4) Вывести хэш-таблицу читателей\n";
            cout << "5) Очистка данных о читателях\n"; 
            cout << "6) Добавить книгу\n";
            cout << "7) Удалить книгу\n";
            cout << "8) Просмотр всех книг\n";
            cout << "9) Очистка данных о книгах\n";
            cout << "10) Поиск книги\n";
            cout << "11) Выдача книги\n";
            cout << "12) Прием книги\n";
            cout << "13) Вывести все выданные книги\n";
            cout << "14) Выход\n";
            cout << " ";
            if (!getline(cin, istr)) break;
        } while (!(istr == "14" || istr == "13" || istr == "12" || istr == "11" || istr == "10" || istr == "9" || istr == "8" || istr == "7" || istr == "6" || istr == "5" || istr == "4" || istr == "3" || istr == "2" || istr == "1"));
        in = atoi(istr.c_str());
        switch (in)
        {
        case 1: {
            int q = 0;
            for (int i = 0; i < H.GetSize(); i++) {
                if (H.arr[i].cellempty()) { q++; }
            }
            if (q == 0) {
                cout << "Таблица переполнена\n";
                break;
            }
            else {
                string tempkey = H.inputKey();
                string Fio = H.inputFIO();
                int Birthyear = H.inputBirthYear();
                string address = H.inputAddress();
                string workplace = H.inputWorkplace();
                H.add(tempkey, Fio, Birthyear, address, workplace);
                cout << H.HashFunctionHorner(tempkey, H.GetSize(), 5) << ": " << tempkey << endl;
                cout << "Читатель успешно добавлен\n";
                system("pause");
                break;
            }
        }
        case 2: {
            H.del();
            break;
        }
        case 3: {
            H.find();
            break;
        }
        case 4: {
            H.print();
            system("pause");
            break;
        }
        case 5: {
            H.clear();
            cout << "Данные о всех читателях были очищены\n";
            system("pause");
            break;
        }
        case 6: {
            Book* book1 = new Book;
            if (add_book(book1) != NULL)
            {
                root = insert(root, book1);
                system("pause");
            }
            break;
        }
        case 7: {
            cout << "Введите элемент, который хотите удалить:" << endl;
            string cipher1 = inputCipher();
            root = remove(root, cipher1);
            if (root == NULL) {
                cout << "Удалено всё дерево\n";
            }
            system("pause");
            break;
        }
        case 8: {
            print_tree1(root);
            print_tree(root, 0);
            system("pause");
            break;
        }
        case 9: {
            delete_arr(root);
            system("pause");
            break;
        }
        case 10: {
            cout << "Введите шифр книги, которую хотите найти:" << endl;
            string cipher2 = inputCipher();
            search1(root, cipher2);
            system("pause");
            break;
        }
        case 11: {
            cout << "Введите номер читательского билета, на который будет оформлена книга\n";
            read = H.inputKey();
            cout << "Введите шифр книги, которую хотите отдать\n" << endl;
            cipher3 = inputCipher();
            Book* book9 = search2(root, cipher3);
            while (book9->InPlace == 0) {
                cout << "Шифр книги введен неверно или ее нет в наличии\n";
                cout << "Введите шифр книги, которую хотите отдать\n" << endl;
                cipher3 = inputCipher();
                Book* book9 = search2(root, cipher3);
            }
            iss = Data();
            rec = Data();
            if (head == NULL) { 
                head = init(read, book9, iss, rec);
            }
            else {
                cur = addelem(head, read, book9, iss, rec);
            }
            system("pause");
            break;
        }
        case 12: {
            BookActivities* cur1 = new BookActivities;
            cout << "Введите шифр книги, которую возвращают\n" << endl;
            string cipher4 = inputCipher();
            Book* book7 = search2(root, cipher4);
            while (head->book != book7) {
                cur1 = head->next;
            }
            deletelem(cur1);
            cout << "Возврат книги совершен.\n";
            system("pause");
            break;
        }
        case 13: {
            cout << "До сортировки\n";
            printList(head);
            quickSort(head);
            cout << "После сортировки\n";
            printList(head);
            system("pause");
            break;
        }
        case 14: {
            menu = false;
            break;
        }
        default: {
            cout << "Ошибка ввода. Попытайтесь снова.";
            system("pause");
        }
        }
    }
    return 0;
}

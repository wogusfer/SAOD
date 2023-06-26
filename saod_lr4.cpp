#pragma once
#include <string>
#include <iostream>
#include <regex>
using namespace std;

class Element
{
private:
	string key;
	int coll;
	bool flag;
public:
	Element();
	Element(string k);
	bool delet(); // true-deleted false-' 
	bool cellempty();
	void setkey(string k);
	void setflag(bool f);
	string getkey();
	bool getflag();
	void setcoll(int c);
	int getcoll();
};
#include "Element.h"
Element::Element()
{
    key = " ";
    flag = false;
    coll = 0;
}
Element::Element(string k)
{
    key = k;
    flag = false;
    coll = 0;
}

bool Element::delet() 
{
    if ((flag == true) && (key ==" ")){ return true; }
    else { return false; }
}

bool Element::cellempty()
{
    if ((key == " ") && (flag == false)) { return true; }
    else { return false; }
}

void Element::setkey(string k)
{
    key = k;
}

void Element::setflag(bool f)
{
    flag = f;
}

string Element::getkey()
{
    return key;
}

bool Element::getflag()
{
    return flag;
}

void Element::setcoll(int c)
{
    coll = c;
}

int Element::getcoll()
{
    return coll;
}
#pragma once
#include <string>
#include <iostream>
#include <regex>
#include "Element.h"
using namespace std;

class HashTable
{
public:
    HashTable();
    ~HashTable();
    Element* arr;
    void add(string key);
    void find();
    void Print();
    void del();
    int GetSize() { return size; }; //нахождение кол-ва элементов  в списке
    string inputKey();
    int inputNum();
    int HashFunctionHorner(const string& s, int table_size, const int key);
private:
    static const int default_size = 3000;
    int size; // сколько элементов у нас сейчас в массиве 
};
#include "HashTable.h"
#include "Element.h"
#include <string>
#include <string>
#include <cstdlib>
regex reg("(([ABCDEFGHIJKLMNOPQRSTUVWXYZ]{2})([\\d]{2})([ABCDEFGHIJKLMNOPQRSTUVWXYZ]{2}))");

int HashTable::HashFunctionHorner(const string& s, int table_size, const int key)// хэш-функция строка которую будут хэшировать,размер таблицы,простое чис-ло
{
    int hash_result = 0;
    for (int i = 0; s[i] != 0; i++)
    {
        hash_result = (key * hash_result + s[i]) % table_size; //деление по модулю или с остатком
    }
    return hash_result; //номер этого ключа в массиве
}

HashTable::HashTable()
{
    size = default_size;
    arr = new Element[size];
    for (int i = 0; i < size; i++)
    {
        arr[i]=Element();
    }
}

HashTable::~HashTable()
{
   delete[] arr;
}

void HashTable::add(string key)
{
    int hashindex = HashFunctionHorner(key, size, 5); //высчитываем номер ячейки где будет храниться ключ
    int numtry = 0;
    int fl = 0;
    string k = arr[hashindex].getkey();
    if ((k == key) && (hashindex < size))
    {
        cout << "Такой ключ уже существует\n";
        return;
    }
    while (fl != 1) {
        if (hashindex<size)
        {
            if (arr[hashindex].cellempty()) {
                arr[hashindex].setkey(key);
                fl = 1;
                break;
            } else {
                arr[hashindex].setcoll(arr[hashindex].getcoll() + 1);
                numtry++;
                hashindex = static_cast<int>( hashindex + (round(2*sqrt(numtry) )) + numtry ) % size;// (хеш ключа)+(константа)*(корень из числа попыток разрешить коллизию)+
            }                                                            // +(константа)*(корень из числа попыток разрешить коллизию в квадрате)
        } else  {
            cout << "Превышен размер таблицы\n";
            cout << "Увеличиваем размер таблицы\n";
            
            Element* arr2 = new Element[size*2];
            
            for (int i = 0; i < (hashindex + 1); i++)
            {
                arr2[i] = Element();
            }
            
            for (int i = 0; i < size; i++)
            {
                arr2[i].setcoll(arr[i].getcoll());
                arr2[i].setflag(arr[i].getflag());
                arr2[i].setkey(arr[i].getkey());
            }
            
            size *=2;
            arr2[hashindex].setkey(key);
            delete[] arr;
            arr = arr2; 
            fl = 1;
            break;
        }
    }
}

void HashTable::find()
{
    int ch;
    cout << "Как вы хотите искать (1-по ключу /2-по номеру)?" << endl;
    cin >> ch;
    while (cin.fail() || (ch < 1) || (ch > 2)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << "Неверно!" << endl;
        cout << "Введите заново: ";
        cin >> ch;
    }

    if (ch == 1) {
        string key = inputKey();
        int hashindex = HashFunctionHorner(key, size, 5);

        if (arr[hashindex].cellempty()) { 
            cout << "Ячейка пуста" << endl; 
        }
        else if (arr[hashindex].delet()) { cout << "Элемент удален" << endl; }
        else {
            cout << "Элемент" << hashindex << endl;
            cout << arr[hashindex].getkey() << endl;
        }
    }
    else  if (ch == 2) {
        int num = inputNum();
        if (arr[num].cellempty()) {
            cout << "Ячейка пуста" << endl;
        }
        else if (arr[num].delet()){ cout << "Элемент удален" << endl; }
        else{ cout << "Элемент" << num <<endl;
        cout << arr[num].getkey() << endl;
        }
    }
}

void HashTable::Print()
{
    for (int i = 0; i < size; i++)
    {
        cout << "Элемент " << i << endl;
        if (arr[i].cellempty()) {
            cout << "Пусто" << endl;
        }
        else if (arr[i].delet()) { cout << "Элемент удален" << endl; }
        else {
            cout << arr[i].getkey() << endl;
        }
    }
}

string HashTable::inputKey()
{
    string key;
    cout << "Введите ключ:" << endl;
    cin >> key;
    while (cin.fail() || (key.size() != 6) || (regex_match(key, reg) == false)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << "Неверно!" << endl;
        cout << "Введите ключ: ";
        cin >> key;
    }
    return key;
}

int HashTable::inputNum()
{
    int num = 0;
    cout << "Введите номер элемента:" << endl;
    cin >> num;
    while (cin.fail() || (num < 0) || (num > (size - 1))) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << "Неверно!" << endl;
        cout << "Введите ключ:" << endl;
        cin >> num;
    }
    return num;
}

void HashTable::del()
{
    int ch;
    cout << "Как вы хотите удалить (1-по ключу /2-по номеру)?" << endl;
    cin >> ch;
    while (cin.fail() || (ch < 1) || (ch > 2)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << "Неверно!" << endl;
        cout << "Введите ключ: ";
        cin >> ch;
    }

    if (ch == 1)
    {
        string key = inputKey();

        int hashindex = HashFunctionHorner(key, size, 5);

        if (arr[hashindex].cellempty()) {
            cout << "Ячейка пуста" << endl;
        }
        else if (arr[hashindex].delet()) { cout << "Элемент удален" << endl; }
        else {
            arr[hashindex].setkey(" ");
            arr[hashindex].setflag(true);
            cout << endl;
            cout << "Элемент удален" << endl;
        }    
    }
    else if (ch == 2) {
        int num = inputNum();

        if (arr[num].cellempty()) {
            cout << "Ячейка пуста" << endl;
        }
        else if (arr[num].delet()) { cout << "Элемент удален" << endl; }
        else {
            arr[num].setkey(" ");
            arr[num].setflag(true);
            cout << endl;
            cout << "Элемент удален" << endl;
            cout << endl;
        }   
    }
}
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "HashTable.h"
using namespace std;

int getRandomNumber(int min, int max) //рандомная генерация 
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

string KeyGenerator() { //генератор ключей
    string key = "      ";

    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string nums = "0123456789";

    for (int i = 0; i < 6; i++)
    {
        int n = getRandomNumber(0, 9);
        int let = getRandomNumber(0, 24);

        if ((i ==0 )|| (i == 1) || (i == 4) || (i == 5)) {
            key[i] = letters[let];
        }
        else { key[i] = nums[n]; }
    }
    return key;
}

int inputCount() { // проверка на количество ключей
    int num = 0;
    cout << "Введите количество ключей для генерации: ";
    cin >> num;
    while (cin.fail() || (num <= 0)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '/n');
        cout << "Неверно!" << endl;
        cout << "Введите  количество ключей для генерации заново: ";
        cin >> num;
    }
    return num;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int v = 0;

    HashTable H;
    string Keys;

    while (v != 7)
    {
        cout << "/////Меню/////\n";
        cout << "1) Заполнить хэш-таблицу\n";
        cout << "2) Добавить элемент\n";
        cout << "3) Удалить элемент\n";
        cout << "4) Вывод хэш-таблицы\n";
        cout << "5) Поиск элемента\n";
        cout << "6) Таблица коллизий\n";
        cout << "7) Выход\n";

        cin >> v;
        while (cin.fail() || (v <= 0) || (v > 8)) {
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(), '/n');
            cout << "Неверно!" << endl;
            cout << "Введите заново: ";
            cin >> v;
        }
        switch (v)
        {
        case 1:
        {   int count = inputCount();
            for (int i = 0; i < count; i++)
            {
                H.add(KeyGenerator());
            }
            cout << "Заполнение хэш-таблицы завершено." << endl;
            break;
        }
        case 2:
        {
            int q = 0;
            for (int i = 0; i < H.GetSize(); i++) {
                if (H.arr[i].cellempty()) { q++; }
            }
            if ( q == 0 ) {
                cout << "Таблица переполнена\n";
                break;
            }
            else {
                string tempkey = H.inputKey();
                H.add(tempkey);
                cout << H.HashFunctionHorner(tempkey, H.GetSize(), 5) << ":  " << tempkey << endl;
                break;
            }
        }
        case 3:
        {  
            H.del();
            break;
        }
        case 4:
        {
            cout << "Вывод таблицы:" << endl;
            H.Print();
            break;
        }
        case 5:
        {  
            H.find();
            break;
        }
        case 6:
        {
            string path = "table.txt";
            fstream fs;
            fs.open(path, fstream::out | fstream::in | fstream::trunc);
            if (!fs.is_open())
            {
                cout << "Ошибка открытия файла" << endl;
            }
            else { cout << "Файл открыт" << endl; }

            for (int i = 0; i < H.GetSize(); i++)
            {
                  fs << H.arr[i].getcoll() << "\n";
            }
            cout << "Запись" << endl;
            fs.close();
            cout << "Файл закрыт" << endl;
            break;
        }
        case 7:
        {
            break;
        }
        default:
        {   cout << "Значение должно быть от 1 до 7!" << endl;  }
        }
    }
    return  0;
}

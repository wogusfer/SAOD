#include <iostream>
using namespace std;

struct list // структура списка
{ 
    int n; // главная степень многочлена
    int a; // коэффициент члена
    struct list* ptr; // указатель на следующий элемент
};

struct list* init(int a, int n) // инициализация первого узла
{
    struct list* lst;
    // выделение памяти под корень списка
    lst = (struct list*)malloc(sizeof(struct list));
    lst->n = n;
    lst->a = a;
    lst->ptr = lst; // указатель на сам корневой узел
    return(lst);
}

struct list* addelem(list* lst, int a, int n) // функция добавления элемента
{
    struct list* temp, * p;
    temp = (struct list*)malloc(sizeof(list));
    p = lst->ptr; // сохранение указателя на следующий элемент
    lst->ptr = temp; // предыдущий узел указывает на создаваемый
    temp->n = n;
    temp->a = a;// сохранение поля данных добавляемого узла
    temp->ptr = p; // созданный узел указывает на следующий элемент
    return(temp);
}

void deletelem(list* lst, int d, int n) // функция удаления элемента
{
    struct list* temp; 
    struct list* p1; 
    struct list* p2;
    temp = lst;//создаем временный узел
    for (int i = n; i > (d+1); i--)// находим адрес предыдущего элемента кото-рый хотим удалить
    {
        temp = temp->ptr; // передвигаемся до нужного элемента
    }
    p1 = temp->ptr; // указатель к удаляемому узлу
    p2 = p1->ptr; // указатель к последующему узлу
    temp->ptr = p2; 
    free(p1); // удаление нужного эелемнта
}

void listprint(list* lst) // функция вывода многочлена
{
    struct list* p;
    p = lst;
    cout << "P(x) = ";
    do {
        if (p->n != 0) {
            if (p->a == -1) cout << "-x^" << p->n;
            if (p->a == 0) cout << "";
            if (p->a == 1) cout << "+x^" << p->n;
            if ((p->a) < -1) cout << p->a << "x^" << p->n;
            if ((p->a) > 1) cout << "+" << p->a << "x^" << p->n;
        }
        else {
            if (p->a == 0) cout << "";
            if ((p->a) < 0) cout << p->a;
            if ((p->a) > 0) cout << "+" << p->a;
        };
        p = p->ptr; // переход к следующему узлу
    } while (p != lst); // условие окончания обхода
    cout << "\n";
}

void proizvodnaya(list* lst) // функция вывода производной
{
    struct list* p;
    p = lst;
    cout << "P'(x) = ";
    do {
        if ((p->n != 0) && (p->n != 1)) {
            if (p->a == -1) cout << (-1) * (p->n) << "x^" << ((p->n) - 1);
            if (p->a == 0) cout << "";
            if (p->a == 1) cout << "+" << p->n << "x^" << ((p->n) - 1);
            if ((p->a) < -1) cout << (p->a) * (p->n) << "x^" << ((p->n) - 1);
            if ((p->a) > 1) cout << "+" << (p->a) * (p->n) << "x^" << ((p->n) - 1);
        }
        else if (p->n == 1) {
            if ((p->a) < 0) cout << p->a;
            if ((p->a) > 0) cout << "+" << p->a;
        }
        else cout << "";
        p = p->ptr; // переход к следующему узлу
    } while (p != lst); // условие окончания обхода
    cout << "\n";
}

int main()
{
    setlocale(LC_ALL, "rus"); // подключаем русский язык
    int n, a; // счетчик элементов и степени
    list*elem1;
    cout << "Старшая степень многочлена: ";
    cin >> n;
    cout << "Введите коэффициент первого члена: ";
    cin >> a;
    elem1=init(a ,n); // создаем первый узел
    list* p;
    p = elem1;
    for (int i = n-1; i >-1; i--) // цикл для создания многочлена
    {
        cout << "Добавьте элемент многочлена №" << i << ": ";
        cin >> a;
        addelem(p, a, i);
        p = p->ptr;
    }
    listprint(elem1); // вывод
    proizvodnaya(elem1); // производная
    int operation;
    cout << "Выберите дальнейшее действие: \n" << "1) Добавить элемент в спи-сок\n" << "2) Удалить элемент из списка\n" << "3)Завершить работу програм-мы\n";
    cin >> operation; // выбираем дальнейшую операцию
    switch (operation) {
    case 1: // добавление
        cout << "Введите степень эелемента, который хотите добавить: ";
        int i;
        cin >> i;
        cout << "И коэффициент, который у него будет: ";
        cin >> a;
        addelem(p, a, i);
        cout << "Измененный многочлен: \n";
        listprint(elem1);
        proizvodnaya(elem1);
        break;
    case 2: // удаление
        cout << "Введите номер члена, который хотите удалить: ";
        int d;
        cin >> d;
        deletelem(elem1, d, n);
        listprint(elem1);
        break;
    case 3: // завершение работы программы
        break;
    }
    return 0;
}

#include <iostream> 
#include <algorithm>
using namespace std;

int n;	// общее кол-во элементов 
int val; // сам элемент - число
int choice; // пункт меню, выбранный пользователем

//структура дерева 
struct tree {
    int key; // содержание узла
    struct tree* left; // указатель на младшего потомка struct 
    tree* right; // указатель на старшего потомка 
    int h = 1; //высота
};

//проверка ввода
void is_digit(int& i) {
    do {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail()); cout << " -> ";
        cin >> i;
    } while (cin.fail());
}

//меню
void menu(int& choice) {
    cout << "МЕНЮ:\n";
    cout << "1) Добавить элемент\n";
    cout << "2) Удалить элемент\n";
    cout << "3) Поиск элемента\n";
    cout << "4) Вывод дерева\n";
    cout << "5) Вывести список элементов\n";
    cout << "6) Вывести максимальную глубину листа и уравнять листья дере-ва\n";
    cout << "7) Выход\n";
    do {
        is_digit(choice);
    } while (choice < 1 || choice>7);
}

//высота
unsigned char height(tree* R)
{
    return R ? R->h : 0;
}

//разность высот левого и правого поддеревьев 
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

//ввод
tree* push(tree*& R, int val) {
    if (R == NULL) {
        tree* root = new tree;
        root->key = val;
        root->right = NULL;
        root->left = NULL;
        R = root;
        return R;
    }
    if (val < R->key) push(R->left, val);
    else push(R->right, val);
    R = balance(R);
}

//поиск
tree* search(tree*& R, int val, int k) {
    if (val == R->key) {
        cout << "Кол-во шагов: " << k++ << endl;
        return R;
    }
    k++;
    if (val < R->key) {
        if (R->left == NULL) {
            tree* R = new tree();
            return NULL;
        }
        search(R->left, val, k);
    }
    else {
        if (R->right == NULL) {
            tree* R = new tree();
            return NULL;
        }
        search(R->right, val, k);
    }
}

//вывод дерева
void print_tree(tree* R, int l) {
    if (R != NULL) {
        print_tree(R->right, l + 1);
        for (int i = 1; i <= l; i++) cout << "	";
        cout << R->key << endl;
        print_tree(R->left, l + 1);
    }
}

tree* find_min(tree* R) {
    if (R->left == NULL) return R;
    else find_min(R->left);
}

tree* taskhelp(tree* R, int n) {
    if (R == NULL) return 0;
    taskhelp(R->left, n);
    if (R->left != NULL) {
        if (((R->h) - (R->left->h)) > 1) {
            if (((R->h) - (R->left->h)) > 1) R->left->h++;
        }
    }
    if (R->right != NULL) {
        if (((R->h) - (R->right->h)) > 1) {
            if (((R->h) - (R->right->h)) > 1) R->right->h++;
        }
    }
    taskhelp(R->right, n);
    return R;
}

tree* task(tree* r, tree* R, int n) {
    if (R == NULL) return 0;
    task(r, R->left, n);
    
    if (((R->left == NULL)) && (R->h > 1)) {
        tree* root = new tree;
        root->key = R->key - 1;
        root->right = NULL;
        root->left = NULL;
        root->h = R->h-1;
        R->left = root;
    }
    if (((R->right == NULL)) && (R->h > 1)) {
        tree* root1 = new tree;
        root1->key = R->key + 1;
        root1->right = NULL;
        root1->left = NULL;
        root1->h = R->h - 1;
        R->right = root1;
    }

    task(r, R->right, n);
    return R;
}

tree* remmin(tree* R) {
    if (R->left == NULL) return R->right;
    R->left = remmin(R->left);
    return balance(R);
}

tree* remove(tree* R, int val) {
    if (R == NULL) return 0;
    if (val < R->key)
        R->left = remove(R->left, val);
    else if (val > R->key)
        R->right = remove(R->right, val);
    else {
        tree* l = R->left; tree* r = R->right; delete R;
        if (r == NULL) return l; tree* min = find_min(r); min->right = rem-min(r); min->left = l;
        return balance(min);
    }
    return balance(R);
}

void print_arr(tree* R) {
    if (R == NULL) return;
    print_arr(R->left);
    cout << R->key << " ";
    print_arr(R->right);
}

int main() {
    setlocale(LC_ALL, "rus");
    tree* root = NULL; // ячейка для корня 
    while (1) {
        menu(choice);
        // добавить
        if (choice == 1) {
            cout << "Введите новый элемент:" << endl;
            is_digit(val);
            if (root != NULL) {
                if (search(root, val, 0) != NULL) cout << "Одинаковых элемен-тов не должно быть в нашем дереве!!!\n";
                else root = push(root, val);
            }
            else root = push(root, val);
        }
        // удалить
        else if (choice == 2) {
            cout << "Введите элемент, который хотите удалить:" << endl;
            is_digit(val);
            root = remove(root, val);
            if (root == NULL) {
                cout << "Удалено всё дерево\n";
                break;
            }
        }
        // поиск
        else if (choice == 3) {
            cout << "Введите элемент, который надо найти:" << endl;
            is_digit(val);
            if (search(root, val, 0) != NULL) cout << "Элемент найден\n";
            else cout << "Элемент не найден\n";
        }
        // вывод дерева
        else if (choice == 4) {
            print_tree(root, 0);
        }
        // вывод списка
        else if (choice == 5) {
            cout << "Список, соответствующий симметричному обходу:\n";
            print_arr(root);
            cout << endl;
        }
        // вывод потомков
        else if (choice == 6) {
            int n = height(root);
            cout << "Максимальная глубина листа: " << n << "\n";
            cout << "Производится уравнивание всех листов дерева.\n";
            tree* r = root;
            for (int i = 0; i < n; i++) {
                taskhelp(root, n);
                task(r, root, n);
            }
            print_tree(root, 0);
        }
        else if (choice == 7) break;
        system("pause");
        system("cls");
    }
    system("pause");
    return 0;
}

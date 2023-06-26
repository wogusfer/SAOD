#include <iostream>
using namespace std;

void zadanie(int* arr, int n) {
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i] == arr[j])
			{
				count++;
			}
		}
		if (count > 1) {
			cout << endl;
			cout << "Элемент " << arr[i] << " встречается в массиве: " << count;
			i = i + count - 1;
		}
		count = 0;
	}
	cout << "\n";
}

void countingSort(int* arr, int n,int m) {
	cout << "Полученный массив: ";
	for (int i = 0; i < n; i++) cout << arr[i] << "  ";
	cout << "\n";

	int srav = 0;
	int per = 0;
	int k = 0;
	int* b = new int[n];
	for (int i = 0; i < n; i++) {
		k = 0;
		for (int j = 0; j < n; j++) {
			srav++;
			if ((arr[j] < arr[i]) || ((arr[j] == arr[i]) && (j < i))) k++;
		}
		b[k] = arr[i];
	}
	cout << "Преобразованный массив: ";
	for (int i = 0; i < n; i++) { 
		if (arr[i] != b[i]) per++;
		arr[i] = b[i]; 
		cout << arr[i] << "  "; 
	}
	cout << "\n";
	cout << "Количество сравнений: " << srav << endl;
	cout << "Количество перестановок: " << per << endl;
}

void find(int* arr, int n) {
	cout << "Как вы хотите искать элемент (1.по порядковой позиции / 2.по содержимому): ";
	int v, x, p=0;
	cin >> v;
	switch (v) {
	case 1:
		cout << "Введите порядковый номер элемента: ";
		cin >> x;
		if ((x < 0) || (x > n)) cout << "В массиве " << n << " элемен-тов!\n";
		else cout << "Результат поиска: " << arr[x] << endl;
		break;
	case 2:
		cout << "Введите содержимое элемента: ";
		cin >> x;
		for (int i = 0; i < n; i++) {
			if (arr[i] == x) {
				cout << "Результат поиска: " << i << " элемент\n";
				p = 1;
			}
		}
		if (p == 0) cout << "Элементов с таким значением нет в масси-ве!\n";
		break;
	}
}

void add(int* &arr, int &n, int value,int m) {
	cout << "Превышен размер массива\n";
	cout << "Увеличиваем размер массива\n";

	int* newArray = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		newArray[i] = arr[i];
	}

	newArray[n] = value;
	n++;

	delete[] arr;
	arr = newArray;
	countingSort(arr, n,m);
}

void del(int* &arr, int &n, int value,int m) {
	if ((value < 0) || (value > n)) cout << "В массиве " << n << " элементов!\n";
	else { 
		int* newArray = new int[n - 1];
		for (int j = 0; j < n - 1; j++)
		{
			newArray[j] = arr[j];
		}
		for (int i = value; i < n - 1; i++)
		{
			newArray[i] = arr[i + 1];
		}
		n--;
		delete[] arr;
		arr = newArray;
		cout << "Элемент удален" << endl; 
		countingSort(arr, n,m);
	}
}

int main()
{
    setlocale(LC_ALL, "rus");
	int n = 10;
	int c=0;
	int m = 0;
	cout << "Введите максимальное значение для числа массива:";
	cin >> m;

    int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		cout << "Введите значение " << i << " элемента массива: ";
		cin >> arr[i];
	}
	countingSort(arr, n,m);

	while (c != 5) {
		cout << "///// Меню /////\n";
		cout << "1) Поиск элемента\n";
		cout << "2) Добавление элемента\n";
		cout << "3) Удаление элемента\n";
		cout << "4) Подсчёт повторяющихся чисел\n";
		cout << "5) Выход\n";
		cin >> c;
		switch (c)
		{
		case 1:
		    find(arr, n);
		    break;
		case 2:
			int x;
			cout << "Введите значение " << (n + 1) << " элемента масси-ва: ";
			cin >> x;
		    add(arr, n, x,m);
		    break;
		case 3:
			cout << "Введите порядковый номер элемента, который хотите удалить: ";
			cin >> x;
		    del(arr, n, x,m);
		    break;
		case 4:
			zadanie(arr, n);
		case 5:
			break;
		default:
			break;
		}
	}
    return 0;
}

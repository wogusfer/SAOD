#include <iostream>
using namespace std;  

const int Vmax = 20;//максимум количество вершин
const int Emax = 60;//максимум количество ребер

int terminal[Emax]; // массив вершин, в которые входят ребра
int point[Emax];//хранит для i-ой вершины номер k-ого элемента массивов terminal, где terminal[k] – следующая вершина смежная с i-ой
int head[Vmax]; //хранит для i-ой вершины номер k-ого элемента массива terminal, где terminal[k] – первая вершина смежная с i-ой
int last[Vmax]; //хранит для i-ой вершины номер k-ого элемента массивов terminal, где terminal[k] – последняя вершина смежная с i-ой

int n = 6; //Количество вершин
int m;//Количество ребер
int v; // первая смежная вершина
int u; // вторая смежная вершина
int k = 0;// номер элемента
int i, j;

void Add(int v, int u) //добавление ребра
{
	k = k + 1;
	terminal[k] = u;
	//если вершина v новая, то
	//первая смежная ей вершина имеет номер k
	if (head[v] == 0) head[v] = k;
	//если вершина v уже просматривалась, то
	//следующая смежная с ней вершина имеет номер k
	if (last[v] != 0) point[last[v]] = k;
	last[v] = k;
}

void print() {
	cout << "Список ребер графа:\n";
	for (i = 0; i < m; i++)//вывод списка ребер
	{
		k = head[i];
		while (k > 0)
		{
			cout << i << "->" << terminal[k] << endl;
			k = point[k];
		}
	}
}

void top_coat() {
	i = 1;
	cout << "Минимальное вершинное покрытие: " << i;
	while (i < m) {
		k = head[i];
		while (point[k]) k = point[k];
		cout << terminal[k];
		i = terminal[k] + 1;
	}
	cout << "\n";
}

void ribbing() {
	cout << "Минимальное реберное покрытие: ";
	i = 1;
	while (i < m) {
		k = head[i];
		while (terminal[k] < i) k = point[k];
		if (terminal[k] == i + 1) {
			cout << i << "->" << terminal[k] << " ";
			i = i + 2;
		}
		else {
			cout << i << "->" << terminal[k] << " ";
			if (i == 4) break;
			i++;
		}
	}
	cout << endl;
}

int main()
{
    setlocale(LC_ALL, "rus");
	cout << "Количество вершин " << n << endl; //заполнение графа
	cout << "Количество ребер >> "; cin >> m;
	cout << "Вводите ребра(v, u):\n";
	for (i = 0; i < m; i++)
	{
		cin >> v >> u;
		Add(v, u);
		Add(u, v);
		cout << "..." << endl;
	}
	print();
	top_coat();
	ribbing();
    return 0;
}

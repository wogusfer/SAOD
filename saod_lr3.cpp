#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;

class Task                                                                                                 
{
private:
	string name;
	int prior;
	int tact;
	int dur;
public:
	void setn(string n) { name = n; }
	void setpr(int p) { prior = p; }
	void sett(int t) { tact = t; }
	void setd(int d) { dur = d; }
	string getn() { return name; }
	int getpr() { return prior; }
	int gett() { return tact; }
	int  getd() { return dur; }
	Task()
	{
		name = "0";
		dur = 0;
		tact = 0;
		prior = 0;
	}
	Task(string n, int p, int t, int d)
	{
		name = n;
		dur = d;
		tact = t;
		prior = p;
	}
};

class Generator {                                                                                              
public:
	Task* generate(int time)
	{
		int prior; // приоритет
		int taсt = time; // время поступления 
		int dur; // время выполнения

		string name = "Задача # " + to_string(time);
		cout << name << "\n";
		cout << "Введите тип задачи [0-2]: ";
		cin >> prior;
		while (cin.fail() || prior < 0 || prior > 2) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '/n');
			cout << "Неверно!\n";
			cout << "Введите приоритет задачи [0-2]: ";
			cin >> prior;
		}
		cout << "Введите продолжительность задачи: ";
		cin >> dur;
		while (cin.fail() || dur < 1) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '/n');
			cout << "Неверно!\n";
			cout << "Введите продолжительность задачи: ";
			cin >> dur;
		}
		Task* task = new Task(name, prior, taсt, dur);
		cout << "\n";
		return task;
	}

	Task* autoGenerate(int timer) {
		srand(time(NULL));
		int prior; 
		int taсt = timer;  
		int dur; 
		string name = "Задача # " + to_string(timer);
		prior = rand() % 3;
		dur = 1 + rand() % 5;
		cout << name << "\n";
		cout << "Тип задачи " << prior << "\n";
		cout << "Продолжительность задачи " << dur << "\n";
		cout << "Время поступления задачи " << taсt << "\n";
		Task* task = new Task(name, prior, taсt, dur);
		cout << "\n";
		return task;
	}
};

class Queue                                                                                                   
{
private:
	class Node
	{
	public:
		Task data;
		Node* next;

		Node(Task t = Task(), Node* n = nullptr)
		{
			data = t;
			next = n;
		}
	};
public:
	Node* head;
	int size;
public:
	Queue()
	{
		size = 0;
		head = nullptr;
	}
	~Queue() { clear(); }
	void addf(Task value)
	{
		if (head == nullptr)
			head = new Node(value);
		else
		{
			for (Node* current = head; ; current = current->next)
				if (current->next == nullptr)
				{
					current->next = new Node(value);
					break;
				}
		}
		size++;
	}
	int getsizef() const { return size; }
	Task& operator[] (int index)
	{
		if (index > size - 1 || index < 0)
		{
			string message = "Недопустимый индекс ";
			message.append(to_string(index));
			throw out_of_range(message);
		}
		Node* current = head;
		for (int i = 0; i < index; i++)
			current = current->next;
		return current->data;
	}
	void deletef()
	{
		if (size <= 0) return;
		Node* temp = head;
		head = head->next;
		delete temp;
		size--;
	}
	void clear() { while (size) deletef(); }
};

class Stack
{                                                                                                       
private:
	class Node {
	public:
		Node* pNext;
		Task data;

		Node(Task data = Task(), Node* pNext = nullptr) {	
			this->data = data;
			this->pNext = pNext;
		}
	};
public:
	int Size;
	Node* head;
public:
	Stack() {                       
		Size = 0;
		head = nullptr;
	}
	~Stack() { clear(); }				
	void clear() {
		while (Size) {
			deletes();
		}
	}
	void deletes() {   
		Node* temp = head;
		head = head->pNext;
		delete temp;
		Size--;
	}
	void adds(Task data) { 
		head = new Node(data, head);
		Size++;
	};
	int getsizes() { return Size; }
	Task& operator[](const int index) {
		int counter = 0;
		Node* current = this->head;
		while (current != nullptr) {
			if (counter == index) {
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
		//Size++;
	}
};

class Processor                                                                                                   
{
private:
	int duration = 0;
	int timer = 0;
	bool work = false;
	Task task_processor;
public:
	int getpr() { return task_processor.getpr(); }
	Task gettaskproc() { return task_processor; }
	void gettask(Task* T, int time)
	{
		task_processor.setd(T->getd());
		task_processor.setpr(T->getpr());
		task_processor.setn(T->getn());
		task_processor.sett(T->gett());

		duration = task_processor.getd();
		timer = time;
		work = true;
	}
	bool workp()
	{
		if ((task_processor.getn() != "0") || (task_processor.getpr() != 0))
		{
			duration--;
		}
		if (duration == 0)
		{
			work = false;
			task_processor.setd(0);
			task_processor.setpr(0);
			task_processor.setn("0");
			task_processor.sett(0);
		}
		else {
			work = true;
		}
		return work;
	}
	bool procisempty() { return work; }
	void printp()
	{
		cout << "\n";
		if (task_processor.getn() != "0")
		{
			cout << "Имя задачи:" << task_processor.getn() << "\n";
			cout << "Тип:" << task_processor.getpr() << "\n";
			cout << "Время поступления:" << task_processor.gett() << "\n";
			cout << "Длительность выполнения:" << task_processor.getd() << "\n";
			cout << "\n";
		}
		else { cout << "Пусто" << "\n"; cout << "\n"; }
	}
};


int main()
{
	setlocale(LC_ALL, "Russian"); 

	Stack S; 
	Queue F;
	Processor P0, P1, P2;
	Generator TG;
	int timer = 1;
	int choice = 0;

	Task temp1;
	Task* temp = &temp1;

	while (choice != 4) {
		cout << "///////////////Такт №" << timer << "///////////////\n";
		cout << "1) Ручной ввод задачи\n" << "2) Машинный ввод задачи\n" << "3) Пропуск такта\n" << "4) Выход из программы\n";
		cin >> choice;
		cout << "\n";
		switch (choice)
		{
		case 1: case 2:
			if (choice == 1) { temp = TG.generate(timer); }
			else if (choice == 2) { temp = TG.autoGenerate(timer); }

			F.addf(*temp);

			if ((S[0].getpr() == 0) && (P0.procisempty() == 0)) {
				P0.gettask(&S.head->data, timer);
				S.deletes();
			}
			if ((*temp).getpr() == 0) {
				if (P0.procisempty() == 0) {
						P0.gettask(temp, timer);
						F.deletef();
				}
				else if (P0.procisempty() != 0) { S.adds(*temp); F.deletef(); }
			}

			if ((S[0].getpr() == 1) && (P1.procisempty() == 0)) {
				P1.gettask(&S.head->data, timer);
				S.deletes();
			}
			if ((*temp).getpr() == 1) {
				if (P1.procisempty() == 0) {
					P1.gettask(temp, timer);
					F.deletef();
				}
				else if (P1.procisempty() != 0) { S.adds(*temp); F.deletef(); }
			}

			if ((S[0].getpr() == 2) && (P2.procisempty() == 0)) {
				P2.gettask(&S.head->data, timer);
				S.deletes();
			}
			if ((*temp).getpr() == 2) {
				if (P2.procisempty() == 0) {
					P2.gettask(temp, timer);
					F.deletef();
				}
				else if (P2.procisempty() != 0) { S.adds(*temp); F.deletef(); }
			}

			cout << "/////Содержимое процессора P0/////\n";
			P0.printp();
			cout << "/////Содержимое процессора P1/////\n";
			P1.printp();
			cout << "/////Содержимое процессора P2/////\n";
			P2.printp();
			cout << "/////Содержимое стека/////\n";
			if (S.getsizes() == 0) {
				cout << "Пусто\n";
				cout << "\n";
			}
			else {
				for (int i = 0; i < S.getsizes(); i++) {
					cout << "Имя задачи:" << S[i].getn() << "\n";
					cout << "Тип:" << S[i].getpr() << "\n";
					cout << "Время поступления:" << S[i].gett() << "\n";
					cout << "Длительность выполнения:" << S[i].getd() << "\n";
					cout << "\n";
				}
			}
			cout << "/////Содержимое очереди/////\n";
			if (F.getsizef() == 0) {
				cout << "Пусто\n";
				cout << "\n";
			}
			for (int i = 0; i < F.getsizef(); i++)
			{
				cout << "Имя задачи:" << F[i].getn() << "\n";
				cout << "Тип:" << F[i].getpr() << "\n";
				cout << "Время поступления:" << F[i].gett() << "\n";
				cout << "Длительность выполнения:" << F[i].getd() << "\n";
				cout << "\n";
			}
		case 3:
		case 4: break;
		default: break;
		}
		P0.workp();
		P1.workp();
		P2.workp();
		timer++;
	}
	return 0;
}

// Autor: Magda Szafranska, nr indeksu AHNS: 18345
// Informatyka NST, rok 2, sem. 3
// Algorytmy, laboratoria nr 3 - part I (one-way list)

#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

class TItem
{
public: int FData;
	  TItem* FNext;

public:
	TItem(TItem* ANext, int AData)
	{
		FData = AData;
		FNext = ANext;
	}
	~TItem()
	{
	}
};

class TList
{
private:
	TItem* FFirst;

public:
	TList(void);
	~TList(void);

	int Pop(void);
	void Push(int AData);
	bool IsExist(int AData);
};

TList::TList(void)
{
	FFirst = NULL;
}
TList::~TList(void)
{
	while (FFirst) Pop();
}
void TList::Push(int AData)
{
	FFirst = new TItem(FFirst, AData);
}
int TList::Pop(void)
{
	int AData = FFirst->FData;
	TItem* AItem = FFirst;
	FFirst = FFirst->FNext;
	delete AItem;
	return AData;
}
bool TList::IsExist(int AData)
{
	TItem* Item = FFirst;
	while (Item)
		if (Item->FData == AData) return true;
		else Item = Item = Item->FNext;
	return false;
}

int main()
{
	TList list;
	list.Push(1);
	list.Push(2);
	list.Push(5);

	int x1 = list.Pop();
	int x2 = list.Pop();
	int x3 = list.Pop();

	// writing to the text file
	fstream fTime, fCount;
	fTime.open("time.txt", ios::out | ios::app);
	fCount.open("count.txt", ios::out | ios::app);

	cout << "x1 = " << x1 << endl;
	cout << "x2 = " << x2 << endl;
	cout << "x3 = " << x3 << endl << endl;

	int T1, T2;

	for (int i = 10000; i <= 50000; i += 1500)
	{
		int Count = 10000;
		fCount << i << endl;

		T1 = (int)GetTickCount64();
		while (--Count)
		{
			int Value = rand();
			if (!list.IsExist(Value))
				list.Push(Value);
		}
		T2 = (int)GetTickCount64();

		cout << "Count: " << i << "\tTime = " << (T2 - T1) * 0.001 << " second(s)." << endl;
		fTime << (T2 - T1) * 0.001 << endl;
	}

	fTime.close();
	fCount.close();
}
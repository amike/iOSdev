// OpenHash.cpp : Defines the entry point for the console application.
//Программная реализация: "Открытое хеширование"
//Дата разработки: 17_12_2012
//	Используемая литература: 
//		1.Лекции по дисциплине "Методы программирования"

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

typedef int T;  // тип элементов
typedef int hashTableIndex; // индекс в хеш-таблице
#define compEQ(a,b) (a == b) //называем по своему операцию проверки равенства 
typedef struct Node_ {
       T data;// данные, хранящиеся в вершине типа int
       struct Node_ *next; // указатель на следующую вершину
} Node;

Node **hashTable; //объявляем указатель на массив указателей, каждый из которых будет указывать на начало списка
int hashTableSize; //размер хеш-таблицы
hashTableIndex myhash(T data);//объявляем функцию преобразования ключа с помощью хэш-функции деления h(k):=k_mod_m в индекс хеш-таблицы
Node *insertNode(T data);//функция вставки нового элемента
void deleteNode(T data);//функция удаления элемента
Node *findNode (T data);//функция нахождения элемента 

int _tmain(int argc, _TCHAR* argv[]){
  int i, *a, maxnum;
  cout << "Введите количество элементов maxnum : ";//размер основного массива
  cin >> maxnum;
  cout << "Введите размер хеш-таблицы HashTableSize : ";
  cin >> hashTableSize;
  a = new int[maxnum];//создаем основной массив
  hashTable = new Node*[hashTableSize];//создаем хэш-таблицу (говоря проще: массив указателей размера хэш-таблицы)
  for (i = 0; i < hashTableSize; i++)
    hashTable[i] = NULL;//обнуляем всю хэш-таблицу
  // генерация массива
  for (i = 0; i < maxnum; i++)
    a[i] = rand();
  // заполнение хеш-таблицы элементами массива
  for (i = 0; i < maxnum; i++) {
    insertNode(a[i]);
  }
  // поиск элементов массива по хеш-таблице
  for (i = maxnum-1; i >= 0; i--) {
    findNode(a[i]);
  }
  // вывод элементов массива в файл List.txt
  ofstream out("D:\OpenList.txt");
  for (i = 0; i < maxnum; i++){
    out << a[i];
    if ( i < maxnum - 1 ) out << "\t";
  }
  out.close();
  // сохранение хеш-таблицы в файл HashTable.txt
  out.open("D:\OpenHashTable.txt");
  for (i = 0; i < hashTableSize; i++){
    out << i << "  :  "; 
    Node *Temp = hashTable[i];//указатель на i-й элемент хеш-таблицы, в котором данные и указатель на следующий элемент списка
    while ( Temp ){
      out << Temp->data << " -> ";//выводим значение данных в текущем элементе списка с помощью указателя ->
      Temp = Temp->next;//переключаемся на следующий элемент
    }
    out << endl;
  }
  out.close();
  // очистка хеш-таблицы
    for (i = maxnum-1; i >= 0; i--) {
        deleteNode(a[i]);
    }
  system("pause");
  return 0;
}

// хеш-функция размещения вершины
hashTableIndex myhash(T data) {
  return (data % hashTableSize);
}

// функция поиска местоположения и вставки вершины в таблицу
Node *insertNode(T data) {
  Node *p, *p0;
  hashTableIndex bucket;
  // вставка вершины в начало списка
  bucket = myhash(data);//хешируем ключ
  if ((p = new Node) == 0) {
    fprintf (stderr, "Нехватка памяти (insertNode)\n");
    exit(1);
  }
  p0 = hashTable[bucket];//присваеваем p0 прохешированный ключ, т.е. индекс в хеш-таблице
  hashTable[bucket] = p;//вставляем элемент в начало списка
  p->next = p0;
  p->data = data;
  return p;
}

//функция удаления вершины из таблицы
void deleteNode(T data) {
  Node *p0, *p;
  hashTableIndex bucket;
  p0 = 0;
  bucket = myhash(data);//хешируем ключ
  p = hashTable[bucket];
  while (p && !compEQ(p->data, data)) {//перелистываем все элементы списка в поисках нужного
    p0 = p;
    p = p->next;
  }
  if (!p) return;
  if (p0)
    p0->next = p->next;
  else
    hashTable[bucket] = p->next;
  free (p);
}

// функция поиска вершины со значением data
Node *findNode (T data) {
  Node *p;
  p = hashTable[myhash(data)];//присваиваем p прохешированный ключ
  while (p && !compEQ(p->data, data)) //перелистываем элементы списка, пока не найдем нужный, и когда нашли, возвращаем его
    p = p->next;
  return p;
}
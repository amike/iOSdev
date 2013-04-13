// OpenHash.cpp : Defines the entry point for the console application.
//����������� ����������: "�������� �����������"
//���� ����������: 17_12_2012
//	������������ ����������: 
//		1.������ �� ���������� "������ ����������������"

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

typedef int T;  // ��� ���������
typedef int hashTableIndex; // ������ � ���-�������
#define compEQ(a,b) (a == b) //�������� �� ������ �������� �������� ��������� 
typedef struct Node_ {
       T data;// ������, ���������� � ������� ���� int
       struct Node_ *next; // ��������� �� ��������� �������
} Node;

Node **hashTable; //��������� ��������� �� ������ ����������, ������ �� ������� ����� ��������� �� ������ ������
int hashTableSize; //������ ���-�������
hashTableIndex myhash(T data);//��������� ������� �������������� ����� � ������� ���-������� ������� h(k):=k_mod_m � ������ ���-�������
Node *insertNode(T data);//������� ������� ������ ��������
void deleteNode(T data);//������� �������� ��������
Node *findNode (T data);//������� ���������� �������� 

int _tmain(int argc, _TCHAR* argv[]){
  int i, *a, maxnum;
  cout << "������� ���������� ��������� maxnum : ";//������ ��������� �������
  cin >> maxnum;
  cout << "������� ������ ���-������� HashTableSize : ";
  cin >> hashTableSize;
  a = new int[maxnum];//������� �������� ������
  hashTable = new Node*[hashTableSize];//������� ���-������� (������ �����: ������ ���������� ������� ���-�������)
  for (i = 0; i < hashTableSize; i++)
    hashTable[i] = NULL;//�������� ��� ���-�������
  // ��������� �������
  for (i = 0; i < maxnum; i++)
    a[i] = rand();
  // ���������� ���-������� ���������� �������
  for (i = 0; i < maxnum; i++) {
    insertNode(a[i]);
  }
  // ����� ��������� ������� �� ���-�������
  for (i = maxnum-1; i >= 0; i--) {
    findNode(a[i]);
  }
  // ����� ��������� ������� � ���� List.txt
  ofstream out("D:\OpenList.txt");
  for (i = 0; i < maxnum; i++){
    out << a[i];
    if ( i < maxnum - 1 ) out << "\t";
  }
  out.close();
  // ���������� ���-������� � ���� HashTable.txt
  out.open("D:\OpenHashTable.txt");
  for (i = 0; i < hashTableSize; i++){
    out << i << "  :  "; 
    Node *Temp = hashTable[i];//��������� �� i-� ������� ���-�������, � ������� ������ � ��������� �� ��������� ������� ������
    while ( Temp ){
      out << Temp->data << " -> ";//������� �������� ������ � ������� �������� ������ � ������� ��������� ->
      Temp = Temp->next;//������������� �� ��������� �������
    }
    out << endl;
  }
  out.close();
  // ������� ���-�������
    for (i = maxnum-1; i >= 0; i--) {
        deleteNode(a[i]);
    }
  system("pause");
  return 0;
}

// ���-������� ���������� �������
hashTableIndex myhash(T data) {
  return (data % hashTableSize);
}

// ������� ������ �������������� � ������� ������� � �������
Node *insertNode(T data) {
  Node *p, *p0;
  hashTableIndex bucket;
  // ������� ������� � ������ ������
  bucket = myhash(data);//�������� ����
  if ((p = new Node) == 0) {
    fprintf (stderr, "�������� ������ (insertNode)\n");
    exit(1);
  }
  p0 = hashTable[bucket];//����������� p0 ��������������� ����, �.�. ������ � ���-�������
  hashTable[bucket] = p;//��������� ������� � ������ ������
  p->next = p0;
  p->data = data;
  return p;
}

//������� �������� ������� �� �������
void deleteNode(T data) {
  Node *p0, *p;
  hashTableIndex bucket;
  p0 = 0;
  bucket = myhash(data);//�������� ����
  p = hashTable[bucket];
  while (p && !compEQ(p->data, data)) {//������������� ��� �������� ������ � ������� �������
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

// ������� ������ ������� �� ��������� data
Node *findNode (T data) {
  Node *p;
  p = hashTable[myhash(data)];//����������� p ��������������� ����
  while (p && !compEQ(p->data, data)) //������������� �������� ������, ���� �� ������ ������, � ����� �����, ���������� ���
    p = p->next;
  return p;
}
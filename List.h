#pragma once
#include "Node.h"
template <typename T>
class List
{
public:
	List();
	~List();
	void insertFront(T data);
	void insertBack(T data);
	void removeBack();
	void remove(T data);
	Node<T>* getHead();
	Node<T>* getTail();
	Node<T>* find(T data);
	bool empty();
	void clear();
	int amount();

private:
	Node<T>* head;
	Node<T>* tail;
};

template <typename T>
List<T>::List() {
	head = nullptr;
	tail = nullptr;
}

template <typename T>
List<T>::~List() {
	clear();
}

template <typename T>
void List<T>::clear() {
	Node<T>* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
}



template<typename T>
void List<T>::insertFront(T data) {
	Node<T>* newNode = new Node<T>(data);
	if (head) head->prev = newNode;
	else tail = newNode;
	newNode->next = head;
	head = newNode;
}

template<typename T>
void List<T>::insertBack(T data) {
	Node<T>* newNode = new Node<T>(data);
	if (tail) tail->next = newNode;
	else head = newNode;
	newNode->prev = tail;
	tail = newNode;
}

template<typename T>
void List<T>::removeBack() {
	if (!head) return;
	else if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node<T>* temp = tail;
		tail->prev->next = nullptr;
		tail = tail->prev;
		delete temp;
	}
}

template<typename T>
Node<T>* List<T>::find(T data) {
	Node<T>* temp = head;
	while (temp)
	{
		if (temp->data == data) return temp;
		temp = temp->next;
	}
	return nullptr;
}

template<typename T>
void List<T>::remove(T data) {
	Node<T>* toRemove = find(data);
	if (!toRemove) return;
	if (toRemove == head && toRemove == tail) head = tail = nullptr;

	if (toRemove->prev) toRemove->prev->next = toRemove->next;
	if (toRemove->next) toRemove->next->prev = toRemove->prev;
	if (toRemove == tail) tail = tail->prev;
	if (toRemove == head) head = head->next;
	delete toRemove;
}

template<typename T>
bool List<T>::empty() {
	if (head == nullptr) return true;
	return false;
}

template<typename T>
Node<T>* List<T>::getHead() {
	return head;
}

template<typename T>
Node<T>* List<T>::getTail() {
	return tail;
}
template<typename T>
int List<T>::amount() {
	int wynik = 0;
	Node<T>* temp = head;
	while (temp)
	{	
		wynik++;
		temp = temp->next;
	}
	return wynik;
}
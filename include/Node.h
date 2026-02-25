#pragma once
template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node<T>* prev;
	Node(T data);
	~Node();
};

template<typename T>
Node<T>::Node(T data)
{
	this->data = data;
	next = nullptr;
	prev = nullptr;
}

template<typename T>
Node<T>::~Node() {}
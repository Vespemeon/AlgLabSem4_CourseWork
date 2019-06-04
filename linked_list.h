#pragma once

#include <cstddef>
#include <iostream>

using namespace std;

template <class T>
struct Node {
	T data;
	Node *next = nullptr;
};
template<class T>
class List {
private:
	Node<T> * head;
	Node<T> *tail;
	template <class T> friend ostream& operator << (ostream &s, const List <T> &list);
public:
	List(Node<T> *head = nullptr, Node<T> *tail = nullptr);
	~List();
	void push_back(T);
	void push_front(T);
	void pop_back();
	void pop_front();
	void insert(size_t, T);
	T at(size_t);
	void remove(size_t);
	size_t get_size();
	void print_to_console();
	void clear();
	void set(size_t, T);
	bool isEmpty();
	bool isThere(T val);
};
template<class T>
void List<T>::push_back(T val) {
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	if (head == nullptr) {
		head = tail = newNode;
	}
	else {
		newNode->next = nullptr;
		tail->next = newNode;
		tail = newNode;
	}
}
template<class T>
void List<T>::push_front(T val) {
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	if (head == nullptr) {
		head = tail = newNode;
	}
	else {

		newNode->next = head;
		head = newNode;
	}
}
template<class T>
void List<T>::pop_back() {
	if ((head == tail) && (head != nullptr)) {
		delete head;
		head = tail = nullptr;
	}
	else if (tail != nullptr) {
		Node<T> *deleting = tail;
		Node<T> *temp = head;
		while (temp->next != tail)
		{
			temp = temp->next;
		}
		tail = temp;
		tail->next = nullptr;
		delete deleting;
	}
	else
		throw(std::out_of_range("List::pop_back out of range"));
}
template<class T>
void List<T>::pop_front() {
	if ((head == tail) && (head != nullptr)) {
		delete head;
		head = tail = nullptr;
	}
	else if (head != nullptr) {
		Node<T> *deleting = head;
		head = head->next;
		delete deleting;
	}
	else
		throw(std::out_of_range("List::pop_front - empty list"));
}
template<class T>
void List<T>::insert(size_t index, T val) {
	size_t i = 0;
	Node<T> *temp = head;
	Node<T> *temppr = head;
	bool flag = false;
	while (temp != nullptr && i != index) {
		temp = temp->next;
		if (flag) temppr = temppr->next;
		i++;
		flag = true;
	}
	if (i < index) {
		temp = nullptr;
		temppr = nullptr;
		delete temp;
		delete temppr;
		throw(std::out_of_range("List::insert out of range"));
	}
	Node<T> *newNode = new Node<T>;
	newNode->data = val;
	if (temp != nullptr) {
		if (temp != head) {
			temppr->next = newNode;
		}
		else {
			head = newNode;
		}
		newNode->next = temp;
	}
	else if ((head == nullptr) && (index == 0)) {
		head = tail = newNode;
	}
	else if (i == index) {
		tail->next = newNode;
		tail = newNode;
	}
}
template<class T>
T List<T>::at(size_t index) {
	size_t i = 0;
	Node<T> *temp = head;
	while (temp != nullptr && i != index) {
		temp = temp->next;
		i++;
	}
	if (temp != nullptr) {
		return temp->data;
	}
	throw(std::out_of_range("List::at out of range"));
}
template <class T>
void List<T>::remove(size_t index) {
	size_t i = 0;
	Node<T> *temp = head;
	Node<T> *temppr = head;
	bool flag = false;
	while (temp != nullptr && i != index) {
		temp = temp->next;
		if (flag) temppr = temppr->next;
		i++;
		flag = true;
	}
	if ((i < index) || (temp == nullptr)) {
		temp = nullptr;
		temppr = nullptr;
		delete temp;
		delete temppr;
		throw(std::out_of_range("List::remove out of range"));
	}
	if (temp != nullptr) {
		if (temp == head && temp->next != nullptr) {
			head = temp->next;
			delete temp;
		}
		else if (temp != head && temp->next == nullptr) {
			tail = temppr;
			tail->next = nullptr;
			delete temp;
		}
		else if (temp == head && temp->next == nullptr) {
			delete temp;
			head = tail = nullptr;
		}
		else if (temp != head && temp->next != nullptr) {
			temppr->next = temp->next;
			delete temp;
		}
	}
}
template<class T>
size_t List<T>::get_size() {
	size_t i = 0;
	Node<T> *temp = head;
	while (temp != nullptr) {
		temp = temp->next;
		i++;
	}

	return i;
}
template<class T>
void List<T>::print_to_console() {
	Node<T> *temp = head;
	while (temp != nullptr) {
		std::cout << temp->data;
		temp = temp->next;
	}
	std::cout << std::endl;
}
template<class T>
void List<T>::clear() {
	while (head != nullptr) {
		pop_back();
	}
}
template<class T>
void List<T>::set(size_t index, T val) {
	size_t i = 0;
	Node<T> *temp = head;
	while (temp != nullptr && i != index) {
		temp = temp->next;
		i++;
	}
	if (temp != nullptr) {
		temp->data = val;
	}
	else {
		throw(std::out_of_range("List::set out of range"));
		temp = nullptr;
		delete temp;
	}
}
template<class T>
bool List<T>::isEmpty() {
	return head == nullptr;
}
template<class T>
bool List<T>::isThere(T val) {
	Node<T> *temp = head;
	while (temp != nullptr) {
		if (temp->data == val)
			return true;
		temp = temp->next;
	}
	return false;
}
template<class T>
List<T>::List(Node<T> * head, Node<T> * tail)
{
	this->head = head;
	this->tail = tail;
}
template<class T>
List<T>::~List() { 
	clear();
}

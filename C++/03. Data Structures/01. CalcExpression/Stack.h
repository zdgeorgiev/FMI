/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Zdravko Ivailov Georgiev
* @idnumber 45115
* @task 1
* @compiler VC
*
*/
#pragma once

#ifndef __STACK_HEADER_INCLUDED__
#define __STACK_HEADER_INCLUDED__

template<typename T>
class Stack {

private:

	struct node {

	public:
		T data;
		node* next;

		node(T data, node* next = nullprt) {
			this->data = data;
			this->next = next;
		};
	};

	node* head;
	int size;

public:

	Stack();

	void push(const T& data);
	T peek() const;
	void pop();
	bool isEmpty() const;
};

template<typename T>
Stack<T>::Stack() : head(nullptr), size(0) {

}

template<typename T>
bool Stack<T>::isEmpty() const {
	return this->size == 0;
}

template<typename T>
void Stack<T>::pop() {
	node* phead = this->head;
	this->head = this->head->next;
	delete phead;
	this->size--;
}

template<typename T>
T Stack<T>::peek() const {
	return this->head->data;
}

template<typename T>
void Stack<T>::push(const T& data) {
	node* newNode = new node(data, this->head);
	this->head = newNode;
	this->size++;
}

#endif
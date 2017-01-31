#pragma once

#ifndef __QUEUE_HEADER_INCLUDED__
#define __QUEUE_HEADER_INCLUDED__

template<typename T>
class Queue {

private:

	struct Node
	{
		T data;
		Node* pNext;

		Node(T data, Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};

	Node* pHead;
	Node* pTail;
	int size;

public:

	Queue() {
		this->pHead = nullptr;
		this->pTail = nullptr;
		this->size = 0;
	}

	bool isEmpty() const;

	int getSize() const;

	const T peek() const;

	void enqueue(const T data);

	void dequeue();
};

template<typename T>
bool Queue<T>::isEmpty() const {
	return this->size == 0;
}

template<typename T>
int Queue<T>::getSize() const {
	return this->size;
}

template<typename T>
const T Queue<T>::peek() const {
	return pHead->data;
}

template<typename T>
void Queue<T>::enqueue(const T data) {

	Node* nextNode = new Node(data, nullptr);

	if (!pHead) {
		pHead = nextNode;
		pTail = pHead;
		nextNode->pNext = nullptr;
	}
	else {
		nextNode->pNext = pTail->pNext;
		pTail->pNext = nextNode;
		pTail = nextNode;
	}

	this->size++;
}

template<typename T>
void Queue<T>::dequeue() {
	Node* headTmp = this->pHead;
	this->pHead = this->pHead->pNext;
	delete headTmp;
	this->size--;
}

#endif
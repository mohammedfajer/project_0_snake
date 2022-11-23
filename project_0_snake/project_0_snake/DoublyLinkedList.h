#pragma once
#include "Node.h"
#include <iostream>


template <typename T>
class DoublyLinkedList {
public:
	Node<T>* head;
	Node<T>* tail;

	DoublyLinkedList() {
		head = nullptr;
		tail = nullptr;
	}
	
	void addFront(T data) {
		auto newNode = new Node<T>(data);
		if (head == nullptr) {
			tail = newNode;
		}
		else {
			newNode->next = head;
			head->prev = newNode;
			
		}
		head = newNode;
	}
	void addEnd(T data) {
		auto newNode = new Node<T>(data);
		if (tail == nullptr) {
			head = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
		}
		tail = newNode;
	}

	void consoleLog() {
		auto current = head;
	
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
	}
};
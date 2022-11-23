#pragma once


template <typename T>
struct Node {
	T data;
	Node* next = nullptr;
	Node* prev = nullptr;

	Node(T data) {
		this->data = data;
		next = nullptr;
		prev = nullptr;
	}
};
#pragma once
#ifndef Vector
#include "Doubly_Linkedlist.h"
	template<typename T>
	//Vector Class 
	class Vector{
	public:
		DoublyLinkedList<T> d_list;
		Vector();					//Constructor
		~Vector();					//Destructor
		int size() const;
        bool empty() const;
		const T& front() const;
		const T& back() const;
		T& get(int i); 
		void erase(int i);
		void push_back(T elem);
		void pop_back();
		void insert(int i, T elem);
	};

	template<typename T>
	Vector<T>::Vector(){}

	template<typename T>
	Vector<T>::~Vector(){}

	template<typename T>
	int Vector<T>::size() const{		//returns size of Vector
		return d_list.size();
	}

	template<typename T>
	bool Vector<T>::empty() const{		//returns bool value for empty
		return d_list.empty();
	}

	template<typename T>
	const T& Vector<T>::front() const{	//returns the front element of a vector
		return d_list.front();
	}

	template<typename T>
	const T& Vector<T>::back() const{	//returns the back element of a vector
		return d_list.back();
	}

	template<typename T>
	T& Vector<T>::get(int i){			//returns the element at index i 
		return d_list.get(i);
	}

	template<typename T>
	void Vector<T>::erase(int i){		//removes an element at index i
		d_list.erase(i);
	}

	template<typename T>
	void Vector<T>::push_back(T elem){	//adds a element
		d_list.addBack(elem);
	}

	template<typename T>
	void Vector<T>::pop_back(){			//removes a element
		d_list.removeBack();
	}

	template<typename T>
	void Vector<T>::insert(int i, T elem){	//insert a element at index i
		d_list.insert(i, elem);
	}

#endif

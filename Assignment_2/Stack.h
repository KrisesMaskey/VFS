#ifndef Stack
	template<typename T>
	//Class Stack
	class Stack{
	public:
		DoublyLinkedList<T> d_list;
		Stack();				//Constructor
		~Stack();				//Destructor
		int size() const;		//Returns Size
        bool empty() const;		//Returns true/false based on size
		const T& top() const;	//returns top element
		void push(T elem);		//adds a new element
		void pop();				//removes a element
	};

	template<typename T>
	Stack<T>::Stack(){}			//Constructor

	template<typename T>
	Stack<T>::~Stack(){}		//Destructor

	template<typename T>
	int Stack<T>::size() const{	//Method Size
		return d_list.size();
	}

	template<typename T>
	bool Stack<T>::empty() const{	//Method Empty
		return d_list.empty();
	}

	template<typename T>
	const T& Stack<T>::top() const{		//Method Top
		return d_list.back();
	}

	template<typename T>
	void Stack<T>::push(T elem){		//Mehod Push
		d_list.addBack(elem);
	}

	template<typename T>
	void Stack<T>::pop(){				//Method Pop
		d_list.removeBack();
	}

#endif

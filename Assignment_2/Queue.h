#ifndef Queue
	template<typename T>
	//Class Queue
	class Queue{
	public:
		DoublyLinkedList<T> d_list;
		Queue();					//Constructor
		~Queue();					//Destructor
		int size() const;			//Returns Size
        bool empty() const;			//Returns true/false
		const T& front() const;		//Returns front element
		void push(T elem);			//Adds element
		void pop();					//removes Element
	};

	template<typename T>
	Queue<T>::Queue(){}		//Constructor

	template<typename T>
	Queue<T>::~Queue(){}	//Destructor

	template<typename T>
	int Queue<T>::size() const{	//Method Size
		return d_list.size();
	}

	template<typename T>
	bool Queue<T>::empty() const{ //Method Empty
		return d_list.empty();
	}

	template<typename T>
	const T& Queue<T>::front() const{ //Method Front
		return d_list.front();
	}

	template<typename T>
	void Queue<T>::push(T elem){	//Method push
		d_list.addBack(elem);
	}

	template<typename T>	//Method pop
	void Queue<T>::pop(){
		d_list.removeFront();
	}

#endif
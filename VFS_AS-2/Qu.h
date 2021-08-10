#ifndef Qu
#include <cstdlib>
using namespace std;
 
  // Define the default capacity of a queue
  #define SIZE 10
   
  // A class to store a queue
  template<typename T>
  class queue
  {
      T *arr;       // array to store queue elements
      int capacity;   // maximum capacity of the queue
      int front;      // front points to the front element in the queue 
      int rear;       // rear points to the last element in the queue
      int count;      // current size of the queue
   
  public:
      queue(int size = SIZE);     // constructor
      ~queue();                   // destructor
   
      void pop();
      void push(T x);
      T Front();
      int size();
      bool empty();
      bool isFull();
  };
   
  // Constructor to initialize a queue
  template<typename T>
  queue<T>::queue(int size)
  {
      arr = new T[size];
      capacity = size;
      front = 0;
      rear = -1;
      count = 0;
  }
   
  // Destructor to free memory allocated to the queue
  template<typename T>
  queue<T>::~queue() {
      delete[] arr;
  }
   
  // Method to pop the front element
  template<typename T>
  void queue<T>::pop()
  {   
      front = (front + 1) % capacity;
      count--;
  }
   
  //Method to add an item to the queue<T>
  template<typename T>
  void queue<T>::push(T item)
  {
      rear = (rear + 1) % capacity;
      arr[rear] = item;
      count++;
  }
   
  //Method to return the front element of the queue<T>
  template<typename T>
  T queue<T>::Front()
  {

      return arr[front];
  }
   
  //Method to return the size of the queue<T>
  template<typename T>
  int queue<T>::size() {
      return count;
  }
   
  //Method to check if the queue<T> is empty or not
  template<typename T>
  bool queue<T>::empty() {
      return (size() == 0);
  }
   
  //Method to check if the queue<T> is full or not
  template<typename T>
  bool queue<T>::isFull() {
      return (size() == capacity);
  }
#endif
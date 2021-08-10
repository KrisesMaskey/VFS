#include<string>
#ifndef DoublyLinkedList
   
   template<typename T> 
   //Node Class
   class Node{
      public:
      T elem;
      Node* next;
      Node* prev;
      Node(): next(NULL), prev(NULL)                     //Constructor
      {}
      Node(T elem) : elem(elem), next(NULL), prev(NULL)  //Constructor
      {}
   };

   template<typename T>
   //Doubly Linked List Class
   class DoublyLinkedList{
      public:
         int s = 0;
         Node<T>* head = NULL;
         Node<T>* tail = NULL;
         DoublyLinkedList();           //Constructor 
         ~DoublyLinkedList();          //Destructor
         int size() const;
         bool empty() const;              // is list empty?
         const T& front() const;          // get the value (element) from front Node of list
         const T& back() const;           // get the value (element) from last Node of the List 
         T& get(int i);                   // get the value (element) from index i 
         void erase(int i);               // remove element at i
         void addFront(T elem);           // add a new node to the front of list
         void addBack(T elem);            // add a new node to the back of the list
         void removeFront();              // remove front node from list
         void removeBack();               // remove last node from list
         void addBefore(int ptr, T elem); // Common method for addFront & addBack
         void insert(int i, T elem);      //insert at index i
   };

   template<typename T>
   DoublyLinkedList<T>::DoublyLinkedList(){
      s = 0;
      Node<T>* new_head = new Node<T>();
      Node<T>* new_tail = new Node<T>();

      head = new_head;
      tail = new_tail;
      head->next = tail;
   }

   template<typename T>
   DoublyLinkedList<T>::~DoublyLinkedList(){
      while(!empty()){
         removeBack();
       }
      delete head;
      delete tail;
   }

   template<typename T>
   bool DoublyLinkedList<T>::empty() const      //get empty or not
   {
      return head->next == tail;
   }

   template<typename T>
   int DoublyLinkedList<T>::size() const        //get Size
   {
      return s;
   }
   template<typename T>
   const T& DoublyLinkedList<T>::front() const // get front element
   {
      if (head->next != NULL){
         return head->next->elem;}
   }

   template<typename T>
   const T& DoublyLinkedList<T>::back() const // get front element
   {
      if (tail->prev != NULL){
         return tail->prev->elem; 
   }}

   template<typename T>
   void DoublyLinkedList<T>::addBefore(int index, T elem)   //add element
   {
      Node<T>* new_node = new Node<T>(elem);
      s++;
      if (empty()){
         tail->prev = new_node;
         head->next = new_node;
         new_node->prev = head;
         new_node->next = tail;
      }
      else if (index==0){
         Node<T>* ptr = head;
         new_node->next = ptr->next;
         ptr->next->prev = new_node;
         new_node->prev = head;
         ptr->next = new_node;
      }else if(index==1){
         Node<T>* ptr = tail;
         ptr->prev->next = new_node;
         new_node->prev = ptr->prev;
         new_node->next = ptr;
         ptr->prev = new_node;
      }  
   }

   template<typename T>
   void DoublyLinkedList<T>::addFront(T elem) // add to front of list
   {
      addBefore(0, elem);
   }

   template<typename T>
   void DoublyLinkedList<T>::addBack(T elem) // add to Back of the list
   {
      addBefore(1, elem);
   }

   template<typename T>
   void DoublyLinkedList<T>::removeFront() // remove front item from list
   {
      s--;
      Node<T>* node = head->next; 
      if (node != NULL && node!=tail){
         node->next->prev = head;
         head->next = node->next;
         delete node;
      }
   }

   template<typename T>
   void DoublyLinkedList<T>::removeBack() // remove last item from list
   {
      s--;
      Node<T>* node = tail->prev; 
      if (node != NULL && node!=head){
         node->prev->next = tail;
         tail->prev = node->prev;
         delete node;
      }
   }

   template<typename T>
   void DoublyLinkedList<T>::erase(int i){   //Erase at index i
      int cnt = 0;
      s--;
      Node<T>* node = head->next;
      while(cnt!=i){
         cnt++;
         node = node->next;
      }
      node->prev->next = node->next;
      node->next->prev = node->prev;   
      delete node;
   }

   template<typename T>
   T& DoublyLinkedList<T>::get(int i) {   //Get element at index i
      int cnt = 0;
      Node<T>* node = head->next;
      while(cnt!=i){
         node = node->next;
         cnt++;
      }
      return node->elem;
   }

   template<typename T>
   void DoublyLinkedList<T>::insert(int i, T elem) {  //Insert element at index i
      int cnt = 0;
      Node<T>* node = head->next;
      while(cnt!=i){
         node = node->next;
         cnt++;
      }
      node->elem = elem;
   }
#endif
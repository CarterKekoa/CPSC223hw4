#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

using namespace std;

template <typename K, typename V>
class LinkedListCollection : public Collection<K,V>{
  public:
    //create an empty linked list
    LinkedListCollection();

    // copy a linked list
    LinkedListCollection(const LinkedListCollection<K,V>& rhs);

    // assign a linked list
    LinkedListCollection<K,V>& operator=(const LinkedListCollection<K,V>& rhs);

    // delete a linked list
    ~LinkedListCollection();

	//deletes a whole node so it can be copied
	void deleteNode();
	
    // insert a key-value pair into the collection
    void insert(const K& key, const V& val);

    // remove a key-value pair from the collection
    void remove(const K& key);

    // find the value associated with the key
    bool find(const K& key, V& val) const;

    // find the keys associated with the range
    void find(const K& k1, const K& k2, std::vector<K>& keys) const;

    // return all keys in the Collection
    void keys(std::vector<K>& keys) const;

    // return collection keys in sorted order
    void sort(std::vector<K>& keys) const;

    // return the number of keys in collection
    int size() const;

  private:
    // linked list node structure
    struct Node {
      K key;
      V value;
      Node* next;
    };

  Node* head; // pointer to first list node
  Node* tail; // pointer to last list node
  int length; // number of linked list nodes in list
};

//create an empty linked list
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection() : head(nullptr), tail(nullptr), length(0){}

// copy a linked list
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection(const LinkedListCollection <K,V>& rhs) : head(nullptr), tail(nullptr), length(0){
  *this = rhs;
}

//delete a node when copying
template <typename K, typename V>
void LinkedListCollection<K,V>::deleteNode(){
	while(head != nullptr){
		Node* ptr = head;   //ptr of type Node, set equal to head pointer of curernt object(this), ptr = head
		head = head->next;	//set head to point at the next node
		delete ptr;			//ptr still at previous node so delete and iterate, if else if else while
		length--;			
	}
}

// assign a linked list
template <typename K, typename V>
LinkedListCollection <K,V>& LinkedListCollection<K,V>::operator=(const LinkedListCollection <K,V>& rhs){
	if(head == rhs.head){		//check to see if heads are equal if, else 
		return *this;
	}else{
		deleteNode();
		Node* ptr = rhs.head;
		head = nullptr;
		tail = nullptr;
		length = 0;
		while(ptr != nullptr){				//while to check and make sure not at the end
			insert(ptr->key, ptr->value);
			ptr = ptr->next;
		}
		return *this;
	}
}

// delete a linked list
template <typename K, typename V>
LinkedListCollection<K,V>::~LinkedListCollection(){
	deleteNode();		//makes use of the delete node I made if
	head = nullptr;
	tail = nullptr;
	length = 0;
}

// insert a key-value pair into the collection
template <typename K, typename V>
void LinkedListCollection<K,V>::insert(const K& key, const V& val){
  Node* ptr = new Node;
  ptr->key = key;
  ptr->value = val;
  ptr->next = nullptr;
  
  if(head == nullptr){			//if head == nullptr then head and tail are equal to same spot else
	  head = ptr;
	  tail = ptr;
  }else{
	  tail->next = ptr;
	  tail = tail->next;
  }
  length++;
}

// remove a key-value pair from the collection
template <typename K, typename V>
void LinkedListCollection<K,V>::remove(const K& key){
	Node* ptr = head;
	if(ptr->key == key){
		if(length == 1){			//checks if the node to be deleted is the head node, if(, }else
			head = nullptr;
			tail = nullptr;
		}else{
			head = ptr->next;
		}
		delete ptr;
		length--;
	}else{
		while(ptr->next != nullptr){	//while to make sure that you arnt at the end
			if(ptr->next->key == key){	//while not there check if the next key is equal to key we want 
				if(ptr->next->next == nullptr){		//if we have key we want and we are before the end
					tail = ptr;
					ptr = ptr->next;
					delete ptr;
					length--;
				}else{								//else
					Node* pntr = ptr->next;
					ptr->next = pntr->next;
					delete pntr;
					pntr = nullptr;
					length--;
				}
			}
			ptr = ptr->next;
		}
	}
}

// find the value associated with the key
template <typename K, typename V>
bool LinkedListCollection<K,V>::find(const K& key, V& val) const{
	Node* ptr = head;
	while(ptr != nullptr){		//while not at the end 
		if(ptr->key == key){	//we found the key we are looking for 
			val = ptr->value;
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

// find the keys associated with the range
template <typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, std::vector<K>& keys) const{
	Node* ptr = head;		//create a pointer that points to same spot as head 
	while(ptr != nullptr){		//while not at end if 
		if(ptr->key >= k1 && ptr->key <= k2){
			keys.push_back(ptr->key);
		}
		ptr = ptr->next;
	}
}

// return all keys in the Collection
template <typename K, typename V>
void LinkedListCollection<K,V>::keys(std::vector<K>& keys) const{
	Node* ptr = head;
	while(ptr != nullptr){
		keys.push_back(ptr->key);
		ptr = ptr->next;
	}
}

// return collection keys in sorted order
template <typename K, typename V>
void LinkedListCollection<K,V>::sort(std::vector<K>& keys) const {
  Node* ptr = head;
  while (ptr != nullptr) {
    keys.push_back(ptr->key);
    ptr = ptr->next;
  }
    std::sort(keys.begin(), keys.end());
}

// return the number of keys in collection
template <typename K, typename V>
int LinkedListCollection<K,V>::size() const{
	return length;
}

#endif

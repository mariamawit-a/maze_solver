#ifndef CS20A_LIST_H
#define CS20A_LIST_H

#include<iostream>
#include<assert.h>

// Linked List object that maintains both head and tail pointers
// and the num_nodes of the list.  Note that you have to keep the head,
// tail and num_nodes consistent with the intended state of the List 
// otherwise very bad things happen. 
template<typename Type>
class List {
public:

	List();

	List(const List<Type>& other);

	List<Type>& operator=(const List<Type>& other);

	~List();

	void	print() const;
	bool	empty() const;

	void	push_front(const Type& item);
	void	push_back(const Type& item);
	void	add_at(int index, const Type& item);

	// Note that the user must first ensure the list is not empty
	// prior to calling these functions.
	Type	front() const;
	Type	rear() const;
	Type	get_at(int index) const;

	int		size() const;
	int		find(const Type& item) const;

	bool	pop_front();
	bool	pop_rear();
	bool	pop_at(int index);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our List.
	// Will be implemented along with list's
	// member functions
	class Node;

	// We'll have both head and tail points for 
	// Fast insertion/deletion from both ends.
	Node* head;
	Node* tail;

	// Keep track of num_nodes of list
	int		num_nodes;
};


/* List Implementation
//
//  Since List is a template class (which is not an actual
//  class yet, not until we actually instantiate the list)
//  we need to keep the implementation together with
//  the definition.  There are ways to simulate having
//  separate "implementation/definition" with templates,
//  but they aren't necessary and can be confusing.
*/

/* Node definition
//		Already implemented, nothing to do here but to use it.
*/
template<typename Type>
class List<Type>::Node {
public:
	Node() :next(nullptr), prev(nullptr) {}
	Node(Type item, Node* p, Node* n) : item(item), next(n), prev(p) {}

	Type  item;
	Node* next;
	Node* prev;
};



/* List default constructor
//		Set head and tail pointer to point to nothing, num_nodes is zero
//		Already implemented, nothing to do.
*/
template<typename Type>
List<Type>::List() :head(nullptr), tail(nullptr), num_nodes(0) {
}


/* Copy constructor
//		This should create an entirely new linked list with the same
//		number of Nodes and the Values stored these Nodes in the same
//		order as seen the other list’s Nodes.  This should not result
//		in any memory leaks or aliasing.
*/
template<typename Type>
List<Type>::List(const List<Type>& other) {
	/* TODO */
	num_nodes = other.num_nodes;
	if (num_nodes == 0)
	{
		head = nullptr;
		tail = nullptr;
	}

	else
	{
		//make a new node with the vale of the head of other and assign it to both the head ans tail of the new list
		Node* trans = other.head;
		Node* node = new Node(trans->item, nullptr, nullptr);
		head = node;
		tail = node;

		//trasverse over the nodes in the other list and copy the item to the tail of the new list num_nodes times
		for (int i = 1; i < num_nodes; ++i)
		{
			trans = trans->next;
			Node* newNode = new Node(trans->item, nullptr, nullptr);
			newNode->prev = tail;
			tail->next = newNode;
			tail = tail->next;
		}

	}
	

}
/* Overloaded assignment operator
//		Causes the already existing linked list to be identical to the
//		other linked list without causing any memory leaks or aliasing.
*/
template<typename Type>
List<Type>& List<Type>::operator=(const List<Type>& other) {
	/* TODO */
	if (this == &other)
		return *this;
	
	while (head != tail)
	{
		head = head->next;
		delete head->prev;
	}
	delete head;
	
	num_nodes = other.num_nodes;

	if (num_nodes == 0)
	{
		head = nullptr;
		tail = nullptr;
		return *this;
	}
	//make a new node with the vale of the head of other and assign it to both the head ans tail of the new list
	Node* trans = other.head;
	Node* node = new Node(trans->item, nullptr, nullptr);
	head = node;
	tail = node;

	//trasverse over the nodes in the other list and copy the item to the tail of the new list num_nodes times
	for (int i = 1; i < num_nodes; ++i)
	{
		trans = trans->next;
		Node* newNode = new Node(trans->item, nullptr, nullptr);
		newNode->prev = tail;
		tail->next = newNode;
		tail = tail->next;
	}

	return *this;
}


/* List destructor
//		Traverses the nodes and deletes them without causing memory leaks
*/
template<typename Type>
List<Type>::~List() {
	/* TODO */
	if (num_nodes == 0)
		return;
	else
	{
		while (head != tail)
		{
			head = head->next;
			delete head->prev;
		}
		delete tail;
		head = nullptr;
		tail = nullptr;
		num_nodes = 0;

	}
}

/* List print
//		Traverses list and prints items in list to console
//		Assumes << is overloaded for object Type.
*/

template<typename Type>
void List<Type>::print() const {
	/* TODO */
	Node* trans = head;
	for (int i = 0; i < num_nodes; ++i)
	{
		if (i + 1 == num_nodes)
		{
			std::cout << trans->item<<std::endl;
			break;
		}	
		std::cout <<trans->item<<" ";
		trans = trans->next;
	}
}

/* List empty
//		returns true if there are no items in the list
//		otherwise returns false.
*/
template<typename Type>
bool List<Type>::empty() const {
	/* TODO */
	if (num_nodes == 0)
		return true;
	else
		return false;
}


/* List push_front
//		Adds a new item to the front of the list
//		updates head, tail, and num_nodes accordingly.
//
//		Two cases to consider: If the list is empty
//		and if the list has items already it.
*/
template<typename Type>
void List<Type>::push_front(const Type& item) {
	/* TODO */
	Node* node = new Node(item, nullptr, nullptr);
	if (num_nodes == 0)
	{
		head = node;
		tail = node;
	}
	else
	{
		head->prev = node;
		node->next = head;
		head = node;
	}
	
	++num_nodes;

}

/* List push_back
//		Adds a new item to the rear of the list
//		updates head, tail, and num_nodes accordingly.
//
//		Two cases to consider: If the list is empty
//		and if the list has items already it.
*/
template<typename Type>
void List<Type>::push_back(const Type& item) {
	/* TODO */
	Node* node = new Node(item, nullptr, nullptr);
	if (num_nodes == 0)
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
	++num_nodes;
	
	
}

/* List add_at
//		Adds a new item at the index indicated
//		updates head, tail, and num_nodes accordingly.
//
//		If the index less than or equal to zero add to the front.
//		If the index is greater than or equal to
//			the num_nodes of the list, add to the rear.
//		All other cases, add the item to the appropriate
//			location
*/
template<typename Type>
void List<Type>::add_at(int index, const Type& item) {
	/* TODO */
	if (index <= 0)
		push_front(item);
	else if (index >= num_nodes)
		push_back(item);
	else
	{
		Node* node = new Node(item, nullptr, nullptr);
		node->next = head;
		
		//go to the index the node is going to be inserted at and adjust the next and prev pointers of neighbouring nodes accordingly
		for (int i = 1; i <= index; ++i)
		{
			node->prev = node->next;
			node->next = node->next->next;
		}
		node->prev = node->next->prev;
		node->prev->next = node;
		node->next->prev = node;

		++num_nodes;
	}

}

/*  List front
//		returns the first item in the list.
*/
template<typename Type>
Type List<Type>::front() const {
	// Force check that the head is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(head != nullptr);

	/* TODO */
	return head->item;
}

/* List rear
//		returns the last item in the list
*/
template<typename Type>
Type List<Type>::rear() const {

	// Force check that the tail is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(tail != nullptr);

	/* TODO */
	return tail->item;

}

/* List get_at
//		returns the item at index
*/
template<typename Type>
Type List<Type>::get_at(int index) const {

	// Force index to be correct before getting the Item
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(index >= 0 && index < num_nodes);

	/* TODO */
	Node* node = head;
	for (int i = 1; i <= index; ++i)
	{
		node = node->next;
	}
	return node->item;

}

/* List size
//		return the num_nodes of the list
*/
template<typename Type>
int List<Type>::size() const {
	/* TODO */
	return num_nodes;
}

/* List find
//		Traverses the list to see if the item is in the list
//		if it is return the index of that item, otherwise
//		return -1. Assumes the == operator is overloaded for
//		object Type.
*/
template<typename Type>
int List<Type>::find(const Type& item) const {

	/* TODO */
	for (int i = 0; i < num_nodes; ++i)
	{
		if (get_at(i) == item)
			return i;
	}

	return -1;

}

/* List pop_front
//		Removes the first item in the list returns true
//		if the item was deleted, false otherwise. Updates
//		head, tail, and num_nodes accordingly.
//
//		Must consider at least two cases where the list: is empty,
//		has one or more items.
*/
template<typename Type>
bool List<Type>::pop_front() {

	if (num_nodes == 0)
		return false;

	else if (num_nodes == 1)
	{
		delete head;
		--num_nodes;
		head = nullptr;
		tail = nullptr;
		return true;
	}
	else
	{
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
		--num_nodes;
		return true;
	}


}
/* List pop_rear
//		Removes the last item in the list returns true
//		if the item was deleted, false otherwise. Updates
//		head, tail, and num_nodes accordingly.
//
//		Must consider at least three cases where the list: is empty,
//		has one item, has two or more items.
*/
template<typename Type>
bool List<Type>::pop_rear() {

	if (num_nodes == 0)
		return false;
	else if (num_nodes == 1)
	{
		pop_front();
		return true;
	}
	else
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
		--num_nodes;
		return true;
	}

}

/* List pop_at
//		Removes the item at the index returns true
//		if the item was deleted, false otherwise. Updates
//		head, tail, and num_nodes accordingly. If the index is
//		out of bounds return false.
*/
template<typename Type>
bool List<Type>::pop_at(int index) {

	/* TODO */
	if (num_nodes == 0 || index >= num_nodes || index < 0)
		return false;

	else if (index == 0)
		pop_front();


	else if (index == num_nodes - 1)
		pop_rear();

	//make the previous of target node to point to the next of the target node and vise versa then delete the node
	else
	{
		Node* node = head;
		for (int i = 1; i <= index; ++i)
		{
			node = node->next;
		}

		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		--num_nodes;

	}


	return true;
}

#endif
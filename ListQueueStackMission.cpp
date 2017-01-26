#include "DetectMemoryLeak.h"
#include "Node.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>

using std::string;
using std::vector;
using std::list;
using std::map;
using std::stack;
using std::queue;

// DO NOT MODIFY ANY LINE ABOVE OR ADD EXTRA INCLUDES

/*! 
 *  \brief     DM2126 Assignment 2
 *  \details   Submit the whole solution, but only this file will be used to grade
 *  \author    <Ho Chee Mun>
 *  \date      2017 
 *  \note      <162670T>
 */

//*******************************************************************//
// Linked list stuff
//*******************************************************************//
LinkedList::LinkedList() 
{
	head_ = new Node();

	head_->next = NULL;
}

LinkedList::~LinkedList()
{ 
}

void LinkedList::push_front(int data)
{
	Node* newNode = new Node(data);

	newNode->next = head_->next;
	head_->next = newNode;
}

void LinkedList::push_back(int data)
{
	Node* newNode = new Node(data);

	for (Node* back = head_->next; back != NULL; back = back->next)
	{
		if (back->next == NULL)
		{
			newNode->next = NULL;
			back->next = newNode;
			break;
		}
	}
}

int LinkedList::pop_front()
{
	short dataResult = 0;
	//-------------------SETTING HEAD NEXT TO DELETOR NODE FOR DELETION OF FRONT NODE-------------------
	Node* deletor = head_->next;

	//-------------------GETTING RESULT-------------------
	dataResult = head_->next->data;

	//-------------------SETTING HEAD NEXT TO THE NEXT AVAILABLE NODE-------------------
	head_->next = head_->next->next;

	//-------------------DELETION OF FRONT NODE-------------------
	delete deletor;
	deletor = nullptr;

	return ((int)dataResult);
}

int LinkedList::pop_back()
{
	short dataResult = 0;
	Node* deletor;

	for (Node* back = head_->next; back != NULL; back = back->next)
	{
		if (back->next->next == NULL)
		{
			deletor = back->next;
			dataResult = back->next->data;

			back->next = NULL;
			
			delete deletor;
			deletor = nullptr;
			break;
		}
	}

	return ((int)dataResult);
}

void LinkedList::insert_at(int pos, int data)
{    

	Node* newNode = new Node(data);
	int i = 0;

	if (pos > size())
		pos = size();
	else if (pos < 0)
		pos = 0;

	if (pos == 0)
	{
		newNode->next = head_->next;
		head_->next = newNode;

		goto here;
	}

	for (Node* back = head_->next; back != NULL; back = back->next, i++)
	{
		 if (i == pos - 1)
		{
			newNode->next = back->next;
			back->next = newNode;

			break;
		}
	}

here:

	;

}

int LinkedList::pop_at(int pos)
{
	int i = 0;

	short dataResult = 0;
	Node* deletor;

	if (pos > size())
		pos = size();
	else if (pos < 0)
		pos = 0;

	if (pos == 0)
	{
		dataResult = head_->next->data;
		deletor = head_->next;
		head_->next = head_->next->next;

		delete deletor;
		deletor = nullptr;

		goto here;
	}

	for (Node* back = head_->next; back != NULL; back = back->next, i++)
	{
		if (i == pos - 1)
		{
			dataResult = back->next->data;
			deletor = back->next;

			back->next = back->next->next;

			delete deletor;
			deletor = nullptr;

			break;
		}
	}

	here:

	return ((int)dataResult);
}

size_t LinkedList::size()
{
	size_t totalSize = 0;

	for (Node* back = head_->next; back != NULL; back = back->next)
		totalSize++;
	

	return totalSize;
}

//*******************************************************************//
// Queue stuff
//*******************************************************************//
Queue::Queue() 
{
}

Queue::~Queue()
{   
}

void Queue::enqueue(int data)
{   
}

int Queue::dequeue()
{
    return 0;
}

size_t Queue::size()
{
    return 0;
}

//*******************************************************************//
// Stack stuff
//*******************************************************************//
Stack::Stack()
{

}

Stack::~Stack()
{
}

void Stack::push(int data)
{
}

int Stack::pop()
{
    return 0;
}

size_t Stack::size()
{
    return 0;
}



// Balanced parenthesis
bool Brackets(const string& input)
{
    return true;
}

// Query machine, hits
void QueryMachine(vector<int>& data, vector<int>& queries, vector<unsigned int>& results)
{
}
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

	head_->next = nullptr;
}

LinkedList::~LinkedList()
{ 

	while (size())
	{
		pop_back();
	}

	delete head_;
	head_ = nullptr;
}

void LinkedList::push_front(int data)
{
	Node* newNode = new Node(data);

	newNode->next = head_->next;
	head_->next = newNode;
}

void LinkedList::push_back(int data)
{

	for (Node* back = head_->next; back != nullptr; back = back->next)
	{
		if (back->next == nullptr)
		{
			Node* newNode = new Node(data);

			newNode->next = nullptr;
			back->next = newNode;
			break;
		}
	}
}

int LinkedList::pop_front()
{
	int data_result = 0;
	if (head_->next != nullptr)
	{
		//-------------------SETTING HEAD NEXT TO DELETOR NODE FOR DELETION OF FRONT NODE-------------------
		Node* deletor = head_->next;

		//-------------------GETTING RESULT-------------------
		data_result = head_->next->data;

		//-------------------SETTING HEAD NEXT TO THE NEXT AVAILABLE NODE-------------------
		head_->next = head_->next->next;

		//-------------------DELETION OF FRONT NODE-------------------
		delete deletor;
		deletor = nullptr;
	}

	return data_result;
}

int LinkedList::pop_back()
{
	int data_result = 0;
	Node* deletor;
	Node* prev = head_->next;

	for (Node* last = head_->next; last != nullptr; last = last->next)
	{
		if (last->next == nullptr)
		{
			deletor = last;
			data_result = prev->next->data;

			prev->next = nullptr;
			
			delete deletor;
			deletor = nullptr;
			break;
		}
	}

	return data_result;
}

void LinkedList::insert_at(int pos, int data)
{    
	int i = 0;

	if (size() <= 1 || pos <= 0)
		push_front(data);
	else if (pos >= size())
		push_back(data);
	else
	{
		for (Node* back = head_->next; back != nullptr; back = back->next, i++)
		{
			if (i == pos - 1)
			{
				Node* newNode = new Node(data);

				newNode->next = back->next;
				back->next = newNode;

				break;
			}
		}
	}
}

int LinkedList::pop_at(int pos)
{
	int i = 0;

	int data_result = 0;
	Node* deletor;

	if (size() <= 1 || pos <= 0)
		data_result = pop_front();
	else if (pos >= size())
		data_result = pop_back();
	else
	{
		for (Node* back = head_->next; back != nullptr; back = back->next, i++)
		{
			if (i == pos - 1)
			{
				data_result = back->next->data;
				deletor = back->next;

				back->next = back->next->next;

				delete deletor;
				deletor = nullptr;

				break;
			}
		}
	}

	return data_result;
}

size_t LinkedList::size()
{
	size_t total_size = 0;

	for (Node* back = head_->next; back != nullptr; back = back->next)
		total_size++;
	

	return total_size;
}

//*******************************************************************//
// Queue stuff
//*******************************************************************//
Queue::Queue() 
{
	back_ = nullptr;
	front_ = nullptr;
}

Queue::~Queue()
{   
	while (size())
	{
		dequeue();
	}
}

void Queue::enqueue(int data)
{   

	Node* newNode = new Node(data);

	if (size() == 0)
	{
		front_ = newNode;
		front_->next = back_;
	}
	else
	{
		for (Node* last = front_; last != nullptr; last = last->next)
		{
			if (last->next == nullptr)
			{
				newNode->next = nullptr;
				last->next = newNode;
				back_ = newNode;
				break;
			}
		}
	}

}

int Queue::dequeue()
{
	int data_result = 0;
	Node* deletor;

	if (size())
	{
		deletor = front_;
		data_result = front_->data;

		front_ = front_->next;

		delete deletor;
		deletor = nullptr;

	}

	return data_result;
}

size_t Queue::size()
{
	size_t total_size = 0;
	
	for (Node* back = front_; back != nullptr; back = back->next)
		++total_size;

	return total_size;
}

//*******************************************************************//
// Stack stuff
//*******************************************************************//
Stack::Stack()
{
	top_ = new Node();
	top_->next = nullptr;
}

Stack::~Stack()
{
	if (size())
		pop();

	delete top_;
	top_ = nullptr;
}

void Stack::push(int data)
{

	Node* newNode = new Node(data);

	if (size())
	{
		for (Node* last = top_->next; last != nullptr; last = last->next)
		{
			if (last->next == nullptr)
			{
				newNode->next = last->next;
				last->next = newNode;
				break;
			}
		}
	}
	else
	{
		top_->next = newNode;
		newNode->next = nullptr;
	}
}

int Stack::pop()
{
	int data_result = 0;
	Node* prev = top_->next;

	if (size() > 1)
	{
		for (Node* last = top_->next; last != nullptr; last = last->next)
		{
			if (last->next == nullptr)
			{
				Node* deletor;

				data_result = last->data;
				deletor = last;
				prev->next = nullptr;

				delete deletor;
				deletor = nullptr;

				break;
			}
		}
	}
	else if (size() == 1)
	{
		Node* deletor;

		data_result = top_->next->data;
		deletor = top_->next;
		top_->next = nullptr;

		delete deletor;
		deletor = nullptr;
	}

	return data_result;
}

size_t Stack::size()
{
	int size_of_stack = 0;

	for (Node* last = top_->next; last != nullptr; last = last->next)
		++size_of_stack;

	return size_of_stack;
}



// Balanced parenthesis
bool Brackets(const string& input)
{
	char current_open_symbol;
	int even_number_checker, same_symbol, paired = 0;

	if (input.size() % 2 == 0)
	{
		for (int i = 0; i < input.size(); i++)
		{
			current_open_symbol = input[i];
			even_number_checker = same_symbol = 0;

			for (int j = i + 1; j < input.size(); j++)
			{
				if (input[j] == current_open_symbol)
				{
					++same_symbol;
				}
				else if (input[j] == ((current_open_symbol == 40) ? (current_open_symbol + 1) : (current_open_symbol + 2)))
				{
					if (same_symbol == 0)
					{
						if (even_number_checker % 2 == 0)
						{
							++paired;
							break;
						}
						else
						{
							return false;
						}
					}
					else if (same_symbol > 0)
					{
						--same_symbol;
						++even_number_checker;
						continue;
					}
				}

				++even_number_checker;

			}

			if (i == input.size() - 1 && (paired * 2) != input.size())
				return false;
		}

		return true;
	}

	return false;
}

// Query machine, hits
void QueryMachine(vector<int>& data, vector<int>& queries, vector<unsigned int>& results)
{
}
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
	head_ = nullptr;
}

LinkedList::~LinkedList()
{ 

	while (size())
	{
		pop_front();
	}
}

void LinkedList::push_front(int data)
{
	Node* newNode = new Node(data);

	newNode->next = head_;
	head_ = newNode;
}

void LinkedList::push_back(int data)
{
	if (head_ != nullptr)
	{
		for (Node* back = head_; back != nullptr; back = back->next)
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
	else
	{
		push_front(data);
	}
}

int LinkedList::pop_front()
{
	int data_result = 0;

	if (size())
	{
		Node* deletor; 
		deletor = head_;

		head_ = head_->next;
		data_result = deletor->data;
		delete deletor;
		deletor = nullptr;
	}

	return data_result;
}

int LinkedList::pop_back()
{
	int data_result = 0;

	if (size() == 1)
	{
		data_result = pop_front();
	}
	else if (size())
	{
		Node* deletor;
		Node* prev = head_;

		for (Node* last = head_; last != nullptr; last = last->next)
		{
			if (last->next == nullptr)
			{
				deletor = last;
				prev->next = nullptr;
		
				break;
			}

			prev = last;
		}

		if (deletor->data)
		{
			data_result = deletor->data;
			
			delete deletor;
			deletor = nullptr;
		}
	}


	return data_result;
}

void LinkedList::insert_at(int pos, int data)
{    
	int i = 0;

	if (pos <= 0)
		push_front(data);
	else if (pos >= (int)size())
		push_back(data);
	else
	{
		for (Node* back = head_; back != nullptr; back = back->next, i++)
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

	if (pos <= 0)
		data_result = pop_front();
	else if (pos == (int)size() - 1)
		data_result = pop_back();
	else if (pos < (int)size() - 1)
	{
		Node* deletor;

		for (Node* curr = head_; curr != nullptr; curr = curr->next)
		{
			if (i == pos - 1)
			{
				deletor = curr->next;

				curr->next = curr->next->next;

				data_result = deletor->data;

				delete deletor;
				deletor = nullptr;

				break;
			}

			i++;
		}
	}

	return data_result;
}

size_t LinkedList::size()
{
	size_t total_size = 0;

	if (head_)
	{
		for (Node* curr = head_; curr != nullptr; curr = curr->next)
		{
			total_size++;
		}
	}

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

	if (front_ == nullptr)
	{
		front_ = newNode;
		front_->next = nullptr;
		back_ = front_;
	}
	else
	{
		newNode->next = nullptr;
		back_->next = newNode;
		back_ = newNode;
	}

}

int Queue::dequeue()
{
	int data_result = 0;
	Node* deletor;

	if (front_ != back_)
	{
		deletor = front_;
		data_result = front_->data;

		front_ = front_->next;

		delete deletor;
		deletor = nullptr;

	}
	else if (front_ == back_ && front_ != nullptr)
	{
		deletor = front_;
		data_result = front_->data;

		delete deletor;
		deletor = nullptr;

		front_ = nullptr;
		back_ = nullptr;
	}

	return data_result;
}

size_t Queue::size()
{
	size_t total_size = 0;
	
	if (front_ != nullptr)
	{
		for (Node* back = front_; back != back_->next; back = back->next)
			++total_size;
	}
	return total_size;
}

//*******************************************************************//
// Stack stuff
//*******************************************************************//
Stack::Stack()
{
	top_ = nullptr;
}

Stack::~Stack()
{
	while (top_ != nullptr)
		pop();
}

void Stack::push(int data)
{

	Node* newNode = new Node(data);

	if (top_ != nullptr)
	{
		newNode->next = top_;
		top_ = newNode;
	}
	else
	{
		newNode->next = nullptr;
		top_ = newNode;
	}
}

int Stack::pop()
{
	int data_result = 0;

	if (top_ != nullptr)
	{
		Node* deletor;

		deletor = top_;
		data_result = top_->data;

		top_ = top_->next;

		delete deletor;
		deletor = nullptr;
	}

	return data_result;
}

size_t Stack::size()
{
	int size_of_stack = 0;

	if (top_ != nullptr)
	{
		for (Node* last = top_; last != nullptr; last = last->next)
			++size_of_stack;
	}

	return size_of_stack;
}



// Balanced parenthesis
bool Brackets(const string& input)
{
	char current_open_symbol;
	int even_number_checker, same_symbol, paired = 0;

	if (input.size() % 2 == 0)
	{
		for (int i = 0; i < (int)input.size(); i++)
		{
			current_open_symbol = input[i];
			even_number_checker = same_symbol = 0;

			for (int j = i + 1; j < (int)input.size(); j++)
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

			if (i == (int)input.size() - 1 && (paired * 2) != (int)input.size())
				return false;
		}

		return true;
	}

	return false;
}

// Query machine, hits
void QueryMachine(vector<int>& data, vector<int>& queries, vector<unsigned int>& results)
{

	for (vector<int>::iterator it = queries.begin(); it != queries.end(); it++)
	{
		results.push_back(0);
	}

	for (vector<int>::iterator i = data.begin(); i != data.end(); i++)
	{
		unsigned short pos = 0;

		for (vector<int>::iterator j = queries.begin(); j != queries.end(); j++)
		{
			if (*i == *j)
			{
				results[pos]++;
			}
			++pos;
		}
	}
}
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
 *  \author    Ho Chee Mun
 *  \date      2017 
 *  \note      162670T
 */

//*******************************************************************//
// Linked list stuff
//*******************************************************************//
LinkedList::LinkedList() 
{
	//SETTING HEAD TO NULL
	head_ = nullptr;
}

LinkedList::~LinkedList()
{ 
	//LOOPING THROUGH IF THERES NODE IN LIST
	while (size())
	{
		pop_front();  //REMOVING FRONT NODE USING POP_FRONT()
	}
}

void LinkedList::push_front(int data)
{
	//CREATING A NEW NODE TO STORE DATA AND TO LINK INTO LINK LIST THROUGH THE FRONT
	Node* newNode = new Node(data);

	//NEW NODE NEXT POINTS TO HEAD_
	newNode->next = head_;

	//SETTING NEW NODE THE THE HEAD_ TO MAKE IT THE FIRST NODE
	head_ = newNode;
}

void LinkedList::push_back(int data)
{
	//MAKING SURE HEAD IS NOT NULL
	if (head_ != nullptr)
	{
		//LOOPING THROUGH THE LIST UNTIL IT REACHES THE END OF THE LIST
		for (Node* back = head_; back != nullptr; back = back->next)
		{
			if (back->next == nullptr)  //CHECKING IF THE NEXT NODE IS NULL, THIS MAKES SURE THAT THE CURRENT NODE IS THE LAST
			{
				//CREATING A NEW NODE TO STORE DATA AND TO LINK INTO LINK LIST
				Node* newNode = new Node(data);

				newNode->next = nullptr;  //SETTING NEW NODE NEXT TO NULL
				back->next = newNode;  //SETTING BACK NEXT TO NEW NODE SO THAT NEW NODE BECOMES THE LAST NODE ON THE LIST
				break;
			}
		}
	}
	else
	{
		//IF HEAD IS NULL, ADD TO FRONT USING PUSH_FRONT()
		push_front(data);
	}
}

int LinkedList::pop_front()
{
	//MAKING AN INT DATA_RESULT TO STORE DATA
	int data_result = 0;

	//CHECKING IF THERE ARE NODES IN THE LIST
	if (size())
	{
		//MAKING A NODE DELETOR TO DELETE NODE
		Node* deletor; 
		deletor = head_; //DELETE BECOMES HEAD_ SO AS TO DELETE THE FIRST NODE

		//SETTING HEAD_ TO HEAD_ NEXT SO THAT THE FIRST NODE BECOMES THE NEXT NODE IN THE LIST
		head_ = head_->next;
		//SETTING DATA RESULT TO THE CURRENT FRONT NODE
		data_result = deletor->data;
		//DELETING FRONT NODE
		delete deletor;
		//SETTING DELETED FRONT NODE TO NULL
		deletor = nullptr;
	}

	return data_result;
}

int LinkedList::pop_back()
{
	//MAKING AN INT DATA_RESULT TO STORE DATA
	int data_result = 0;

	//CHECKING IF THERE IS ONLY ONE NODE IN THE LIST
	if (size() == 1)
	{
		data_result = pop_front();  //USE POP_FRONT IF THERE IS ONLY ONE NODE IN THE LIST
	}
	else if (size())  //CHECKING IF THERE ARE NODES IN THE LIST
	{
		//MAKING A NODE DELETOR TO DELETE NODE
		Node* deletor;
		//MAKING A NODE PREV TO STORE PREVIOUS NODE
		Node* prev = head_;

		//LOOPING THROUGH THE LIST UNTIL THE END
		for (Node* last = head_; last != nullptr; last = last->next)
		{
			if (last->next == nullptr)  //CHECKING IF THE NEXT NODE IS NULL, THIS MAKES SURE THAT THE CURRENT NODE IS THE LAST
			{
				//SETTING LAST TO DELETOR
				deletor = last;
				prev->next = nullptr;  //SETTING PREV NEXT TO NULL
		
				data_result = deletor->data;  //SETTING DATA TO DATA_RESULT

				delete deletor;  //DELETING DELETOR
				deletor = nullptr;  //SETTING DELETOR TO NULL

				break;
			}
			//SETTING LAST TO PREV
			prev = last;
		}
	}


	return data_result;
}

void LinkedList::insert_at(int pos, int data)
{    
	int i = 0;

	//CHECKING IF THE GIVEN POSITION IS BELOW 0
	if (pos <= 0)
		push_front(data);   //USE PUSH_FRONT IF POSITION IS BELOW OR EQUALS TO 0
	else if (pos >= (int)size())  //CHECKING IF GIVEN POSITION IS ABOVE THE SIZE OF THE LIST
		push_back(data);  //USE PUSH_BACK IF POSIITON IS ABOVE THE SIZE OF THE LIST
	else
	{
		//LOOPING THROUGH UNTIL WANTED CONDITION
		for (Node* back = head_; back != nullptr; back = back->next, i++)
		{
			if (i == pos - 1)  //CHECKING FOR BEFORE WANTED POSITION IN THE LIST
			{
				Node* newNode = new Node(data);  //CREATING A NEW NODE TO STORE DATA AND TO LINK INTO LINK LIST THROUGH THE POSITION

				newNode->next = back->next;  //SETTING NEW NODE NEXT TO THE NEXT NODE IN THE LIST SO AS TO LINK THEM
				back->next = newNode;  //SETTING BACK NEXT TO THE NEW NODE TO LINK THEM TOGETHER

				break;
			}
		}
	}
}

int LinkedList::pop_at(int pos)
{
	int i = 0;
	// MAKING AN INT DATA_RESULT TO STORE DATA
	int data_result = 0;

	if (pos <= 0)  //CHECKING IF THE GIVEN POSITION IS BELOW 0
		data_result = pop_front();  //USE POP_FRONT IF POSITION IS BELOW OR EQUALS TO 0
	else if (pos == (int)size() - 1)  //CHECKING IF GIVEN POSITION IS ABOVE THE SIZE OF THE LIST
		data_result = pop_back();  //USE POP_BACK IF POSIITON IS ABOVE THE SIZE OF THE LIST
	else if (pos < (int)size() - 1)  //CHECKING IF THE GIVEN POSITION IS LESS THAN THE SIZE
	{
		//MAKING A NODE DELETOR TO DELETE NODE
		Node* deletor;
		
		//LOOPING THROUGH THE LIST UNTIL THE END
		for (Node* curr = head_; curr != nullptr; curr = curr->next)
		{
			if (i == pos - 1)  //CHECKING FOR BEFORE WANTED POSITION IN THE LIST
			{
				deletor = curr->next;  //SETTING CURRENT NEXT TO DELETOR

				curr->next = curr->next->next;  //SETTING CURRENT NEXT TO CURRENT NEXT NEXT SO AS TO LINK THEM

				data_result = deletor->data;  //SETTING DATA TO DATA_RESULT

				delete deletor;  //DELETING DELETOR
				deletor = nullptr;  //SETTING DELETOR TO NULL

				break;
			}

			i++;  //ADDING TO I IF THE CODITION IS NOT MET 
		}
	}

	return data_result;
}

size_t LinkedList::size()
{
	size_t total_size = 0;

	if (head_)  //CHECKING IF HEAD IS NULL
	{
		for (Node* curr = head_; curr != nullptr; curr = curr->next)  //LOOPING THROUGH UNTIL THE END OF LIST
		{
			total_size++;  //ADDING 1 FOR EVERY NODE IN THE LIST
		}
	}

	return total_size;
}

//*******************************************************************//
// Queue stuff
//*******************************************************************//
Queue::Queue() 
{
	//SETTING FRONT AND BACK TO NULL
	back_ = nullptr;
	front_ = nullptr;
}

Queue::~Queue()
{   
	//LOOPING THROUGH IF THERES NODE IN LIST
	while (size())
	{
		dequeue();  //REMOVING FRONT NODE USING DEQUEUE()
	}
}

void Queue::enqueue(int data)
{   
	//CREATING A NEW NODE TO STORE DATA AND TO LINK INTO LINK LIST THROUGH THE FRONT
	Node* newNode = new Node(data);

	if (front_ == nullptr)  //CHECKING IF FRONT_ IS NULL
	{
		front_ = newNode;  //SETTING FRONT_ TO THE NEW NODE
		front_->next = nullptr;  //SETTING FRONT_ NEXT TO NULL
		back_ = front_;  //SETTING BACK TO FRONT
	}
	else  //IF FRONT_ IS NOT NULL
	{
		newNode->next = nullptr;  //SETTING NEW NODE NEXT TO NULL
		back_->next = newNode;  //SETTING LAST NODE POINTED BY BACK_ NEXT TO NEW NODE
		back_ = newNode;  //SETTING BACK_ TO NEW NODE
	}

}

int Queue::dequeue()
{
	//MAKING AN INT DATA_RESULT TO STORE DATA
	int data_result = 0;
	//MAKING A NODE DELETOR TO DELETE NODE
	Node* deletor;

	if (front_ != back_)  //CHECKING IF FRONT_ IS NOT POINTING TO BACK_
	{
		deletor = front_;  //SETTING DELETOR TO FRONT_
		data_result = front_->data;  //SETTING DATA FROM FRONT_ INTO DATA_RESULT

		front_ = front_->next;  //SETTING FRONT_ TO FRONT_ NEXT

		delete deletor;  //DELETING DELETOR
		deletor = nullptr;  //SETTING DELETOR TO NULL

	}
	else if (front_ == back_ && front_ != nullptr)  //CHECKING IF FRONT_ IS POINTING TO BACK_ AND IF FRONT IS NOT NULL
	{
		deletor = front_;  //SETTING DELETOR TO FRONT_
		data_result = front_->data;  //SETTING DATA FROM FRONT_ INTO DATA_RESULT

		delete deletor;  //DELETING DELETOR
		deletor = nullptr;  //SETTING DELETOR TO NULL

		front_ = nullptr;  //SETTING FRONT_ TO NULL
		back_ = nullptr;  //SETTING BACK_ TO NULL
	}

	return data_result;
}

size_t Queue::size()
{
	size_t total_size = 0;
	
	if (front_ != nullptr)  //CHECKING IF FRONT_ IS NULL
	{
		for (Node* back = front_; back != back_->next; back = back->next)  //LOOPING THROUGH UNTIL THE END OF LIST
			++total_size;  //ADDING 1 FOR EVERY NODE IN THE LIST
	}
	return total_size;
}

//*******************************************************************//
// Stack stuff
//*******************************************************************//
Stack::Stack()
{
	//SETTING TOP_ TO NULL
	top_ = nullptr;
}

Stack::~Stack()
{
	while (top_ != nullptr)  //LOOPING THROUGH IF THERES NODE IN LIST
		pop();  //REMOVING BACK NODE USING POP()
}

void Stack::push(int data)
{
	//CREATING A NEW NODE TO STORE DATA AND TO LINK INTO LINK LIST THROUGH THE BACK
	Node* newNode = new Node(data);

	if (top_ != nullptr)  //CHECKING IF TOP_ IS NOT NULL
	{
		newNode->next = top_;  //SETTING NEW NODE NEXT TO TOP_
		top_ = newNode;  //SETTING TOP_ TO NEW NODE
	}
	else  //CHECKING IF TOP_ IS NULL
	{
		newNode->next = nullptr;  //SETTING NEW NODE NEXT TO NULL
		top_ = newNode;  //SETTING TOP_ TO NEW NODE
	}
}

int Stack::pop()
{
	int data_result = 0;  // MAKING AN INT DATA_RESULT TO STORE DATA

	if (top_ != nullptr)  //CHECKING IF TOP_ IS NOT NULL
	{
		Node* deletor;  //MAKING A NODE DELETOR TO DELETE NODE

		deletor = top_;  //SETTING DELETOR TO TOP_
		data_result = top_->data;  //SETTING DATA FROM TOP_ TO DATA_RESULT

		top_ = top_->next;  //SETTING TOP_ TO THE NEXT AVAILABLE NODE IN THE LIST

		delete deletor;  //DELETING DELETOR
		deletor = nullptr;  //SETTING DELETOR TO NULL
	}

	return data_result;
}

size_t Stack::size()
{
	int size_of_stack = 0;

	if (top_ != nullptr)  //CHECKING IF TOP IS NULL
	{
		for (Node* last = top_; last != nullptr; last = last->next)  //LOOPING THROUGH UNTIL THE END OF LIST
			++size_of_stack;  //ADDING 1 FOR EVERY NODE IN THE LIST
	}

	return size_of_stack;
}



// Balanced parenthesis
bool Brackets(const string& input)
{
	char current_open_symbol;  //A CHARACTER TO STORE CURRENT CHARACTER

	int even_number_checker,		//EVEN_NUMBER_CHECKER IS TO CHECK FOR EVEN NUMBERS IN BETWEEN THE SYMBOLS
		same_symbol,				//SAME_SYMBOL IS TO CHECK FOR REPEATING SYMBOLS
		paired = 0;					//PAIRED IS TO CHECK IF THERE ARE ANY PAIRS													 

	if (input.size() % 2 == 0)  //CHECKING IF THE INPUT SIZE IS EVEN
	{
		for (int i = 0; i < (int)input.size(); i++)  //LOOPING THROUGH UNTIL THE END
		{
			current_open_symbol = input[i];  //SETTING FIRST CHARACTER IN THE STRING TO CURRENT_OPEN_SYMBOL
			even_number_checker = same_symbol = 0;  //RESETTING THEM TO 0

			for (int j = i + 1; j < (int)input.size(); j++)  //LOOPING THROUGH UNTIL THE END
			{
				if (input[j] == current_open_symbol)  //CHECKING FOR SAME OPEN SYMBOL
				{
					++same_symbol;  //ADDING ONE IF THERE IS SIMILAR OPENING SYMBOL
				}
				else if (input[j] == ((current_open_symbol == 40) ? (current_open_symbol + 1) : (current_open_symbol + 2)))  //CHECKING IF THE NEXT SYMBOL IS THE NEEDED CLOSING SYMBOL
				{
					if (same_symbol == 0)  //CHECKING IF SAME_SYMBOL IS 0
					{
						if (even_number_checker % 2 == 0)  //CHECKING IF THE SYMBOLS IN BETWEEN THE TWO OPENING AND CLOSING ARE EVEN
						{
							++paired;  //INCReASE PAIRED BY 1
							break;
						}
						else
						{
							return false;  //ELSE RETURN FALSE
						}
					}
					else if (same_symbol > 0)  //IF SAME SYMBOL HAS OCCURED
					{
						--same_symbol;  //MINUS 1 FROM THE CHECK
						++even_number_checker;  //ADD 1 TO THE NUMBER OF SYMBOL IN BETWEEN THE TWO OPENING AND CLOSING ARE EVEN
						continue;
					}
				}

				++even_number_checker;  //ADD 1 TO THE NUMBER OF SYMBOL IN BETWEEN THE TWO OPENING AND CLOSING ARE EVEN

			}

			if (i == (int)input.size() - 1 && (paired * 2) != (int)input.size())  //CHECKING IF RACHED THE END OF STRING OR PAIRED * 2 IS NOT EQUALS TO THE TOTAL SIZE
				return false;
		}

		return true;
	}

	return false;
}

// Query machine, hits
void QueryMachine(vector<int>& data, vector<int>& queries, vector<unsigned int>& results)
{

	for (vector<int>::iterator it = queries.begin(); it != queries.end(); it++)  //LOOPING THROUGH UNTIL THE END
	{
		results.push_back(0);  //PUSH BACK FOR EVERY QUERY
	}

	for (vector<int>::iterator i = data.begin(); i != data.end(); i++)  //LOOPING THROUGH UNTIL THE END
	{
		unsigned short pos = 0;  //SETTING POSITION OF THE VECTOR TO 0

		for (vector<int>::iterator j = queries.begin(); j != queries.end(); j++)  //LOOPING THROUGH UNTIL THE END
		{
			if (*i == *j)  //CHECKING IF BOTH VALUES ARE SIMILAR
			{
				results[pos]++;  //INCREASE BY ONE IN RESULT IF FOUND SIMILAR NUMBERS IN DATA NAD THE QUERY
			}
			++pos;  //ADD ONE TO POS TO MOVE ON TO THE NEXT NUMBER IN RESULT
		}
	}
}
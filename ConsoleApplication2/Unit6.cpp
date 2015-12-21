#include <cassert>
#include <crtdbg.h>
#include <iostream>
class List {
private:
	class Node {
	public:
		Node(){}
		Node(double value) {
			this->value = value;
			next = nullptr;
		}

		Node(double value, Node* next) {
			this->value = value;
			this->next = next;
		}
		double value;
	public:
		Node* next;
	};
	Node* head;
public:
	Node* const operator[](int i) {
			Node* toReturn = head;
			int index = 0;
			while (index != i) {
				toReturn = toReturn->next;
				++index;
			}
			return toReturn;
	}
	List() : head(nullptr){}
	~List() {
		std::cout << "CALLED dtor!" << std::endl;
		Node* current = head;

		while (nullptr != current) {
			Node* toDelete = current;
			current = current->next;
			delete toDelete;
		}
	}

	List(const List &src) {
		std::cout << "CALLED cpyctor!" << std::endl;
		this->head = nullptr;
		Node* temp = (&src)->head;
		while (nullptr != temp) {
			std::cout << "CALLED while in cpyctor!" << std::endl;
			(*this).pushback(temp->value);
			temp = temp->next;
		}
	}

	size_t length() {
		if (nullptr == head) {
			return 0;
		}
		Node* temp = head;
		int count = 0;

		while (nullptr != temp) {
			++count;
			temp = temp->next;
		}
		return count;
	}
	void pushback(double value) {
		if (nullptr == head) {
			head = new Node(value, head);
			return;
		}
		Node* temp = head;

		while (nullptr != temp->next) {
			temp = temp->next;
		}
		temp->next = new Node(value);
	}

	void removeAt(int i) {
		try {
			if ((*this).length() <= i) throw i;
			if (0 == i) {
				Node* toDelete = head;
				head = head->next;
				delete toDelete;

			}
			else if ((*this).length()-1 == i) {
				delete (*this)[i];
				(*this)[i - 1]->next = nullptr;

			}
			else {
				Node* prev = (*this)[i - 1];
				Node* next = (*this)[i]->next;
				delete (*this)[i];
				prev->next = next;
			}
		}
		catch(int e){
			std::cout << "Out of bounds: " << e << std::endl;
		}

		
	}

	void printList() {
		for (int i = 0; i < this->length(); ++i) {
			std::cout << (*this)[i]->value << std::endl;
		}
	}
};


/*	Im folgenden Abschnitt befinden sich die Testcases,
	als auch die main und die run Methode, die diese ausführen.*/



class TestList {
private:
	void test_Listctor() {
		List testItem;
		assert(0 == testItem.length());
	}
	void test_pushbackOneElementIncLengthTo1() {
		List testItem;
		testItem.pushback(1.3);
		assert(1 == testItem.length());
	}
	void test_pushbackTwoElementIncLengthTo2() {
		List testItem;
		testItem.pushback(1.3);
		testItem.pushback(2.3);
		assert(2 == testItem.length());
	}

	void test_threeItemsDeleteOne() {
		List testItem;
		int len;
		testItem.pushback(1.0);
		testItem.pushback(2.1);
		testItem.pushback(3.2);

		testItem.removeAt(2);
		assert(2 == testItem.length());

	}

	void test_CopyConstructor() {
		List testItem;
		int len = 0;
		testItem.pushback(3.1415);
		testItem.pushback(6.2830);
		testItem.pushback(1.2345);

		List cpyItem = testItem;
		len = cpyItem.length();
		/*
		std::cout << "CALLED testItem output!" << std::endl;
		testItem.printList();
		std::cout << "CALLED cpyItem output!" << std::endl;
		cpyItem.printList();
		*/

		std::cout << "The length is: " << len << std::endl;
		
		for (int i = 0; i < testItem.length(); ++i) {
			std::cout << i << ". assert call" << std::endl;
			assert(&(testItem[i]->value) != &(cpyItem[i]->value));
			assert(testItem[i]->value == cpyItem[i]->value);
		}
		assert(testItem.length() == cpyItem.length());
		
	}

	void test_Output() {
		List testItem;
		int len = 0;
		testItem.pushback(3.1415);
		testItem.pushback(6.2830);
		testItem.pushback(1.2345);

		testItem.printList();
	}
public:
	void Run() {
		test_Listctor();
		test_pushbackOneElementIncLengthTo1();
		test_pushbackTwoElementIncLengthTo2();
		test_threeItemsDeleteOne();
		test_CopyConstructor();
		test_Output();
	}
};

int main() {
	TestList test;
	test.Run();
	
	assert(_CrtCheckMemory());
	assert(0 == _CrtDumpMemoryLeaks());
}

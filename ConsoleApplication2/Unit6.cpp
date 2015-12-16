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
		Node* current = head;

		while (nullptr != current) {
			Node* toDelete = current;
			current = current->next;
			delete toDelete;
		}
	}
	/*
	List(const List &liste) {
		List copy = new List();
		*copy = liste;
	}
	*/
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
		head = new Node(value, head);
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
};

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

	int test_threeItemsDeleteOne() {
		List testItem;
		int len;
		testItem.pushback(1.0);
		testItem.pushback(2.1);
		testItem.pushback(3.2);

		//len = testItem.length();
		//std::cout << len << std::endl;

		testItem.removeAt(5);

		//len = testItem.length();
		//std::cout << len << std::endl;

		return testItem.length();
	}
public:
	void Run() {
		test_Listctor();
		//test_pushbackOneElementIncLengthTo1();
		//test_pushbackTwoElementIncLengthTo2();
		test_threeItemsDeleteOne();
	}
};

int main() {
	TestList test;
	test.Run();
	
	assert(_CrtCheckMemory());
	assert(0 == _CrtDumpMemoryLeaks());
}

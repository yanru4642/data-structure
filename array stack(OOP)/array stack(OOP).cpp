#include <iostream>
using namespace std;

class ArrayStack
{
public:
	ArrayStack();
	~ArrayStack();
	bool isEmpty();
	void Push(int inElement);
	int Pop();

	void output();
private:
	int* stack;
	int top;
	int capacity;
	void DoubleCapacity();

};

int main(){
	ArrayStack stack1 = ArrayStack();

	cout << "Stack status: ";
	stack1.output();
	cout << "----------------------------" << endl;
	cout << "Pushing..."<< endl;
	stack1.Push(14);
	cout << "Stack status: ";
	stack1.output();
	cout << "----------------------------" << endl;
	cout << "Popping: "<< stack1.Pop() << endl;
	cout << "Stack status: ";
	stack1.output();
	cout << "----------------------------" << endl;
	cout << "Pushing..." << endl;
	stack1.Push(9);
	cout << "Stack status: ";
	stack1.output();
	cout << "----------------------------" << endl;
	cout << "Pushing..." << endl;
	stack1.Push(7);
	cout << "Stack status: ";
	stack1.output();
	cout << "----------------------------" << endl;
	cout << "Pushing..." << endl;
	stack1.Push(-3);
	cout << "Stack status: ";
	stack1.output();
	cout << "----------------------------" << endl;
	cout << "Popping: " << stack1.Pop() << endl;
	cout << "Stack status: ";
	stack1.output();
	cout << "----------------------------" << endl;
	cout << "Popping: " << stack1.Pop() << endl;
	cout << "Stack status: ";
	stack1.output();
	cout << "----------------------------" << endl;
	cout << "Popping: " << stack1.Pop() << endl;
	cout << "Stack status: ";
	stack1.output();
	cout << "----------------------------" << endl;
	cout << "Popping: " << endl;
	stack1.Pop();


	system("pause");
	return 0;
}

ArrayStack::ArrayStack() :top(-1), capacity(1) {
	stack = new int[capacity];
}
ArrayStack::~ArrayStack() {
	delete [] stack;
}
void ArrayStack::DoubleCapacity() {
	capacity *= 2;
	int* newStack = new int[capacity];
	for (int i = 0; i < capacity/2; i++){
		newStack[i] = stack[i];
	}
	delete [] stack;
	stack = newStack; // redirect stack to newStack
}
bool ArrayStack::isEmpty(){
	return (top == -1);
}
void ArrayStack::Push(int inElement) {
	//if stack if ful, double the capacity
	if (top==capacity-1){
		DoubleCapacity();
	}
	//update top
	top++;
	//put inElement into stack
	stack[top] = inElement;
}
int ArrayStack::Pop() {
	if (!isEmpty()){
		int popped;
		popped = stack[top];
		top--;
		return popped;
	}
	else {
		cout << "Error. Stack is empty!" << endl;
		exit(1);
	}
}
void ArrayStack::output() {
	if (!isEmpty()){
		for (int i = top; i >= 0; i--) {
			cout << stack[i] << " ";
		}
	}
	else {
		cout << "Empty ";
	}
	cout << "(top:" << top << ")" << endl;
}

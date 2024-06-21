#include <iostream>
using namespace std;

class MyIntStack {
	int p[10];
	int tos;
public:
	MyIntStack();
	bool push(int n);
	bool pop(int& n);
};
//스택 포인터 0
MyIntStack::MyIntStack() {
	for (int i = 0; i < 10; i++) {
		p[i] = 0;
	}
	tos = 0;
}
//스택이 꽉차면 리턴, 아니면 값 넣기
bool MyIntStack::push(int  n) {
	if (tos > 9) { return false; }
	p[tos++] = n;
	return true;
}

bool MyIntStack::pop(int&  n) {
	if (tos <= 0) { return false; }
	n = p[--tos];

	return true;
}

int main() {
	MyIntStack a;
	for (int i = 0; i < 11; i++) {
		if (a.push(i)) cout << i << ' ';
		else cout << endl << i + 1 << " 번쨰 stack full" << endl;
	}
	int n;
	for (int i = 0; i < 11; i++) {
		if (a.pop(n)) cout << n << ' ';
		else cout << endl << i + 1 << " 번쨰 stack empty";
	}
	cout << endl;
}
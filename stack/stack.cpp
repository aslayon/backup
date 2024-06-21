#include <iostream>
#include<cstdlib>
#include <random>
#include<iomanip>
using namespace std;


template <typename T>
class Tstack {
private:
	int SIZE_ = 10;
	T* stackT;
	int itop = -1;
	int isize = 0;
public:
	Tstack();
	~Tstack();
	int capacity() {
		cout << "스택 사이즈 _ " << isize * SIZE_ << " //요소 갯수 _ "<< itop+1 <<" //가용 공간 _ "<< (SIZE_ * isize) - (itop + 1)<<endl;
		return ((SIZE_ * isize) - (itop + 1));
	}
	int size() {
		cout << "스택 사이즈 _ " << isize * SIZE_<<endl;
		return isize * SIZE_;
	}
	void push(T value);
	void push(int location, T value);
	void push_range(T values[], int arrSize);
	void push_range(int location, T values[],int arrSize);
	T pop();
	T pop(int location);
	void printStack();
	bool isFull() {
		if (itop % SIZE_ == 9) return true;
		else return false;
	}
	bool isEmpty() {
		if (itop == -1) return true;
		else return false;
	}
	void sort();
};

template <typename T>
Tstack<T>::Tstack(){
	stackT = new T[SIZE_ * (++isize)];
	if (!stackT) {
		cout << "초기 스택 할당 실패" << endl;
		isize--;
	}
}

template <typename T>
Tstack<T>::~Tstack() {
	delete[] stackT;
}

template<typename T>
void Tstack<T>::push(T value){
	T* temp;
	if (isFull()) {//스택이 FULL 상태이면
		cout << "================================" << endl;
		cout << "Change Stack Size(inc)"<<SIZE_*isize <<">"<<SIZE_*(isize+1) << endl;
		cout << "================================" << endl;
		temp = stackT;
		stackT = new T[SIZE_ * (++isize)];
		if (!stackT) {
			cout << "메모리 할당 오류" << endl;
			return;
		}
		for (int i = 0; i < itop + 1; i++)stackT[i] = temp[i];
		stackT[++itop] = value;
		delete[] temp;
	}
	else {
		stackT[++itop] = value;
	}

}

template<typename T>
void Tstack<T>::push_range(T value[], int arrSize) {
	T* temp;
	int iReSize = (itop + 1 + arrSize) / SIZE_;
	if ((itop + 1 + arrSize) % SIZE_ != 0) {
			iReSize++;
	}
	
	if (isize == iReSize) {//사이즈 크기변경 필요없는 경우
		for (int i = 0; i < arrSize; i++) {
			stackT[++itop] = value[i];
		}
		
		return;
	}
	else {
		
		cout << "================================" << endl;
		cout << "Change Stack Size(inc)" << SIZE_ * isize << ">" << iReSize * SIZE_ << endl;
		cout << "================================" << endl;
		temp = stackT;
		stackT = new T[SIZE_ * iReSize];
		if (!stackT) {
			cout << "메모리 할당 오류" << endl;
			return;
		}
		for (int i = 0; i < itop + 1; i++) {
			stackT[i] = temp[i];
		}
		for (int i = 0; i < arrSize; i++) {
			stackT[++itop] = value[i];
		}
		isize = iReSize;
		delete[] temp;
	}
}


template<typename T>
void Tstack<T>::push(int location, T value) {
	T* temp;
	if (location < 0 || location > itop + 1) {
		cout<<"Push location Error\n";
		return;
	}
	if (isFull()) {
		cout << "================================" << endl;
		cout << "Change Stack Size(inc)" << SIZE_ * isize << ">" << SIZE_ * (isize + 1) << endl;
		cout << "================================" << endl;
		temp = stackT;
		stackT = new T[SIZE_ * (++isize)];
		if (!stackT) {
			cout << "메모리 할당 오류" << endl;
			return;
		}
		for (int i = 0; i < location; i++) {
			stackT[i] = temp[i];
		}
		stackT[location] = value;
		for (int i = location; i < itop + 1; i++) {
			stackT[i + 1] = temp[i];
		}
		itop++;
		
		delete[] temp;
	}
	else {
		if (location > itop) stackT[location] = value;  // top을 증가시킨 후 현재 top에 원소 삽입
		else {
			for (int i = itop; i >= location; i--) stackT[i + 1] = stackT[i];
			stackT[location] = value;
		}
		itop++;
	}
}

template <typename  T>
void Tstack<T>::push_range(int location,T value[], int arrSize) {
	
	if (location < 0 || location > itop + 1) {
		cout << "Push location Error\n";
		return;
	}
	int iReSize = (itop + 1 + arrSize) / SIZE_;
	if ((itop + 1 + arrSize) % SIZE_ != 0) {
		iReSize++;
	}
	
	if (isize == iReSize) {//사이즈 크기변경 필요없는 경우
		T* temp;
		int top = itop;
		int count = 0;
		temp = new T[isize * SIZE_];
		if (!temp) {
			cout << "메모리 할당 오류" << endl;
			return;
		}
		for (int i = location; i < itop+1; i++) {// location 부터 끝까지 템프에 저장
			temp[count++] = stackT[i];
		}
		count = 0;
		for (int i = location; i < location + arrSize; i++) {
			stackT[i] = value[count++]; //value 넣기
		}
		count = 0;
		for (int i = location + arrSize; i< itop + 1 + arrSize; i++) {
			stackT[i] = temp[count++];
		}
		itop += arrSize;
		delete[] temp;
		return;
	}
	else {
		T* temp;
		cout << "================================" << endl;
		cout << "Change Stack Size(inc)" << SIZE_ * isize << ">" << iReSize * SIZE_ << endl;
		cout << "================================" << endl;

		
		temp = stackT;
		capacity();
		
		stackT = new T[SIZE_ * iReSize];
		if (!temp) {
			cout << "메모리 할당 오류" << endl;
			return;
		}
		for (int i = location; i < itop+1; i++) {//location 부터 itop 까지 
			stackT[i + arrSize] = temp[i];
		}

		
		for (int i = 0; i < location; i++) {//0부터 location 까지 
			stackT[i] = temp[i];
		}
		
		int count = 0;
		for (int i = location; i < location + arrSize; i++) {//사이 채우기
			stackT[i] = temp[count++];
		}

		//cout << "오류" << endl;
		isize = iReSize;
		itop += arrSize;
		if(temp != NULL)
			delete[] temp;
		return;
	}
}



template <typename T>
void Tstack<T>::printStack() {
	int i;
	
	cout <<endl<< " STACK SIZE [" << SIZE_ * isize << "]" << endl;
	cout <<endl <<" STACK[";
	for (i = 0; i <= itop; i++) cout << stackT[i] << ",";
	cout << "]\n\n";
	
}

template <typename T>
T Tstack<T>::pop() {
	if (isEmpty()) {
		cout<<"\n\n Stack is Empty\n";
		return 0;
	}
	else {
		
		if (itop % 10 == 0) {
			
			T* temp, re;
			cout << "================================" << endl;
			cout << "Change Stack Size(inc)" << SIZE_ * isize << ">" << SIZE_ * (isize - 1) << endl;
			cout << "================================" << endl;
			re = stackT[itop];
			temp = stackT;
			stackT = new T[SIZE_ * (--isize)];
			if (!stackT) {
				cout << "메모리 할당 오류" << endl;
				return -1;
			}
				for (int i = 0; i < itop; i++) {
					stackT[i] = temp[i];
				}
			itop--;
			cout << "Popped " << re << endl;
			delete[] temp;
			return re;

		}
		else {
			
			T* temp, re;
			re = stackT[itop--];
			cout << "Popped " << re << endl;
			return re; 
			
		}
	}
}
template <typename T>
T Tstack<T>::pop(int location) {
	if (isEmpty()) {
		cout << "\n\n Stack is Empty\n";
		return 0;
	}
	else {
		
		if (location < 0 || location > itop) {
			cout << "Pop location Error" << endl;
			return 0;
		}
		if (itop % 10 == 0) {
			int i;
			T re, * temp;
			cout << "================================" << endl;
			cout << "Change Stack Size(inc)" << SIZE_ * isize << ">" << SIZE_ * (isize - 1) << endl;
			cout << "================================" << endl;
			re = stackT[location];
			temp = stackT;
			stackT = new T[SIZE_ * (--isize)];
			if (!stackT) {
				cout << "메모리 할당 오류" << endl;
				return -1;
			}
			for (i = 0; i < location; i++) {
				stackT[i] = temp[i];
			}
			for (i = location; i < itop; i++) {
				stackT[i] = temp[i + 1];
			}
			itop--;
			cout << "Popped " << re << endl;
			delete[] temp;
			return re;
		}
		else {
			if (location < 0 || location > itop) {
				cout << "Pop location Error" << endl;
				return 0;
			}
			int i;
			T re, * temp;
			re = stackT[location];
			for (i = location; i < itop; i++) {
				stackT[i] = stackT[i + 1];
				
			}
			itop--;
			cout << "Popped " << re << endl;
			return re;
		}
	}
}

template <typename T>
void Tstack<T>::sort() {//선택정렬
	cout << "================================" << endl;
	cout << "Sort Start" <<  endl;
	cout << "================================" << endl;
	int least;
	for (int i = 0; i < itop ; i++) {
		least = i;
		for (int j = i+1; j < itop + 1; j++) {
			if (stackT[j] < stackT[least]) {
				least = j;
			}
		}
		if (least != i) {
			T temp;
			temp = stackT[i];
			stackT[i] = stackT[least];
			stackT[least] = temp;
		}
	}
}




int main() {
	Tstack<int> intStack;
	int arr[] = { 5, 2, 8, 1, 9 };

	cout << "Push single values:" << endl;
	intStack.push(3);
	intStack.push(7);
	intStack.push(2, 10); // Push 10 at index 2
	intStack.printStack();

	cout << "\nPush array values:" << endl;
	intStack.push_range(arr, 5);
	intStack.printStack();

	cout << "\nPush array values at index 3:" << endl;
	intStack.push_range(3, arr, 5);
	intStack.printStack();

	cout << "\nPop elements:" << endl;
	intStack.pop();
	intStack.pop(4); // Pop element at index 4
	intStack.printStack();

	cout << "\nSort the stack:" << endl;
	intStack.sort();
	intStack.printStack();

	cout << "\nStack capacity: " << intStack.capacity() << endl;
	cout << "Stack size: " << intStack.size() << endl;

	// char 형 테스트 케이스
	Tstack<char> charStack;
	char charArr[] = { 'a', 'b', 'c', 'd', 'e' };

	cout << "\nPush char array values:" << endl;
	charStack.push_range(charArr, 5);
	charStack.printStack();

	cout << "\nPush char array values at index 2:" << endl;
	charStack.push_range(2, charArr, 5);
	charStack.printStack();

	cout << "\nPop char elements:" << endl;
	charStack.pop();
	charStack.pop(3); // Pop element at index 3
	charStack.printStack();

	cout << "\nSort char stack:" << endl;
	charStack.sort();
	charStack.printStack();

	cout << "\nChar stack capacity: " << charStack.capacity() << endl;
	cout << "Char stack size: " << charStack.size() << endl;

	return 0;
}
#include<iostream>
#include<string>
using namespace std;

int move_r() {
	string s;
	cout << "문자열 입력하세요 :";
	getline(cin, s);
	int len = s.length();
	string a, b;
	for (int i = 0; i < len; i++) {
		
		a = s.substr(len - 1);
		b = s.substr(0, len - 1);
		s = a + b;
		cout << a + b << endl;
	}
	return 0;
}

int sum__() {
	string s;
	cout << "덧셈식 입력하세요\n" ;
	getline(cin, s,'\n');
	/*
		시작점
	*/
	string sub;
	int a = 0;
	int b = 0;
	int c = 0;
	int sum = 0;
	while (1) {
		b = s.find('+',a);
		if (b == -1) {
			sub = s.substr(a);
			if (sub == "")break;
			c = stoi(sub);
			cout << c << endl;
			sum += c;
			break;
		}
		sub = s.substr(a, b-a);
		c = stoi(sub);
		cout << c << endl;
		sum += c;
		a = b + 1;
	}
	cout << "합은 = " << sum << endl;
	return sum;
}

int ASDF() {
	string s;
	getline(cin, s, '&');
	cin.ignore();
	string f, w;
	cout << endl << "find: ";
	getline(cin, f);
	cout << endl << "대체 단어 : ";
	getline(cin, w);
	int start = 0;
	int fin;
	while (1) {
		fin = s.find(f, start);

		if (fin == -1)break;
		int len = f.length();
		s.replace(fin, f.length(), w);
		start = fin + w.length();
	}
	cout << endl << s;
	return 0;
}

int main() {
	for (int n = 0; n < 4; n++) {
		char a = '*';
		for (int j = 0; j < n+1; j++) {
			cout << a;
		}
		cout << endl;
	}
}  
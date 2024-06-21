#include<iostream>
using namespace std;

/*
	테이블 만들기.
	

	멤버:
	table 5*5   -> string 으로 할 예정 (예외 조건 때문에  Q/Z)
	num = 0   -> 테이블 인덱수 갯수
	except -> Q/Z 가 뭔지 넣을거

	함수:
	요소 넣기
	
	


	암호문(2글자씩 끊어 넣기)

	인풋 넣기_
	조건1. 같은 글자면 x 넣기
	조건2. except 면 x 넣기
	조건3. 최종 글자수 혼수면 끝에 x 넣기

	결과
	조건1. i,j 모두 다를경우 ab  cd  -> ad  cb
	조건 2. 높이가 같을 경우 ab ac -> a,(b+1)%5 a,(c+1)%5
	조건 3.  _               ab cb -> a+1,b (c+1)%5,b
	
	멤버:
	input 초기
	output 결과
	count = 0
	a_i  = -1
	a_j  = -1

	b_i  = -1
	b_j  = -1

	함수:
	fill_input(string) 
		for (0 부터 string 길이까지 i = i+2)  //짝수 일때만
			만약 i == i+1  insert(i, 'X')

		만약 string 길이가 홀수면 append('x')

	fill_output() //////테이블 만들기와 프렌드
		while(count <input.len)
			for(i, 5, ++)
				for(j,5,++)
					for(k, table[i][j] 의 길이까지)
						만약 input 의 글자가 table[i],[j] 와 같으면 a_i = i  a_j = j
			
			count++

			for(i, 5, ++)
				for(j,5,++)
					for(k, table[i][j] 의 길이까지)
						만약 input 의 글자가 table[i],[j] 와 같으면 b_i = i  b_j = j	
			count++
			조건1
			조건2
			조건3

		


*/



class table {
	string t[5][5];
	int num;
	string except = "QZ";
	string input;
	string output;
public:
	void printt();
	void filltable_with_key(string& key);
	void filltable(string& key);
	void printin();
	void fill_input(string& str);
	void printout();
	void fill_output();
};

void table::printt() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << t[i][j] << " ";
		}
		cout << endl;
	}
}


void table::printin() {
	cout << "원본 :\t\t" << input << endl;
}


void table::printout() {
	cout << "암호화 :\t" << output << endl;
}


void table::filltable_with_key(string& key) {
	int keyptr = 0;  //key pointer
	string tmp = key;
	string key_tmp;


	if (key.empty()) {
		cout << "키값 없음" << endl;
		return;
	}

	num = 0;   //초기화

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			t[i][j] = "";
		}
	}

	while (keyptr < key.length()) {

		key_tmp = key.substr(keyptr, 1);
		if (key_tmp == except.substr(0, 1) || key_tmp == except.substr(1, 1)) {   //만약 조건에 들어가면 바꿔치기
			key_tmp = except;
		}
		keyptr++;
		
		if (num == 0) {
			
			t[0][0] = key_tmp;
			cout << key_tmp << "추가" << endl;
			num++;
			continue;
		}

		int flag = 0;  //중복

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				
				if (t[i][j] == key_tmp) {      //중복
					cout << key_tmp << "중복" << endl;
					flag = 1;
					break;
				}


				
			}
			if (flag == 1)  break;   
		}

		if (flag == 0) {
			
			cout << key_tmp << "추가" << endl;
			t[num/5][num%5] = key_tmp;  //삽입
			num++;
		}
	}
	
	
	
}



void table::filltable(string& key){

	filltable_with_key(key);

	char alpha = 65;

	int flag = 0;
	int blank_flag = 0;
	while (alpha < 91 && num<25) {
		string alphabet(1, alpha++);
		flag = 0;
		blank_flag = 0;
		cout << alphabet << "탐색 시작" << endl;

		if (alphabet == except.substr(0, 1) || alphabet == except.substr(1, 1)) {   //만약 조건에 들어가면 바꿔치기
			alphabet = except;
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (t[i][j] == alphabet) {
					flag = 1;  break;
				}																														//중복 탐색 종료
				if (t[i][j] == "") {
					
					blank_flag = 1;
				}
			}
			if (flag == 1) break;
		}
		if (blank_flag == 1) {
			cout << alphabet << "추가" << endl;
			t[num / 5][num % 5] = alphabet;  //삽입
			num++;
		}
	}
	
}



void table::fill_input(string& str) {
	if (str.empty()) {
		cout << "입력 없음" << endl;
		return;
	}
	int len = 0;
	string tmp = str;
	len = tmp.length();
	for (int i = 0; i < len; i=i+2) {
		
		cout << tmp.substr(i, 1) << "," << tmp.substr(i + 1, 1) << "비교" << endl;
		if (tmp.substr(i, 1) == tmp.substr(i + 1, 1)) {
			cout << "중복 확인 X 삽입" << endl;
			tmp.insert(i+1, "X");
			len = tmp.length();
		}
	}

	if (tmp.length()%2 ==1) {
		tmp.append("X");
		cout << "끝, 홀수 X 삽입" << endl;

	}																 //끝이고 홀수면 X 추가

	input = tmp;
}


/*
	조건1. i,j 모두 다를경우 ab  cd  -> ad  cb
	조건 2. 높이가 같을 경우 ab ac -> a,(b+1)%5 a,(c+1)%5
	조건 3.  _               ab cb -> a+1,b (c+1)%5,b
*/

void table::fill_output() {
	int a_i;
	int a_j;
	int b_i;
	int b_j;
	
	int count = 0;

	string a;
	string b;
	string tmp = input;
	output = "";

	while (count < input.length()) {
		int aflag = 0;										//a  찾음
		int bflag = 0;										//b  찾음

		a = tmp.substr(count++, 1);
		if (a == except.substr(0,1) || a ==except.substr(1, 1)) {   //만약 조건에 들어가면 바꿔치기
			a =except;
		}
		b = tmp.substr(count++, 1);
		if (b == except.substr(0, 1) || b ==except.substr(1, 1)) {   //만약 조건에 들어가면 바꿔치기
			b = except;
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (a == t[i][j]) {
					aflag =1;
					a_i = i;
					a_j = j;
				}
				if (b == t[i][j]) {
					bflag = 1;
					b_i = i;
					b_j = j;
				}
				if (aflag == 1 && bflag == 1) {
					break;
				}
			}
			if (aflag == 1 && bflag == 1) {
				break;
			}
		}
		if (a_i != b_i && a_j != b_j) {								//조건 1
			output.append(t[a_i][b_j]);
			output.append(t[b_i][a_j]);
		}
		if (a_i == b_i && a_j != b_j) {
			output.append(t[a_i][(a_j + 1) % 5]);
			output.append(t[b_i][(b_j + 1) % 5]);
		}
		if (a_i != b_i && a_j == b_j) {
			output.append(t[(a_i + 1) % 5][a_j]);
			output.append(t[(b_i + 1) % 5][b_j]);
		}
	}
}


int main() {
	table myTable;
	string a = "ASSASSINATOR";
	myTable.filltable(a);
	myTable.printt();
	string in = "BECAREFULFORASSASSINATOR";
	myTable.fill_input(in);
	myTable.printin();
	myTable.fill_output();
	myTable.printout();
	return 0;
}







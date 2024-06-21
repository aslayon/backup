#include<iostream>
using namespace std;

/*
	���̺� �����.
	

	���:
	table 5*5   -> string ���� �� ���� (���� ���� ������  Q/Z)
	num = 0   -> ���̺� �ε��� ����
	except -> Q/Z �� ���� ������

	�Լ�:
	��� �ֱ�
	
	


	��ȣ��(2���ھ� ���� �ֱ�)

	��ǲ �ֱ�_
	����1. ���� ���ڸ� x �ֱ�
	����2. except �� x �ֱ�
	����3. ���� ���ڼ� ȥ���� ���� x �ֱ�

	���
	����1. i,j ��� �ٸ���� ab  cd  -> ad  cb
	���� 2. ���̰� ���� ��� ab ac -> a,(b+1)%5 a,(c+1)%5
	���� 3.  _               ab cb -> a+1,b (c+1)%5,b
	
	���:
	input �ʱ�
	output ���
	count = 0
	a_i  = -1
	a_j  = -1

	b_i  = -1
	b_j  = -1

	�Լ�:
	fill_input(string) 
		for (0 ���� string ���̱��� i = i+2)  //¦�� �϶���
			���� i == i+1  insert(i, 'X')

		���� string ���̰� Ȧ���� append('x')

	fill_output() //////���̺� ������ ������
		while(count <input.len)
			for(i, 5, ++)
				for(j,5,++)
					for(k, table[i][j] �� ���̱���)
						���� input �� ���ڰ� table[i],[j] �� ������ a_i = i  a_j = j
			
			count++

			for(i, 5, ++)
				for(j,5,++)
					for(k, table[i][j] �� ���̱���)
						���� input �� ���ڰ� table[i],[j] �� ������ b_i = i  b_j = j	
			count++
			����1
			����2
			����3

		


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
	cout << "���� :\t\t" << input << endl;
}


void table::printout() {
	cout << "��ȣȭ :\t" << output << endl;
}


void table::filltable_with_key(string& key) {
	int keyptr = 0;  //key pointer
	string tmp = key;
	string key_tmp;


	if (key.empty()) {
		cout << "Ű�� ����" << endl;
		return;
	}

	num = 0;   //�ʱ�ȭ

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			t[i][j] = "";
		}
	}

	while (keyptr < key.length()) {

		key_tmp = key.substr(keyptr, 1);
		if (key_tmp == except.substr(0, 1) || key_tmp == except.substr(1, 1)) {   //���� ���ǿ� ���� �ٲ�ġ��
			key_tmp = except;
		}
		keyptr++;
		
		if (num == 0) {
			
			t[0][0] = key_tmp;
			cout << key_tmp << "�߰�" << endl;
			num++;
			continue;
		}

		int flag = 0;  //�ߺ�

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				
				if (t[i][j] == key_tmp) {      //�ߺ�
					cout << key_tmp << "�ߺ�" << endl;
					flag = 1;
					break;
				}


				
			}
			if (flag == 1)  break;   
		}

		if (flag == 0) {
			
			cout << key_tmp << "�߰�" << endl;
			t[num/5][num%5] = key_tmp;  //����
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
		cout << alphabet << "Ž�� ����" << endl;

		if (alphabet == except.substr(0, 1) || alphabet == except.substr(1, 1)) {   //���� ���ǿ� ���� �ٲ�ġ��
			alphabet = except;
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (t[i][j] == alphabet) {
					flag = 1;  break;
				}																														//�ߺ� Ž�� ����
				if (t[i][j] == "") {
					
					blank_flag = 1;
				}
			}
			if (flag == 1) break;
		}
		if (blank_flag == 1) {
			cout << alphabet << "�߰�" << endl;
			t[num / 5][num % 5] = alphabet;  //����
			num++;
		}
	}
	
}



void table::fill_input(string& str) {
	if (str.empty()) {
		cout << "�Է� ����" << endl;
		return;
	}
	int len = 0;
	string tmp = str;
	len = tmp.length();
	for (int i = 0; i < len; i=i+2) {
		
		cout << tmp.substr(i, 1) << "," << tmp.substr(i + 1, 1) << "��" << endl;
		if (tmp.substr(i, 1) == tmp.substr(i + 1, 1)) {
			cout << "�ߺ� Ȯ�� X ����" << endl;
			tmp.insert(i+1, "X");
			len = tmp.length();
		}
	}

	if (tmp.length()%2 ==1) {
		tmp.append("X");
		cout << "��, Ȧ�� X ����" << endl;

	}																 //���̰� Ȧ���� X �߰�

	input = tmp;
}


/*
	����1. i,j ��� �ٸ���� ab  cd  -> ad  cb
	���� 2. ���̰� ���� ��� ab ac -> a,(b+1)%5 a,(c+1)%5
	���� 3.  _               ab cb -> a+1,b (c+1)%5,b
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
		int aflag = 0;										//a  ã��
		int bflag = 0;										//b  ã��

		a = tmp.substr(count++, 1);
		if (a == except.substr(0,1) || a ==except.substr(1, 1)) {   //���� ���ǿ� ���� �ٲ�ġ��
			a =except;
		}
		b = tmp.substr(count++, 1);
		if (b == except.substr(0, 1) || b ==except.substr(1, 1)) {   //���� ���ǿ� ���� �ٲ�ġ��
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
		if (a_i != b_i && a_j != b_j) {								//���� 1
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







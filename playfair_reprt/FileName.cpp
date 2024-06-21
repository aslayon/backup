#define _CRT_SECURE_NO_WARNINGS?

#include <iostream>
#include<string.h>
using namespace std;

class Playfair {
	char mTable[25];
	string mPair;
	string mKey;
public:
	Playfair(string mKey, string mPair);
	void makeTable();
	void showTable();
	string makeEncryption(string mEncryption);
};

Playfair::Playfair(string mKey, string mPair) {
	this->mKey = mKey;
	this->mPair = mPair;
}

void Playfair::makeTable() {
	
		int keyptr = 0;  //key pointer
		string tmp = mKey;
		string key_tmp;
		char* pair;


		if (mKey.empty()) {
			cout << "Ű�� ����" << endl;
			return;
		}

		int num = 0;   //�ʱ�ȭ
		char letter_case;

		for (int i = 0; i < 25; i++) {
			
				mTable[i] = '@';
			
		}

		while (keyptr < mKey.length()) {

			key_tmp = mKey.substr(keyptr, 1);
			if (key_tmp == mPair.substr(0, 1) || key_tmp == mPair.substr(2, 1)) {   //���� ���ǿ� ���� �ٲ�ġ��
				key_tmp = '*';
			}
			keyptr++;

			letter_case = key_tmp[0];
			if (letter_case >= 'a' && letter_case <= 'z') {
				letter_case = letter_case - 32;
			}

			if (num == 0) {

				mTable[num] = letter_case;
				cout << letter_case << "�߰�" << endl;
				num++;
				continue;
			}

			int flag = 0;  //�ߺ�

			for (int i = 0; i < 25; i++) {
				

					if (mTable[i] == letter_case) {      //�ߺ�
						cout << letter_case << "�ߺ�" << endl;
						flag = 1;
						break;
					}



				
				
			}

			if (flag == 0) {

				cout << letter_case << "�߰�" << endl;
				mTable[num] = letter_case;  //����
				num++;
			}
		}
		char alpha = 65; // alpha = A
		while (alpha <91 && num <25) {             //Z �� �Ѱų� ���̺� ��� ����  25(full) �̸� �ݺ� ����

			string alphabet(1, alpha++);
			cout << mPair.substr(0, 1) <<mPair.substr(2, 1);
			if (alphabet == mPair.substr(0, 1) || alphabet == mPair.substr(2, 1)) {   //���� ���ǿ� ���� �ٲ�ġ��
				letter_case = '*';
			}
			
			else letter_case = alphabet[0];


			if (letter_case >= 'a' && letter_case <= 'z') {
				letter_case = letter_case - 32;
			}

			printf("%c", letter_case);

			int flag = 0;  //�ߺ�

			for (int i = 0; i < 25; i++) {


				if (mTable[i] == let ter_case) {      //�ߺ�
					cout << letter_case << "�ߺ�" << endl;
					flag = 1;
					break;
				}





			}

			if (flag == 0) {

				cout << letter_case << "�߰�" << endl;
				mTable[num] = letter_case;  //����
				num++;
			}
		}
		


}

void Playfair::showTable() {
	cout << endl;
	for (int i = 0; i < 25; i++) {
		cout << mTable[i] << '\t';
		if (i % 5 == 4) {
			cout << endl <<endl;
		}
	}

}

string Playfair::makeEncryption(string mEncryption) {
	return NULL;
}


int main() {
	Playfair pfair("assasinator", "q/z");
	pfair.makeTable();
	pfair.showTable();
}
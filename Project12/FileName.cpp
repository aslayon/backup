

#include <iostream>
#include<string>
#include<cctype>  //for upper lower
#include <fstream>

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

	int keyptr = 0;								//key pointer
	string tmp = mKey;
	string key_tmp;

	

	if (mKey.empty()) {
		cout << "키값 없음" << endl;			//키값이 없을땐 종료
		return;
	}

	for (int i = 0; i < mPair.length(); i++) {
		mPair[i] = toupper(mPair[i]);					//페어도 대문자로 통일
	}

	int num = 0;   //초기화
	char letter_put;									//테이블에 넣을 요소

	for (int i = 0; i < 25; i++) {
											//테이블 초기화
		mTable[i] = '@';

	}

	while (keyptr < mKey.length()) {

		key_tmp = mKey.substr(keyptr, 1);


		letter_put = key_tmp[0];
		if (letter_put >= 'a' && letter_put <= 'z') {
			letter_put = letter_put - 32;							//소문자면	대문자로
		}

		if (letter_put == mPair[0] || letter_put == mPair[2]) {   //만약 조건에 들어가면 바꿔치기
			key_tmp = '*';
		}
		keyptr++;

		letter_put = key_tmp[0];
		if (letter_put >= 'a' && letter_put <= 'z') {
			letter_put = letter_put - 32;
		}

		if (num == 0) {

			mTable[num] = letter_put;
			cout << letter_put << "추가" << endl;
			num++;
			continue;
		}

		int flag = 0;  //중복

		for (int i = 0; i < 25; i++) {


			if (mTable[i] == letter_put) {      //중복
				cout << letter_put << "중복" << endl;
				flag = 1;
				break;
			}





		}

		if (flag == 0) {

			cout << letter_put << "추가" << endl;
			mTable[num] = letter_put;  //삽입
			num++;
		}
	}
	char alpha = 65; // alpha = A
	while (alpha < 91 && num < 25) {             //Z 를 넘거나 테이블 요소 수가  25(full) 이면 반복 종료

		string alphabet(1, alpha++);

		if (alphabet == mPair.substr(0, 1) || alphabet == mPair.substr(2, 1)) {   //만약 조건에 들어가면 바꿔치기
			letter_put = '*';
		}

		if (alphabet == mPair.substr(0, 1) || alphabet == mPair.substr(2, 1)) {   //만약 조건에 들어가면 바꿔치기
			letter_put = '*';
		}



		else letter_put = alphabet[0];


		if (letter_put >= 'a' && letter_put <= 'z') {
			letter_put = letter_put - 32;
		}



		int flag = 0;  //중복

		for (int i = 0; i < 25; i++) {


			if (mTable[i] == letter_put) {      //중복
				cout << letter_put << "중복" << endl;
				flag = 1;
				break;
			}





		}

		if (flag == 0) {

			cout << letter_put << "추가" << endl;
			mTable[num] = letter_put;  //삽입
			num++;
		}
	}



}

void Playfair::showTable() {
	cout << endl;
	for (int i = 0; i < 25; i++) {
		cout << mTable[i] << '\t';
		if (i % 5 == 4) {
			cout << endl << endl;
		}
	}

}

string Playfair::makeEncryption(string mEncryption) {

	for (int i = mEncryption.length(); i >= 0; --i) {
		if (mEncryption[i] == ' ') {
			mEncryption.erase(i,1);
		}
	}

	string input;						//x 를 삽입한 암호화 되기 전 
	string output_whole = "";
	if (mEncryption.empty()) {
		cout << "입력 없음" << endl;
		return 0;
	}

	int LastFlag = 0;

	int startindex = 0;

	int line = 0;
	

	while (startindex < mEncryption.length()) {

		line++;

		int fIndex = mEncryption.find('.', startindex);

		if (fIndex == -1) {
			string part = mEncryption.substr(startindex);
			if (part == "")break;
			input = part;

			LastFlag = 1;
		}
		else {
			int count_1 = fIndex - startindex;
			string part = mEncryption.substr(startindex, count_1);

			input = part;
			startindex = fIndex + 1;
		}


		string output = "";
		int len = 0;
		string tmp = input;
		len = tmp.length();
		string front, back;

		for (int i = 0; i < len; i = i + 2) {
			front = tmp.substr(i, 1);
			if (front[0] >= 'a' && front[0] <= 'z') front[0] = toupper(front[0]);
			back = tmp.substr(i + 1, 1);
			if (back[0] >= 'a' && back[0] <= 'z') back[0] = toupper(back[0]);		//대문자로 변경




			if (front == back || front == mPair.substr(0, 1) || front == mPair.substr(2, 1)) {   //앞뒤 같거나  페어와 겹치면


				tmp.insert(i + 1, "X");
				cout << tmp << endl;
				len = tmp.length();
			}
		}

		if (tmp.length() % 2 == 1) {
			tmp += 'X';

		}																 //끝이고 홀수면 X 추가

		cout << endl<<line << "번째 문장:"<<endl;
		cout << tmp << endl;


		input = tmp;




		string pair = "*";
		string a;
		string b;
		tmp = input;               //tmp 는 이제부터 input
		


		/*
		조건1. i,j 모두 다를경우 ab  cd  -> ad  cb
		조건 2. 높이가 같을 경우 ab ac -> a,(b+1)%5 a,(c+1)%5
		조건 3.  _               ab cb -> a+1,b (c+1)%5,b

		*/
		int count = 0;
		int a_i = 0;
		int a_j = 0;
		int b_i = 0;
		int b_j = 0;
		int frontflag = 0;
		int backflag = 0;
		while (count < input.length()) {
			int aflag = 0;										//a  찾음
			int bflag = 0;										//b  찾음

			front = tmp.substr(count, 1);
			if (a == mPair.substr(0, 1) || a == mPair.substr(2, 1)) {   //만약 조건에 들어가면 바꿔치기
				a = pair;

			}
			if (front[0] >= 'a' && front[0] <= 'z') { //대소문자 
				front[0] = toupper(front[0]);
				frontflag = 1;
			}
			back = tmp.substr(count + 1, 1);
			if (b == mPair.substr(0, 1) || b == mPair.substr(2, 1)) {   //만약 조건에 들어가면 바꿔치기
				b = pair;

			}
			if (back[0] >= 'a' && back[0] <= 'z') { //대소문자 
				back[0] = toupper(back[0]);
				backflag = 1;
			}



			for (int i = 0; i < 25; i++) {

				if (front[0] == mTable[i]) {
					aflag = 1;
					a_i = i / 5;
					a_j = i % 5;

				}
				if (back[0] == mTable[i]) {
					bflag = 1;
					b_i = i / 5;
					b_j = i % 5;

				}
				if (aflag == 1 && bflag == 1) {
					break;
				}


			}
			if (a_i != b_i && a_j != b_j) {								//조건 1
				output += (mTable[(a_i * 5) + b_j]);
				output += (mTable[(b_i * 5) + a_j]);
			}
			if (a_i == b_i && a_j != b_j) {

				output += (mTable[(a_i) * 5 + (a_j + 1) % 5]);
				output += (mTable[(b_i) * 5 + (b_j + 1) % 5]);

			}
			if (a_i != b_i && a_j == b_j) {
				output += (mTable[((a_i + 1) % 5) * 5 + a_j]);
				output += (mTable[((b_i + 1) % 5) * 5 + b_j]);
			}
			if (frontflag == 1) {
				output[count] = tolower(output[count]);
				frontflag = 0;
			}
			if (backflag == 1) {
				output[count + 1] = tolower(output[count + 1]);
				backflag = 0;
			}
			count += 2;
		}
		output += '.';
		count++;
		cout << endl <<"암호화 결과: " << output << endl;

		cout << "/////////////////////////////////////////////////////////////" << endl;

		output_whole += output;
		
		if (LastFlag == 1) {
			break;
		}
	}
	return output_whole;
}


int main() {
	cout << "모드를 선택하세요.\n" << "1. 콘솔로부터 입력   2. 파일로부터 입력 \n Mode:";
	int mode;
	cin >> mode;
	cin.ignore(1);	//mode 입력 값 지워주기.
	if (mode == 1) {
		string key;
		cout << "키값 ?(assassinator) :";
		getline(cin, key);
		string pair;
		cout << "페어 ? (q/z) : ";
		getline(cin, pair);
		Playfair pfair(key, pair);
		pfair.makeTable();
		pfair.showTable();
		string a;
		cout << "string :";
		getline(cin, a);
		string result = pfair.makeEncryption(a);
		cout << endl<<"전체 번역 결과" << result<<endl<<endl;
	}
	if (mode == 2) {


		string key;

		cout << "\n키값 ?(assassinator) :";
		getline(cin, key);

		string pair;
		cout << "\n페어 ? (q/z) : ";
		getline(cin, pair);

		Playfair pfair(key, pair);
		pfair.makeTable();
		pfair.showTable();
		ifstream fin;
		fin.open("input.txt");
		if (!fin) {	//파일 열기 실패
			cout << "파일을 열 수 없습니다." << endl;
			return 0;


		}
		string input;
		getline(fin, input);
		string result = pfair.makeEncryption(input);
		cout << endl<<"전체 번역 결과" << result<<endl<<endl;
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include <stdlib.h>
#include "LinkedList_int.h"
#include <CoreWindow.h>
#include <windows.h>
#include <limits.h>
#define Max 10
using namespace std;

void Create(LinkedList** _ptList);																		//�������� ����
void Destroy(LinkedList** _ptList);																		//�������� ����
NodeList* GetNodeList(LinkedList** _NodeList, string String);											//��帮��Ʈ(ȯ�� �̸�) ����
Node* GetNode(int _iObject, string String);																// ��� ����
int Read(LinkedList* _ptList, unsigned int i);															// ���ϴ� ȯ���� ���� �б�
void Traversal(LinkedList* _ptList);																	//��� ȯ�� �б�
void AppendFromHead(LinkedList* _ptList, unsigned int i, int _iObject, string String);					// ȯ���� ��忡 �׸� �߰�
Node* AppendFromTail(LinkedList* _ptList, unsigned int i, int _iObject, string String);					//ȯ���� ���Ͽ� �׸� �߰�
Node* AppendFromTail_(LinkedList* _ptList, string Date);												// ȯ�� �߰�
Node* InsertBefore(LinkedList* _ptList, unsigned int k, Node* _ptNode, int Object, string String);		//���ϴ� ȯ���� ���ϴ� �׸� �տ� ���ο� �׸� �߰�
Node* InsertAfter(LinkedList* _ptList, unsigned int k, Node* _ptNode, int Object, string String);		//-- �ڿ� �߰�
Node* Insert_Count_Before(LinkedList* _ptList, unsigned int k, int Count, int Object, string String);	//���ϴ� ȯ���� ���ϴ� ��ġ �տ� �׸� �߰�
Node* Insert_Count_After(LinkedList* _ptList, unsigned int k, int Count, int Object, string String);	//���ϴ� ȯ���� ���ϴ� ��ġ �ڿ� �׸� �߱�
Node* DeleteFromHead(LinkedList* _ptList, unsigned int k);												//���ϴ� ȯ����  ����� �׸� ����
Node* DeleteFromTail(LinkedList* _ptList, unsigned int k);												// -- ������ �׸� ����
Node* Delete(LinkedList* _ptList, Node* _ptNode, unsigned int k);										//���ϴ� ȯ���� ���ϴ� �׸� ����(Node * �� ���ڷ�)
Node* DeleteNode_Count(LinkedList* _ptList, unsigned int k, int count);									//���ϴ� ȯ���� ���ϴ� ��ġ�� �׸� ����(���° �׸����� int �� ���ڷ�)
void DeleteAll(LinkedList* _ptList, unsigned int k);													//���ϴ� ȯ���� ��� �׸� ����
Node* Modify(LinkedList* _ptList, Node* _ptNode, unsigned int k, int iObject, string String);			//���ϴ�ȯ���� ���ϴ� �׸� ����
Node* Modify_String(LinkedList* _ptList, Node* _ptNode, unsigned int k, string String);					//ȯ���� �׸��� string ����
Node* Modify_by_Count_String(LinkedList* _ptList, unsigned int k, int count, string String);			//���ڸ� int �� �޾Ƽ� string ����
Node* Modify_Object(LinkedList* _ptList, Node* _ptNode, unsigned int k, int iObject); 					//ȯ���� �׸��� int ����
Node* Modify_by_Count_Object(LinkedList* _ptList, unsigned int k, int count, int iObject);				//���ڸ� int �� �޾Ƽ� int ����(�� ����)
void LinearSearchByDuplicate_KyeWord_String(LinkedList* _ptList, string String, int* _resultSize, Node*** _resultArray);//Ű���带 �޾Ƽ� �˻�(����� -> ����|| ���||�� ������ �˻�
void SortBySelection_Object(LinkedList* _ptList);														//�� ȯ���� �׸���� int ���� ����

void SortBySelection_String(LinkedList* _ptList);														// string ���� ����
NodeList* DeleteNode_Count_k(LinkedList* _ptList, int count);											//���ϴ�ȯ�ڸ� ����
Node* Modify_by_Count(LinkedList* _ptList, unsigned int k, int count, int iObject, string String);		//int �� ���°���� �޾Ƽ� ����
Node* Modify_Date(LinkedList* _ptList, unsigned int k, string String);// ȯ���� �̸� ����
void cur(short x, short y)		//ȭ���� ���ϴ� x, y��ǥ�� ����
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}





int main() {

	long long L = (-2147483647 - 1);
	int R = 2147483647;
	char Cont;
	int flag = 0;
	LinkedList* Lists = { NULL };
	string String = "asdfsa";
	long long Num_tmp = 0;
	long long Num_tmp2 = 0;
	long long Num_tmp3 = 0;
	Node* Node_tmp = NULL;
	int SearchResultSize;
	Node** SearchSortResultArr;
	COORD pos = { 0,0 };
	int k = 0;
	Create(&Lists);

	while (flag == 0) {



		int Selection_flag = 0;
		int selection_flag2 = 0;

		printf("���� ����. ����Ʈ(��������) -> ȯ��(���͸�) -> �׸�(������)");
		printf("\n\n");
		long long Num_tmp = 0;
		long long Num_tmp2 = 0;
		long long Num_tmp3 = 0;
		if (!Node_tmp) Node_tmp == NULL;

		printf("ȯ��(���͸�)�� _\n");

		if (Lists != NULL) {
			int count = 0;
			printf("\nList  _");
			if (!Lists->m_pHead) { printf("Empty"); }
			NodeList* curr = Lists->m_pHead;
			while (count < Lists->m_uCount) {

				cout << endl << curr->m_Date << "  _  " << curr->m_uCount;
				curr = curr->m_pNext;
				count++;
			}
			printf("\n\n");
			cout << "-------------------------------------------------" << endl;
		}
		else printf("\n@ \n------------------------------------------------\n");




		cout << "1. �߰�  2. ����. 3. Ž��  4. ����" << endl;
		printf("\n\n->");
		
		int err = scanf("%d", &selection_flag2);
		if (err != 1) {

			printf("\n�߸��� �Է�\n");
			Sleep(300);
			while (getchar() != '\n') {}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			continue;

		}

		printf("\n\n");

		if (selection_flag2 != 1 && selection_flag2 != 2 && selection_flag2 != 3 && selection_flag2 != 4) {
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			continue;
		}
		if (selection_flag2 == 1) {
			printf("---------------------------------------------------------------------------\n0. ���� ���� ����\t\t1. �� �߰�(���)\t\t2. �� �߰�(����)\n");
			printf("\n3. ���ϴ� ��ġ �տ� �߰�\t4. ���ϴ� ��ġ �� ����\t\t5. ȯ�� ����\n---------------------------------------------------------------------------\n");
		}
		if (selection_flag2 == 2) {
			printf("---------------------------------------------------------------------------\n1. ��� �׸� ����\t\t2. ���� �׸� ����\n");
			printf("3. ���� �׸� ����\t\t4. ȯ�� ������ �ʱ�ȭ\t5. ȯ�� ����\n---------------------------------------------------------------------------\n");
		}
		if (selection_flag2 == 3) {
			printf("---------------------------------------------------------------------------\n1. ���ϴ� ȯ�� �б�\t\t2. ��ü ������ �б�\t\t3. �� �̸� �˻�\n---------------------------------------------------------------------------\n");
		}
		if (selection_flag2 == 4) {
			printf("---------------------------------------------------------------------------\n1. ��, ���� ����\t\t2. ó�� �� ����\t\t3. ���� ���� ����\n4. ȯ�� �̸� ����\t\t5.���� ���� ���� ����\t\t6. ���� �̸� ���� ����\n---------------------------------------------------------------------------\n");
		}






		int Selection = -1;

		printf("\n��� ����:");
		err = scanf("%d", &Selection);
		if (err != 1) {

			printf("\n�߸��� �Է�\n");
			Sleep(300);
			while (getchar() != '\n') {}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			continue;

		}

		printf("\n\n");
		if (Selection == 0 && selection_flag2 == 1) {
			Selection_flag = 1;
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);


			if (Lists == NULL) {
				Create(&Lists);



			}



			else { printf("�̹� ����Ʈ�� �����մϴ�.\n"); }
			continue;
		}

		if (Selection == 5 && selection_flag2 == 1) {
			Selection_flag = 1;

			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {};
			printf("���� ������ ȯ�ڸ� �Է�:");
			std::getline(cin, String);

			Lists->m_pCurrent = Lists->m_pHead;
			for (int i = 0; i < Lists->m_uCount; i++) {
				if (Lists->m_pCurrent->m_Date == String) {
					printf("�̹� �����ϴ� ȯ���Դϴ�.\n");
					continue;
				}
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			AppendFromTail_(Lists, String);


			continue;
		}

		if (Selection == 1 && selection_flag2 == 1) {
			Selection_flag = 1;
			if (!Lists) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�������� ���� �ʿ�\n");
				continue;
			}
			if (Lists->m_uCount == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("���� ȯ�ڸ� �߰��ؾ� �մϴ�.\n\n");
				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���°�� �߰� ? :");

			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}



		
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {};
			printf("�� �̸�? :");
			std::getline(cin, String);

			printf("���� ? :");
			err = scanf("%lld", &Num_tmp2);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp2 >= INT_MIN && Num_tmp2 <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}


			if (Lists != NULL) {
				AppendFromHead(Lists, k, Num_tmp2, String);
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			else {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�ش縮��Ʈ�� ��������� �ʾҽ��ϴ�.\n\n\n");
				continue;

			}
		}

		if (Selection == 2 && selection_flag2 == 1) {
			Selection_flag = 1;
			if (!Lists) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�������� ���� �ʿ�\n");
				continue;
			}
			if (Lists->m_uCount == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("���� ȯ�ڸ� �߰��ؾ� �մϴ�.\n\n");
				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���°�� �߰� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}



		
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {};
			printf("�� �̸� ? :");
			std::getline(cin, String);

			printf("���� ? :");
			err = scanf("%lld", &Num_tmp2);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp2 >= INT_MIN && Num_tmp2 <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}

			if (Lists != NULL) {
				AppendFromTail(Lists, k, Num_tmp2, String);
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			else {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�ش縮��Ʈ�� ��������� �ʾҽ��ϴ�.\n\n\n");
				continue;

			}
		}

		if (Selection == 1 && selection_flag2 == 3) {
			Selection_flag = 1;
			if (!Lists) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�������� ���� �ʿ�\n");
				continue;
			}
			if (Lists->m_uCount == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("������ ȯ�ڰ� �����ϴ�..\n");
				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���� ȯ�ڴ� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			Read(Lists, k);
			cout << "\n---------------------------------------------------------------------------\n";



		}
		if (Selection == 2 && selection_flag2 == 3) {
			Selection_flag = 1;

			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			Traversal(Lists);
			continue;
		}

		if (Selection == 3 && selection_flag2 == 1) {
			Selection_flag = 1;
			if (!Lists) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�������� ���� �ʿ�\n");
				continue;
			}
			if (Lists->m_uCount == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("���� ȯ�ڸ� �߰��ؾ� �մϴ�.\n\n");
				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���°�� �߰� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			if (Read(Lists, k) == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("��� �տ� �߰� ? :");
			err = scanf("%lld", &Num_tmp);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp >= INT_MIN && Num_tmp <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}



			
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {};
			printf("�� �̸�? :");
			std::getline(cin, String);

			printf("���� ? :");
			err = scanf("%lld", &Num_tmp2);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp2 >= INT_MIN && Num_tmp2 <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}

			if (Lists != NULL) {
				Insert_Count_Before(Lists, k, Num_tmp, Num_tmp2, String);
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			else {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�ش縮��Ʈ�� ��������� �ʾҽ��ϴ�.\n\n\n");
				continue;

			}
		}



		if (Selection == 4 && selection_flag2 == 1) {
			Selection_flag = 1;
			if (!Lists) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�������� ���� �ʿ�\n");
				continue;
			}
			if (Lists->m_uCount == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("���� ȯ�ڸ� �߰��ؾ� �մϴ�.\n\n");
				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���° ȯ�� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			cout << "\n---------------------------------------------------------------------------\n";
			if (Read(Lists, k) == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("���° �׸� �ڿ� ? :");
			err = scanf("%lld", &Num_tmp);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp >= INT_MIN && Num_tmp <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}

			
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {};
			printf("�� �̸� ? :");
			std::getline(cin, String);

			printf("���� ? :");
			err = scanf("%lld", &Num_tmp2);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp2 >= INT_MIN && Num_tmp2 <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}

			if (Lists != NULL) {
				Insert_Count_After(Lists, k, Num_tmp, Num_tmp2, String);
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			else {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�ش縮��Ʈ�� ��������� �ʾҽ��ϴ�.\n\n\n");
				continue;

			}

		}

		if (Selection == 1 && selection_flag2 == 2) {
			Selection_flag = 1;

			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���°�� ���� ���� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}

			DeleteFromHead(Lists, k);
		}
		if (Selection == 2 && selection_flag2 == 1) {
			Selection_flag = 1;

			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���°�� �ڸ� ���� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}

			DeleteFromTail(Lists, k);
			continue;
		}
		//���ϴ� ��ġ�� �׸� ����
		if (Selection == 3 && selection_flag2 == 2) {
			Selection_flag = 1;

			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n ������ �׸��� �ִ� ȯ�� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << "\n---------------------------------------------------------------------------\n";
			if (Read(Lists, k) == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n ���° �׸��� ���� ? :");
			err = scanf("%d", &Num_tmp2);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}

			DeleteNode_Count(Lists, k, Num_tmp2);
			continue;
		}

		if (Selection == 4 && selection_flag2 == 2) {
			Selection_flag = 1;

			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n �ʱ�ȭ �� ȯ�� ?:");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}



			DeleteAll(Lists, k);
			continue;

		}

		if (Selection == 5 && selection_flag2 == 2) {
			Selection_flag = 1;

			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���° ȯ�ڸ� ���� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}

			DeleteNode_Count_k(Lists, k);
		}

		if (Selection == 1 && selection_flag2 == 4) {
			Selection_flag = 1;
			if (!Lists) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�������� ���� �ʿ�\n");
				continue;
			}
			if (Lists->m_uCount == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("���� ȯ�ڸ� �߰��ؾ� �մϴ�.\n\n");
				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���° ȯ�� ���� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << "\n---------------------------------------------------------------------------\n";
			if (Read(Lists, k) == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("���° �׸��� ���� ? :");
			err = scanf("%lld", &Num_tmp);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp >= INT_MIN && Num_tmp <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}

			
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {};
			printf("�� �̸� ? :");
			getline(cin, String);

			printf("���� ? :");
			err = scanf("%lld", &Num_tmp2);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp2 >= INT_MIN && Num_tmp2 <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}
			if (Lists != NULL) {
				Modify_by_Count(Lists, k, Num_tmp, Num_tmp2, String);
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			else {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�ش縮��Ʈ�� ��������� �ʾҽ��ϴ�.\n\n\n");
				continue;

			}
		}

		if (Selection == 2 && selection_flag2 == 4) {
			Selection_flag = 1;
			if (!Lists) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�������� ���� �ʿ�\n");
				continue;
			}
			if (Lists->m_uCount == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("���� ȯ�ڸ� �߰��ؾ� �մϴ�.\n\n");
				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���° ȯ�� ���� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << "\n---------------------------------------------------------------------------\n";
			if (Read(Lists, k) == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("���° �׸��� ���� ? :");
			err = scanf("%lld", &Num_tmp);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp >= INT_MIN && Num_tmp <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}

			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {};

			printf("������ ������? :");
			std::getline(cin, String);

			if (Lists != NULL) {
				Modify_by_Count_String(Lists, k, Num_tmp, String);
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			else {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�ش縮��Ʈ�� ��������� �ʾҽ��ϴ�.\n\n\n");
				continue;

			}
		}

		if (Selection == 3 && selection_flag2 == 4) {
			Selection_flag = 1;
			if (!Lists) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�������� ���� �ʿ�\n");
				continue;
			}
			if (Lists->m_uCount == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("���� ȯ�ڸ� �߰��ؾ� �մϴ�.\n\n");
				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("\n���° ȯ�� ���� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << "\n---------------------------------------------------------------------------\n";
			if (Read(Lists, k) == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			cout << "\n---------------------------------------------------------------------------\n";
			printf("���° �׸��� ���� ? :");
			err = scanf("%lld", &Num_tmp);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp >= INT_MIN && Num_tmp <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}

			printf("���� ? :");
			err = scanf("%lld", &Num_tmp2);
			if (err != 1) {
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF) {}

				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;

			}
			else {
				if (Num_tmp2 >= INT_MIN && Num_tmp2 <= INT_MAX) {

				}
				else {
					system("cls");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
					printf("����,����÷ο� �߻�\n\n");


					continue;
				}
			}

			if (Lists != NULL) {
				Modify_by_Count_Object(Lists, k, Num_tmp, Num_tmp2);
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			else {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�ش縮��Ʈ�� ��������� �ʾҽ��ϴ�.\n\n\n");
				continue;

			}
		}

		if (Selection == 4 && selection_flag2 == 1) {
			Selection_flag = 1;
			if (!Lists) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�������� ���� �ʿ�\n");
				continue;
			}
			if (Lists->m_uCount == 0) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);


				printf("���� ȯ�ڸ� �߰��ؾ� �մϴ�.\n\n");
				continue;
			}
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < Lists->m_uCount; i++) {
				cout << endl << i << ".\t" << Lists->m_pCurrent->m_Date;
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << "\n---------------------------------------------------------------------------\n";

			printf("\n���° ȯ�� ���� ? :");
			err = scanf("%d", &k);
			if (err != 1) {

				while (getchar() != '\n') {}
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("\n�߸��� �Է�\n");
				Sleep(300);
				continue;

			}
			if (k < 0 || k >= Lists->m_uCount) {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				cout << "0~" << Lists->m_uCount - 1 << "���̸� ����" << endl;

				continue;
			}

			Lists->m_pCurrent = Lists->m_pHead;

			for (int i = 0; i < k; i++) {
				Lists->m_pCurrent = Lists->m_pCurrent->m_pNext;
			}
			cout << Lists->m_pCurrent->m_Date << endl << "-> ";
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {};
			std::getline(cin, String);

			if (Lists != NULL) {
				Modify_Date(Lists, k, String);
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				continue;
			}
			else {
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("�ش縮��Ʈ�� ��������� �ʾҽ��ϴ�.\n\n\n");
				continue;

			}
		}

		if (Selection == 3 && selection_flag2 == 3) {
			Selection_flag = 1;
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF) {};
			cout << "�˻��� :";
			getline(cin, String);
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			LinearSearchByDuplicate_KyeWord_String(Lists, String, &SearchResultSize, &SearchSortResultArr);
		}

		if (Selection == 5 && selection_flag2 == 4) {

			Selection_flag = 1;
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			SortBySelection_Object(Lists);
			
	
		}
		if (Selection == 6 && selection_flag2 == 4) {
			
			Selection_flag = 1;
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			SortBySelection_String(Lists);
			
		
		}
		if (Selection_flag == 0) {
			system("cls");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); continue;
		}
	}


	return 0;
}

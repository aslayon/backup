#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 10

int* queue;
int	front;			// 전단
int	rear;			// 후단
int size = 1;

int isEmpty() {
	if (front == rear) return 1;
	else return 0;
}

// 큐가 포화 상태인지 확인하는 연산
int isFull() {
	if (front == (rear + 1) % (QUEUE_SIZE * size)) return 1;
	else return 0;
}

int queueSize() {
	return(rear - front + (QUEUE_SIZE * size)) % (QUEUE_SIZE * size);
}

void enqueue(int item) {
	if (isFull()) {
		printf(" Full QUEUE\n");
		int* temp = (int*)malloc((QUEUE_SIZE * size) * sizeof(int));

		if (rear > front)
			for (int i = 0; i < (rear + 1); i++) temp[i] = queue[i];
		else {
			for (int i = front; i < (QUEUE_SIZE * size); i++) temp[i - front] = queue[i];
			for (int i = 0; i < (rear + 1); i++) temp[QUEUE_SIZE * size - (rear + 1) + i] = queue[i];
			front = 0;
			rear = QUEUE_SIZE * size - 1;
		}

		free(queue);
		queue = (int*)malloc((QUEUE_SIZE * (size + 1)) * sizeof(int));
		for (int i = 0; i < (rear + 1); i++) queue[i] = temp[i];
		rear = (rear + 1) % (QUEUE_SIZE * (size + 1));
		queue[rear] = item;
		size++;
		free(temp);
	}
	else {
		rear = (rear + 1) % (QUEUE_SIZE * size);
		queue[rear] = item;
	}
}

void enqueue_(int item) {
	if (isFull()) {
		printf(" Full QUEUE\n");

		int* temp = (int*)malloc((QUEUE_SIZE * (size + 1)) * sizeof(int));
		for (int i = 0; i < QUEUE_SIZE * size; i++) {
			temp[i] = 0;

		}
		if (rear > front)
			for (int i = 0; i < (rear + 1); i++) temp[i] = queue[i];
		else {
			for (int i = 0; i < (rear + 1); i++) temp[i] = queue[i];
			for (int i = front; i < QUEUE_SIZE * size; i++) temp[
				QUEUE_SIZE + i] = queue[i];
				front = (front + QUEUE_SIZE) % (QUEUE_SIZE * (size + 1));
		}
		free(queue);
		queue = temp;
		rear = (rear + 1) % (QUEUE_SIZE * (size + 1));
		queue[rear] = item;
		size++;
	}
	else {
		rear = (rear + 1) % (QUEUE_SIZE * size);
		queue[rear] = item;
	}
}


void enqueueAt_(int index, int item) {

	if (index <0 || index > QUEUE_SIZE * size - 1) return; // 인덱스에 대한 예외처리




	int queue_Volume;


	if (rear > front) {
		queue_Volume = rear - front;
	}
	else if(rear < front){
		queue_Volume = QUEUE_SIZE * size - (front - rear - 1);
	}
	else {
		queue_Volume = 0;
	}
	if (index == queue_Volume) {
		enqueue(item);
		return;

	}

	int index_Loc = front + 1;

	for (int i = 0; i < index; i++) {
		index_Loc++;
	}

	if (isFull()) {
		printf(" Full QUEUE\n");
		
		int* temp = (int*)malloc((QUEUE_SIZE * (size + 1)) * sizeof(int));
		
		if (rear > front) {
			for (int i = 0; i < (rear + 1); i++) temp[i] = queue[i];

		}
		else {
			for (int i = 0; i < (rear + 1); i++) { temp[i] = queue[i]; }
			for (int i = front; i < QUEUE_SIZE * size; i++) temp[
				QUEUE_SIZE + i] = queue[i];
				front = (front + QUEUE_SIZE) % (QUEUE_SIZE * (size + 1));
		}
		free(queue);


		if (rear > front) { //삽입
			for (int i = rear; i > front; i--) {
				if (i + 1 != QUEUE_SIZE * (size+1))			// 현재의 rear 가 배열의 끝인 경우
					temp[i + 1] = temp[i];
				if (i == index_Loc) {
					if (index_Loc == QUEUE_SIZE * (size+1)-1) {// 현재의 rear 가 배열의 끝일 경우. 위치 조정
						temp[0] = temp[i];
					}
					temp[i] = item;
					break;
				}
			}
		}
		else {				//삽입
			index_Loc += QUEUE_SIZE;
			int i = rear;
			if (index_Loc > QUEUE_SIZE * (size + 1) - 1) {
				index_Loc = index_Loc % (QUEUE_SIZE * (size + 1));
			}
			while (i != index_Loc) {
				
				if (i > rear) {// front 부터 끝까지
					if (i + 1 != QUEUE_SIZE * (size + 1))
					temp[i + 1] = temp[i];

				}
				else{			// 처음부터 rear 까지
					temp[i + 1] = temp[i];
				}
				i--;
				if (i == -1) {	//처음부터 rear 까지를 마친 후  배열의 끝으로 이동
					i = QUEUE_SIZE * (size + 1) - 1;
					temp[0] = temp[i];
					
				}
			}
			temp[i] = item;


		}


		queue = temp;
		rear = (rear + 1) % (QUEUE_SIZE * (size + 1));





		size++;
	}
	else {
		if (rear > front) { //삽입
			for (int i = rear; i > front; i--) {
				if(i + 1 != QUEUE_SIZE * (size))				// 현재의 rear 가 배열의 끝인 경우
					queue[i + 1] = queue[i];
				else {
					queue[0] = queue[i];
				}
				if (i == index_Loc) {
					if (index_Loc == QUEUE_SIZE * (size) - 1) {// 현재의 rear 가 배열의 끝일 경우. 위치 조정
						queue[0] = queue[i];
					}
					queue[i] = item;
					break;
				}
			}
		}
		else {				//삽입

			int i = rear;
			if (index_Loc > QUEUE_SIZE * (size) - 1) {
				index_Loc = index_Loc % (QUEUE_SIZE * (size));
			}
			while (i != index_Loc) {
				if (i + 1 != QUEUE_SIZE * (size))
					queue[i + 1] = queue[i];
				else {
					queue[0] = queue[i];
				}
				i--;
				if (i == -1) {	//처음부터 rear 까지를 마친 후  배열의 끝으로 이동
					i = QUEUE_SIZE * (size) - 1;
					queue[0] = queue[i];
				}
			}
			queue[i] = item;


		}
		rear = (rear + 1) % (QUEUE_SIZE * size);
		
	}
}


int dequeue() {
	if (isEmpty()) {	// 큐가 공백 상태인 경우
		printf("\n\n Queue is Empty!!\n");
		return 0;
	}
	else
	{
		if (queueSize() % QUEUE_SIZE == 0)
		{
			printf(" CHANGE DEQUEUE\n");
			int re;
			int* temp = (int*)malloc((QUEUE_SIZE * (size - 1)) * sizeof(int));

			re = queue[front + 1];
			queue[front + 1] = 0;
			if (rear > front)
				for (int i = front + 1; i < rear + 1
					; i++) temp[i - (front + 1)] = queue[i];
			else {
				for (int i = front + 1; i < QUEUE_SIZE * size; i++) temp[i - (front + 1)] = queue[i];
				for (int i = 0; i < (rear + 1); i++) temp[QUEUE_SIZE * (size - 1) - (rear + 1) + i] = queue[i];
			}

			free(queue);

			queue = (int*)malloc((QUEUE_SIZE * (size - 1)) * sizeof(int));

			for (int i = 0; i < QUEUE_SIZE * (size - 1); i++) queue[i] = temp[i];

			front = 0;
			rear = QUEUE_SIZE * (size - 1) - 1;
			size--;

			free(temp);
			return re;
		}
		else {
			queue[front] = 0;
			front = (front + 1) % (QUEUE_SIZE * size);
			
			return queue[front];
		}
	}
	return 0;
}

int dequeueAt(int index) {

	if (index <0 || index > QUEUE_SIZE * size - 1) return NULL; // 인덱스에 대한 예외처리
	int index_Loc = front + 1;
	int queue_Volume;
	if (rear > front) {
		queue_Volume = rear - front;
	}
	else if (rear < front) {
		queue_Volume = QUEUE_SIZE * size - (front - rear - 1);
	}
	else {
		queue_Volume = 0;
	}

	if (index > queue_Volume-1) return NULL;

	for (int i = 0; i < index; i++) {
		index_Loc++;
	}

	index_Loc = index_Loc % (QUEUE_SIZE * size);


	if (index == 0) {
		return dequeue();

	}

	if (isEmpty()) {	// 큐가 공백 상태인 경우
		printf("\n\n Queue is Empty!!\n");
		return 0;
	}
	else
	{
		if (queueSize() % QUEUE_SIZE == 0)
		{
			printf(" CHANGE DEQUEUE\n");
			int re;
			int* temp = (int*)malloc((QUEUE_SIZE * (size - 1)) * sizeof(int));
			for (int i = 0; i < QUEUE_SIZE * (size -1); i++) {
				temp[i] = i;
			}
			
			
			if (rear > front)
				for (int i = front ; i < rear + 1; i++) { 
					int j = i;
					if (i < index_Loc) {
						temp[i - (front)] = queue[i];
					}
					else {				// index 이후는 한칸 뒤를 가져온다.
						if (i == index_Loc) {
							re = queue[i];
						}
						j = i + 1;
						if(j < QUEUE_SIZE * (size)) 
						temp[i - (front )] = queue[j];
					}
				}
				
			else {

				int i = front;
				while (i != index_Loc) {//front 부터 끝까지
					i++;
					if (i > QUEUE_SIZE * (size)) {
						i = 0;
					}
				}
				re = queue[i];
				if (i > rear) {//index 가  front ~ 끝 사이에 있을 때
					for (int j = i; j < QUEUE_SIZE * (size)-2; j++) {
						queue[j] = queue[j + 1];	//index 위치부터 한칸씩 당기기(끝까지) _ 끝 한칸 비어있음
					}
					queue[QUEUE_SIZE * (size)-1] = queue[0];	//끝 한칸 채우기
					for (int j = 0; j < rear + 1; j++) {
						queue[j] = queue[j + 1];	// 시작 ~ rear 까지 한칸씩 당기기
					}
				}
				else {
					for (int j = i; j < rear - 1; j++) {
						queue[j] = queue[j + 1];
					}
				}



				for (int i = front; i < QUEUE_SIZE * size; i++) { 
					temp[i - (front)] = queue[i]; 
				}
				for (int i = 0; i < (rear ); i++) { 
					temp[QUEUE_SIZE * (size - 1) - (rear + 1) + i] = queue[i]; 
				}
			}

			free(queue);

			queue = (int*)malloc((QUEUE_SIZE * (size - 1)) * sizeof(int));

			for (int i = 0; i < QUEUE_SIZE * (size - 1); i++) queue[i] = temp[i];
			
			front = 0;
			rear =   (QUEUE_SIZE * (size - 1)-1);
			
			size--;

			
			return re;
		}
		else {
			int re;
			if (front < rear) {
				for (int i = 0; i < QUEUE_SIZE * (size); i++) {
					if (i >= index_Loc) {
						if (i == index_Loc) {
							re = queue[i];
						}
						if(i+1< QUEUE_SIZE * (size))
						queue[i] = queue[i + 1];
					}
				}
			}
			else {
				int i = front;
				while (i != index_Loc) {//front 부터 끝까지
					i++;
					if (i > QUEUE_SIZE * (size)-1) { 
						i = 0;
					}
				}
				re = queue[i];
				if (i > rear) {//index 가  front ~ 끝 사이에 있을 때
					for (int j = i; j < QUEUE_SIZE * (size)-2; j++) {
						queue[j] = queue[j + 1];	//index 위치부터 한칸씩 당기기(끝까지) _ 끝 한칸 비어있음
					}
					queue[QUEUE_SIZE * (size)-1] = queue[0];	//끝 한칸 채우기
					for (int j = 0; j < rear + 1; j++) {
						queue[j] = queue[j + 1];	// 시작 ~ rear 까지 한칸씩 당기기
					}
				}
				else {
					for (int j = i; j < rear - 1; j++) {
						queue[j] = queue[j + 1];
					}
				}
			}
			rear = (rear - 1) % (QUEUE_SIZE * (size));
			if (rear < 0) {
				rear =  QUEUE_SIZE * (size) + rear;
			}
			return re;
		}
	}
	return 0;
}



// 큐의 원소를 출력하는 연산
void printQueue() {
	int i, maxi = rear;
	if (front >= rear) maxi += (QUEUE_SIZE * size);
	printf("QUEUE SIZE [%d]\n", (QUEUE_SIZE * size));
	printf("\n QUEUE [ ");
	for (i = 0; i < QUEUE_SIZE * size; i++) {
		
			printf("%d ", queue[i]);
		
	}
	printf("]\n");
	for (i = front + 1; i <= maxi; i++)
		printf("%d ", queue[i % (QUEUE_SIZE * size)]);
	printf("]\n\n");
}

void main(void) {
	int i;
	queue = (int*)malloc(QUEUE_SIZE * sizeof(int));


	for (i = 0; i < 10; i++) {
		enqueueAt_(i % 10, i);

	}

	

	for (i = 0; i < 10; i++) {
		enqueueAt_(i % 10, i);
		
	}for (i = 0; i < 10; i++) {
		enqueueAt_(i % 10, i);

	}for (i = 0; i < 10; i++) {
		enqueueAt_(i % 10, i);

	}for (i = 0; i < 10; i++) {
		enqueueAt_(i % 10, i);

	}
	printQueue();
	for (i = 0; i < 10; i++) {
		printf("%d\n\n", i);
		printf("'%d'\n", dequeueAt(i));
		printQueue();
	}
	for (i = 0; i < 10; i++) {
		printf("%d\n\n", i);
		printf("'%d'\n", dequeueAt(i));
		printQueue();
	}
	
	free(queue);
	
}
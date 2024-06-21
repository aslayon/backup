/* Chapter 1. Basic cp file copy program. C library Implementation. */
/* cp file1 file2: Copy file1 to file2. */

//버퍼 사이즈 1 , 256, 512 1024 4096 8192    시간의 차이 보고서
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#define BUF_SIZE 1






#include <windows.h>


/* Chapter 1. Basic cp file copy program - cpUC.c
	Win32 UNIX Compatibility Implementation. */
	/* cp file1 file2: Copy file1 to file2. */

#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

int Unixcp()
{
	int input_fd, output_fd;
	int bytes_in, bytes_out;
	char rec[BUF_SIZE];
	
	input_fd = _open("src.jpg", O_RDONLY | O_BINARY);
	if (input_fd == -1) {
		perror("error1");
		return 2;
	}
	output_fd = _open("Unix.jpg", O_WRONLY | O_CREAT | O_BINARY);
	if (output_fd == -1) {
		perror("error2");
		return 3;
	}
	/* Process the input file a record at a time. */
	
	while ((bytes_in = _read(input_fd, &rec, BUF_SIZE)) > 0) {
		bytes_out = _write(output_fd, &rec, bytes_in);
		if (bytes_out != bytes_in) {
			perror("Fatal write error.");
			return 4;
		}
	}
	
	_close(input_fd);
	_close(output_fd);
	return 0;
}





int Windcp()
{
	HANDLE hIn, hOut;
	DWORD nIn, nOut;
	CHAR Buffer[BUF_SIZE];
	
	hIn = CreateFile("src.jpg", GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn == INVALID_HANDLE_VALUE) {
		printf("Cannot open input file. Error: %x\n", GetLastError());
		return 2;
	}

	hOut = CreateFile("wind.jpg", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOut == INVALID_HANDLE_VALUE) {
		printf("Cannot open output file. Error: %x\n", GetLastError());
		return 3;
	}
	while (ReadFile(hIn, Buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
		WriteFile(hOut, Buffer, nIn, &nOut, NULL);
		if (nIn != nOut) {
			printf("Fatal write error: %x\n", GetLastError());
			return 4;
		}
	}
	CloseHandle(hIn);
	CloseHandle(hOut);
	return 0;
}






//int main (int argc, char *argv []) // $cp a.txt b.txt
int stanCcp() // $cp a.txt b.txt
{
	FILE* in_file, * out_file;
	char rec[BUF_SIZE];   //unsigned char  로 선언해야 오류방지 , 아스키코드 char 은 7바이트임, 남은 1바이트의 오염 방지 위해 unsigned 
	size_t bytes_in, bytes_out;
	//if (argc != 3) {
		//printf ("Usage: cp file1 file2\n");
		//return 1;
	//}
	in_file = fopen("src.jpg", "rb"); //b 는 바이너리 파일임을 의미 // 걍  b 다 붙이면 좋음
	if (in_file == NULL) {
		perror("");
		return 2;
	}
	out_file = fopen("stanC.jpg", "wb");
	if (out_file == NULL) {
		perror("");
		
		return 3;
	}

	/* Process the input file a record at a time. */

	while ((bytes_in = fread(rec, 1, BUF_SIZE, in_file)) > 0) {
		bytes_out = fwrite(rec, 1, bytes_in, out_file);
		if (bytes_out != bytes_in) {
			perror("Fatal write error.");
			return 4;
		}
	}

	fclose(in_file);
	fclose(out_file);
	return 0;
}


int main() {
	clock_t start, finish;
	double duration;

	start = clock();
	stanCcp();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("버퍼 사이즈 %d stan 걸린 시간 : %f\n", BUF_SIZE, duration);

	
	start = clock();
	Windcp();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("버퍼 사이즈 %d Win 걸린 시간 : %f\n", BUF_SIZE, duration);
	
	start = clock();
	Unixcp();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("버퍼 사이즈 %d Unix 걸린 시간 : %f\n", BUF_SIZE, duration);
}
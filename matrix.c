#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //Matrix 생성
void print_matrix(int** matrix, int row, int col); //Matrix 출력
int free_matrix(int** matrix, int row, int col); //종료시 할당했던 메모리 해제
int fill_data(int** matrix, int row, int col); //데이터 입력
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //Matrix A + B
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); //Matrix A - B
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //전치행렬 출력
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); //Matrix A x B

int main()
{
    char command;
    printf("[----- [조정동]  [2017015041] -----]\n");

	int row, col;
	srand(time(NULL)); //row, col에 랜덤함수 적용

	printf("Input row and col : ");
	scanf("%d %d", &row, &col); //row, col에 입력
    int** matrix_a = create_matrix(row, col); //row x col의 Matrix A 생성
	int** matrix_b = create_matrix(row, col); //row x col의 Matrix B 생성
    int** matrix_a_t = create_matrix(col, row); //A의 전치행렬 생성

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //command 입력

		switch(command) {
		case 'z': case 'Z': //z 또는 Z 입력시 Matrix 초기화
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col); //row x col 의 Matrix A 생성
			fill_data(matrix_b, row, col); //row x col 의 Matrix B 생성
			break;
        case 'p': case 'P': //p 또는 P 입력시 Matrix 출력
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col); //row x col의 Matrix A 생성
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); //row x col의 Matrix B 생성
			break;
        case 'a': case 'A': //a 또는 A 입력시 두 Matrix의 합 계산
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);
			break;
        case 's': case 'S': //s 또는 S 입력시 두 Matrix의 차 계산
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
        case 't': case 'T': //t 또는 T 입력시 전치행렬 A 계산
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
			break;
        case 'm': case 'M': //m 또는 M 입력시 두 Matrix의 곱 계산
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
        case 'q': case 'Q': //q 또는 Q 입력시 종료 후 할당한 메모리 해제
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) //Matrix 생성 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row 또는 col이 0이하면 아래의 문구 출력 후 프로그램 종료
		printf("Check the size of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); //row 생성
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col); //col 생성
	}

	/* Check post conditions */
	if (matrix == NULL) { //Matrix이 NULL값이면 아래의 문구 출력
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) //Matrix 출력 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row 또는 col이 0이하면 아래의 문구 출력 후 프로그램 종료
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { //row x col의 행렬 생성
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) { //Matrix이 NULL값이면 아래의 문구 출력
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) //프로그램 종료시 할당 메모리 해제 함수 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row 또는 col이 0이하면 아래의 문구 출력 후 프로그램 종료
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]);
	}

	free(matrix);
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //Matrix에 데이터 입력 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row 또는 col이 0이하면 아래의 문구 출력 후 프로그램 종료
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) 
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20; //row x col Matrix에 랜덤함수를 이용하여 숫자 채움
	/* Check post conditions */
    if (matrix == NULL) { //정상종료와 비정상종료를 나타내는 값을 돌려줌
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) //Matrix의 덧셈 함수
{
    int** matrix_sum = create_matrix(row, col);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row 또는 col이 0이하면 아래의 문구 출력 후 프로그램 종료
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col]; //Matrix의 덧셈 계산
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col); //Matrix값 출력
	free_matrix(matrix_sum, row, col); //Matrix값 free시킴
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) //MAtrix의 뺄셈 함수
{
    int** matrix_sub = create_matrix(row, col);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row 또는 col이 0이하면 아래의 문구 출력 후 프로그램 종료
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col]; //Matrix의 뺄셈 계산
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) //전치행렬 계산 함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row 또는 col이 0이하면 아래의 문구 출력 후 프로그램 종료
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row]; //전치행렬 계산
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) //Matrix의 곱셈 함수
{
    int** matrix_axt = create_matrix(row, row);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { //row 또는 col이 0이하면 아래의 문구 출력 후 프로그램 종료
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; 
			matrix_axt[matrix_a_row][matrix_t_row] = temp; //Matrix의 곱셈 계산
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) { //메모리 할당 실패
		printf("Memory Allocation Failed.\n");
		return -1; 
	}
	print_matrix(matrix_axt, row, row);
	free_matrix(matrix_axt, row, col);
	return 1;
}


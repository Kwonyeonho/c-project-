/*
* ����ȯ�� : window 11, visualstudio 2022, gallaxy book3 pro
* ���߱Ⱓ : 2023/12/13~2023/12/15
*/
#include <stdio.h>    // ǥ�� �����
#include <Windows.h>  // Ŀ�� �̵�
#include <conio.h>	 // getch�Լ� (Ű�� �ϳ� �޴� �Լ�)

// �Լ� ���� �� ��������
void gotoxy(int x, int y);									// Ŀ�� �̵��Լ�
void gamecontrol();											// ���� ��Ʈ�� �Լ� (������ �۵��ϴ� ���� ����)
void Draw_Board();										    // �ٵ��� �׸��� (18*18������)
void Enter_Key(int Board[][20], char key, int* x, int* y);	// Ű�� �ԷµǾ��� �� ó���ϴ� �Լ� (����Ű �� �����̽���)
void Erase_Stone(int x, int y);								// �׷��� �ٵϵ��� ����� �Լ� (�̵��ϱ� ���ؼ� �̹� ��µȰ� ������ ��)
void Draw_Stone();											// �ٵϵ� ��� �Լ� (�̵��ϴ� Ű�� �Է��� ���Ŀ� �ٵϵ� ����ؾ� ��)
void Put_Stone(int Board[][20], int x, int y);				// �ٵϵ� ���� �Լ� (������ ���ڴٰ� �� �ڸ��� �ٵϵ��� ���ƾ� �ϹǷ�)
void print_Stone(int Board[][20]);						    // ������ �ٵϵ��� ����ϴ� �Լ�
int Win_Check(int Board[][20], char key);					// �¸� üũ �Լ�
int check = 1;												// ���� �ٵϵ��� �׷����� �ϴ��� üũ�ϴ� ����(1 - �鵹, 2 - �浹)													

//���� �Լ�
int main(void) {
	while (1) {
		gamecontrol(); // gamecontrol()�Լ� ȣ��
		gotoxy(0, 23); // �Լ��� �������� 0,23���� Ŀ���� ����
		printf("\n������ �ٽ� �����Ͻ÷��� �ƹ�Ű�� ��������!!");
		getch();
		system("cls"); //�ܼ� ȭ�� �����

	}
	return 0;
}

//���� ��Ʈ�� �Լ�
void gamecontrol() {
	int Baduk_Board[20][20] = { 0 }; /* �ٵ��� �迭, 20*20�� 2��������� �������� 0���� �ʱ�ȭ
	0�̸� �ƹ��͵� ���� ����, 20*20���� ������ ������ 18*18�ٵ����� ��� ���� 19������ ������ �ֱ� �����̴�.*/
	int x = 0, y = 0; // x��ǥ�� y��ǥ
	char Key;         // Ű�� �ԷµǾ��� �� �� ASCII �ڵ带 ���� ����
	Draw_Board();	  // �ٵ��� �׸��� �Լ� ȣ��	
	gotoxy(x, y);	  // �켱 0,0���� Ŀ���� �ű�(������ x�� y�� 0���� �ʱ�ȭ ��)
	Draw_Stone();	  // �� �׸��� �Լ�.
	while (1) {		  // while �� ���ѹݺ�
		Key = getch();	    // Ű �ϳ��� �Է¹޾� �װ��� ASCII �ڵ带 Key ������ ����
		Erase_Stone(x, y);	// �׷��� �ٵϵ��� ����� �Լ� ȣ��

		Enter_Key(Baduk_Board, Key, &x, &y);			// Ű�� �������� �� ó���ϴ� �Լ� ȣ��
		print_Stone(Baduk_Board);						// ������ ���� �׸��� �Լ� ȣ��
		if (Win_Check(Baduk_Board, Key, &x, &y)) {		// �̰峪 üũ��. Win_Check�Լ����� �浹�̳� �鵹�� �̱�� 1�� ��ȯ�ϴµ� if������ 1�� true�̴�. 			
			return;  // �������� �̰����� ���� ��Ʈ�� �Լ� ���� == ���� ����
		}
		gotoxy(x, y); // Key_Down �Լ����� ����� �ڸ��� �̵�
		Draw_Stone(); // �̵��� Ŀ���� �� ���
	}

}

//�� ����� �Լ�
void Erase_Stone(int x, int y) {
	gotoxy(x, y);					// ���� ���� ��ġ�� ������ �̵� ����Ű�� ����Ͽ��� ���� ��ġ�� �����̸� ������ġ�� �ִ� ���� ����
	if (x == 0 && y == 0)			// �װ��� ���� 0,0 (���� �� �𼭸�)�� ���
		printf("��");
	else if (x == 36 && y == 0)		// �װ��� ���� 36,0 (������ �� �𼭸�)�� ��� 
		printf("��");
	else if (x == 0 && y == 18)		// �װ��� ���� 0,18 (���� �Ʒ� �𼭸�)�� ���
		printf("��");
	else if (x == 36 && y == 18)	// �װ��� ���� 36,18 (������ �Ʒ� �𼭸�)�� ���
		printf("��");
	else if (x == 0)				// �װ��� ���� 0,1~17 (������)�� ���						
		printf("��");
	else if (y == 0)				// �װ��� ���� 1~35,0 (����)�� ���
		printf("��");
	else if (x == 36)				// �װ��� ���� 36,1~17 (��������)�� ���
		printf("��");
	else if (y == 18)				// �װ��� ���� 1~35,18 (�Ʒ���)�� ���
		printf("��");
	else							// �� ���� ���
		printf("��");
}

//�� �׸��� �Լ�
void Draw_Stone() {
	if (check == 1)	   // �������� check �� 1�̸� �鵹 ���
		printf("��");
	else
		printf("��");  // �������� check �� 2�̸� �浹 ���
}

//Ű�� �Էµ��� �� ó���ϴ� �Լ�
void Enter_Key(int Board[][20], char key, int* x, int* y) {
	// Board�� �����̽��� , key�� ����Ű���� �޾Ҵ��� �˾ƾ� �ؼ�, x,y��ǥ���� Ű�� ������ �� ��ġ�� �ٲ���� �ϴϱ� �Ű������� �޽��ϴ�.
	switch (key) {
	case 72:			 // key���� ASCII�ڵ尡 72���� �� (���� ����Ű)
		if (*y - 1 < 0)	 // y-1�� 0���� ���� ��쿡�� �ٵ����� ������ ����⶧���� ����
			break;
		else			 // y-1�� 0�̸��� �ƴ� ��쿡�� �������� �̵��ϱ� ���ؼ� y�� 1����
			*y -= 1;
		break;
	case 80:			 // key���� ASCII�ڵ尡 80���� �� (�Ʒ��� ����Ű)
		if (*y + 1 > 18) // y+1 18�� �ʰ��ϸ� �ٵ����� ������ ����⶧���� ����
			break;
		else			 // 18�� �ʰ����� �ʾ��� ��� �Ʒ������� �̵��ϱ����ؼ� y�� 1 ����
			*y += 1;
		break;
	case 75:			 // key���� ASCII�ڵ尡 75���� �� (���� ����Ű)
		if (*x - 2 < 0)	 // x-2 ���� �� 0 �̸��̸� ��� ���� y���� �ٸ��� -2�� �ϴ� ������ �ܼ�â�� y���� x���� �ι��̱⶧���̴�.
			break;
		else			 // 0 �̸��� �ƴҰ�쿡�� x�� 2 ����
			*x -= 2;
		break;
	case 77:			 // key���� ASCII�ڵ尡 77���� �� (������ ����Ű)
		if (*x + 2 > 36) // x+2���� �� 36�� �ʰ��ϸ� ����
			break;
		else			 // 36�� �ʰ����� �ʾ��� ��� x�� 2 ����
			*x += 2;
		break;
	case 32:			 // key���� ASCII�ڵ尡 32���� �� (�����̽���)
		Put_Stone(Board, *x, *y); // Put_Stone()�Լ� ȣ��, Board�� �� ��ǥ�� �Ű������� ������.
		break;
	default:			 //�� ���� ���, ����
		break;
	}
}

//�� ���� �Լ�
void Put_Stone(int Board[][20], int x, int y) {
	//Board�� 2���� �迭�� ���� 20���� ������ ������ 18*18�ٵ����� ��쿡�� �� 19������ ���� ���� �� �ֱ� �����̴�.
	if (Board[y][x / 2] == 0) {		// �������� �κп� ���� �ƹ��͵� �������� ���� ���
		if (check == 1) {			// �������� check�� 1�� ���
			Board[y][x / 2] = 1;	// Board[y][x/2] �� 1�� �ְ�
			check = 2;              // �������� check�� 2�� �浹�� ����
		}

		else {						// 1�� �ƴҰ��						
			Board[y][x / 2] = 2;	// Board[y][x/2]�� 2�� �ְ�
			check = 1;              // �������� check�� 1�� �鵹�� ����
		}
	}
}

//������ �� ����Լ�
void print_Stone(int Board[][20]) {
	int i;
	int j;
	for (i = 0; i < 20; i++) {				// ����for���� ����Ͽ��� Board�� 2���� �迭�� ����� ���� Ž��
		for (j = 0; j < 20; j++) {
			if (Board[j][i] == 1) {			// ���� Board���� 1�� ������			
				gotoxy(i * 2, j);			// Ŀ���� i*2,j �� ������
				printf("��");               // �鵹 ���
			}

			else if (Board[j][i] == 2) {	// ���� Board���� 2�� ������ (Put_Stone�Լ������ʹ� �ٸ��� else if�� ���� ������ �ƹ��͵� �������� ���� ����� 0�� �ֱ⶧���̴�.)
				gotoxy(i * 2, j);			// Ŀ���� i*2,j �� ������
				printf("��");               // �浹 ���
			}
		}
	}
}

//�¸� üũ �Լ�
int Win_Check(int Board[][20], char Key) {
	int i;
	int j;
	for (i = 2; i < 18; i++) {	// ���� �Ǵ� ���θ� �˻��ϱ� ���� for��
		for (j = 0; j < 20; j++) {
			if (Board[j][i - 2] == 1 && Board[j][i - 1] == 1 && Board[j][i] == 1 && Board[j][i + 1] == 1 && Board[j][i + 2] == 1) {	// ���ι���˻�
				gotoxy(0, 22);
				printf("*** �鵹 �¸� ***");
				return 1;
			}
			else if (Board[j][i - 2] == 2 && Board[j][i - 1] == 2 && Board[j][i] == 2 && Board[j][i + 1] == 2 && Board[j][i + 2] == 2) {//�浹�� 5�� ������ ���
				gotoxy(0, 22);
				printf("*** �浹 �¸� ***");
				return 1;
			}

			else if (Board[i - 2][j] == 1 && Board[i - 1][j] == 1 && Board[i][j] == 1 && Board[i + 1][j] == 1 && Board[i + 2][j] == 1) { //���� ���� �˻�
				gotoxy(0, 22);
				printf("*** �鵹 �¸� ***");
				return 1;
			}
			else if (Board[i - 2][j] == 2 && Board[i - 1][j] == 2 && Board[i][j] == 2 && Board[i + 1][j] == 2 && Board[i + 2][j] == 2) {
				gotoxy(0, 22);
				printf("*** �浹 �¸� ***");
				return 1;
			}
		}
	}

	for (i = 2; i < 18; i++) {	// �밢�� ������ �˻��ϱ� ���� for��
		for (j = 2; j < 18; j++) {
			if (Board[j - 2][i - 2] == 1 && Board[j - 1][i - 1] == 1 && Board[j][i] == 1 && Board[j + 1][i + 1] == 1 && Board[j + 2][i + 2] == 1) { // �ٴ밢�� �˻�.
				gotoxy(0, 22);
				printf("*** �鵹 �¸� ***");
				return 1;
			}
			else if (Board[j - 2][i - 2] == 2 && Board[j - 1][i - 1] == 2 && Board[j][i] == 2 && Board[j + 1][i + 1] == 2 && Board[j + 2][i + 2] == 2) {
				gotoxy(0, 22);
				printf("*** �浹 �¸� ***");
				return 1;
			}

			else if (Board[j + 2][i - 2] == 1 && Board[j + 1][i - 1] == 1 && Board[j][i] == 1 && Board[j - 1][i + 1] == 1 && Board[j - 2][i + 2] == 1) { // �ִ밢�� �˻�.
				gotoxy(0, 22);
				printf("*** �鵹 �¸� ***");
				return 1;
			}
			else if (Board[j + 2][i - 2] == 2 && Board[j + 1][i - 1] == 2 && Board[j][i] == 2 && Board[j - 1][i + 1] == 2 && Board[j - 2][i + 2] == 2) {
				gotoxy(0, 22);
				printf("*** �浹 �¸� ***");
				return 1;
			}
		}
	}
	return 0;
}

// �ٵ����� �׸��� �Լ�
void Draw_Board() {
	int i;
	int j;
	printf("��");  // �������� �׸���
	for (i = 0; i < 17; i++) { //���η� 17ĭ����µ� ������ ���������� �̷�ĭ�� ��µ�
		printf("��");
		printf("��");
	}
	printf("��");//18��°ĭ
	printf("��\n");//���

	for (i = 0; i < 17; i++) {
		printf("��������������������������������������������������������������������������\n");//�߰��� �׸���
	}

	printf("��");// ����Ʒ��� �׸��� �������ٰ� ����� ������
	for (i = 0; i < 17; i++) {
		printf("��");
		printf("��");
	}
	printf("��");
	printf("��");
}

//Ŀ�� �̵��Լ�
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
/*
* 개발환경 : window 11, visualstudio 2022, gallaxy book3 pro
* 개발기간 : 2023/12/13~2023/12/15
*/
#include <stdio.h>    // 표준 입출력
#include <Windows.h>  // 커서 이동
#include <conio.h>	 // getch함수 (키를 하나 받는 함수)

// 함수 정의 및 전역변수
void gotoxy(int x, int y);									// 커서 이동함수
void gamecontrol();											// 게임 컨트롤 함수 (게임이 작동하는 순서 정의)
void Draw_Board();										    // 바둑판 그리기 (18*18사이즈)
void Enter_Key(int Board[][20], char key, int* x, int* y);	// 키가 입력되었을 때 처리하는 함수 (방향키 및 스페이스바)
void Erase_Stone(int x, int y);								// 그려진 바둑돌을 지우는 함수 (이동하기 위해선 이미 출력된걸 지워야 함)
void Draw_Stone();											// 바둑돌 출력 함수 (이동하는 키를 입력한 이후에 바둑돌 출력해야 함)
void Put_Stone(int Board[][20], int x, int y);				// 바둑돌 저장 함수 (유저가 놓겠다고 한 자리에 바둑돌을 놓아야 하므로)
void print_Stone(int Board[][20]);						    // 놓여진 바둑돌을 출력하는 함수
int Win_Check(int Board[][20], char key);					// 승리 체크 함수
int check = 1;												// 무슨 바둑돌이 그려져야 하는지 체크하는 변수(1 - 백돌, 2 - 흑돌)													

//메인 함수
int main(void) {
	while (1) {
		gamecontrol(); // gamecontrol()함수 호출
		gotoxy(0, 23); // 함수가 끝났으면 0,23으로 커서를 보냄
		printf("\n게임을 다시 시작하시려면 아무키나 누르세요!!");
		getch();
		system("cls"); //콘솔 화면 지우기

	}
	return 0;
}

//게임 컨트롤 함수
void gamecontrol() {
	int Baduk_Board[20][20] = { 0 }; /* 바둑판 배열, 20*20의 2차원행렬을 선언전부 0으로 초기화
	0이면 아무것도 없는 상태, 20*20으로 선언한 이유는 18*18바둑판의 경우 돌을 19군데에 놓을수 있기 때문이다.*/
	int x = 0, y = 0; // x좌표와 y좌표
	char Key;         // 키가 입력되었을 때 그 ASCII 코드를 받을 변수
	Draw_Board();	  // 바둑판 그리는 함수 호출	
	gotoxy(x, y);	  // 우선 0,0으로 커서를 옮김(위에서 x와 y를 0으로 초기화 함)
	Draw_Stone();	  // 돌 그리는 함수.
	while (1) {		  // while 문 무한반복
		Key = getch();	    // 키 하나를 입력받아 그것의 ASCII 코드를 Key 변수에 저장
		Erase_Stone(x, y);	// 그려진 바둑돌을 지우는 함수 호출

		Enter_Key(Baduk_Board, Key, &x, &y);			// 키가 눌려졌을 때 처리하는 함수 호출
		print_Stone(Baduk_Board);						// 놓여진 돌을 그리는 함수 호출
		if (Win_Check(Baduk_Board, Key, &x, &y)) {		// 이겼나 체크함. Win_Check함수에서 흑돌이나 백돌이 이기면 1을 반환하는데 if문에서 1은 true이다. 			
			return;  // 누군가가 이겼으면 게임 컨트롤 함수 종료 == 게임 종료
		}
		gotoxy(x, y); // Key_Down 함수에서 변경된 자리로 이동
		Draw_Stone(); // 이동된 커서로 돌 출력
	}

}

//돌 지우는 함수
void Erase_Stone(int x, int y) {
	gotoxy(x, y);					// 현재 돌이 위치한 곳으로 이동 방향키를 사용하여서 돌의 위치를 움직이면 이전위치에 있던 돌을 지움
	if (x == 0 && y == 0)			// 그곳이 만약 0,0 (왼쪽 위 모서리)인 경우
		printf("┌");
	else if (x == 36 && y == 0)		// 그곳이 만약 36,0 (오른쪽 위 모서리)인 경우 
		printf("┐");
	else if (x == 0 && y == 18)		// 그곳이 만약 0,18 (왼쪽 아래 모서리)인 경우
		printf("└");
	else if (x == 36 && y == 18)	// 그곳이 만약 36,18 (오른쪽 아래 모서리)인 경우
		printf("┘");
	else if (x == 0)				// 그곳이 만약 0,1~17 (왼쪽줄)인 경우						
		printf("├");
	else if (y == 0)				// 그곳이 만약 1~35,0 (윗줄)인 경우
		printf("┬");
	else if (x == 36)				// 그곳이 만약 36,1~17 (오른쪽줄)인 경우
		printf("┤");
	else if (y == 18)				// 그곳이 만약 1~35,18 (아랫줄)인 경우
		printf("┴");
	else							// 그 외의 경우
		printf("┼");
}

//돌 그리는 함수
void Draw_Stone() {
	if (check == 1)	   // 전역변수 check 가 1이면 백돌 출력
		printf("●");
	else
		printf("○");  // 전역변수 check 가 2이면 흑돌 출력
}

//키가 입력됐을 때 처리하는 함수
void Enter_Key(int Board[][20], char key, int* x, int* y) {
	// Board는 스페이스바 , key는 무슨키값을 받았는지 알아야 해서, x,y좌표값은 키를 눌렷을 때 위치를 바꿔줘야 하니까 매개변수로 받습니다.
	switch (key) {
	case 72:			 // key값의 ASCII코드가 72번일 때 (위쪽 방향키)
		if (*y - 1 < 0)	 // y-1이 0보다 작은 경우에는 바둑판의 범위를 벗어나기때문에 정지
			break;
		else			 // y-1이 0미만이 아닐 경우에는 위쪽으로 이동하기 위해서 y값 1감소
			*y -= 1;
		break;
	case 80:			 // key값의 ASCII코드가 80번일 때 (아래쪽 방향키)
		if (*y + 1 > 18) // y+1 18을 초과하면 바둑판의 범위를 벗어나기때문에 정지
			break;
		else			 // 18을 초과하지 않았을 경우 아래쪽으로 이동하기위해서 y값 1 증가
			*y += 1;
		break;
	case 75:			 // key값의 ASCII코드가 75번일 때 (왼쪽 방향키)
		if (*x - 2 < 0)	 // x-2 했을 때 0 미만이면 경우 정지 y값과 다르게 -2를 하는 이유는 콘솔창의 y값은 x값의 두배이기때문이다.
			break;
		else			 // 0 미만이 아닐경우에는 x값 2 감소
			*x -= 2;
		break;
	case 77:			 // key값의 ASCII코드가 77번일 때 (오른쪽 방향키)
		if (*x + 2 > 36) // x+2했을 때 36을 초과하면 정지
			break;
		else			 // 36을 초과하지 않았을 경우 x값 2 증가
			*x += 2;
		break;
	case 32:			 // key값의 ASCII코드가 32번일 때 (스페이스바)
		Put_Stone(Board, *x, *y); // Put_Stone()함수 호출, Board와 현 좌표를 매개변수로 보낸다.
		break;
	default:			 //그 외의 경우, 정지
		break;
	}
}

//돌 놓는 함수
void Put_Stone(int Board[][20], int x, int y) {
	//Board의 2차원 배열의 행을 20으로 설정한 이유는 18*18바둑판의 경우에는 총 19군데에 돌을 놓을 수 있기 때문이다.
	if (Board[y][x / 2] == 0) {		// 놓으려는 부분에 돌이 아무것도 놓여있지 않은 경우
		if (check == 1) {			// 전역변수 check가 1일 경우
			Board[y][x / 2] = 1;	// Board[y][x/2] 에 1을 넣고
			check = 2;              // 전역변수 check값 2인 흑돌로 변경
		}

		else {						// 1이 아닐경우						
			Board[y][x / 2] = 2;	// Board[y][x/2]에 2를 넣고
			check = 1;              // 전역변수 check값 1인 백돌로 변경
		}
	}
}

//놓여진 돌 출력함수
void print_Stone(int Board[][20]) {
	int i;
	int j;
	for (i = 0; i < 20; i++) {				// 이중for문을 사용하여서 Board의 2차원 배열에 저장된 숫자 탐색
		for (j = 0; j < 20; j++) {
			if (Board[j][i] == 1) {			// 그중 Board에서 1이 나오면			
				gotoxy(i * 2, j);			// 커서를 i*2,j 에 보내서
				printf("●");               // 백돌 출력
			}

			else if (Board[j][i] == 2) {	// 그중 Board에서 2가 나오면 (Put_Stone함수에서와는 다르게 else if를 쓰는 이유는 아무것도 놓여지지 않은 경우인 0이 있기때문이다.)
				gotoxy(i * 2, j);			// 커서를 i*2,j 에 보내서
				printf("○");               // 흑돌 출력
			}
		}
	}
}

//승리 체크 함수
int Win_Check(int Board[][20], char Key) {
	int i;
	int j;
	for (i = 2; i < 18; i++) {	// 가로 또는 세로를 검사하기 위한 for문
		for (j = 0; j < 20; j++) {
			if (Board[j][i - 2] == 1 && Board[j][i - 1] == 1 && Board[j][i] == 1 && Board[j][i + 1] == 1 && Board[j][i + 2] == 1) {	// 가로방향검사
				gotoxy(0, 22);
				printf("*** 백돌 승리 ***");
				return 1;
			}
			else if (Board[j][i - 2] == 2 && Board[j][i - 1] == 2 && Board[j][i] == 2 && Board[j][i + 1] == 2 && Board[j][i + 2] == 2) {//흑돌이 5개 연속일 경우
				gotoxy(0, 22);
				printf("*** 흑돌 승리 ***");
				return 1;
			}

			else if (Board[i - 2][j] == 1 && Board[i - 1][j] == 1 && Board[i][j] == 1 && Board[i + 1][j] == 1 && Board[i + 2][j] == 1) { //세로 방향 검사
				gotoxy(0, 22);
				printf("*** 백돌 승리 ***");
				return 1;
			}
			else if (Board[i - 2][j] == 2 && Board[i - 1][j] == 2 && Board[i][j] == 2 && Board[i + 1][j] == 2 && Board[i + 2][j] == 2) {
				gotoxy(0, 22);
				printf("*** 흑돌 승리 ***");
				return 1;
			}
		}
	}

	for (i = 2; i < 18; i++) {	// 대각선 방향을 검사하기 위한 for문
		for (j = 2; j < 18; j++) {
			if (Board[j - 2][i - 2] == 1 && Board[j - 1][i - 1] == 1 && Board[j][i] == 1 && Board[j + 1][i + 1] == 1 && Board[j + 2][i + 2] == 1) { // ↘대각선 검사.
				gotoxy(0, 22);
				printf("*** 백돌 승리 ***");
				return 1;
			}
			else if (Board[j - 2][i - 2] == 2 && Board[j - 1][i - 1] == 2 && Board[j][i] == 2 && Board[j + 1][i + 1] == 2 && Board[j + 2][i + 2] == 2) {
				gotoxy(0, 22);
				printf("*** 흑돌 승리 ***");
				return 1;
			}

			else if (Board[j + 2][i - 2] == 1 && Board[j + 1][i - 1] == 1 && Board[j][i] == 1 && Board[j - 1][i + 1] == 1 && Board[j - 2][i + 2] == 1) { // ↗대각선 검사.
				gotoxy(0, 22);
				printf("*** 백돌 승리 ***");
				return 1;
			}
			else if (Board[j + 2][i - 2] == 2 && Board[j + 1][i - 1] == 2 && Board[j][i] == 2 && Board[j - 1][i + 1] == 2 && Board[j - 2][i + 2] == 2) {
				gotoxy(0, 22);
				printf("*** 흑돌 승리 ***");
				return 1;
			}
		}
	}
	return 0;
}

// 바둑판을 그리는 함수
void Draw_Board() {
	int i;
	int j;
	printf("┌");  // 가장윗줄 그리기
	for (i = 0; i < 17; i++) { //가로로 17칸이출력됨 ┌─┬ 마지막에는 이런칸이 출력됨
		printf("─");
		printf("┬");
	}
	printf("─");//18번째칸
	printf("┐\n");//출력

	for (i = 0; i < 17; i++) {
		printf("├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤\n");//중간줄 그리기
	}

	printf("└");// 가장아랫줄 그리기 가장윗줄과 방식은 동일함
	for (i = 0; i < 17; i++) {
		printf("─");
		printf("┴");
	}
	printf("─");
	printf("┘");
}

//커서 이동함수
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
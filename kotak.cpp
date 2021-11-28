#include <iostream> 
#include <conio.h> 
#include <time.h>
#include <windows.h>

#define dinoPos 2
#define hurdlePos 74

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
//dinopos= ferisna
//hurdlepos= kotak
//dinoy=cika

int dinoY;
int speed = 40;
int gameover = 0;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcursor(bool visible, DWORD size){
    if (size == 0) {
        size = 20; // default cursor size Changing to numbers from 1 to 20, decreases cursor width
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, & lpCursor);
}
 
void init() {
    system("cls"); 
    gameover = 0;
    gotoxy(3, 2); cout<<"SCORE : ";
    for (int i = 0; i < 79; i++){
    	gotoxy(1+i, 1); cout<<"ß";
    	gotoxy(1+i, 25); cout<<"ß";
	} 
}

void moveDino(int jump = 0) {
    static int foot = 0;

    if (jump == 0)
        dinoY = 0;
    else if (jump == 2)
        dinoY--;
    else dinoY++;

    gotoxy(dinoPos, 19 - dinoY);cout<<"      ____      ";
    gotoxy(dinoPos, 20 - dinoY);cout<<"     /    |     ";
    gotoxy(dinoPos, 21 - dinoY);cout<<"     | :V |     ";
    gotoxy(dinoPos, 22 - dinoY);cout<<"     |____/     ";
    gotoxy(dinoPos, 23 - dinoY);

    if (jump == 1 || jump == 2) {
        cout<<"     ____        ";
        gotoxy(2, 24 - dinoY);
        cout<<"    |    |       ";
    } 
	else if (foot == 0) {
        cout<<"    |    |       ";
        gotoxy(2, 24 - dinoY);
        cout<<"    |    |       ";
        foot = !foot;
    } 
	else if (foot == 1) {
        cout<<"      |    |     ";
        gotoxy(2, 24 - dinoY);
        cout<<"      /   /      ";
        foot = !foot;
    }
    
    gotoxy(2, 25 - dinoY);
    if (jump == 0) {
        cout<<"ßßßßßßßßßßßßßßßßß";
    } else {
        cout<<"                ";
    } 
    Sleep(speed);
}
void drawHurdle() {
    static int plantX = 0;
	static int score = 0;
    if (plantX == 56 && dinoY < 4) {
        score = 0;
        speed = 40;
        gotoxy(36, 8);cout<<"meninggoy";
        getch();
        gameover = 1; 
    }
    
    gotoxy(hurdlePos - plantX, 23);cout<<" [ ]  ";
    gotoxy(hurdlePos - plantX, 24);cout<<" [ ]  ";
     
    plantX++;
    
    if (plantX == 73) {
        plantX = 0;
        score++;
        gotoxy(11, 2);cout<<"     ";
        gotoxy(11, 2);cout<<score;
        if (speed > 20)
            speed--;
    }
}
void play(){ 
	system("cls");
    char ch;
    int i;
	init();
    while (true) {
        while (!kbhit()) {
            if( gameover==1 ){
            	return;
			}
			moveDino();
            drawHurdle();
        }
        ch = getch();
        if (ch == 32) {
        	i = 0;
            while( i < 12) {
                moveDino(1);
                drawHurdle();
                i++;
            }
            while(i > 0) {
                moveDino(2);
                drawHurdle();
                i--;
        	}
        }
		else if (ch == 'p'||ch=='P')
           getch();
		else if (ch == 27)
           break;
    }
}

int main() {

    setcursor(0, 0);
    
    do{
		system("cls");
		gotoxy(10,4); cout<<"GAME LOMPAT KOTAK";
		gotoxy(10,7); cout<<"1. Mulai ";
		gotoxy(10,8); cout<<"3. Keluar";
		char mulai = getche();
		
		if( mulai=='1') play();
		else if( mulai=='3') exit(0);
		
	}while(1);
    
	return 0;
}

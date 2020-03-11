#include <iostream>
#include <conio.h>

using namespace std;

bool GameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score, nTail;
int tailX[width * height], tailY[width * height];
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

bool isTail(int cx, int cy) {
	for (int k = 0; k < nTail; k++)
		if (tailX[k] == cx && tailY[k] == cy) return true;
	return false;
}
void Setup() {
	GameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = (rand() % width)+1;
	fruitY = (rand() % height)+1;
	score = 0;
	nTail = 0;
}

void Draw() {
	system("cls"); //system("clear"); //for linux
	cout << "Score: " << score << '\n';
	for (int i = 0; i < width + 2; i++)
		cout << '#';
	cout << '\n';

	for (int i = 0; i < height; i++) {
		cout << '#';
		for (int j = 0; j < width; j++) {
			if (i == y && j == x)
				cout << '0';
			else if (i == fruitY && j == fruitX)
				cout << 'F';
			else if (isTail(j, i))
				cout << 'o';
			else
				cout << ' ';
		}
	cout << '#' << '\n';
	}

	for (int i = 0; i < width+2; i++) 
		cout << '#';
	cout << '\n';
}

void Input(int n) {
	bool press = 0;
	for (int i = 0; i < n; i++) {
		if (_kbhit()) {
			switch (_getch())
			{
			case 'a':
				dir = LEFT;
				press = true;
				break;
			case 's':
				dir = DOWN;
				press = true;
				break;
			case 'd':
				dir = RIGHT;
				press = true;
				break;
			case 'w':
				dir = UP;
				press = true;
				break;
			case 'x':
				GameOver = true;
				press = true;
			}
		}
		if (press) break;
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0) 
	//	GameOver = true;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y) GameOver = true;
	if (x >= width) x = 0;
	if (x < 0) x = width - 1;

	if (y >= height) y = 0;
	if (y < 0) y = height - 1;

	if (x == fruitX && y == fruitY) {
		score+= 10;
		nTail++;
		while (isTail(fruitX = rand() % width, fruitY = rand() % height));
	}
}

int main() {
	Setup();
	while (!GameOver) {
		Draw();
		Input(500);
		Logic();
	}
	system("cls");
	cout << "~####~~~~####~~~##~~~##~#####~~~~####~~~##~~##~~#####~~~#####\n##~~~~~~##~~##~~###~###~##~~~~~~##~~##~~##~~##~~##~~~~~~##~~##\n##~###~~######~~##~#~##~####~~~~##~~##~~##~~##~~####~~~~#####\n##~~##~~##~~##~~##~~~##~##~~~~~~##~~##~~~####~~~##~~~~~~##~~##\n~####~~~##~~##~~##~~~##~#####~~~~####~~~~~##~~~~#####~~~##~~##\n\t\t\t Your score: " << score;
}
// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cmath>
using namespace std;

class chessFigurue {
public:
	char type; //К - Король, Ф - Ферзь, Л - Ладья, С - Слон, Г - Конь, п - пешка, # - пустая клетка
	int faction; // 0 - пустое поле, 1 - белые, 2 - чёрные
	bool PawnMovedTwo = 0;

};

void movePawn(chessFigurue chessPlate[8][8], chessFigurue &a, chessFigurue &b, int y1, int x1, int y2, int x2) {
	
	switch (a.faction)
	{
	case 2:
		if ((x1 == x2) && (y2 == y1 - 1)) {
			if (b.faction == 0) {
				a.PawnMovedTwo = 0;
				b = a;
				a.faction = 0;
				a.type = '#';
				break;
			}
			else {
				cout << "Клетка занята. Сходить нельзя" << endl;
				break;
			}
		}
		else if ((x1 == x2) && (y1==6)&&(y2==4)) {
			if (b.faction == 0) {
				b = a;
				b.PawnMovedTwo = 1;
				a.faction = 0;
				a.type = '#';
				break;
			}
			else {
				cout << "Клетка занята. Сходить нельзя" << endl;
				break;
			}
		}
		else {
			cout << "ОШИБКА" << endl;
		}
		
	}
} 
// поменять

void moveKnight(chessFigurue chessPlate[8][8], chessFigurue &a, chessFigurue &b, int y1, int x1, int y2, int x2) {
	bool canMove = 0;//будет ли ход коня соблюдать правила своего хода
	if ((abs(x1 - x2) == 2) && (abs(y1 - y2) == 1)) {
		canMove = 1;
	}
	else if ((abs(x1 - x2) == 1) && (abs(y1 - y2) == 2)) {
		canMove = 1;
	}
	if (canMove == 1) {
		switch (b.faction) {
		case 0:
			b = a;
			a.faction = 0;
			a.type = '#';
			break;
		case 1:
			if (a.faction == 2) {
				cout << "Вы съели : " << b.type << endl;
				b = a;
				a.faction = 0;
				a.type = '#';
				break;
			}
			else {
				cout << "Вы не можете ходить на свою фигуру" << endl;
				break;
			}
		case 2:
			if (a.faction == 1) {
				cout << "Вы съели : " << b.type << endl;
				b = a;
				a.faction = 0;
				a.type = '#';
				break;
			}
			else {
				cout << "Вы не можете ходить на свою фигуру" << endl;
				break;
			}

		}
	}
	else {
		cout << "Конь не может так ходить" << endl;
	}
}

void moveBishop(chessFigurue chessPlate[8][8], chessFigurue &a, chessFigurue &b, int y1, int x1, int y2, int x2) {
	if (abs(x2-x1) == abs(y2-y1)) {
		int checkSpaces = abs((x2 - x1)) - 1;//количество клеток между клетками y1x1 и y2x2
		int occupiedSpace = 0;//количество занятых клеток между y1x1 и y2x2
		
		if ((x1 == x2) || (y1 == y2)) {
			cout << "Вы не можете ходить сами на себя" << endl;
		}
		else {
			for (int i = 1; i < checkSpaces; i++) {
				if (chessPlate[y1 + i * (y2 - y1) / abs(y2 - y1)][x1 + i * (x2 - x1) / abs(x2 - x1)].faction != 0) { // y1 + i*(y2-y1)/abs(y2-y1) - чтобы узнать надо ли вычесть i или прибавить
					occupiedSpace++;
						cout << "Занята клетка: " << char(x1 + i * (x2 - x1) / abs(x2 - x1) + 'a') << y1 + i * (y2 - y1) / abs(y2 - y1) + 1 << endl; // char() нужно для преобразования числовой координаты обратно в буквенный номер столбца на поле
				}
			}
			if (occupiedSpace == 0) {
				switch (b.faction)
				{
				case 0:
					b = a;
					a.faction = 0;
					a.type = '#';
					break;
				case 1:
					if (a.faction == 2) {
						cout << "Вы съели: " << b.type << endl;
						b = a;
						a.faction = 0;
						a.type = '#';
					}
					else {
						cout << "Вы не можете ходить на свою фигуру" << endl;
					}
					break;
				case 2:
					if (a.faction == 1) {
						cout << "Вы съели: " << b.type << endl;
						b = a;
						a.faction = 0;
						a.type = '#';
					}
					else {
						cout << "Вы не можете ходить на свою фигуру" << endl;
					}
					break;
				default:
					cout << "Слон не может так ходить" << endl;
					break;
				}
			}
			else {
				cout << "На пути есть занятые клетки" << endl;
			}
		}
	}
	else {
		cout << "Слон не может так ходить" << endl;
	}
}

void moveRook(chessFigurue chessPlate[8][8], chessFigurue &a, chessFigurue &b, int y1, int x1, int y2, int x2) {
	
	if ((x2 == x1) || (y2 == y1)) {
		int checkSpaces = abs((x2 - x1) + (y1 - y2)) - 1;//количество клеток между клетками y1x1 и y2x2
		int occupiedSpace = 0;//количество занятых клеток между y1x1 и y2x2

		if ((x2 == x1) && (y2 != y1)) {
			for (int i = 1; i <= checkSpaces; i++) {

				if (chessPlate[(y1 + y2 - abs(y2 - y1)) / 2 + i][x2].faction != 0) {  // (y1 + y2 - abs(y2 - y1)) / 2 - выбирает наименьшее из двух переменных
					occupiedSpace++;
					cout << "Занята клетка: " << char(x2 + 'a') << (y1 + y2 - abs(y2 - y1)) / 2 + i + 1 << endl; // char() нужно для преобразования числовой координаты обратно в буквенный номер столбца на поле
				}
			}
		}
		else if ((y2 == y1) && (x2 != x1)) {
			for (int i = 1; i <= checkSpaces; i++) {

				if (chessPlate[y2][(x1 + x2 - abs(x1 - x2)) / 2 + i].faction != 0) {
					occupiedSpace++;
					cout << "Занята клетка: " << char((x1 + x2 - abs(x1 - x2)) / 2 + 'a' + i) << y1 + 1 << endl;
				}
			}

		}
		if (occupiedSpace == 0) {
			switch (b.faction) {
			case 0:
				b = a;
				a.type = '#'; a.faction = 0;
				break;
			case 1:
				if (a.faction == 2) {
					cout << "Вы съели: " << b.type << endl;
					b = a;
					a.type = '#'; a.faction = 0;
				}
				else {
					cout << "Вы не можете ходить на свою фигуру" << endl;
				}
				break;
			case 2:
				if (a.faction == 1) {
					cout << "Вы съели: " << b.type << endl;
					b = a;
					a.type = '#'; a.faction = 0;
				}
				else {
					cout << "Вы не можете ходить на свою фигуру" << endl;
				}
				break;
			default:
				cout << "Ладья не может так ходить" << endl;
				break;
			}
		}
		else {
			cout << "На пути есть занятые клетки" << endl;
		}
	}
	else {
		cout << "Ладья не может так ходить" << endl;
	}
}

void moveQueen(chessFigurue chessPlate[8][8], chessFigurue &a, chessFigurue &b, int y1, int x1, int y2, int x2) {
	int occupiedSpace = 0;//количество занятых клеток между y1x1 и y2x2
	int checkSpaces = 0; //количество занятых клеток между y1x1 и y2x2
	if ((x2 == x1) || (y2 == y1)) {
		checkSpaces = abs((x2 - x1) + (y1 - y2)) - 1;

		if ((x2 == x1) && (y2 != y1)) {
			for (int i = 1; i <= checkSpaces; i++) {

				if (chessPlate[(y1 + y2 - abs(y2 - y1)) / 2 + i][x2].faction != 0) {  // (y1 + y2 - abs(y2 - y1)) / 2 - выбирает наименьшее из двух переменных
					occupiedSpace++;
					cout << "Занята клетка: " << char(x2 + 'a') << (y1 + y2 - abs(y2 - y1)) / 2 + i + 1 << endl; // char() нужно для преобразования числовой координаты обратно в буквенный номер столбца на поле
				}
			}
		}
		else if ((y2 == y1) && (x2 != x1)) {
			for (int i = 1; i <= checkSpaces; i++) {

				if (chessPlate[y2][(x1 + x2 - abs(x1 - x2)) / 2 + i].faction != 0) {
					occupiedSpace++;
					cout << "Занята клетка: " << char((x1 + x2 - abs(x1 - x2)) / 2 + 'a' + i) << y1 + 1 << endl;
				}
			}
		}
		else {
			cout << "На пути есть занятые клетки" << endl;
		}
	}
	else if (abs(x2 - x1) == abs(y2 - y1)) {
		if ((x1 == x2) || (y1 == y2)) {
			cout << "Вы не можете ходить сами на себя" << endl;
		}
		else {
			for (int i = 1; i < checkSpaces; i++) {
				if (chessPlate[y1 + i * (y2 - y1) / abs(y2 - y1)][x1 + i * (x2 - x1) / abs(x2 - x1)].faction != 0) { // y1 + i*(y2-y1)/abs(y2-y1) - чтобы узнать надо ли вычесть i или прибавить
					occupiedSpace++;
					cout << "Занята клетка: " << char(x1 + i * (x2 - x1) / abs(x2 - x1) + 'a') << y1 + i * (y2 - y1) / abs(y2 - y1) + 1 << endl; // char() нужно для преобразования числовой координаты обратно в буквенный номер столбца на поле
				}
			}
		}
	}
	else {
		cout << "Ферзь не может так ходить" << endl;
	}
	if (((x2 == x1) || (y2 == y1)) ||(abs(x2 - x1) == abs(y2 - y1))) {
		if (occupiedSpace == 0) {
			switch (b.faction) {
			case 0:
				b = a;
				a.type = '#'; a.faction = 0;
				break;
			case 1:
				if (a.faction == 2) {
					cout << "Вы съели: " << b.type << endl;
					b = a;
					a.type = '#'; a.faction = 0;
				}
				else {
					cout << "Вы не можете ходить на свою фигуру" << endl;
				}
				break;
			case 2:
				if (a.faction == 1) {
					cout << "Вы съели: " << b.type << endl;
					b = a;
					a.type = '#'; a.faction = 0;
				}
				else {
					cout << "Вы не можете ходить на свою фигуру" << endl;
				}
				break;
			default:
				cout << "Ферзь не может так ходить" << endl;
				break;
			}
		}
		else {
			cout << "На пути есть занятые клетки" << endl;
		}

	}
}

void move(chessFigurue chessPlate[8][8], chessFigurue &a, chessFigurue &b, int y1, int x1, int y2, int x2) {
	if (a.type != '#') {
		switch (a.type)
		{
		case 'п':
			movePawn(chessPlate, a, b, y1, x1, y2, x2);
			break;
		case 'Л':
			moveRook(chessPlate, a, b, y1, x1, y2, x2);
			break;
		case 'С':
			moveBishop(chessPlate, a, b, y1, x1, y2, x2);
			break;
		case 'Ф':
			moveQueen(chessPlate, a, b, y1, x1, y2, x2);
			break;
		case 'Г':
			moveKnight(chessPlate, a, b, y1, x1, y2, x2);
			break;
		default:
			cout << "Вы выбрали пустую клетку" << endl;
			break;
		}
	} else {
		cout << "Вы выбрали пустую клетку" << endl;
	}
}



int main()
{
	setlocale(LC_ALL, "Russian");

	int checkEnd = 0;

	
	int x1; // x1,y1 координаты отправки; x2,y2 координаты назначения
	int y1;
	int x2;
	int y2;

	

	chessFigurue chessPlate[8][8]{};
	for (int x = 0; x < 8; x++) {
		chessPlate[0][x].type = 'п';
		chessPlate[0][x].faction = 1;
	}

	for (int y = 1; y < 7; y++) {
		for (int x = 0; x < 8; x++) {
			chessPlate[y][x].type = '#';
			chessPlate[y][x].faction = 0;

		}
	}

	for (int x = 0; x < 8; x++) {
		chessPlate[7][x].type = 'п';
		chessPlate[7][x].faction = 2;
	}

	cout << "К - Король, Ф - Ферзь, Л - Ладья, С - Слон, Г - Конь, п - пешка, # - пустая клетка" <<  endl;

	while (checkEnd == 0)
	{
		cout << endl;
		cout << "a b c d e f g h" << endl;
		for (int x = 0; x < 8; x++) { cout << '-' << ' '; }
		cout << endl;
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				cout << chessPlate[y][x].type << ' ';
			};
			cout <<'|'<< y+1<< endl;
		};
		
		
		//пользователь может ввести инструкцую хода в привычном в шахматах формате, к примеру: a4c2 или b1c2
		x1 = (cin.get() - 'a');//преобразуем код ascii символа в цифру, т.е. при вводе символа 'a' в переменной окажется 0, при 'b' окажется 1 и так далее
		y1 = ((cin.get() - '0')-1);
		x2 = (cin.get() - 'a');
		y2 = ((cin.get() - '0')-1);
		
		cin.ignore(1000, '\n');

		move(chessPlate, chessPlate[y1][x1], chessPlate[y2][x2], y1, x1, y2, x2);
		
		//cout << endl;
		//cin >> checkEnd;
		//cin.ignore(1000, '\n');
	}
}

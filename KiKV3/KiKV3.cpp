#include <iostream>
#include <Windows.h>
#include <string>
#include <locale.h>
#include <time.h>
#include <cstdlib>

int winsP1 = 0;
int winsP2 = 0;
int& wP1 = winsP1;
int& wP2 = winsP2;

void game(std::string& nick1, std::string& nick2, int& mode);

bool isNotGoodPos(std::string pos)
{
	if (pos[1] || !(isdigit(pos[0]))) return true;

	return false;
}
void nickCreator()
{
	int mode;
	int flag = 1;

	std::string nick1;
	std::string nick2;

	system("CLS");

	std::cout << "Wybierz tryb:\n";
	std::cout << "VS Komputer (wciśnij k)\n";
	std::cout << "VS Gracz (wciśnij g)\n";

	while (flag == 1)
	{
		Sleep(50);
		if (GetAsyncKeyState('K') & 0x8000)
		{
			mode = 0;
			flag = 0;
		}
		if (GetAsyncKeyState('G') & 0x8000)
		{
			mode = 1;
			flag = 0;
		}
	}

	std::cin.clear();
	system("CLS");

	if (mode == 0)
	{
		std::cout << "Podaj swoją nazwę: ";
		std::cin >> nick1;
		nick2 = "komputer";
	}
	else if (mode == 1)
	{
		std::cout << "Podaj nazwę gracza 1: ";
		std::cin >> nick1;

		system("CLS");

		std::cout << "Podaj nazwę gracza 2: \n";
		std::cin >> nick2;
	}
	
	game(nick1, nick2, mode);
}
void reloadBoard(char a, char b, char c, char d, char e, char f, char g,char h,char i)
{
	char board[9] = {a,b,c,d,e,f,g,h,i};

	system("CLS");

	std::cout << "###################" << std::endl;
	std::cout << "#     #     #     #" << std::endl;
	std::cout << "#  " << board[0] << "  #  " << board[1] << "  #  " << board[2] << "  #" << std::endl;
	std::cout << "#    1#    2#    3#" << std::endl;
	std::cout << "###################" << std::endl;
	std::cout << "#     #     #     #" << std::endl;
	std::cout << "#  " << board[3] << "  #  " << board[4] << "  #  " << board[5] << "  #" << std::endl;
	std::cout << "#    4#    5#    6#" << std::endl;
	std::cout << "###################" << std::endl;
	std::cout << "#     #     #     #" << std::endl;
	std::cout << "#  " << board[6] << "  #  " << board[7] << "  #  " << board[8] << "  #" << std::endl;
	std::cout << "#    7#    8#    9#" << std::endl;
	std::cout << "###################" << std::endl;
	std::cout << "\n\n";
}

void intermission(std::string& nick1, std::string& nick2, int& mode)
{
	std::cin.clear();

	std::cout << "Wygrane " << nick1 << ": " << wP1 << "\n";
	std::cout << "Wygrane " << nick2 << ": " << wP2 << "\n\n";

	Sleep(1000);

	std::cout << "Chcesz zagrać kolejną rundę? (wciśnij enter by rozpocząć, escape by wyjść)";

	while (true)
	{
		Sleep(50);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) return;

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			game(nick1, nick2, mode);
			return;
		}
	}
}
void game(std::string& nick1, std::string& nick2, int& mode)
{
	std::cin.clear();
	system("CLS");

	char board[9] = {' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

	std::string nick[2] = { nick1, nick2 };
	int currentPlayer = 0;
	int victoriousPlayer;
	int posInt;
	int temp = 0;
	int randField;
	

	bool win = false;
	bool occupiedField = false;

	std::string pos;
	
	do
	{
		do randField = rand() % 9 + 1;
		while (board[randField - 1] != ' ');
			 
		do
		{
			reloadBoard(board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8]);

			if (occupiedField)
			{
				std::cout << "W tym miejscu już znajduje się znak \n";
				occupiedField = false;
			}

			if (mode == 1)
			{
				std::cout << "Teraz kolej gracza " << nick[currentPlayer] << "\n";
				std::cout << "Gdzie chcesz dać znak? \n";
				std::cin >> pos;
			}
			else if (mode == 0 && currentPlayer == 0)
			{
				std::cout << "Teraz twoja kolej \n";
				std::cout << "Gdzie chcesz dać znak? \n";
				std::cin >> pos;
			}
			else if (mode == 0 && currentPlayer == 1)
			{
				std::cout << "Teraz kolej komputera \n";
				std::cout << "Wybrane pole: ";
				Sleep(700);
				std::cout << randField << "\n";
				Sleep(500);
				pos = std::to_string(randField);
			}

		} while (isNotGoodPos(pos) || pos == "0");

		posInt = std::stoi(pos,nullptr,10);

		if (board[posInt-1] != ' ') occupiedField = true;
		else
		{
			victoriousPlayer = currentPlayer;

			if (currentPlayer == 0)
			{
				board[posInt - 1] = 'X';
				currentPlayer = 1;
				temp++;
			}
			else if (currentPlayer == 1)
			{
				board[posInt - 1] = 'O';
				currentPlayer = 0;
				temp++;
			}

			for (int x = 0; x < 3; x++)
			{
				if (board[x] == board[x + 3] && board[x + 3] == board[x + 6] && board[x] != ' ') win = true;
				if (board[3 * x] == board[3 * x + 1] && board[3 * x + 1] == board[3 * x + 2] && board[3 * x] != ' ') win = true;
			}
			if (board[0] == board[4] && board[4] == board[8] && board[0] != ' ') win = true;
			if (board[2] == board[4] && board[4] == board[6] && board[2] != ' ') win = true;
		}
	} while (win != true && temp < 9);

	system("CLS");

	std::cout << "Koniec gry! \n";
	if (temp >= 9) std::cout << "Remis!\n";
	else
	{
		std::cout << "Wygrał " << nick[victoriousPlayer] << "\n";

		if (victoriousPlayer == 0) wP1++;
		else if (victoriousPlayer == 1) wP2++;
	}

	Sleep(1500);
	intermission(nick[0], nick[1], mode);
}
int main()
{
	setlocale(LC_CTYPE, "Polish");

	srand(time(NULL));

	std::cout << "Kolko i Krzyzyk \n";
	std::cout << "Wersja: 3.0 \n";
	std::cout << "Wciśnij enter aby rozpocząć, escape by wyjść \n";

	while (true)
	{
		Sleep(50);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) return 0;
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) nickCreator();
	}
}
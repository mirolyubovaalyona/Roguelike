#pragma once
#include "GameLoop.h"

using namespace std;
const int quantity = 5;

class MainMenue {
private:
	int pointer;
	string picture;
	string text;
	string menue[quantity] = {
		"New Game",
		"Load Game", 
		"Show Highscores",
		"Show Manual", 
		"Quit Game"
	};

	string question[quantity] = {
		" This will erase your previously saved game.\n Are you sure ? \n\n     y / n\n \n",
		"    Are you sure ?\n      ?????? \n\n      y / n\n \n",
		"    Are you sure ?\n      ?????? \n\n      y / n\n \n",
		"    Are you sure ?\n      ?????? \n\n      y / n\n \n",
		"    Are you sure ?\n      ?????? \n\n      y / n\n \n"
	};
	string press_enter = "  Press <Enter> to continue...";

	string esc[4] = {
		"Return to game",
		"Help     <No one can help you...>",
		"Save and quit        <keep score>",
		"Quit"
	};


	void Help() {
		bool c = true;
		while (c) {
			Draw(picture);
			cout << "    No one can help you...\n      No one can help you...\n        No one can help you...\n          No one can help you...\n";
			cout << "\n" << press_enter;
			if (_kbhit()) {
				if (_getch() == 13) {
					c = false;
				}
			}
			system("cls");
		}
	}

	void Score() {
		string s = "";
		string crown = "";
		std::ifstream in("Score.txt");
		if (in.is_open()) {
			while (!in.eof()) {
				getline(in, s);;
				crown += s + "\n";
			}
		}
		in.close();
		bool c = true;
		while (c) {
			Draw(crown+ "\n"+text);
			cout << "\n" << press_enter;
			if (_kbhit()) {
				if (_getch() == 13) {
					c = false;
				}
			}
			system("cls");
		}
		Menue();
	}

	void  Input(char d, int a) {
			switch (d) {
			case 'w':
				if (pointer > 0)
				pointer --;
				break;
			case 's':
				if (pointer < a -1)
					pointer++;
				break;
			}

	}

	void Menue() {
		pointer = 0;
		bool c = true;
		char d;
		while (c) {
			system("cls");
			Draw(picture + text);
			for (int i = 0; i < quantity; i++) {
				if (pointer == i) {
					cout << " ==> x " << menue[i] << " x\n";
				}
				else {
					cout << "    O " << menue[i] << " O\n";
				}
			}
			if (_kbhit()) {
				d = _getch();
				if (d == 13) {
					c = false;
				}
				else {
					Input(d, quantity);
				}
			}
		}
		Question();
	}

	void Question() {
		bool c = true;
		char d;
		while (c) {
			system("cls");
			Draw(picture);
			cout << question[pointer];
			for (int i = 0; i < quantity; i++) {
				if (pointer == i) {
					cout << " ==> x " << menue[i] << " x\n";
				}
				else {
					cout << "    O " << menue[i] << " O\n";
				}
			}
			if (_kbhit()) {
				d = _getch();
				if (d == 'y') {
					switch (pointer){
						case 2:
							Score();
						case 3:
							Help();
							Menue();
						case 4:
							exit(1);
					}
					c = false;
				}
				if (d == 'n') {
					c = false;
					Menue();
				}
			}
		}
	}

public:
	MainMenue() {
		picture = "";
		text = "";
		string s;
        std::ifstream in("candle.txt");
        if (in.is_open()) {
            while (!in.eof()) {
				getline(in, s);;
				picture += s + "\n";
            }
        }
        in.close();
		std::ifstream inp("mainText.txt");
		if (inp.is_open()) {
			while (!inp.eof()) {
				getline(inp, s);
				text += s + "\n";
			}
		}
		inp.close();
	}

	void Start() {
		bool c = true;
		while (c) {
			Draw(picture + text);
			cout << "\n" << press_enter;
			if (_kbhit()) {
				if (_getch() == 13) {
					c = false;
				}
			}
			system("cls");
		}
		Menue();
	}

	void Draw(string s) {
		cout << s;
	}

	bool Esc(int score) {
		pointer = 0;
		bool c = true;
		char d;
		while (c) {
			system("cls");
			Draw(picture);
			for (int i = 0; i < 4; i++) {
				if (pointer == i) {
					cout << " ==> x " << esc[i] << " x\n";
				}
				else {
					cout << "    O " << esc[i] << " O\n";
				}
			}
			if (_kbhit()) {
				d = _getch();
				if (d == 13) {
					c = false;
				}
				else {
					Input(d, 4);
				}
			}
		}
		std::ofstream vmdelet_out;                    //создаем поток 
		switch (pointer){
			case 0:
				return false;
				break;
			case 1:
				Help();
				Esc(score);
				return false;
				break;
			case 2:
				vmdelet_out.open("Score.txt", std::ios::app);  // открываем файл для записи в конец
				vmdelet_out << score << "\n";                        // сама запись
				vmdelet_out.close();
				return true;
				break;
			case 3:
				return true;
				break;
		}
	}
	
	void ToWin (int score) {
		std::ofstream vmdelet_out;
		vmdelet_out.open("Score.txt", std::ios::app);
		vmdelet_out << score << "\n";
		vmdelet_out.close();
		string s = "";
		string crown = "";
		std::ifstream in("crown.txt");
		if (in.is_open()) {
			while (!in.eof()) {
				getline(in, s);;
				crown += s + "\n";
			}
		}
		in.close();
		bool c = true;
		while (c) {
			Draw(crown);
			cout << "\n" << press_enter;
			if (_kbhit()) {
				if (_getch() == 13) {
					c = false;
				}
			}
			system("cls");
		}
	}
	void ToLose (int score) {
		std::ofstream vmdelet_out;
		vmdelet_out.open("Score.txt", std::ios::app);
		vmdelet_out << score << "\n";
		vmdelet_out.close();
		string s = "";
		string crown = "";
		std::ifstream in("dead.txt");
		if (in.is_open()) {
			while (!in.eof()) {
				getline(in, s);;
				crown += s + "\n";
			}
		}
		in.close();
		bool c = true;
		while (c) {
			Draw(crown);
			cout << "\n" << press_enter;
			if (_kbhit()) {
				if (_getch() == 13) {
					c = false;
				}
			}
			system("cls");
		}
	}


};


/*MainMenue::MainMenue()
{
}

MainMenue::~MainMenue()
{
}*/
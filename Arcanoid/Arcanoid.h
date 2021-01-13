#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <conio.h>
#include "win10.h"

#define StdRowMenu 14
#define StdColumnMenu 30
#define StdMenuW 29
#define StdMenuH 14

#define StdKolButton 10

#define StdStrelkaX 2
#define StdStrelkaY 2

#define StdScorePosX 40 
#define StdScorePosY 7 

#define KraiY 19

#define LeftKraiBat 0
#define RightKraiBat 17

#define LeftBatBall -1
#define MiddleBatBall 0
#define RightBatBall 1

#define RightWallBall 0
#define LeftWallBall 2
#define UpWallBall 1
#define DownWallBall 3
#define LeftDownWallBall 4
#define LeftUpWallBall 5
#define RightDownWallBall 6
#define RightUpWallBall 7

#define StdMinusVel 5

#define HP1 1
#define HP3 3
#define HP5 5

#define StandartKolUnUpAndDown 22
#define StandartKolUnLeftAndRight 20
#define StandartKolBr 10

#define StdX 8
#define StdY 3
#define StdW 22
#define StdH 20
#define StdVel 50

#define BallSpawnX 5
#define BallSpawnY 7
#define BatSpawnX 8
#define BatSpawnY 17

#define DIR_MAX 6
#define RND(min, max) rand() % ((max) - (min) + 1) + (min)
using namespace std;
enum button_fun_result { new_game = 0, continue_ = 1, shop = 2, save = 3, load = 4, top5 = 5, help = 6, infoAboutCreator = 7, def_settings = 8, exit_ = 9, null = 100 };
enum direct_move { up, down, up_left, up_right, down_left, down_right };
enum dir_contr { left = 75, right = 77, enter = 13, escape = 27, strelka_up = 72, strelka_down = 80 };
int _left = dir_contr::left, _right = dir_contr::right;
bool isGame = false;
bool finishProg = false;
class Obj {
public:
	static int kol_game;
	static int _x, _y, _w, _h;
};
int Obj::_x = 8, Obj::_y = 3, Obj::_w = 0, Obj::_h = 0, Obj::kol_game = 0;
class Player : virtual public Obj {
private:
	string _name;
	long long _point;
public:
	Player() : _name("St_Player"), _point() {}
	Player(string& name) : _name(name), _point() {}
	Player(int point) : _name(), _point(point) {}
	Player(long long point) : _name(), _point(point) {}
	Player(string& name, int point) : _name(name), _point(point) {}
	Player(string& name, long long point) : _name(name), _point(point) {}

	void printGame() {
		SetPos(40, 7);
		cout << "Score: " << _point;
	}
	void setName() {
		SetPos(40, 9);
		cout << "Write Yout NickName: ";
		cin >> _name; cin.ignore();
	}
	void print() {

	}
};

class wall : virtual public Obj {
protected:
	int _xPos, _yPos;
	string sym;
public:
	wall(int x, int y) : _xPos(x), _yPos(y) { sym = "\xB1\xB1"; }
	wall() : _xPos(NULL), _yPos(NULL) { sym = "\xB1\xB1"; }
	int getXPos() { return _xPos; }
	int getYPos() { return _yPos; }
	void setPos(int x, int y) { _xPos = x; _yPos = y; }
	void setSym(string& _sym) { sym = _sym; }
	virtual void damage() = 0;
	virtual bool IsKilled() = 0;
	virtual void prov() = 0;
	virtual void print() = 0;
	virtual ~wall() = 0;
};
wall::~wall() {}

class wall_1h : virtual public wall {
private:
	int _helth;
	bool isKilled;
public:
	wall_1h(int x, int y) : _helth(HP1), isKilled(false), wall(x, y) { }
	wall_1h() : _helth(HP1), isKilled(false), wall() {  }
	virtual void damage() override { _helth--; }
	virtual bool IsKilled() override { return isKilled; }
	virtual void prov() override {
		if (_helth <= 0) {
			isKilled = true;
		}
	}
	virtual void print() override {
		if (!isKilled) {
			SetPos(_x + _xPos, _y + _yPos);
			SetColor(0xC);
			cout << sym;
		}
		else {
			SetPos(_x + _xPos, _y + _yPos);
			cout << "  ";
		}
	}
	virtual ~wall_1h() {}
};

class wall_3h : virtual public wall {
private:
	int _helth;
	bool isKilled;
public:
	wall_3h(int x, int y) : _helth(HP3), isKilled(false), wall(x, y) {  }
	wall_3h() : _helth(HP3), isKilled(false), wall() {  }
	virtual void damage() override { _helth--; }
	virtual bool IsKilled() override { return isKilled; }
	virtual void prov() override {
		if (_helth <= 0) {
			isKilled = true;
		}
	}
	virtual void print() override {
		if (!isKilled) {
			SetPos(_x + _xPos, _y + _yPos);
			SetColor(0xA);
			cout << sym;
		}
		else {
			SetPos(_x + _xPos, _y + _yPos);
			cout << "  ";
		}
	}
	virtual ~wall_3h() {}
};

class wall_5h : virtual public wall {
private:
	int _helth;
	bool isKilled;
public:
	wall_5h(int x, int y) : _helth(HP5), isKilled(false), wall(x, y) {  }
	wall_5h() : _helth(HP5), isKilled(false), wall() {  }
	virtual void damage() override { --_helth; }
	virtual bool IsKilled() override { return isKilled; }
	virtual void prov() override {
		if (_helth <= 0) {
			isKilled = true;
		}
	}
	virtual void print() override {
		if (!isKilled) {
			SetPos(_x + _xPos, _y + _yPos);
			SetColor(0x9);
			cout << sym;
		}
		else {
			SetPos(_x + _xPos, _y + _yPos);
			cout << "  ";
		}
	}
	virtual ~wall_5h() {}
};

class wall_unbreak : virtual public wall {
public:
	wall_unbreak(int x, int y) : wall(x, y) { sym = '\XB1'; }
	wall_unbreak() : wall() { sym = '\xB1'; }
	virtual void damage() override {}
	virtual bool IsKilled() override { return 0; }
	virtual void prov() override {}
	virtual void print() override {
		::SetPos(_x + _xPos, _y + _yPos);
		::SetColor(0x8);
		cout << sym;
	}
	virtual ~wall_unbreak() {}
};

class ball : virtual public Obj {
protected:
	string _sym;
	int _xPosPrev, _yPosPrev;
	int _xPos, _yPos;
	direct_move _direction;
public:
	int _vel;
	ball(int x, int y) : _xPos(x), _yPos(y), _xPosPrev(-1), _yPosPrev(-1), _direction(direct_move::down), _vel(StdVel) { _sym = "*"; }
	ball() : _xPos(), _yPos(), _xPosPrev(-1), _yPosPrev(-1), _direction(direct_move::down), _vel(StdVel) { _sym = "*"; }
	int getXPos() { return _xPos; }
	int getYPos() { return _yPos; }
	int getVel() { return _vel; }
	direct_move getDir() { return _direction; }
	void setPos(int x, int y) { _xPos = x; _yPos = y; }
	void setDir(direct_move dir) {
		_direction = dir;
	}
	void setVel(int vel) { _vel = vel; }
	bool isMove() {
		if (_xPos == _xPosPrev && _yPos == _yPosPrev) { return false; }
		return true;
	}
	void move() {
		_xPosPrev = _xPos;
		_yPosPrev = _yPos;
		switch (_direction) {
		case direct_move::up:
			_yPos--; break;
		case direct_move::down:
			_yPos++; break;
		case direct_move::up_left:
			_yPos--; _xPos--; break;
		case direct_move::up_right:
			_yPos--; _xPos++; break;
		case direct_move::down_left:
			_yPos++; _xPos--; break;
		case direct_move::down_right:
			_yPos++; _xPos++; break;
		}
	}
	virtual void print() = 0;
	virtual ~ball() = 0;
};
ball::~ball() {}

class ball_st : virtual public ball {
public:
	ball_st(int x, int y) : ball(x, y) {}
	ball_st() : ball() {}
	virtual void print() override {
		if (isMove()) {
			SetPos(_x + _xPosPrev, _y + _yPosPrev);
			cout << " ";
			SetPos(_x + _xPos, _y + _yPos);
			cout << _sym;
		}
	}
	virtual ~ball_st() {}
};

class bat : virtual public Obj {
protected:
	string _sym;
	int _xPosPrev, _yPosPrev;
	bool isMove;
	int _xPos, _yPos;
public:
	bat(int x, int y) : _xPos(x), _yPos(y), _xPosPrev(-1), _yPosPrev(_yPos), isMove(false) {
		_sym = "\x16\x16\x16\x16\x16";
	}
	bat() : _xPos(NULL), _yPos(NULL), _xPosPrev(-1), _yPosPrev(_yPos), isMove(false) { _sym = "\x16\x16\x16\x16\x16"; }
	int getXPos() { return _xPos; }
	int getYPos() { return _yPos; }
	void setPos(int x, int y) { _xPos = x; _yPos = y; }
	bool IsMove() {
		if (_xPos == _xPosPrev && _yPos == _yPosPrev) { return false; }
		return true;
	}
	void move(int key) {
		_xPosPrev = _xPos;
		_yPosPrev = _yPos;
		if (key == _left) {
			_xPos--;
			isMove = true;
			if (_xPos == LeftKraiBat) { _xPos++; isMove = false; }
		}
		else if (key == _right) {
			_xPos++;
			isMove = true;
			if (_xPos == RightKraiBat) { _xPos--; isMove = true; }
		}
	}
	virtual void print() = 0;
	virtual ~bat() = 0;
};
bat::~bat() {}

class bat_st : virtual public bat {
public:
	bat_st() : bat() {}
	bat_st(int x, int y) : bat(x, y) {}
	virtual void print() override {
		SetPos(_x + _xPosPrev, _y + _yPosPrev);
		cout << "     ";
		SetPos(_x + _xPos, _y + _yPos);
		SetColor(0x9);
		cout << _sym;
	}
	virtual ~bat_st() {}
};
//bat
int operator==(bat& _bat, ball& _ball) {
	if (_bat.getYPos() == _ball.getYPos() + 1) {
		if ((_bat.getXPos() == _ball.getXPos()) || (_bat.getXPos() + 1 == _ball.getXPos())) {
			return LeftBatBall;
		}
		else if (_bat.getXPos() + 2 == _ball.getXPos()) { return MiddleBatBall; }
		else if ((_bat.getXPos() + 3 == _ball.getXPos()) || (_bat.getXPos() + 4 == _ball.getXPos())) {
			return RightBatBall;
		}
	}
}
int operator==(ball& _ball, bat& _bat) {
	return _bat == _ball;
}
//wall_unbreak_left
bool operator<(ball& _ball, wall* _wall) {
	if ((_wall->getXPos() + 1 == _ball.getXPos()) && (_wall->getYPos() == _ball.getYPos())) {
		return true;
	}
	return false;
}
bool operator<(wall* _wall, ball& _ball) {
	return _ball < _wall;
}
//wall_unbreak_right
bool operator>(ball& _ball, wall* _wall) {
	if ((_wall->getXPos() == _ball.getXPos() + 1) && (_wall->getYPos() == _ball.getYPos())) {
		return true;
	}
	return false;
}
bool operator>(wall* _wall, ball& _ball) {
	return _ball > _wall;
}
//wall_unbreak_up
bool operator^(ball& _ball, wall* _wall) {
	if ((_wall->getXPos() == _ball.getXPos()) && (_wall->getYPos() + 1 == _ball.getYPos())) {
		return true;
	}
	return false;
}
bool operator^(wall* _wall, ball& _ball) {
	return _ball ^ _wall;
}
//wall_break
int operator*(ball& _ball, wall* _wall) {
	if (((_wall->getXPos() == _ball.getXPos()) && (_wall->getYPos() == _ball.getYPos() - 1)) ||
		((_wall->getXPos() == _ball.getXPos() - 1) && (_wall->getYPos() == _ball.getYPos() - 1)))
	{
		return DownWallBall;
	}
	else if ((_wall->getXPos() == _ball.getXPos() + 1) && (_wall->getYPos() == _ball.getYPos()))
	{
		return LeftWallBall;
	}
	else if ((_wall->getXPos() == _ball.getXPos() - 1) && (_wall->getYPos() == _ball.getYPos()))
	{
		return RightWallBall;
	}
	else if (((_wall->getXPos() == _ball.getXPos()) && (_wall->getYPos() == _ball.getYPos() + 1)) ||
		((_wall->getXPos() == _ball.getXPos() - 1) && (_wall->getYPos() == _ball.getYPos() + 1)))
	{
		return UpWallBall;
	}
	else if ((_wall->getXPos() == _ball.getXPos() + 1) && (_wall->getYPos() == _ball.getYPos() - 1)) {
		return LeftDownWallBall;
	}
	else if ((_wall->getXPos() == _ball.getXPos() + 1) && (_wall->getYPos() == _ball.getYPos() + 1)) {
		return LeftUpWallBall;
	}
	else if ((_wall->getXPos() == _ball.getXPos() - 2) && (_wall->getYPos() == _ball.getYPos() + 1)) {
		return RightUpWallBall;
	}
	else if ((_wall->getXPos() == _ball.getXPos() - 2) && (_wall->getYPos() == _ball.getYPos() - 1)) {
		return RightDownWallBall;
	}
	return -5;
}
int operator*(wall* _wall, ball& _ball) {
	return _ball * _wall;
}

class Button : virtual public Obj {
private:
	int _xPos, _yPos;
	string _name;
public:
	Button() : _name(), _xPos(), _yPos() {}
	Button(string name, int _x, int _y) : _name(name), _xPos(_x), _yPos(_y) {}
	Button(const char* name, int _x, int _y) : _name(name), _xPos(_x), _yPos(_y) {}
	virtual void print() {
		SetPos(_x + _xPos, _y + _yPos);
		cout << _name;
	}
	virtual button_fun_result fun() = 0;
	virtual ~Button() = 0;
};
Button::~Button() {}
class NewGame_button : virtual public Button {
public:
#define NewGameX 4
#define NewGameY 2
	NewGame_button() : Button("New Game", NewGameX, NewGameY) {}
	virtual button_fun_result fun() {
		return button_fun_result::new_game;
	}
	virtual ~NewGame_button() {}
};
class Continue_button : virtual public Button {
public:
#define ContinueX 4
#define ContinueY 3
	Continue_button() : Button("Continue", ContinueX, ContinueY) {}
	virtual button_fun_result fun() {
		return button_fun_result::continue_;
	}
	virtual ~Continue_button() {}
};
class Shop_button : virtual public Button {
public:
#define ShopX 4
#define ShopY 4
	Shop_button() : Button("Shop", ShopX, ShopY) {}
	virtual button_fun_result fun() {
		return button_fun_result::shop;
	}
	virtual ~Shop_button() {}
};
class Save : virtual public Button {
public:
#define SaveX 4
#define SaveY 5
	Save() : Button("Save", SaveX, SaveY) {}
	virtual button_fun_result fun() {
		return button_fun_result::save;
	}
	virtual ~Save() {}
};
class Load : virtual public Button {
public:
#define LoadX 4
#define LoadY 6
	Load() : Button("Load", LoadX, LoadY) {}
	virtual button_fun_result fun() {
		return button_fun_result::load;
	}
	virtual ~Load() {}
};
class Top5_button : virtual public Button {
public:
#define Top5X 4 
#define Top5Y 7 
	Top5_button() : Button("Top 5 list", Top5X, Top5Y) {}
	virtual button_fun_result fun() {
		return button_fun_result::top5;
	}
	virtual ~Top5_button() {}
};
class Help_button : virtual public Button {
public:
#define HelpX 4
#define HelpY 8
	Help_button() : Button("Help (F1)", HelpX, HelpY) {}
	virtual button_fun_result fun() {
		return button_fun_result::help;
	}
	virtual ~Help_button() {}
};
class InfoAboutCreator_button : virtual public Button {
#define StdRowCon 13
#define StdColumnCon 31
	char infoAboutCreator[StdRowCon][StdColumnCon]
	{
		"$$$$$$$$$$$$$$$$$$$$$$$$$$$",
		"$                         $",
		"$ Game: 2048              $",
		"$ Name: Alisher           $",
		"$ Group: SEP-181          $",
		"$ Age: 15                 $",
		"$ Teacher: Kasenov Zhanat $",
		"$                         $",
		"$$$$$$$$$$$$$$$$$$$$$$$$$$$",
	};
public:
#define InfoAboutX 4
#define InfoAboutY 9
	InfoAboutCreator_button() : Button("Info About Creator", InfoAboutX, InfoAboutY) {}
	virtual button_fun_result fun() {
		system("cls");
		for (int i = 0; i < StdRowCon; i++) {
			SetPos(_x, _y + i);
			for (int j = 0; j < StdColumnCon; j++) {
				if (infoAboutCreator[i][j] == '$') {
					cout << char(177);
				}
				else {
					cout << infoAboutCreator[i][j];
				}
			}
		}
		while (true)
		{
			int key = _getch();
			if (key == dir_contr::escape) {
				system("cls");
				break;
			}
		}
		return button_fun_result::infoAboutCreator;
	}
	virtual ~InfoAboutCreator_button() {}
};
class DefaultSettings_button : virtual public Button {
#define StdRowSettings 9
#define StdColumnSettings 33
	char settings_menu[StdRowSettings][StdColumnSettings] = {
		"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
		"$                           $",
		"$   DEFAULT SETTING IS SET  $",
		"$                           $",
		"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
	};
public:
#define DefaultSettingsX 4
#define DefaultSettingsY 10
	DefaultSettings_button() : Button("Default Settings", DefaultSettingsX, DefaultSettingsY) {}
	virtual button_fun_result fun() {
		system("cls");
		for (int i = 0; i < StdRowSettings; i++) {
			SetPos(_x, _y + i);
			for (int j = 0; j < StdColumnSettings; j++) {
				if (settings_menu[i][j] == '$') {
					cout << char(177);
				}
				else {
					cout << settings_menu[i][j];
				}
			}
		}
		Sleep(200);
		system("cls");
		return button_fun_result::def_settings;
	}
	virtual ~DefaultSettings_button() {}
};
class Exit_button : virtual public Button {
public:
#define ExitX 4
#define ExitY 11
	Exit_button() : Button("Exit (ESC)", ExitX, ExitY) {}
	virtual button_fun_result fun() {
		return button_fun_result::exit_;
	}
	virtual ~Exit_button() {}
};

class Game_Pole : virtual public Obj {
protected:
	int _x, _y, _w, _h;
	wall** _unbreak_up;
	wall** _unbreak_down;
	wall** _unbreak_left;
	wall** _unbreak_right;
	wall** _break_5h;
	wall** _break_3h;
	wall** _break_1h;
	ball* _ball;
	bat* _bat;
public:
	Game_Pole() : _x(StdX), _y(StdY), _w(StdW), _h(StdH) {
		Obj::_x = _x;
		Obj::_y = _y;
		Obj::_w = _w;
		Obj::_h = _h;
		_unbreak_up = new wall * [StandartKolUnUpAndDown];
		_unbreak_down = new wall * [StandartKolUnUpAndDown];
		_unbreak_left = new wall * [StandartKolUnLeftAndRight];
		_unbreak_right = new wall * [StandartKolUnLeftAndRight];
		for (int i = 0; i < StandartKolUnUpAndDown; i++) {
			_unbreak_up[i] = new wall_unbreak;
			_unbreak_down[i] = new wall_unbreak;
		}
		for (int i = 0; i < StandartKolUnLeftAndRight; i++) {
			_unbreak_left[i] = new wall_unbreak;
			_unbreak_right[i] = new wall_unbreak;
		}
		for (int i = 0, x = 0, yUp = 0, yDown = 20; i < StandartKolUnUpAndDown; i++, x++) {
			_unbreak_up[i]->setPos(x, yUp);
			_unbreak_down[i]->setPos(x, yDown);
		}
		for (int i = 0, y = 1, xLeft = 0, xRight = 21; i < StandartKolUnLeftAndRight; i++, y++) {
			_unbreak_left[i]->setPos(xLeft, y);
			_unbreak_right[i]->setPos(xRight, y);
		}

		_break_5h = new wall * [StandartKolBr];
		_break_3h = new wall * [StandartKolBr];
		_break_1h = new wall * [StandartKolBr];
		for (int i = 0; i < StandartKolBr; i++) {
			_break_1h[i] = new wall_1h;
			_break_3h[i] = new wall_3h;
			_break_5h[i] = new wall_5h;
		}
		for (int i = 0, x = 1, y1 = 5, y3 = 4, y5 = 3; i < StandartKolBr; i++, x += 2) {
			_break_1h[i]->setPos(x, y1);
			_break_3h[i]->setPos(x, y3);
			_break_5h[i]->setPos(x, y5);
		}

		_ball = new ball_st(BallSpawnX, BallSpawnY);
		_bat = new bat_st(BatSpawnX, BatSpawnY);
	}
	void print() {
		for (int i = 0; i < StandartKolUnUpAndDown; i++) {
			_unbreak_up[i]->print();
			_unbreak_down[i]->print();
		}
		for (int i = 0; i < StandartKolUnLeftAndRight; i++) {
			_unbreak_left[i]->print();
			_unbreak_right[i]->print();
		}
		for (int i = 0; i < StandartKolBr; i++) {
			_break_1h[i]->print();
			_break_3h[i]->print();
			_break_5h[i]->print();
		}
		_ball->print();
		if (_bat->IsMove()) {
			_bat->print();
		}
	}
	inline void Clear() {
		delete _ball;
		delete _bat;
		for (int i = 0; i < StandartKolUnUpAndDown; i++) {
			delete _unbreak_up[i];
			delete _unbreak_down[i];
		}
		for (int i = 0; i < StandartKolUnLeftAndRight; i++) {
			delete _unbreak_left[i];
			delete _unbreak_right[i];
		}
		for (int i = 0; i < StandartKolBr; i++) {
			delete _break_1h[i];
			delete _break_3h[i];
			delete _break_5h[i];
		}
		delete[] _unbreak_up;
		delete[] _unbreak_down;
		delete[] _unbreak_left;
		delete[] _unbreak_right;
		delete[] _break_5h;
		delete[] _break_3h;
		delete[] _break_1h;
	}
	inline void StartSet() {
		_unbreak_up = new wall * [StandartKolUnUpAndDown];
		_unbreak_down = new wall * [StandartKolUnUpAndDown];
		_unbreak_left = new wall * [StandartKolUnLeftAndRight];
		_unbreak_right = new wall * [StandartKolUnLeftAndRight];
		for (int i = 0; i < StandartKolUnUpAndDown; i++) {
			_unbreak_up[i] = new wall_unbreak;
			_unbreak_down[i] = new wall_unbreak;
		}
		for (int i = 0; i < StandartKolUnLeftAndRight; i++) {
			_unbreak_left[i] = new wall_unbreak;
			_unbreak_right[i] = new wall_unbreak;
		}
		for (int i = 0, x = 0, yUp = 0, yDown = 20; i < StandartKolUnUpAndDown; i++, x++) {
			_unbreak_up[i]->setPos(x, yUp);
			_unbreak_down[i]->setPos(x, yDown);
		}
		for (int i = 0, y = 1, xLeft = 0, xRight = 21; i < StandartKolUnLeftAndRight; i++, y++) {
			_unbreak_left[i]->setPos(xLeft, y);
			_unbreak_right[i]->setPos(xRight, y);
		}

		_break_5h = new wall * [StandartKolBr];
		_break_3h = new wall * [StandartKolBr];
		_break_1h = new wall * [StandartKolBr];
		for (int i = 0; i < StandartKolBr; i++) {
			_break_1h[i] = new wall_1h;
			_break_3h[i] = new wall_3h;
			_break_5h[i] = new wall_5h;
		}
		for (int i = 0, x = 1, y1 = 5, y3 = 4, y5 = 3; i < StandartKolBr; i++, x += 2) {
			_break_1h[i]->setPos(x, y1);
			_break_3h[i]->setPos(x, y3);
			_break_5h[i]->setPos(x, y5);
		}

		_ball = new ball_st(BallSpawnX, BallSpawnY);
		_bat = new bat_st(BatSpawnX, BatSpawnY);
	}
	void Start(button_fun_result& _res) {
		for (int i = 0; true; i++) {
			print();
			if (_kbhit()) {
				int key = _getch();
				if (key == dir_contr::escape) {
					isGame = false;
					_res = button_fun_result::null;
					kol_game++;
					break;
				}
				_bat->move(key);
			}
			if (i % _ball->getVel() == 0) {
				int vib;
				//wall_break
				for (int i = 0; i < StandartKolBr; i++) {
					if (!_break_1h[i]->IsKilled()) {
						vib = _break_1h[i] * (*_ball);
						if (vib == UpWallBall) {
							if (_ball->getDir() == direct_move::down) {
								_ball->setDir(direct_move::up);
								_break_1h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::down_left) {
								_ball->setDir(direct_move::up_left);
								_break_1h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::down_right) {
								_ball->setDir(direct_move::up_right);
								_break_1h[i]->damage();
							}
						}
						else if (vib == DownWallBall) {
							if (_ball->getDir() == direct_move::up) {
								_ball->setDir(direct_move::down);
								_break_1h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::up_left) {
								_ball->setDir(direct_move::down_left);
								_break_1h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::up_right) {
								_ball->setDir(direct_move::down_right);
								_break_1h[i]->damage();
							}
						}
						else if (vib == RightWallBall) {
							if (_ball->getDir() == direct_move::down_left) {
								_ball->setDir(direct_move::up_right);
								_break_1h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::up_left) {
								_ball->setDir(direct_move::down_right);
								_break_1h[i]->damage();
							}
						}
						else if (vib == LeftWallBall) {
							if (_ball->getDir() == direct_move::up_right) {
								_ball->setDir(direct_move::down_left);
								_break_1h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::down_right) {
								_ball->setDir(direct_move::up_left);
								_break_1h[i]->damage();
							}
						}
						else if (vib == LeftDownWallBall) {
							if (_ball->getDir() == direct_move::up_right) {
								_ball->setDir(direct_move::down_left);
								_break_1h[i]->damage();
							}
						}
						else if (vib == LeftUpWallBall) {
							if (_ball->getDir() == direct_move::down_right) {
								_ball->setDir(direct_move::up_left);
								_break_1h[i]->damage();
							}
						}
						else if (vib == RightUpWallBall) {
							if (_ball->getDir() == direct_move::down_left) {
								_ball->setDir(direct_move::up_right);
								_break_1h[i]->damage();
							}
						}
						else if (vib == RightDownWallBall) {
							if (_ball->getDir() == direct_move::up_left) {
								_ball->setDir(direct_move::down_right);
								_break_1h[i]->damage();
							}
						}
					}
					_break_1h[i]->prov();
				}
				for (int i = 0; i < StandartKolBr; i++) {
					if (!_break_3h[i]->IsKilled()) {
						vib = _break_3h[i] * (*_ball);
						if (vib == UpWallBall) {
							if (_ball->getDir() == direct_move::down) {
								_ball->setDir(direct_move::up);
								_break_3h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::down_left) {
								_ball->setDir(direct_move::up_left);
								_break_3h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::down_right) {
								_ball->setDir(direct_move::up_right);
								_break_3h[i]->damage();
							}
						}
						else if (vib == DownWallBall) {
							if (_ball->getDir() == direct_move::up) {
								_ball->setDir(direct_move::down);
								_break_3h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::up_left) {
								_ball->setDir(direct_move::down_left);
								_break_3h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::up_right) {
								_ball->setDir(direct_move::down_right);
								_break_3h[i]->damage();
							}
						}
						else if (vib == RightWallBall) {
							if (_ball->getDir() == direct_move::down_left) {
								_ball->setDir(direct_move::up_right);
								_break_3h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::up_left) {
								_ball->setDir(direct_move::down_right);
								_break_3h[i]->damage();
							}
						}
						else if (vib == LeftWallBall) {
							if (_ball->getDir() == direct_move::up_right) {
								_ball->setDir(direct_move::down_left);
								_break_3h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::down_right) {
								_ball->setDir(direct_move::up_left);
								_break_3h[i]->damage();
							}
						}
						else if (vib == LeftDownWallBall) {
							if (_ball->getDir() == direct_move::up_right) {
								_ball->setDir(direct_move::down_left);
								_break_3h[i]->damage();
							}
						}
						else if (vib == LeftUpWallBall) {
							if (_ball->getDir() == direct_move::down_right) {
								_ball->setDir(direct_move::up_left);
								_break_3h[i]->damage();
							}
						}
						else if (vib == RightUpWallBall) {
							if (_ball->getDir() == direct_move::down_left) {
								_ball->setDir(direct_move::up_right);
								_break_3h[i]->damage();
							}
						}
						else if (vib == RightDownWallBall) {
							if (_ball->getDir() == direct_move::up_left) {
								_ball->setDir(direct_move::down_right);
								_break_3h[i]->damage();
							}
						}
					}
					_break_3h[i]->prov();
				}
				for (int i = 0; i < StandartKolBr; i++) {
					if (!_break_5h[i]->IsKilled()) {
						vib = _break_5h[i] * (*_ball);
						if (vib == UpWallBall) {
							if (_ball->getDir() == direct_move::down) {
								_ball->setDir(direct_move::up);
								_break_5h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::down_left) {
								_ball->setDir(direct_move::up_left);
								_break_5h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::down_right) {
								_ball->setDir(direct_move::up_right);
								_break_5h[i]->damage();
							}
						}
						else if (vib == DownWallBall) {
							if (_ball->getDir() == direct_move::up) {
								_ball->setDir(direct_move::down);
								_break_5h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::up_left) {
								_ball->setDir(direct_move::down_left);
								_break_5h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::up_right) {
								_ball->setDir(direct_move::down_right);
								_break_5h[i]->damage();
							}
						}
						else if (vib == RightWallBall) {
							if (_ball->getDir() == direct_move::down_left) {
								_ball->setDir(direct_move::up_right);
								_break_5h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::up_left) {
								_ball->setDir(direct_move::down_right);
								_break_5h[i]->damage();
							}
						}
						else if (vib == LeftWallBall) {
							if (_ball->getDir() == direct_move::up_right) {
								_ball->setDir(direct_move::down_left);
								_break_5h[i]->damage();
							}
							else if (_ball->getDir() == direct_move::down_right) {
								_ball->setDir(direct_move::up_left);
								_break_5h[i]->damage();
							}
						}
						else if (vib == LeftDownWallBall) {
							if (_ball->getDir() == direct_move::up_right) {
								_ball->setDir(direct_move::down_left);
								_break_5h[i]->damage();
							}
						}
						else if (vib == LeftUpWallBall) {
							if (_ball->getDir() == direct_move::down_right) {
								_ball->setDir(direct_move::up_left);
								_break_5h[i]->damage();
							}
						}
						else if (vib == RightUpWallBall) {
							if (_ball->getDir() == direct_move::down_left) {
								_ball->setDir(direct_move::up_right);
								_break_5h[i]->damage();
							}
						}
						else if (vib == RightDownWallBall) {
							if (_ball->getDir() == direct_move::up_left) {
								_ball->setDir(direct_move::down_right);
								_break_5h[i]->damage();
							}
						}
					}
					_break_5h[i]->prov();
				}
				//wall_unbreak
				for (int i = 0; i < StandartKolUnLeftAndRight; i++) {
					if (_unbreak_left[i] < *_ball) {
						if (_ball->getDir() == direct_move::up_left) {
							_ball->setDir(direct_move::up_right);
						}
						else if (_ball->getDir() == direct_move::down_left) {
							_ball->setDir(direct_move::down_right);
						}
					}
					if (_unbreak_right[i] > *_ball) {
						if (_ball->getDir() == direct_move::up_right) {
							_ball->setDir(direct_move::up_left);
						}
						else if (_ball->getDir() == direct_move::down_right) {
							_ball->setDir(direct_move::down_left);
						}
					}
				}
				for (int i = 0; i < StandartKolUnUpAndDown; i++) {
					if (_unbreak_up[i] ^ *_ball) {
						if (_ball->getDir() == direct_move::up) {
							_ball->setDir(direct_move::down);
						}
						else if (_ball->getDir() == direct_move::up_right) {
							_ball->setDir(direct_move::down_right);
						}
						else if (_ball->getDir() == direct_move::up_left) {
							_ball->setDir(direct_move::down_left);
						}
					}
				}
				//bat
				vib = (*_ball == *_bat);
				if (vib == LeftBatBall) {
					_ball->setDir(direct_move::up_left);
					if (_ball->_vel > 10) {
						_ball->_vel -= StdMinusVel;
					}
				}
				else if (vib == MiddleBatBall) {
					_ball->setDir(direct_move::up);
					if (_ball->_vel > 10) {
						_ball->_vel -= StdMinusVel;
					}
				}
				else if (vib == RightBatBall) {
					_ball->setDir(direct_move::up_right);
					if (_ball->_vel > 10) {
						_ball->_vel -= StdMinusVel;
					}
				}
				_ball->move();
				i = 1;
			}
			if (_ball->getYPos() == KraiY) {
				break;
			}
		}
	}
	~Game_Pole() {
		Clear();
	}
};
class Menu : virtual public Obj {
private:
	int _xStrelka, _yStrelka, _w, _h;
	char _strelka;
	Button** _bt;
	const char menu[StdRowMenu][StdColumnMenu]
	{
		"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
		"$                           $",
		"$                           $",
		"$                           $",
		"$                           $",
		"$                           $",
		"$                           $",
		"$                           $",
		"$                           $",
		"$                           $",
		"$                           $",
		"$                           $",
		"$                           $",
		"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
	};
public:
	button_fun_result _result;
	Menu() : _strelka('>'), _xStrelka(StdStrelkaX), _yStrelka(StdStrelkaY), _w(StdMenuW), _h(StdMenuH), _result(button_fun_result::null) {
		_bt = new Button * [StdKolButton];
		_bt[0] = new NewGame_button;
		_bt[1] = new Continue_button;
		_bt[2] = new Shop_button;
		_bt[3] = new Save;
		_bt[4] = new Load;
		_bt[5] = new Top5_button;
		_bt[6] = new Help_button;
		_bt[7] = new InfoAboutCreator_button;
		_bt[8] = new DefaultSettings_button;
		_bt[9] = new Exit_button;
	}
	void print() {
		for (int i = 0; i < StdRowMenu; i++) {
			SetPos(_x, _y + i);
			for (int j = 0; j < StdColumnMenu; j++) {
				if (menu[i][j] == '$') {
					cout << char(177);
				}
				else {
					cout << menu[i][j];
				}
			}
		}
		for (int i = 0; i < StdKolButton; i++) {
			_bt[i]->print();
		}
		SetPos(_x + _xStrelka, _y + _yStrelka);
		cout << _strelka;
	}
	void Start(Game_Pole& gm) {
		system("cls");
		print();
		while (true)
		{
			if (_kbhit()) {
				int key = _getch();
				if (key == dir_contr::strelka_up) {
#define StrelkaKrai1 1
#define StrelkaKrai2 12
					SetPos(_x + _xStrelka, _y + _yStrelka);
					cout << " ";
					_yStrelka--;
					if (_yStrelka == StrelkaKrai1) {
						_yStrelka++;
					}
					SetPos(_x + _xStrelka, _y + _yStrelka);
					cout << _strelka;
				}
				else if (key == dir_contr::strelka_down) {
					SetPos(_x + _xStrelka, _y + _yStrelka);
					cout << " ";
					_yStrelka++;
					if (_yStrelka == StrelkaKrai2) {
						_yStrelka--;
					}
					SetPos(_x + _xStrelka, _y + _yStrelka);
					cout << _strelka;
				}
				else if (key == dir_contr::enter) {
					_result = _bt[_yStrelka - 2]->fun();
					print();
				}
				else if (key == dir_contr::escape) {
					finishProg = true;
					break;
				}
			}
			if (_result == button_fun_result::exit_) {
				finishProg = true;
				break;
			}
			else if (_result == button_fun_result::new_game) {
				isGame = true;
				gm.Clear();
				gm.StartSet();
				kol_game = 0;
				system("cls");
				break;
			}
			else if (_result == button_fun_result::continue_) {
				if (kol_game >= 1) {
					isGame = true;
					system("cls");
					break;
				}
			}
		}
	}
};
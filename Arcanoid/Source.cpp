#include "Arcanoid.h"
class LC {
public: LC() { system("chcp 1251 > nul"); srand(time(0)); } ~LC() { system("pause>>nul"); }
}lc;

void main() {
	start();
	Game_Pole gm;
	Menu m;
	while (true) {
		m.Start(gm);
		if (isGame) {
			gm.Start(m._result);
		}
		if (finishProg) {
			cout << "a";
			break;
		}
	}
	system("cls");
	cout << "Good bye...";
}
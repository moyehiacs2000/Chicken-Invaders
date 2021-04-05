#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include"chicken_game.h";
#include"Amr.h"
using namespace std;
using namespace sf;
int main()
{
	while (true){
		levels l;
		while (true){
			if (l.start_game1() && !l.level1() && !l.levelAmr() && !l.levelAhmed()){
				start s;
				s.start_game();
			}
			else if (!l.start_game1() && l.level1() && !l.levelAmr() && !l.levelAhmed()){
				mohmed m;
				m.mohmed_yehia();
			}
			else if (!l.start_game1() && !l.level1() && !l.levelAmr() && l.levelAhmed()){
				ahmed a;
				a.Gemy();
			}
			else if (!l.start_game1() && !l.level1() && !l.levelAmr() && !l.levelAhmed()){
				Amr a;
	    		a.Run();
			}
		}
	}

	return 0;
}

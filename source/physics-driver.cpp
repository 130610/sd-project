#include <iostream>
#include "physics.h"
using namespace std;

int main()
{
	Velocity v;
	Hitbox h(100, 100, 50, 80);
	Point2 pos2;
	Point2 pos3;
	pos2.x = 10; pos2.y = 110;
	pos3.x = 110; pos3.y = 110;
	v.set(pos2, pos3, 15);
	v.show();
	cout << "begin: " << pos2.x << "   " << pos2.y << endl;
	while (!h.detect(pos2, 5, 5)) {
		v.move(pos2);
		cout << "move: " << pos2.x << "   " << pos2.y << endl;
	}
	v.set(pos2, pos2, 1);
	cout << "end: " << pos2.x << "   " << pos2.y << endl;
	return 0;
}

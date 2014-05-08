#include <cmath>
#include "physics.h"
using namespace std;

#define MIN(a, b)  (abs(a) < abs(b)?a:b)

void Velocity::set(Point2 start, Point2 end, int frames)
{
	velX = (double) (end.x - start.x) / (double) frames;
	velY = (double) (end.y - start.y) / (double) frames;
}

void Velocity::move(Point2 &p)
{
	p.x += velX;
	p.y += velY;
}

bool Hitbox::detect(Point2 &p, int w, int h)
{
	if (p.x + w < pos.x || p.y + h < pos.y ||
	    p.x > pos.x + width || p.y > pos.y + height) {
		return false;
	} else {
		int min = MIN(MIN((p.x +  (w - pos.x)), (p.y + (h - pos.y))),
		          MIN((p.x - (pos.x + width)), (p.y - (pos.y + height))));
		if        (p.x + (w - pos.x) == min) {
			p.x = pos.x - w;
		} else if (p.y + (h - pos.y) == min) {
			p.y = pos.y - h;
		} else if (p.x - (pos.x + width) == min) {
			p.x = pos.x + width;
		} else if (p.y - (pos.y + height) == min) {
			p.y = pos.y + height;
		}
	}
	return true;
}

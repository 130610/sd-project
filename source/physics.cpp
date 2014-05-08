#include <cmath>
#include "physics.h"
#include "globaldefs.h"
using namespace std;

#define MIN(a, b)  (abs(a) < abs(b)?a:b)

void Velocity::set(Point2d start, Point2d end)//, double time)
{
	velX = (double) (end.x - start.x) / (FPS * POWER_TIME);
	velY = (double) (end.y - start.y) / (FPS * POWER_TIME);
	cout << velX << "     " << velY << endl;
}

void Velocity::move(Point2d &p)
{
	p.x += velX;
	p.y += velY;
	if (GRAVITY) gravity(METER_LENGTH);
	if (FRICTION) friction(FRICTION_FACTOR);
}

void Velocity::gravity(double meter)
{
	velY -= meter / FPS;
}

void Velocity::friction(double factor)
{
	if (velX > 0) {
		velX -= factor;
	}
	if (velY > 0) {
		velY -= factor;
	}
	if (velX < 0) {
		velX += factor;
	}
	if (velY < 0) {
		velY += factor;
	}
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

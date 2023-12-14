#ifndef _TYPE_HEADER_
#define _TYPE_HEADER_

#define PI 3.141592
#define toRadian(degree) degree * (PI / 180)

typedef struct Point
{
	float x, y;
}Point;


enum class EShape
{
	dot = 0,
	line,
	tri,
	rec,
};


#endif
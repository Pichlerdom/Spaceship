#ifndef _TEST_H_
#define _TEST_H_




typedef struct {
	float x;
	float y;
}Vec;

typedef struct{
	Vec p1;
	Vec p2;
}Rect;

typedef struct{
	Vec pos;
	Vec dir;
	float mass;
	float radius;
}Planet;

typedef struct{
	Planet *planets;
	int count;
	int size;

}PlanetArr;
typedef struct{
	Vec pos;
	Vec dir;
	Vec orient;
	float angle;
	float mass;
	float thrust_level;
	float thrust_max;
	float rotation_speed;
	
}Ship;


#endif

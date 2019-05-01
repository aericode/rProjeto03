#include "orthogonal_camera.h"
#include "camera.h"
#include "ray.h"
#include "vec3.h"

typedef vec3 Point;


Orthogonal_camera::Orthogonal_camera(){};

Orthogonal_camera::Orthogonal_camera(Point origin, Point vertical, Point horizontal, Point corner)
	:Camera(origin,vertical,horizontal,corner){}

ray Orthogonal_camera::traceRay(float x, float y){
	Point direction = corner + x*horizontal + y*vertical;
	ray generated(origin, direction);
	return generated;
}
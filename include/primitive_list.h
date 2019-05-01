#ifndef PRIMITIVELISTH
#define PRIMITIVELISTH

#include <iostream>
#include <vector>
#include "primitive.h"

using namespace std;

//based on Shirley's model
class Primitive_list{
public:
	vector<Primitive*> list;

	Primitive_list(){}
	Primitive_list(vector<Primitive*> list){
		this->list = list;
	}
	
	
	bool intersect(const ray& r, float t_min, float t_max, SurfaceInteraction& inter){
		SurfaceInteraction aux;
		bool hit_something = false;
		float closest_dist = t_max;
		for(int i = 0; i < list.size(); i++){
			if (list.at(i)->intersect(r,t_min,closest_dist, aux)){
				hit_something = true;
				closest_dist = aux.time;
				inter = aux;
			}
		}
		return hit_something;

	}


	bool intersect_p(const ray& r, float t_min, float t_max){
		for(int i = 0; i < list.size(); i++){
			if (list[i]->intersect_p(r,t_min,t_max)){
				return true;
			}
		}
		return false;
	}

};


#endif
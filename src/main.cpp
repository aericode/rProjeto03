#include <iostream>
#include <fstream>

#include "json.hpp"
#include "jsonReader.h"
#include "perspective_camera.h"
#include "orthogonal_camera.h"
#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "plotter.h"
#include "primitive_list.h"


using json::JSON;
typedef vec3 Color;
typedef vec3 Point;

int main(){
	
	JSON obj = parseFile("./jsonInput/scene.json");
	Perspective_camera cam = Perspective_camera(Point(0,0,-2),Point(0,2,0),Point(4,0,0),Point(-2,-1,-1));
	Primitive_list *world = primitivesFromJSON(obj);

	int nx = 200;
	int ny = 100;

	Plotter plotter(nx,ny,"./imageOutput/default.ppm");


	for (int j = ny-1; j >= 0 ; j--){
		for(int i = 0; i <  nx; i++){
			float u = float(i) / float (nx);
			float v = float(j) / float (ny);
			
			ray r = cam.traceRay(u,v);

			//COL recebe um raio
			vec3 col = cam.sample(r, world);

			int ir  = int(255.99*col[0]);
			int ig  = int(255.99*col[1]);
			int ib  = int(255.99*col[2]);

			plotter.changePixel(i,j, Color(ir,ig,ib));
			
		}
	}

	plotter.plotFile();
	
}
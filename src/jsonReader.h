#include "json.hpp"
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <fstream>
#include <string>


#include "vec3.h"
#include "orthogonal_camera.h"
#include "camera.h"
#include "sphere.h"
#include "primitive.h"
#include "primitive_list.h"


using json::JSON;
using namespace std;

typedef vec3 Color;
typedef vec3 Point;

string stringFromFile(string filename)
{
    //pega o arquivo e transforma em uma string pronta para ser convertida em objeto
    string aux;
    string userInput;
    ifstream infile;
    infile.open (filename);
        while(!infile.eof()){
            getline(infile,aux);
            userInput += aux;
        }
    infile.close();

    return userInput;
}

JSON parseFile(string filename){
    JSON obj;
    string userInput = stringFromFile(filename);
    obj = JSON::Load(userInput);
    return obj;
}

Camera cameraFromJSON(JSON obj){

    if (obj["camera"].IsNull()){
        std::cout<<"no instructions for camera in JSON file"<<std::endl;
        return Orthogonal_camera();
    }else{
        string camParts[4] = {"origin","vertical","horizontal","corner"};
        vec3 aux[4];

        for(int i = 0; i < 4; i++){
            for(int j = 0;j < 3;j++){
                aux[i][j] = obj["camera"][camParts[i]][j].ToFloat();
            }
        }
        if(obj["camera"]["type"].ToString()=="orthogonal"){
            return Orthogonal_camera(aux[0],aux[1],aux[2],aux[3]);
        }
    }
}

Primitive_list * primitivesFromJSON(JSON obj){
    if (obj["primitives"].IsNull()){
        std::cout<<"no instructions for primitives in JSON file"<<std::endl;
        return nullptr;
    }else{


        int num_primitives = obj["primitives"].length();


        Primitive **list = new  Primitive*[num_primitives];

        Point aux;
        float radius;


        for(int i =0; i < num_primitives; i++){

            aux[0] = obj["primitives"][i][0].ToInt();
            aux[1] = obj["primitives"][i][1].ToInt();
            aux[2] = obj["primitives"][i][2].ToInt();

            radius = obj["primitives"][i][3].ToFloat();

            list[i] = new Sphere(aux, radius);
        }
        
        Primitive_list * result = new Primitive_list(list, num_primitives);

        return result;
    }
}
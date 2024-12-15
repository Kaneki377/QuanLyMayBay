#pragma once
#include "UI.h"
#include "GlobalVariable.h"


//Struct thong tin may bay
struct Plane{
	char id[15];
	char type[40];
	int rows;
	int cols;

	//
	int flyTimes;
};
typedef Plane plane;

struct PlaneList {
	int size;
	Plane* PList[MAX_PLANE];
};
typedef struct PlaneList planeList;

//Fucntion in Plane.cpp
void initListPlane(planeList& pl);
int findIndexPlane(planeList pl, const char* id);
bool planeDataIsEmpty(plane* p);
bool removePlaneIsSucceed(planeList& pl, char idToRemove[]);
void showPlane(plane* p, int position);
void showListPlaneOnePage(planeList pl, int index);
void changePlaneMenuManagerPage(planeList pl);
void inputPlane(planeList& pl, bool confirm);
void menuManagerPlane(planeList& pl);





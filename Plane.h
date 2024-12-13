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
	bool isAvail;
};
typedef Plane plane;

struct PlaneList {
	int size;
	Plane* PList[MAX_PLANE];
};
typedef struct PlaneList planeList;

//Fucntion in Plane.cpp
void initListPlane(PlaneList& pl);
int findIndexPlane(PlaneList pl, const char* id);
bool planeDataIsEmpty(Plane* p);
bool removePlaneIsSucceed(PlaneList& pl, char idToRemove[]);
void showPlane(Plane* p, int position);
void showListPlaneOnePage(PlaneList pl, int index);
void changePlaneMenuManagerPage(PlaneList pl);
void inputPlane(PlaneList& pl, bool confirm);
void menuManagerPlane(PlaneList& pl);





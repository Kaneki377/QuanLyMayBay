#pragma once
#include "UI.h"
#include "Plane.h"
#include <fstream>

/*Xu li may bay*/
void ReadOneAirplane(plane& p, ifstream& filein);
void ReadPlaneFile(planeList& pl);
void WritePlaneToFile(planeList& pl);

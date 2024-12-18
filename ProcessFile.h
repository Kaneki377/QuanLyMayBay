#pragma once

#include "UI.h"
#include "Plane.h"
#include "fstream"
#include "Flight.h"

/*Xu li may bay*/
void ReadOneAirplane(plane& p, ifstream& filein);
void ReadPlaneFile(planeList& pl);
void WritePlaneToFile(planeList& pl);

/*Xu li chuyen bay*/
void readFlightFromFile(flightList &fl, planeList &pl);
void saveTicketListOfOneFlight(flight& f);
void saveFlight(flight &f, ofstream &fileOut);
void writeFlightToFile(flightList &fl);

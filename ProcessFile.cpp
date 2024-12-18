#pragma once

#include "UI.h"
#include "MyLib.h"
#include "ProcessFile.h"
#include "Plane.h"
#include "Flight.h"
#include "string"

void ReadOneAirplane(plane& p, ifstream& filein)
{
}

void ReadPlaneFile(planeList& pl)
{
	ifstream filein;
	filein.open("PlaneList.txt", ios_base::in);// ios_base::in la de doc


	string temp;
	int i = 0;
	if (filein.is_open())
	{
		while (!filein.eof())
		{
			plane* p = new plane;

			filein >> p->id;
			if (strcmp(p->id, "") == 0) continue;
			filein >> p->type;
			filein >> p->rows;
			filein >> p->cols;
			filein.ignore();
			// cap nhat phan tu trong mang con tro
			pl.PList[i++] = p;
			// cap nhat so luong phan tu trong mang
			pl.size++;
		}
	}
	filein.close();
}

void WritePlaneToFile(planeList& pl)
{
	ofstream fileout;
	fileout.open("PlaneList.txt", ios_base::out);// ios_base::out la de ghi vao file
	if (fileout.is_open())
	{
		for (int i = 0; i < pl.size; i++)
		{
			fileout << pl.PList[i]->id << " " << pl.PList[i]->type << " " << pl.PList[i]->rows << " " << pl.PList[i]->cols << endl;
		}
	}
	else
	{
		gotoxy(X_Notification, Y_Notification + 1);
		cout << " Ket noi file de ghi vao that bai";
	}
	fileout.close();
}

//Function doc chuyen bay tu file.
void readFlightFromFile(flightList& fl, planeList& pl)
{
	ifstream fileIn;

	fileIn.open("FlightList.TXT", ios_base::in);
	for (int i = 0; i < pl.size; i++) {
		pl.PList[i]->flyTimes = 0;
	}

	flight f;
	int index;
	if (fileIn.is_open()) {
		int numFlight;
		fileIn >> numFlight;

		string temp;
		getline(fileIn, temp);
		for (int j = 0; j < numFlight; j++) {
			if (strcmp(f.idFlight, "") == 0) {
				break;
			}
			fileIn.getline(f.idFlight, 15, '\n');
			fileIn.getline(f.airportTo, 20, '\n');
			fileIn.getline(f.idPlane, 15, '\n');

			//Thoi gian khoi hanh
			fileIn >> f.departureTime.hour;
			fileIn >> f.departureTime.minutes;
			fileIn >> f.departureTime.day;
			fileIn >> f.departureTime.month;
			fileIn >> f.departureTime.year;

			fileIn >> f.totalTickets;
			fileIn >> f.status;

			getline(fileIn, temp);
			//Tesst
			cout << f.idFlight << f.airportTo << f.idPlane << f.departureTime.hour << f.departureTime.minutes << f.departureTime.day << f.departureTime.month << f.departureTime.year;

			for (index = 0; index < pl.size; index++) {
				if (_stricmp(f.idPlane, pl.PList[index]->id) == 0) {
					pl.PList[index]->flyTimes++;
				}
			}

			//addEndingList(fl, f);
			insertFlightAfter(fl, f);
		}
		fl.numsOfFlight++;
	}
	fileIn.close();
}

void saveTicketListOfOneFlight(flight& f)
{
}

void saveFlight(flight &f, ofstream &fileOut)
{
	fileOut << f.idFlight << endl;
	fileOut << f.airportTo << endl;
	fileOut << f.idPlane << endl;
	fileOut << f.departureTime.hour << endl;
	fileOut << f.departureTime.minutes << endl;
	fileOut << f.departureTime.day << endl;
	fileOut << f.departureTime.month << endl;
	fileOut << f.departureTime.year << endl;
	fileOut << f.totalTickets << endl;
	fileOut << f.status << endl;
	saveTicketListOfOneFlight(f);
}

void writeFlightToFile(flightList &fl)
{
	ofstream fileOut;
	fileOut.open("FlightList.TXT", ios_base::out);

	if (fileOut.is_open()) {
		fileOut << fl.numsOfFlight << endl;
		for (flightNode* search = fl.pHead; search != NULL; search = search->pNext) {
			saveFlight(search->data, fileOut);
		}
	}
	else {
		gotoxy(X_Notification, Y_Notification + 1);
		cout << " Ket noi file de ghi vao that bai!";
	}

	fileOut.close();
}

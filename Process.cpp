#pragma once
#include "UI.h"
#include "MyLib.h"
#include "Process.h"
#include "Plane.h"

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

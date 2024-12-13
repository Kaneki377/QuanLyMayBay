#pragma once
#include "Plane.h"
#include "GlobalVariable.h"
#include "UI.h"
#include "MyLib.h"


// thong tin vi tri hien tai
int CurPosAirplane = 0;
int CurAirplanePage = 1;
int TotalAirplanePage = 0;
extern string ContentAirplane[3];


//Init
void initListPlane(PlaneList& pl)
{
	pl.size = 0;
}

// tim vi tri cua may bay trong danh sach
Plane* findPlane(PlaneList& pl, const char* id) {
	for (int i = 0; i < pl.size; i++) {
		if (_stricmp(pl.PList[i]->id, id) == 0) {
			return pl.PList[i];
		}
	}
}

int findIndexPlane(PlaneList pl, const char* id)
{
	for (int i = 0; i < pl.size; i++) {
		if (_stricmp(pl.PList[i]->id, id) == 0) {
			return i;
		}
	}
	return -1;
}

//Check xem co nhap du data khong
bool planeDataIsEmpty(Plane* p)
{
	if (strlen(p->id) == 0 || strlen(p->type) == 0 || p->rows || p->cols) {
		return false;
	}
	return true;
}

bool removePlaneIsSucceed(PlaneList& lp, char idToRemove[])
{
	return false;
}
bool removePlaneIsSucceed(PlaneList& pl, int position) {
	if (position < 0) {
		return false; //Khong co plane
	}
	//Xoa vi tri thu i => PList[i] = PList[i+1]
	for (int i = position; i < pl.size; i++) {
		pl.PList[i] = pl.PList[i + 1];
	}
	pl.size--;//giam size, giai phong bo nho
	return true;//xoa thanh cong
}
//Function cho plane & planelist
//Show 1 plane
void showPlane(Plane* p, int position)
{
	int xKeyDisPlay[7] = { 1, 20, 45, 63, 80, 95, 107 };//coord for x

	gotoxy(xKeyDisPlay[0] + 4, Y_Display + 4 + position * 4);
	printf("%-15s", p->id);
	gotoxy(xKeyDisPlay[1] + 4, Y_Display + 4 + position * 4);
	printf("%-15s", p->type);
	gotoxy(xKeyDisPlay[2] + 4, Y_Display + 4 + position * 4);
	printf("%-15d", p->rows);
	gotoxy(xKeyDisPlay[3] + 4, Y_Display + 4 + position * 4);
	printf("%-15d", p->cols);
}

void showListPlaneOnePage(PlaneList pl, int index)
{
	gotoxy(1, 2);
	cout << "Plane list size: " << pl.size;
	int i;
	for (i = 0; i < pl.size && i < NumberPerPage; i++) {
		showPlane(pl.PList[i + index], i);
	}
	gotoxy(X_Page, Y_Page);
	cout << "Page: " << CurAirplanePage << "/" << TotalAirplanePage;
}

void changePlaneMenuManagerPage(PlaneList lp)
{
	gotoxy(X_TitlePage, Y_TitlePage);
	cout << "Plane Management";

	Display(ContentAirplane, sizeof(ContentAirplane) / sizeof(string));
	showListPlaneOnePage(lp, (CurAirplanePage - 1) * NumberPerPage);
}

void inputPlane(PlaneList& lp, bool confirm)
{
}

void menuManagerPlane(PlaneList& lp)
{
}

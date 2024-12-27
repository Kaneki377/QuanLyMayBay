#pragma once
#include "Plane.h"
#include "GlobalVariable.h"
#include "UI.h"
#include "MyLib.h"
#include "Constraint.h"
#include "ProcessingFile.h"


// thong tin vi tri hien tai
int CurPosAirplane = 0;
int CurAirplanePage = 1;
int TotalAirplanePage = 0;
extern string ContentAirplane[4];


//Init
void initListPlane(planeList& pl)
{
	pl.size = 0;
}

// tim vi tri cua may bay trong danh sach
Plane* findPlane(planeList& pl, const char* id) {
	for (int i = 0; i < pl.size; i++) {
		if (_stricmp(pl.PList[i]->id, id) == 0) {
			return pl.PList[i];
		}
	}
}

int findIndexPlane(planeList pl, const char* id)
{
	for (int i = 0; i < pl.size; i++) {
		if (_stricmp(pl.PList[i]->id, id) == 0) {
			return i;
		}
	}
	return -1;
}

//Check xem co nhap du data khong
bool planeDataIsEmpty(plane* p)
{
	if (strlen(p->id) == 0 || strlen(p->type) == 0 || p->rows || p->cols) {
		return false;
	}
	return true;
}

bool removePlaneIsSucceed(planeList& lp, char idToRemove[])
{
	return false;
}
bool removePlaneIsSucceed(planeList& pl, int position) {
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
void showPlane(plane* p, int position)
{
	int xKeyDisPlay[7] = { 1, 20, 45, 63, 80, 95, 107 };//coord for x

	gotoxy(xKeyDisPlay[0] + 3, Y_Display + 3 + position * 3);
	printf("%-15s", p->id);
	gotoxy(xKeyDisPlay[1] + 3, Y_Display + 3 + position * 3);
	printf("%-15s", p->type);
	gotoxy(xKeyDisPlay[2] + 3, Y_Display + 3 + position * 3);
	printf("%-15d", p->rows);
	gotoxy(xKeyDisPlay[3] + 3, Y_Display + 3 + position * 3);
	printf("%-15d", p->cols);
}

void showListPlaneOnePage(planeList pl, int index)
{
	gotoxy(1, 2);
	cout << "Plane list size: " << pl.size;
	int i;
	for (i = 0; i + index  < pl.size && i < NumberPerPage; i++) {
		showPlane(pl.PList[i + index], i);
	}
	RemoveExceedMember(i, 4);
	gotoxy(X_Page + 1, Y_Page + 1);
	cout << "Page: " << CurAirplanePage << "/" << TotalAirplanePage;
}

void changePlaneMenuManagerPage(planeList pl)
{
	gotoxy(X_TitlePage, Y_TitlePage);
	cout << "Plane Management";

	Display(ContentAirplane, sizeof(ContentAirplane) / sizeof(string));
	showListPlaneOnePage(pl, (CurAirplanePage - 1) * NumberPerPage);
}

/*Input plane detail - requirement input*/
void inputPlane(planeList& pl, bool EditedOrNot,bool DeleteOrNot)
{
	ShowCur(true);

	bool SaveOrNot = true;//Check if data had save
	bool MoveOrNot = false;
	bool IDExisted = false;
	string ID;//so hieu may bay
	string Type;//loai may bay
	int nRow = 0;//so hang
	int nCol = 0;//so cot
	int index = 0;//stt bat dau viet
	int target = -1;

	while (true) {
		switch (index)
		{
		case 0:
		{
			ConstraintForLetterAndNumber(ID, MoveOrNot, index, SaveOrNot, 12);

			if (SaveOrNot == false)
			{
				RemoveFormComplete();
				return;
			}
			if (DeleteOrNot)
			{
				int target = RemoveConfirm();
				gotoxy(50, 50);

				RemoveFormComplete();

				if (!removePlaneIsSucceed(pl, findIndexPlane(pl, ID.c_str())))
				{
					gotoxy(X_Notification + 1, Y_Notification + 1);
					cout << "Delete Failed!";
				}
				else {
					gotoxy(X_Notification + 1, Y_Notification + 1);
					cout << "Delete Succeeded!";
				}

				system("Color 0E");
				return;
			}

			if (ID == "") {
				gotoxy(X_Notification + 1, Y_Notification + 1);
				cout << "Required Input!";
				break;
			}

			//Check if ID existed
			target = findIndexPlane(pl, ID.c_str());
			if (target > -1 && EditedOrNot == false)
			{
				gotoxy(X_Notification, Y_Notification + 1);
				cout << " ID Existed !";
				break;
			}

			if (target < 0 && EditedOrNot == true) {
				gotoxy(X_Notification, Y_Notification + 1);
				cout << " ID Not Existed!";
				break;
			}

			if (EditedOrNot) {
				ID = pl.PList[target]->id;
				Type = pl.PList[target]->type;
				nRow = pl.PList[target]->rows;
				nCol = pl.PList[target]->cols;

				gotoxy(X_Add + 12, 0 * 3 + Y_Add);
				cout << ID;
				gotoxy(X_Add + 12, 1 * 3 + Y_Add);
				cout << Type;
				gotoxy(X_Add + 12, 2 * 3 + Y_Add);
				cout << nRow;
				gotoxy(X_Add + 12, 3 * 3 + Y_Add);
				cout << nCol;
			}
			index++;
			break;
		}
		case 1://Input plane type
		{
			ConstraintForOnlyLetter(Type, MoveOrNot, index, SaveOrNot, 12);
			if (SaveOrNot == false) {
				RemoveFormComplete();
				return;
			}
			if (Type == "") {
				gotoxy(X_Notification, Y_Notification + 1);
				cout << "Input Required!";
				break;
			}
			index++;
			break;
		}
		case 2:
		{
			ConstraintForOnlyNumber(nRow, MoveOrNot, index, SaveOrNot, 12, 999);
			if (SaveOrNot == false)
			{
				RemoveFormComplete();
				return;
			}
			if (nRow < 1) {
				gotoxy(X_Notification, Y_Notification + 1);
				cout << " Input Required! ";
				break;
			}
			if (nRow < 10) {
				gotoxy(X_Notification, Y_Notification + 1);
				cout << " Row must be >= 10";
				break;
			}
			index++;
			break;
		}
		case 3:
		{
			ConstraintForOnlyNumber(nCol, MoveOrNot, index, SaveOrNot, 12, 999);
			if (SaveOrNot == false)
			{
				RemoveFormComplete();
				return;
			}
			if (nCol < 1) {
				gotoxy(X_Notification, Y_Notification + 1);
				cout << " Input Required! ";
				break;
			}
			if (nCol < 2) {
				gotoxy(X_Notification, Y_Notification + 1);
				cout << " Col must be >= 2";
				break;
			}
			index++;
			break;
		}
		case 4:
		{
			// Edit Plane
			if (EditedOrNot && target > -1) {
				
				strcpy_s(pl.PList[target]->id, ID.c_str());
				strcpy_s(pl.PList[target]->type, Type.c_str());
				pl.PList[target]->rows = nRow;
				pl.PList[target]->cols = nCol;
				gotoxy(X_Notification, Y_Notification + 1);
				cout << " Edit Success! ";
			}
			//Add new plane
			else {
				pl.PList[pl.size] = new plane;
				strcpy_s(pl.PList[pl.size]->id, ID.c_str());
				strcpy_s(pl.PList[pl.size]->type, Type.c_str());
				pl.PList[pl.size]->rows = nRow;
				pl.PList[pl.size]->cols = nCol;
				pl.PList[pl.size]->flyTimes = 0;
				pl.size++;

				gotoxy(X_Notification, Y_Notification + 1);
				cout << " Add Success! ";
			}
			WritePlaneToFile(pl);
			ID = "";
			Type = "";
			nRow = 0;
			nCol = 0;
			index = 0;
			RemoveForm();
		}
		break;
		}//switch
	}//while
	ShowCur(false);
}

/*========== MENU Plane Management ==========*/
void menuManagerPlane(planeList& pl)
{
	ShowCur(false);
	system("cls");
		
	CurAirplanePage = 1;
	TotalAirplanePage = (int)ceil((double)pl.size / NumberPerPage);

	Display(ContentAirplane, sizeof(ContentAirplane) / sizeof(string));
	showListPlaneOnePage(pl, 0);

	gotoxy(X_TitlePage, Y_TitlePage);
	cout << "Plane Management";

	int signal;
	while (true) {
		while (_kbhit()) {
			signal = _getch();
			if (signal == ESC)
				return;
			if (signal == 224) {
				signal = _getch();
				if (signal == PAGE_UP && CurAirplanePage > 1) {
					CurAirplanePage--;
					changePlaneMenuManagerPage(pl);
				}
				else if (signal == PAGE_DOWN && CurAirplanePage < TotalAirplanePage) {
					CurAirplanePage++;
					changePlaneMenuManagerPage(pl);
				}
				//Add Plane
				else if (signal == INSERT) {
					if (pl.size == MAX_PLANE) {
						gotoxy(X_Notification, Y_Notification + 1);cout << "Plane list is full!";
						return;
					}
					CreateForm(ContentAirplane, 0, 4, 27);
					inputPlane(pl, false, false);
					TotalAirplanePage = (int)ceil((double)pl.size / NumberPerPage);
					showListPlaneOnePage(pl, (CurAirplanePage - 1) * NumberPerPage);
					ShowCur(false);
				}

				//Delete Plane
				else if (signal == DEL) {
					CreateForm(ContentAirplane, 0, 1, 27);
					inputPlane(pl, false, true);
					TotalAirplanePage = (int)ceil((double)pl.size / NumberPerPage);
					showListPlaneOnePage(pl, (CurAirplanePage - 1) * NumberPerPage);
				}

				//Update Plane
				else if (signal == HOME) {
					CreateForm(ContentAirplane, 0, 4, 27);
					inputPlane(pl, true, false);
					TotalAirplanePage = (int)ceil((double)pl.size / NumberPerPage);
					showListPlaneOnePage(pl, (CurAirplanePage - 1) * NumberPerPage);
				}
			}
		}//while(_kbhit)
	}//while(true)
}

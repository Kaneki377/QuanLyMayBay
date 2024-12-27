#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "Plane.h"
#include "GlobalVariable.h"
#include "Ticket.h"
#include "DateTime.h"
#include "Flight.h"
#include "Constraint.h"
#include "ProcessingFile.h"

/*Vi tri cua danh sach chuyen bay*/
int CurPosFlight = 0;
int CurPosPreFlight = 0;
int CurFlightPage = 1;
int TotalFlightPage = 0;

int CurPosTicket = 1;
int CurPosPreTicket = 1;

extern string ContentFlight[6];
extern string ContentFlightForInsert[4];
extern planeList PList;

void initFlightList(flightList &fl) {
	fl.pHead = NULL;
	fl.pTail = NULL;
	fl.numsOfFlight = 0;
}

//Ham tao flightNode
flightNode *createFlightNode(flight data)
{
	flightNode *tempNode = new flightNode;

	if (tempNode == NULL)
	{
		return NULL;
	}
	tempNode->data = data;
	tempNode->pNext = NULL;

	return tempNode;
}

//Them node moi vao dau danh sach
void addBeginningList(flightList &fl, flight data)
{
	flightNode *tempoNode = createFlightNode(data);

	tempoNode->pNext = fl.pHead;
	fl.pHead = tempoNode;
	fl.numsOfFlight++;
}

//Them node moi vao cuoi danh sach
void addEndingList(flightList &fl, flight data)
{
	flightNode *tempNode = createFlightNode(data);

	if (fl.pHead == NULL)
	{
		fl.pHead = fl.pTail = tempNode;
	}
	else
	{
		fl.pTail->pNext = tempNode;
		fl.pTail = tempNode;
	}
	fl.numsOfFlight++;
}

//Function them chuyen bay moi vao theo ma thu tu tang dan(ma chuyen bay)
void insertFlightAfter(flightList &fl, flight data)
{
	flightNode* newNode = createFlightNode(data);
	//Neu danh sach rong hoac ma chuyen bay moi nho hon ma chuyen bay node dau tien
	if (fl.pHead == NULL || _strcmpi(data.idFlight, fl.pHead->data.idFlight) < 0) {
		newNode->pNext = fl.pHead;
		fl.pHead = newNode;
		if (fl.pTail == NULL) {
			fl.pTail = newNode;
		}
	}
	else {
		flightNode* tempNode = fl.pHead;
		while (tempNode->pNext != NULL && _strcmpi(data.idFlight, tempNode->pNext->data.idFlight) > 0) {
			tempNode = tempNode->pNext;
		}
		newNode->pNext = tempNode->pNext;
		tempNode->pNext = newNode;
		if (newNode->pNext == NULL) {
			fl.pTail = newNode;
		}
	}
	fl.numsOfFlight++;
}

//Linear search
int findIndexFlightById(flightList fl, const char *idFlightToFind)
{
	int index = 0;
	for (flightNode *search = fl.pHead; search != NULL; search = search->pNext) {
		//So sanh 2 chuoi co phan biet ky tu in hoa va in thuong
		if (_strcmpi(search->data.idFlight, idFlightToFind) == 0) {
			return index;
		}
		index++;
	}

	return -1;
}

int findDestinationByAirPort(flightList fl, const char *airportToFind)
{
	int index = 0;
	for (flightNode *search = fl.pHead; search != NULL; search = search->pNext) {
		if (_strcmpi(search->data.airportTo, airportToFind) == 0) {
			return index;
		}
		index++;
	}

	return -1;
}

flightNode *findFlightById(flightList fl, const char *idFlightToFind)
{
	if (fl.pHead == NULL) {
		return NULL;
	}

	for (flightNode *search = fl.pHead; search != NULL; search = search->pNext) {
		if (_strcmpi(search->data.idFlight, idFlightToFind) == 0) {
			return search;
		}
	}
	return NULL;
}

void inputDateTimeInfor(dateTime &dt, int ordinal)
{
	//Vi tri khoi dau cho viec nhap
	int dateTimeOrdinal = 0;
	bool saveOrCancel = false;
	//Form hien thi ngay - gio
	gotoxy(X_Add + 12 + 2, ordinal * 3 + Y_Add);
	cout << ":";
	gotoxy(X_Add + 12 + 8, ordinal * 3 + Y_Add);
	cout << "/";
	gotoxy(X_Add + 12 + 11, ordinal * 3 + Y_Add);
	cout << "/";

	while (true) {
		//Check theo trinh tu hour -> minutes -> day -> month -> year
		switch (dateTimeOrdinal)
		{
		case 0:
			ConstraintForDateAndTime(dt.hour, dateTimeOrdinal, saveOrCancel, 12, 23);
			dateTimeOrdinal++;
			break;
		case 1:
			ConstraintForDateAndTime(dt.minutes, dateTimeOrdinal, saveOrCancel, 12, 59);
			dateTimeOrdinal++;
			break;
		case 2:
			ConstraintForDateAndTime(dt.day, dateTimeOrdinal, saveOrCancel, 12, 31);
			dateTimeOrdinal++;
			break;
		case 3:
			ConstraintForDateAndTime(dt.month, dateTimeOrdinal, saveOrCancel, 12, 13);
			dateTimeOrdinal++;
			break;
		case 4: 
			ConstraintForDateAndTime(dt.year, dateTimeOrdinal, saveOrCancel, 12, 2100);
			return;
		}
	}
}

//Xoa node dau khoi danh sach
bool removeHead(flightList &fl)
{
	if (fl.pHead == NULL) {
		return false;
	}

	flightNode* tempNode = fl.pHead;
	if (fl.pHead == fl.pTail) { // Trường hợp danh sách chỉ có 1 phần tử
		fl.pHead = fl.pTail = NULL;
	}
	else {
		fl.pHead = fl.pHead->pNext;
	}

	delete tempNode;
	fl.numsOfFlight--;

	return true;
}

bool removeEnding(flightList& fl)
{
	if (fl.pHead == NULL) {
		return false;
	}

	//Truong hop danh sach chi co 1 phan tu
	if (fl.pHead == fl.pTail) {
		delete fl.pHead;
		fl.pHead = fl.pTail = NULL;
		--fl.numsOfFlight;
		return true;
	}

	//Duyet toi phan tu ke cuoi
	flightNode* tempNode = fl.pHead;
	while (tempNode->pNext != fl.pTail) {
		tempNode = tempNode->pNext;
	}
	

	tempNode->pNext = NULL;
	delete fl.pTail;
	fl.pTail = tempNode;
	--fl.numsOfFlight;

	return true;
}

//Function xoa node dung sau mot node khac (tempFlight)
bool removeAfterAnother(flightList &fl, flightNode *tempFlight)
{
	if (tempFlight == NULL || tempFlight->pNext == NULL) {
		return false;
	}

	flightNode *removedNode = tempFlight->pNext;
	tempFlight->pNext = removedNode->pNext;
	delete removedNode;
	fl.numsOfFlight--;

	return true;
}

//Function xoa chuyen bay(node) theo id
bool removeFlightById(flightList &fl, const char *idFlightToFind)
{
	flightNode *cleanedFlight = findFlightById(fl, idFlightToFind);
	
	if (cleanedFlight == NULL) {
		return false;
	}
	else if (cleanedFlight == fl.pHead) {
		return removeHead(fl);
	}
	else if (cleanedFlight == fl.pTail) {
		return removeEnding(fl);
	}
	else {
		flightNode *tempNode = fl.pHead;
		while (true) {
			if (tempNode->pNext == cleanedFlight) {
				break;
			}
			tempNode = tempNode->pNext;
		}
		return removeAfterAnother(fl, tempNode);
	}
}

//Cap nhat trang thai chuyen bay
void updateFlightStatus(flightList &fl)
{

	for (flightNode *search = fl.pHead; search != NULL; search = search->pNext) {
		if (isDateTimeValid(search->data.departureTime) == false) {
			search->data.status = 3;
			//0. huy Chuyen, 1. Con ve, 2. Het ve, 3. Hoan tat
		}
	}
}

//Xuat thong tin 1 chuyen bay
void showFlightInfor(flight f, int position)
{
	//Toa do tren truc x cua cac nut
	int xKeyDisplay[7] = { 1, 20, 45, 63, 83, 98, 115 };

	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position * 3);
	printf("%-15s", f.idFlight);

	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position * 3);
	printf("%-18s", f.airportTo);

	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position * 3);
	printf("%-15s", f.idPlane);

	gotoxy(xKeyDisplay[3] + 3, Y_Display + 3 + position * 3);
	showDateTime(f.departureTime);

	gotoxy(xKeyDisplay[4] + 3, Y_Display + 3 + position * 3);
	printf("%-3d", f.totalTickets);

	gotoxy(xKeyDisplay[5] + 3, Y_Display + 3 + position * 3);
	
	switch (f.status)
	{
	case 0: 
		cout << "Huy     ";
		break;
	case 1: 
		cout << "Con ve  ";
		break;
	case 2:
		cout << "Het ve  ";
		break;
	case 3: 
		cout << "Hoan tat";
		break;
	default:
		break;
	}

}

//Xuat thong tin danh sach chuyen bay
void showFlightListInfor(flightList fl)
{
	if (fl.pHead == NULL && fl.pTail == NULL) {
		return;
	}

	int count = -1;
	updateFlightStatus(fl);

	for (flightNode *search = fl.pHead; search != NULL; search = search->pNext) {
		count++;
		showFlightInfor(search->data, count);
	}
}

//Hien thi thong tin chuyen bay theo trang
void showFlightListPerPage(flightList fl, int startIndex)
{
	gotoxy(1, 2);
	cout << " Numbers of flights: " << fl.numsOfFlight;

	if (fl.pHead == NULL && fl.pTail == NULL) {
		return;
	}

	int count = -1;
	updateFlightStatus(fl);

	for (flightNode *search = fl.pHead; search != NULL; search = search->pNext) {
		count++;
		if (count == startIndex) {
			int index = -1;
			while (search != NULL && index < NumberPerPage - 1) {
				showFlightInfor(search->data, ++index);
				search = search->pNext;
			}
			RemoveExceedMember(index + 1, 7);
			break;
		}
	}

	gotoxy(X_Page, Y_Page);
	cout << "Trang " << CurFlightPage << "/" << TotalFlightPage;
}

void changePageManageFlightList(flightList fl)
{
	gotoxy(1, 2);
	cout << " Numbers of flights: " << fl.numsOfFlight;
	gotoxy(X_TitlePage, Y_TitlePage);
	cout << " Flight Management ";

	showFlightListPerPage(fl, (CurFlightPage - 1) * NumberPerPage);

	gotoxy(X_Page, Y_Page);
	cout << "Trang " << CurFlightPage << "/" << TotalFlightPage;
}

void inputFlightInFor(flightList &fl, bool editedOrNot, bool deleteOrNot)
{
	ShowCur(true);

	int ordinal = 0;
	bool moveOrNot = false; //Khong di chuyen
	bool saveOrNot = true; //Mac dinh la nguoi dung se luu lai
	bool idExisted = false; //Ma chuyen bay luon nhap moi
	string idFlight;
	string airportTo;
	string idPlane;
	dateTime dt;
	int numSoldTicket = 0;
	int nTicketInFlight = 0;
	int status = 1; // Status mac dinh la con ve
	int checkIdFlight = -1; //Kiem tra ma chuyen bay ton tai hay khong
	int checkIdPlane = -1; //Kiem tra so hieu may bay ton hay hay khong?
	while (true) {
		switch (ordinal) {
			case 0:
			{ //Nhap ma chuyen bay
				ConstraintForLetterAndNumber(idFlight, moveOrNot, ordinal, saveOrNot, 12);
				RemoveNotification();
				//Neu nguoi dung thoat ra giua chung
				if (saveOrNot == false) {
					RemoveFormComplete();
					return;
				}
				//Xu ly o nhap lieu bo trong
				if (idFlight == "") {
					gotoxy(X_Notification, Y_Notification);
					cout << "Thong Bao";
					gotoxy(X_Notification, Y_Notification + 1);
					cout << " Vui long khong bo trong Id Flight";
					break;
				}
				//Xu ly trong truong hop xoa
				if (deleteOrNot) {
					int confirmResult = RemoveConfirm();
					gotoxy(50, 50);

					RemoveFormComplete();
					if (confirmResult == 0) { // 0 means Yes
						if (!removeFlightById(fl, idFlight.c_str())) {
							gotoxy(X_Notification, Y_Notification);
							cout << "Thong Bao";
							gotoxy(X_Notification, Y_Notification + 1);
							cout << "Xoa khong thanh cong";
						}
						else {
							gotoxy(X_Notification, Y_Notification);
							cout << "Thong Bao";
							gotoxy(X_Notification, Y_Notification + 1);
							cout << "Xoa thanh cong";
						}
					}
					else {
						gotoxy(X_Notification, Y_Notification);
						cout << "Thong Bao";
						gotoxy(X_Notification, Y_Notification + 1);
						cout << "Tu Choi Xoa";
					}
					system("color 0E");
					return;
				}
				//Tim kiem ma chuyen bay
				checkIdFlight = findIndexFlightById(fl, idFlight.c_str());

				if (checkIdFlight > -1 && editedOrNot == false) {
					gotoxy(X_Notification, Y_Notification);
					cout << "Thong Bao";
					gotoxy(X_Notification, Y_Notification + 1);
					cout << "Id flight da ton tai";
					gotoxy(X_Notification, Y_Notification + 2);
					cout << "He thong khong chap nhan";
					gotoxy(X_Notification, Y_Notification + 3);
					cout << "Id co cung noi dung";
					break;
				}
				else if (checkIdFlight < 0 && editedOrNot == true) {
					gotoxy(X_Notification, Y_Notification);
					cout << "Thong Bao";
					gotoxy(X_Notification, Y_Notification + 1);
					cout << "Id khong ton tai";
					break;
				}

				flightNode *editFlight = findFlightById(fl, idFlight.c_str());
				if (editedOrNot) {
					idFlight = editFlight->data.idFlight;
					airportTo = editFlight->data.airportTo;
					idPlane = editFlight->data.idPlane;
					dt = editFlight->data.departureTime;
					nTicketInFlight = editFlight->data.totalTickets;
					status = editFlight->data.status;

					gotoxy(X_Add + 12, 0 * 3 + Y_Add);
					cout << idFlight;
					gotoxy(X_Add + 12, 1 * 3 + Y_Add);
					cout << airportTo;
					gotoxy(X_Add + 12, 2 * 3 + Y_Add);
					cout << idPlane;
					gotoxy(X_Add + 12, 3 * 3 + Y_Add);
					showDateTime(dt);
					gotoxy(X_Add + 12, 4 * 3 + Y_Add);
					cout << nTicketInFlight;
					gotoxy(X_Add + 12, 5 * 3 + Y_Add);
					cout << status;
				}

				ordinal++;
				break;
			}
			case 1: { //San bay den 
				ConstraintsForLetterAndSpace(airportTo, moveOrNot, ordinal, saveOrNot, 12);
				RemoveNotification();

				if (saveOrNot == false) {
					RemoveFormComplete();
					return;
				}

				if (airportTo == "") {
					gotoxy(X_Notification, Y_Notification);
					cout << "Thong Bao";
					gotoxy(X_Notification, Y_Notification + 1);
					cout << "Vui long khong bo trong airport To ";
					break;
				}
			}
			ordinal++;
			break;

			case 2: { //So hieu may bay
				ConstraintForLetterAndNumber(idPlane, moveOrNot, ordinal, saveOrNot, 12);
				RemoveNotification();
				
				if (saveOrNot == false) {
					RemoveFormComplete();
					return;
				}
				//Kiem tra so hieu may bay nhap vao co ton tai
				if (idPlane == "") {
					gotoxy(X_Notification, Y_Notification); 
					cout << "Thong Bao";
					gotoxy(X_Notification, Y_Notification + 1);
					cout << " Vui Long Khong Bo Trong idPlane ";
					break;
				}

				checkIdPlane = findIndexPlane(PList, idPlane.c_str());
				//Neu may bay khong ton tai
				if (checkIdPlane < 0) {
					gotoxy(X_Notification, Y_Notification);
					cout << "Thong Bao";
					gotoxy(X_Notification, Y_Notification + 1);
					cout << "Id plane khong ton tai";
					break;
				}
			}
			
			ordinal++;
			break;

			case 3: { //Nhap thoi gian khoi hanh cua may bay
				//Khoi tao cac gia tri date time la thoi gian he thong
				initDateTime(dt);
				inputDateTimeInfor(dt, ordinal);
				
				if (saveOrNot == false) {
					RemoveFormComplete();
					return;
				}
				ordinal++;
			}
			break;

			case 4: { //Nhap so ve may bay
				//Lay obj may bay hien tai
				plane* currentPlane = PList.PList[checkIdPlane];

				//Neu o che do edit
				if (editedOrNot) {
					ConstraintForOnlyNumber(nTicketInFlight, moveOrNot, ordinal, saveOrNot, 12, 999);

					RemoveNotification();
					if (saveOrNot == false) {
						RemoveFormComplete();
						return;
					}
					int maxNumOfSeat = currentPlane->rows * currentPlane->cols;
					if (nTicketInFlight > maxNumOfSeat || nTicketInFlight < 20) {
						gotoxy(X_Notification, Y_Notification); 
						cout << "Thong Bao";
						gotoxy(X_Notification, Y_Notification + 1); 
						cout << "So ve khong nam trong  ";
						gotoxy(X_Notification, Y_Notification + 2); 
						cout << "khoang phu hop";
						gotoxy(X_Notification, Y_Notification + 3); cout << "20 <= So cho <=" << maxNumOfSeat;
						break;
					}
				}
				else {
					
					nTicketInFlight = currentPlane->rows * currentPlane->cols; //Tinh tong so ve
				}
				
				ordinal++;
				break;
			}
			case 5: {
				if (editedOrNot) {
					gotoxy(X_Notification, Y_Notification + 1); 
					cout << "0 = Huy     ";
					gotoxy(X_Notification, Y_Notification + 2); 
					cout << "1 = Con ve  ";
					gotoxy(X_Notification, Y_Notification + 3); 
					cout << "2 = Het ve  ";
					gotoxy(X_Notification, Y_Notification + 4); 
					cout << "3 = Hoan tat";
					ConstraintForOnlyNumber(status, moveOrNot, ordinal, saveOrNot, 12, 4);

					RemoveNotification();

					if (saveOrNot == false) {
						RemoveFormComplete();
						return;
					}
				}
				else { //Che do Insert
					//Mac dinh status = 1 kh insert
					status = 1; 
				}
				ordinal++;
				break;
			}
				  			
			case 6: {
				flight addingFlight;
				strcpy_s(addingFlight.idFlight, idFlight.c_str());
				StandardName((char*)airportTo.c_str());
				strcpy_s(addingFlight.airportTo, airportTo.c_str());
				strcpy_s(addingFlight.idPlane, idPlane.c_str());

				addingFlight.departureTime = dt;
				addingFlight.totalTickets = nTicketInFlight;
				addingFlight.status = status;

				if (editedOrNot && checkIdFlight > -1) {
					//Lay du lieu ve
					flightNode *tempNode = findFlightById(fl, addingFlight.idFlight);
					addingFlight.totalTicketsSold = tempNode->data.totalTicketsSold;
					addingFlight.TicketList = tempNode->data.TicketList;

					tempNode->data = addingFlight;
				}
				else { //Them moi
					addingFlight.totalTicketsSold = 0;
					//addEndingList(fl, addingFlight);
					insertFlightAfter(fl, addingFlight);
				}

				idFlight = "";
				airportTo = "";
				initDateTime(dt);
				numSoldTicket = 0;
				nTicketInFlight = 0;
				status = 1;

				RemoveNotification();
				RemoveForm();
				ordinal = 0;
			}
			break;
		} //End switch
	} //End while
}

void menuManageFlightList(flightList &fl)
{
	system("cls");

	gotoxy(X_TitlePage, Y_TitlePage);
	cout << " Flight Management ";

	CurFlightPage = 1;
	TotalFlightPage = (int)ceil((double)fl.numsOfFlight / NumberPerPage);

	Display(ContentFlight, sizeof(ContentFlight) / sizeof(string));

	showFlightListPerPage(fl, 0);

	int signal;
	while (true) {
		while (_kbhit()) {
			signal = _getch();
			if (signal == ESC) {
				ShowCur(false);
				return;
			}

			if (signal == 224) {
				signal = _getch();

				if (signal == PAGE_UP && CurFlightPage > 1) {
					CurFlightPage--;
					changePageManageFlightList(fl);
				}
				else if (signal == PAGE_DOWN && CurFlightPage < TotalFlightPage) {
					CurFlightPage++;
					changePageManageFlightList(fl);
				}
				else if (signal == INSERT) {
					CreateForm(ContentFlightForInsert, 0, 4, 30);
					inputFlightInFor(fl);

					TotalFlightPage = (int)ceil((double) fl.numsOfFlight / NumberPerPage);
					showFlightListPerPage(fl, (CurFlightPage - 1) / NumberPerPage);
				}
				else if (signal == DEL) {
					CreateForm(ContentFlight, 0, 1, 30);
					inputFlightInFor(fl, false, true);
					TotalFlightPage = (int)ceil((double)fl.numsOfFlight / NumberPerPage);
					showFlightListPerPage(fl, (CurFlightPage - 1) / NumberPerPage);
					ShowCur(false);
				}
				else if (signal == HOME) {
					CreateForm(ContentFlight, 0, 6, 30);
					inputFlightInFor(fl, true, false);
					TotalFlightPage = (int)ceil((double)fl.numsOfFlight / NumberPerPage);
					showFlightListPerPage(fl, (CurFlightPage - 1) / NumberPerPage);
					ShowCur(false);
				}
			}
		}
	}
}

int checkOutTicket(flight f, int x)
{
	for (int i = 0; i < f.totalTicketsSold; i++)
	{
		if (x == f.TicketList[i].seatNumber)
		{
			return 1;
		}
	}
	return 0;
}

void showTicketChairBoard(flight f)
{
	int x = X_TicketChair + 8;
	int y = Y_TicketChair + 5;
	int Limit = f.totalTickets;

	// Get the plane information
	plane* currentPlane = nullptr;
	for (int i = 0; i < PList.size; i++) {
		if (strcmp(PList.PList[i]->id, f.idPlane) == 0) {
			currentPlane = PList.PList[i];
			break;
		}
	}

	if (currentPlane == nullptr) {
		std::cerr << "Plane not found!" << std::endl;
		return;
	}

	int rows = currentPlane->rows;
	int cols = currentPlane->cols;

	for (int i = 0; i < cols; i++)
	{
		for (int j = 1; j <= rows; j++)
		{

			char colLabel = 'A' + i;
			char rowLabel[3];
			sprintf(rowLabel, "%02d", j);
			std::string ticketLabel = std::string(1, colLabel) + rowLabel;

			TicketStack(x, y, ticketLabel, checkOutTicket(f, i * rows + j));
			gotoxy(x, y);
			//std::cout << ticketLabel;

			x += 8;
		}

		y += 5;
		x = X_TicketChair + 8;
	}

}

void effectTicketMenu(int index) {
	ShowCur(false);
	int column = (index - 1) % 10; // Tính cột của vé hiện tại
	int row = (index - 1) / 10;    // Tính hàng của vé hiện tại

	// Highlight vé hiện tại
	SetBGColor(1); // Đặt màu nền xanh lam
	gotoxy(X_TicketChair + (column + 1) * 8, Y_TicketChair + (row + 1) * 5);
	char colLabel = 'A' + row;  // Nhãn dãy
	char rowLabel[3];
	sprintf(rowLabel, "%02d", column + 1); // Nhãn dòng (02 số)
	std::cout << char(176) << colLabel << rowLabel << char(176);

	// Bỏ highlight vé trước đó
	column = (CurPosPreTicket - 1) % 10;
	row = (CurPosPreTicket - 1) / 10;

	SetBGColor(ColorCode_Black); // Đặt màu nền đen
	gotoxy(X_TicketChair + (column + 1) * 8, Y_TicketChair + (row + 1) * 5);
	colLabel = 'A' + row; // Nhãn dãy của vé trước đó
	sprintf(rowLabel, "%02d", column + 1);
	std::cout << char(176) << colLabel << rowLabel << char(176);

	CurPosPreTicket = index; // Cập nhật vé trước đó
}

int chooseTicket(flight& f)
{
	//system("color 0E");
	// tao lai vi tri chon ve
	CurPosTicket = 1;
	CurPosPreTicket = 1;

	showTicketChairBoard(f);
	int signal;
	int PASS = 1;// pass dung nhu 1 cai cong tac neu enter thi thoat ra ngoai
	SetBGColor(1);// blue
	gotoxy(X_TicketChair + (0 + 1) * 8, Y_TicketChair + (0 + 1) * 5);// (28,9)
	cout << char(176) << setw(3) << "A01" << char(176);

	while (PASS)
	{
		signal = _getch();
		if (signal == 0) signal = _getch();

		switch (signal)
		{
		case KEY_DOWN:
			if (CurPosTicket + 10 <= f.totalTickets)
			{
				CurPosTicket = CurPosTicket + 10;
				effectTicketMenu(CurPosTicket);
			}
			break;
		case KEY_UP:
			if (CurPosTicket - 10 >= 1)
			{
				CurPosTicket = CurPosTicket - 10;
				effectTicketMenu(CurPosTicket);
			}
			break;
		case KEY_LEFT:
			if (CurPosTicket > 1)
			{
				CurPosTicket--;
				effectTicketMenu(CurPosTicket);
			}
			break;
		case KEY_RIGHT:
			if (CurPosTicket < f.totalTickets)
			{
				CurPosTicket++;
				effectTicketMenu(CurPosTicket);
			}
			break;
		case ESC:
			return -1;
		case ENTER:
			if (checkOutTicket(f, CurPosTicket) == 1) {

				gotoxy(3, 5);
				cout << "Ve nay da co Hanh khach dat cho";
				Sleep(1000);
				gotoxy(3, 5);
				SetBGColor(ColorCode_Black);
				printf("%-50s", " ");
				break;
			}
			PASS = 0;
			return CurPosTicket;
		}// end switch
	}// while
	return 0;
}

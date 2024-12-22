#pragma once
#include"UI.h"
#include"Constraint.h"
#include"Passenger.h"
#include"GlobalVariable.h"
#include"Flight.h"
#include"Plane.h"
#include"ProcessingFile.h"
int curPosPassenger = 1;
int curPassengerPage = 1;
int totalPassengerPage = 0;

extern FlightList fList;
extern planeList PList;
extern string ContentPassenger[5];
extern string ContentFlight[6];
extern int nPassenger;
unsigned int* arrPassengerId;
/*Noi dung cho chuc nang thu 8*/
string specifedFlight[6] = {
		"Flight Id",
		"Plane Id",
		"Total Tickes",
		"Departure Times",
		"Tickets Sold",
		"UnUsed Tickets" };
void createAVLTree(AVLTree& root)
{
	root = NULL;
	nPassenger = 0;
}

// tim max giua a va b
int maxi(int a, int b)
{
	if (a >= b)
	{
		return a;
	}
	return b;
}
// chieu cao cua cay
int height(AVLTree root)
{
	if (root == NULL)
	{
		return 0;
	}
	return root->height;
}

AVLTree createTree(passenger data)
{
	AVLTree newpassenger = new passengerNode;
	newpassenger->data = data;
	newpassenger->pLeft = NULL;
	newpassenger->pRight = NULL;
	newpassenger->height = 1;
	return newpassenger;
}
/*BE LEFT*/
AVLTree rightRotate(AVLTree y)
{
	AVLTree x = y->pLeft;
	AVLTree T2 = x->pRight;

	// thuc hien xoay
	x->pRight = y;
	y->pLeft = T2;
	// cap nhat chieu cao
	y->height = maxi(height(y->pLeft), height(y->pRight)) + 1;
	x->height = maxi(height(x->pLeft), height(x->pRight)) + 1;

	// tra ve node moi
	return x;
}
/*BE RIGHT*/
AVLTree leftRotate(AVLTree x)
{
	AVLTree y = x->pRight;
	AVLTree T2 = y->pLeft;

	// thuc hien phep quay
	y->pLeft = x;
	x->pRight = T2;

	// cap nhat chieu cao
	x->height = maxi(height(x->pLeft), height(x->pRight)) + 1;
	y->height = maxi(height(y->pLeft), height(y->pRight)) + 1;

	return y;
}

// lay gia tri can bang
int getBalanceFactor(AVLTree root)
{
	if (root == NULL)
	{
		return 0;
	}
	return height(root->pLeft) - height(root->pRight);
}

// them theo toan bo thong tin cua hanh khach
AVLTree addPassenger(AVLTree& root, passenger data)
{
	//them nhu cay nhi phan binh thuong
	if (root == NULL)
	{
		return createTree(data);
	}
	if (data.idCard < root->data.idCard)
	{
		root->pLeft = addPassenger(root->pLeft, data);
	}
	else if (data.idCard > root->data.idCard)
	{
		root->pRight = addPassenger(root->pRight, data);
	}
	else  return root;
	/*cap nhat lai chieu cao cho cay*/
	root->height = maxi(height(root->pLeft), height(root->pRight)) + 1;


	/*kiem tra xem co bi mat can bang hay khong*/
	int balanceFactor = getBalanceFactor(root);
	// height(root->pLeft) - height(root->pRight);

	/*neu no mat can bang thi xay ra 4 truong hop*/

	// Left left case
	if (balanceFactor > 1 &&
		data.idCard < root->pLeft->data.idCard)
	{
		return rightRotate(root);
	}
	// right right case
	if (balanceFactor < -1 &&
		data.idCard > root->pRight->data.idCard)
	{
		return leftRotate(root);
	}
	// left right case
	if (balanceFactor > 1 &&
		data.idCard > root->pLeft->data.idCard)
	{
		root->pLeft = leftRotate(root->pLeft);
		return  rightRotate(root);
	}

	// right left case
	if (balanceFactor < -1 &&
		data.idCard < root->pRight->data.idCard)
	{
		root->pRight = rightRotate(root->pRight);
		return leftRotate(root);
	}

	return root;

}

// tra ve gia tri cuc trai thap nhat
AVLTree minValuePassenger(AVLTree root)
{
	AVLTree current = root;
	if (current->pLeft != NULL)
	{
		current = current->pLeft;
	}
	return current;
}

// xoa theo CMND cua hanh khach
AVLTree removePassenger(AVLTree& root, passenger data)
{
	// B1 tim vi tri ung voi cai node can xoa
	if (root == NULL)
	{
		return root;
	}

	if (data.idCard < root->data.idCard)
	{
		root->pLeft = removePassenger(root->pLeft, data);
	}
	else if (data.idCard > root->data.idCard)
	{
		root->pRight = removePassenger(root->pRight, data);
	}
	// neu da tim ra CMND bang dung CMND co trong cay AVL,thi no la node can xoa
	else
	{
		// TH1: ID co 1 cay con hoac khong co cay con nao
		if ((root->pLeft == NULL) || (root->pRight == NULL))
		{
			AVLTree tempo = root->pLeft ? root->pLeft : root->pRight;

			// TH khong co nhanh con
			if (tempo == NULL)
			{
				tempo = root;
				root = NULL;
			}
			// TH co 1 nhanh con TRAI hoac PHAI
			else
			{
				*root = *tempo;/*TRUYEN DIA CHI CUA *TEMPO cho *ROOT*/
				free(tempo);/*GIAI PHONG VUNG NHO TEMPO DO khong dung toi nua*/
			}
		}
		// TH2 :node can xoa co 2 nhanh con
		else
		{
			/*Node thay the la node trai nhat cua nhanh ben PHAI*/
			/*Vi no lon hon tat ca node ben o nhanh ben trai va nho hon tat
			ca node o nhanh ben phai*/
			AVLTree tempo = minValuePassenger(root->pRight);
			/*tim duoc thi chep noi dung cua node thay the vao vi tri node can
			xoa*/
			root->data = tempo->data;
			/*xoa node thay the o vi tri cu di*/
			root->pRight = removePassenger(root->pRight, tempo->data);
		}
		// B2: cap nhat do cao cua node
		root->height = maxi(height(root->pLeft), height(root->pRight)) + 1;
		// B3 : can bang cay
		int balanceFactor = getBalanceFactor(root);

		// Left left case
		if (balanceFactor > 1 &&
			data.idCard < root->pLeft->data.idCard)
		{
			return rightRotate(root);
		}
		// right right case
		if (balanceFactor < -1 &&
			data.idCard > root->pRight->data.idCard)
		{
			return leftRotate(root);
		}
		// left right case
		if (balanceFactor > 1 &&
			data.idCard > root->pLeft->data.idCard)
		{
			root->pLeft = leftRotate(root->pLeft);
			return rightRotate(root);
		}

		// right left case
		if (balanceFactor < -1 &&
			data.idCard < root->pRight->data.idCard)
		{
			root->pRight = rightRotate(root->pRight);
			return leftRotate(root);
		}
	}
}

bool findPassengerFollowID(AVLTree root, unsigned int idCardToFind)
{
	if (root != NULL)
	{
		if (root->data.idCard == idCardToFind)
		{
			return true;
		}
		else if (root->data.idCard < idCardToFind)
		{
			findPassengerFollowID(root->pLeft, idCardToFind);
		}
		else if (root->data.idCard > idCardToFind)
		{
			findPassengerFollowID(root->pRight, idCardToFind);
		}
	}
	return false;
}

passengerNode* findPassenger(AVLTree root, unsigned int idCardToFind)
{
	if (root == NULL) return NULL;
	if (root->data.idCard == idCardToFind)
		return root;
	if (root->data.idCard > idCardToFind)
		findPassenger(root->pLeft, idCardToFind);
	else
		findPassenger(root->pRight, idCardToFind);
}

void showPassenger(passenger p, int position)
{
	int xKeyDisplay[7] = { 1,20,45,63,80,95, 107 };// toa do X cac diem nut
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position * 3);printf("%-5d", position + 1);
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position * 3);printf("%-12d", p.idCard);
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position * 3);printf("%-20s", p.firstname);
	gotoxy(xKeyDisplay[3] + 3, Y_Display + 3 + position * 3);printf("%-10s", p.lastName);
	gotoxy(xKeyDisplay[4] + 5, Y_Display + 3 + position * 3);
	if (p.gender == 1)
		std::cout << "Nam";
	if (p.gender == 0)
		std::cout << "Nu";
}

void showListPassengerPerPage(AVLTree root, int beginIndex)
{
	int i;

	for (i = 0; i + beginIndex <= nPassenger && i < NumberPerPage;i++)
	{
		passengerNode* tempo = findPassenger(root, arrPassengerId[i + beginIndex]);
		showPassenger(tempo->data, i);
	}

	RemoveExceedMember(i, 4);
	gotoxy(X_Page, Y_Page);
	cout << curPassengerPage << "/" << totalPassengerPage;
}

void swap(unsigned int& x, unsigned int& y)
{
	unsigned int tempo;
	tempo = x;
	x = y;
	y = tempo;
}
/*sap xep so CMND trong mang CMND[100]*/
void quickSort(int left, int right, unsigned int a[]) {
	int key = a[(left + right) / 2];
	int i = left, j = right;
	do {
		while (a[i] < key) i++;// tien den khi gap a[i] > KEY
		while (a[j] > key) j--;// lui ve den khi a[j] < KEY
		if (i <= j) {// neu vi tri i < j trong mang thi doi cho
			if (i < j)
				swap(a[i], a[j]);
			i++;	j--;// tiep tuc thuc hien duyet
		}
	} while (i <= j);
	if (left < j) quickSort(left, j, a);
	if (right > i) quickSort(i, right, a);
}
void watchRoot(AVLTree root)
{
	if (root != NULL)
	{
		watchRoot(root->pLeft);
		std::cout << root->data.lastName << "- " << root->data.idCard << endl;
		watchRoot(root->pRight);
	}
}
void inputPassenger(AVLTree& root, bool editedOrNot, bool deleteOrNot, int idPassenger)
{
	ShowCur(true);
	bool SaveOrNot = true;
	bool MoveOrNot = false;
	bool IDExisted = false;

	string first_name;// Ho
	string last_name;// Ten
	int gender = 1;// 0 la nu , 1 la nam

	int ordinal = 1;
	gotoxy(X_Notification, Y_Notification);std::cout << " Thong Bao ";
	gotoxy(X_Notification, Y_Notification + 1);std::cout << " 0 la Nu , 1 la Nam";

	int signal;
	while (true)
	{
		system("color 0E");
		switch (ordinal)
		{
		case 1:// NHAP Ho
		{
			ConstraintsForLetterAndSpace(first_name, MoveOrNot, ordinal, SaveOrNot, 12);
			if (SaveOrNot == false)
			{
				RemoveFormComplete();
				return;
			}
			if (first_name == "")
			{
				gotoxy(X_Notification, Y_Notification);
				std::cout << " Thong Bao ";
				gotoxy(X_Notification, Y_Notification + 1);
				std::cout << "Khong bo trong";
			}

			ordinal++;
		}

		break;
		case 2:// Nhap ten
		{
			ConstraintForOnlyLetter(last_name, MoveOrNot, ordinal, SaveOrNot, 12);
			if (SaveOrNot == false)
			{
				RemoveFormComplete();
				return;
			}
			if (last_name == "")
			{
				gotoxy(X_Notification, Y_Notification);std::cout << " Thong Bao ";
				gotoxy(X_Notification, Y_Notification + 1);std::cout << "Khong bo trong";
			}
			ordinal++;
		}
		break;
		case 3:// nhap gioi tinh
		{
			ConstraintForOnlyGender(gender, MoveOrNot, ordinal, SaveOrNot, 12);
			if (SaveOrNot == false)
			{
				RemoveFormComplete();
				return;
			}
			// 0 la nu , 1 la nam
			if (gender == -1)
			{
				gotoxy(X_Notification, Y_Notification);
				std::cout << " Thong Bao ";
				gotoxy(X_Notification, Y_Notification + 1);
				std::cout << "Khong bo trong";
			}
			ordinal++;
		}
		break;
		case 4:
		{
			passenger p;
			p.idCard = idPassenger;
			//strcpy(P.Ho, FirstName.c_str());
			//strcpy(P.Ten, LastName.c_str());
			StandardName(p.firstname);
			StandardName(p.lastName);
			p.gender = gender;

			addPassenger(root, p);

			gotoxy(X_Notification, Y_Notification);
			std::cout << " Thong Bao ";
			gotoxy(X_Notification, Y_Notification + 1);
			std::cout << " Dat ve thanh cong !!!";
			RemoveNotification();
			RemoveFormComplete();
			return;
		}
		break;
		}/*switch(ordinal)*/
	}/*While(true)*/
}


void watchPassengerListOfFlight(AVLTree root, flight F)
{
	ShowCur(false);
	DisplayForWatchOnly(ContentPassenger, sizeof(ContentPassenger) / sizeof(string), F.totalTicketsSold);

	for (int i = 0; i < F.totalTicketsSold;i++)
	{

		passengerNode* tempora = findPassenger(root, F.TicketList[i].CMND);
		if (tempora == NULL) continue;
		//gotoxy(1,1);.
		//cout << F.TicketList[i].CMND << endl;
		showPassenger(tempora->data, i);

	}
}
/*"5.Xem Danh Sach Hanh Khach Chi Tiet"*/
void seePassengerList(AVLTree root)
{
	system("cls");

	gotoxy(X_TitlePage - 55, Y_TitlePage + 3);
	std::cout << "Kinh moi Thay nhap Ma chuyen bay theo phan danh sach chuyen bay hien co de kiem tra thong tin --->";
	/*Kiem tra xem MaChuyenBay co ton tai*/
	string result;
	CreateForm(ContentFlight, 0, 1, 30);
	bool flag = false;
	bool MoveOrNot = false;
	bool SaveOrNot = true;
	int ordinal = 0;
	FlightNode* WatchingFlight = NULL;
	while (flag == false)
	{
		ShowCur(true);
		ConstraintForLetterAndNumber(result, MoveOrNot, ordinal, SaveOrNot, 12);
		if (SaveOrNot == false)
		{
			RemoveFormComplete();
			return;
		}

		WatchingFlight = findFlightById(fList, result.c_str());
		if (WatchingFlight == NULL)
		{
			gotoxy(X_Notification, Y_Notification);
			std::cout << " Thong Bao ";
			gotoxy(X_Notification, Y_Notification + 1);
			std::cout << "So hieu khong ton tai";
		}
		else
		{
			flag = true;
		}
	}

	system("cls");
	gotoxy(X_TitlePage - 35, Y_TitlePage);

	std::cout << " Danh sach hanh khach co ma chuyen bay " << WatchingFlight->data.idFlight << " toi " << WatchingFlight->data.airportTo;
	std::cout << " luc ";showDateTime(WatchingFlight->data.departureTime);

	//int countdown = nPassenger;

	watchPassengerListOfFlight(root, WatchingFlight->data);

	/*thao tac de thoat ve man hinh chinh*/
	int signal;
	while (true)
	{
		while (_kbhit())
		{
			signal = _getch();
			if (signal == ESC)
			{
				return;
			}
		}
	}
}
/*"4.Huy Bo Ve May Bay",*/
void cancelFlightTicket(AVLTree root)
{
	system("cls");

	gotoxy(X_TitlePage - 55, Y_TitlePage + 3);
	std::cout << "Kinh moi Thay nhap CMND theo phan danh sach chuyen bay hien co de HUY ve -->>";
	gotoxy(X_Notification, Y_Notification);std::cout << " Thong Bao ";
	/*Kiem tra xem MaChuyenBay co ton tai*/
	string result;
	CreateForm(ContentFlight, 0, 1, 30);
	bool flag = false;
	bool MoveOrNot = false;
	bool SaveOrNot = true;
	int ordinal = 0;
	FlightNode* WatchingFlight = NULL;
	while (flag == false)
	{
		system("color 0E");
		ShowCur(true);
		ConstraintForLetterAndNumber(result, MoveOrNot, ordinal, SaveOrNot, 12);
		if (SaveOrNot == false)
		{
			RemoveFormComplete();
			return;
		}

		WatchingFlight = findFlightById(fList, result.c_str());
		if (WatchingFlight == NULL)
		{

			gotoxy(X_Notification, Y_Notification + 1);
			std::cout << "Chuyen bay khong ton tai       ";
			gotoxy(X_Notification, Y_Notification + 2);
			std::cout << "Vui long nhap lai";
		}
		else
		{
			if (WatchingFlight->data.status == 1 || WatchingFlight->data.status == 4)
			{
				ShowCur(false);
				gotoxy(X_Notification, Y_Notification + 1);
				std::cout << "Chuyen bay da HUY hoac HOAN TAT";
				gotoxy(X_Notification, Y_Notification + 2);
				std::cout << "Vui long nhap lai";
				continue;
			}
			flag = true;
		}
	}
	RemoveNotification();
	gotoxy(X_TitlePage - 55, Y_TitlePage + 3);
	std::cout << "Kinh moi Thay nhap CMND theo phan danh sach chuyen bay hien co de kiem tra thong tin --->";
	CreateForm(ContentPassenger, 1, 2, 30);
	int IDHanhKhach = 0;
	int target = -1;
	while (true)
	{
		ShowCur(true);
		ConstraintForOnlyNumber(IDHanhKhach, MoveOrNot, ordinal, SaveOrNot, 12, 999999);
		if (SaveOrNot == false)
		{
			RemoveFormComplete();
			return;
		}

		for (int i = 0; i < WatchingFlight->data.totalTicketsSold; i++)
		{
			if (WatchingFlight->data.TicketList[i].CMND == IDHanhKhach) {
				target = i; break;
			}
		}

		if (target == -1)
		{
			gotoxy(X_Notification, Y_Notification);
			std::cout << " Thong Bao ";
			gotoxy(X_Notification, Y_Notification + 1);
			std::cout << "So CMND khong co";
			gotoxy(X_Notification, Y_Notification + 2);
			std::cout << "o danh sach hanh khach";
		}
		else break;
	}
	RemoveNotification();
	int confirm = RemoveConfirm();
	if (confirm == 0) {

		for (int i = target; i < WatchingFlight->data.totalTicketsSold; i++)
		{
			WatchingFlight->data.TicketList[i - 1] = WatchingFlight->data.TicketList[i];
		}
		WatchingFlight->data.totalTicketsSold--;
	}
	else {
		RemoveFormComplete();
	}
	return;
}
/*3.Dang Ky Ve May Bay*/
void bookTicket(AVLTree& root)
{
	system("cls");

	gotoxy(X_TitlePage - 55, Y_TitlePage + 3);
	std::cout << "Kinh moi Thay nhap Ma chuyen bay theo phan danh sach chuyen bay hien co de kiem tra thong tin --->";
	/*Kiem tra xem MaChuyenBay co ton tai*/

	string result;
	CreateForm(ContentFlight, 0, 1, 30);
	bool flag = false;
	bool MoveOrNot = false;
	bool SaveOrNot = true;
	int ordinal = 0;
	FlightNode* WatchingFlight = NULL;
	while (flag == false)
	{
		system("color 0E");
		ShowCur(true);
		ConstraintForLetterAndNumber(result, MoveOrNot, ordinal, SaveOrNot, 12);
		if (SaveOrNot == false)
		{
			RemoveFormComplete();
			return;
		}

		WatchingFlight = findFlightById(fList, result.c_str());
		if (WatchingFlight == NULL)
		{
			gotoxy(X_Notification, Y_Notification);
			std::cout << " Thong Bao ";
			gotoxy(X_Notification, Y_Notification + 1);
			std::cout << "Chuyen bay khong ton tai       ";
			gotoxy(X_Notification, Y_Notification + 2);
			std::cout << "Vui long nhap lai";

		}
		else
		{

			if (WatchingFlight->data.status == 3 || WatchingFlight->data.status == 1 || WatchingFlight->data.status == 4)
			{
				ShowCur(false);
				gotoxy(X_Notification, Y_Notification + 1);
				std::cout << "Chuyen bay da HUY hoac HOAN TAT";
				gotoxy(X_Notification, Y_Notification + 2);
				std::cout << "Vui long nhap lai";
				continue;
			}
			flag = true;
		}
	}
	/*CHON VE MUON DAT*/
	system("cls");

	gotoxy(X_TitlePage - 32, Y_TitlePage);
	std::cout << " Danh sach hanh khach co ma chuyen bay " << WatchingFlight->data.idFlight<< " toi " << WatchingFlight->data.airportTo;
	std::cout << " luc "; showDateTime(WatchingFlight->data.departureTime);

	gotoxy(3, 4);
	std::cout << "CHU Y ->> Ve co mau Do = ve da co nguoi dat cho!!!!";

	while (true) {
		system("color 0E");
		int ChoosenTicket = chooseTicket(WatchingFlight->data);

		if (ChoosenTicket == -1) return;
		int IDHanhKhach = 0, target = -1;


		gotoxy(X_TitlePage + 30, Y_TitlePage + 3);
		system("color 0E");
		std::cout << "Vui Long Nhap CMND ->";
		CreateForm(ContentPassenger, 1, 2, 30);
		ShowCur(true);
		ConstraintForOnlyNumber(IDHanhKhach, MoveOrNot, ordinal, SaveOrNot, 12, 999999);
		if (SaveOrNot == false)
		{
			gotoxy(X_TitlePage + 30, Y_TitlePage + 3);
			printf("%-50s", " ");
			RemoveFormComplete();
			continue;
		}
		/*Tim kiem xem cai ID nay co nam trong danh sach ve chua*/
		for (int i = 0; i < WatchingFlight->data.totalTicketsSold; i++)
		{
			if (WatchingFlight->data.TicketList[i].CMND == IDHanhKhach) {
				target = i;
				break;
			}
		}
		/*Da dat ve roi va dat them lan nua*/
		if (target > -1) {
			gotoxy(3, 5);
			std::cout << "Ban da dat ve roi !!! (^_^)";
			Sleep(1000);
			gotoxy(3, 5);
			printf("%-50s", " ");


			gotoxy(X_TitlePage + 30, Y_TitlePage + 3);
			printf("%-50s", " ");
			RemoveFormComplete();
			continue;
		}
		/*Khong tim ra*/
		if (target == -1)
		{
			passengerNode* tempora = findPassenger(root, IDHanhKhach);
			/*Neu chua ton tai thi nhap moi*/
			if (tempora == NULL) {
				CreateForm(ContentPassenger, 1, sizeof(ContentPassenger) / sizeof(string), 27);
				gotoxy(X_Add + 12, 0 * 3 + Y_Add);
				std::cout << IDHanhKhach;
				inputPassenger(root, false, false, IDHanhKhach);
				nPassenger++;
			}
			Ticket AddingTicket;
			AddingTicket.CMND = IDHanhKhach;
			AddingTicket.seatNumber = ChoosenTicket;
			WatchingFlight->data.TicketList[WatchingFlight->data.totalTicketsSold] = AddingTicket;
			WatchingFlight->data.totalTicketsSold++;
		}
	}
}
/*"6.Xem So Do Cho Ngoi & Danh Sach Ve Con Trong",*/
void watchUnbookedTicket()
{
	system("cls");

	gotoxy(X_TitlePage - 50, Y_TitlePage + 3);
	std::cout << "Enter the Flight Id according to the existing flight list to check the information --->";

	string idFlight;
	CreateForm(ContentFlight, 0, 1, 15);
	bool saveOrNot = true;
	bool deleteOrNot;
	bool moveOrNot = false;
	flightNode *watchingFlight = NULL;
	int ordinal = 0;
	while (true)
	{
		system("color 0E");
		ShowCur(true);
		ConstraintForLetterAndNumber(idFlight, moveOrNot, ordinal, saveOrNot, 12);
		if (saveOrNot == false)
		{
			RemoveFormComplete();
			return;
		}
		watchingFlight = findFlightById(fList, idFlight.c_str());
		if (watchingFlight == NULL)
		{
			gotoxy(X_Notification, Y_Notification + 1);
			std::cout << "Chuyen bay khong ton tai";
			gotoxy(X_Notification, Y_Notification + 2);
			std::cout << "Vui long nhap lai";
		}
		else
		{
			break;
		}
	}

	system("cls");
	ShowCur(false);
	gotoxy(X_TitlePage, Y_TitlePage);
	std::cout << "Flight Seat Lists of id: " << watchingFlight->data.idFlight << " in -> " << watchingFlight->data.airportTo;
	std::cout << " at -> ";  showDateTime(watchingFlight->data.departureTime);
	gotoxy(3, 4);
	std::cout << " Ve mau Do = ve da co Hanh khach dat ve";
	showTicketChairBoard(watchingFlight->data);

	int signal;
	while (true)
	{
		signal = _getch();
		if (signal == ESC)
		{
			return;
		}
	}
}

void gotoDetailForWatchFlightHistory() {
	string GotoDetail[] = { "Chu thich" ,
							"1.Plane Id = So Hieu May Bay",
							"2.Airline Company = Hang May Bay",
							"3.Number Of Rows = So luong hang ghe",
							"4.Number Of Columns = So luong cot ghe",
							"5.Flights Times = So lan thuc hien chuyen bay"
							 };

	for (int i = 0; i < 6; i++) {  // Cập nhật vòng lặp để duyệt qua 6 phần tử mảng
		gotoxy(X_Add - 10, Y_Add + i * 3);
		std::cout << GotoDetail[i];
	}
}
void showHowManyTimesAirplaneTookOff(plane* A, int position)
{
	int xKeyDisplay[7] = { 1,20,45,63,80,95, 107 };
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position * 3); printf("%-20s", A->id);
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position * 3); printf("%-20s", A->type);
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position * 3); printf("%-5d", A->rows);
	gotoxy(xKeyDisplay[3] + 3, Y_Display + 3 + position * 3); printf("%-5d", A->cols);
	gotoxy(xKeyDisplay[4] + 6, Y_Display + 3 + position * 3); printf("%-5d", A->flyTimes);
}

//sắp xếp giảm dần số lượt thực hiện chuyến bay bubble_sort
void bubbleSortByFlyTimes(plane* planes[], int size) {
	for (int i = 0; i < size - 1; i++) {
		// Lặp qua mảng từ đầu đến cuối, giảm dần số phần tử chưa sắp xếp
		for (int j = 0; j < size - 1 - i; j++) {
			// So sánh flyTimes của hai phần tử liên tiếp
			if (planes[j]->flyTimes < planes[j + 1]->flyTimes) {
				// Hoán đổi nếu flyTimes của planes[j] nhỏ hơn planes[j+1]
				plane* temp = planes[j];
				planes[j] = planes[j + 1];
				planes[j + 1] = temp;
			}
		}
	}
}

/*"7.Xem Chi Tiet So Lan Thuc Hien Chuyen Bay",*/ //câu h
void watchHowManyTimeFlightTookOff()
{
	system("cls");

	gotoxy(X_TitlePage, Y_TitlePage);
	cout << " SO CHUYEN BAY DA THUC HIEN CUA CAC MAY BAY";

	string StaticsTable[5] = { "Plane Id","Airline Company" ,"Number Of Rows","Number Of Columns","Flights Times"};
	gotoDetailForWatchFlightHistory();

	bubbleSortByFlyTimes(PList.PList, PList.size);
	for (int i = 0; i < PList.size; i++)
	{
		showHowManyTimesAirplaneTookOff(PList.PList[i], i);
	}
	DisplayForWatchOnly(StaticsTable, 5, PList.size);
	/*ESC de quay lai man hinh chinh*/
	int signal;
	while (true)
	{
		signal = _getch();
		if (signal == ESC)
		{
			return;
		}
	}
}

/* 8.Xem Cac Chuyen Bay Di Toi Cac Dia Danh & Ngay Gio Cu The*/
void watchFlightsWithDateTimeAndDestination()
{
	system("cls");
	int ordinal = 0;
	bool saveOrNot = true;
	bool moveOrNot = false;
	bool flag = true;
	int destinationExisted = -1;// tim kiem san bay den co ton tai khong
	string destination;
	DateTime dt;
	/*Man hinh mo dau*/
	gotoxy(X_TitlePage - 55, Y_TitlePage + 3);
	cout << "Enter the destination name to check the information -->>        Airport To: ";
	
	while (flag == true)
	{
		switch (ordinal)
		{
		case 0:
		{
			//CreateForm(ContentFlight,1,2,30);
			ShowCur(true);
			ConstraintsForLetterAndSpace(destination, moveOrNot, ordinal, saveOrNot, 20);
			/*Neu nhan phim ESCAPE*/
			if (saveOrNot == false)
			{
				RemoveFormComplete();
				return;
			}
			/*Neu bi bo trong*/
			if (destination == "")
			{
				gotoxy(X_Notification, Y_Notification);cout << "Thong Bao";
				gotoxy(X_Notification, Y_Notification + 1);cout << "Vui Long Khong Bo Trong";
			}
			/*Xu li xem co ton tai dia danh nay khong*/
			destinationExisted = findDestinationByAirPort(fList, destination.c_str());
			StandardName((char*)destination.c_str());

			if (destinationExisted == -1)
			{
				gotoxy(X_Notification, Y_Notification);cout << "Thong Bao";
				gotoxy(X_Notification, Y_Notification + 1);cout << "Khong co chuyen bay toi " << destination;
				gotoxy(X_Notification, Y_Notification + 2);cout << "Vui long chon dia diem khac";
				break;
			}
		}
		ordinal++;
		break;
		case 1:
		{
			flag = false;
			break;
		}
		}
	}
	system("cls");
	gotoxy(X_TitlePage - 35, Y_TitlePage);
	cout << " List of flights to the " << destination << " airport: ";

	int count = 0;
	for (flightNode *search = fList.pHead;search != NULL;search = search->pNext)
	{
		if (_strcmpi(search->data.airportTo, destination.c_str()) == 0)
		{
			showSpecificFlight(search->data, count++);
		}
	}
	DisplayForWatchOnly(specifedFlight, sizeof(specifedFlight) / sizeof(string), count);
	int signal;
	while (true)
	{
		while (_kbhit())
		{
			signal = _getch();
			if (signal == ESC)
			{
				return;
			}
		}
	}
}

void showSpecificFlight(flight f, int position)
{
	int xKeyDisplay[7] = { 1,20,45,63,80,95, 107 };// toa do X cac diem nut
	gotoxy(xKeyDisplay[0] + 3, Y_Display + 3 + position * 3); printf("%-20s", f.idFlight);
	gotoxy(xKeyDisplay[1] + 3, Y_Display + 3 + position * 3); printf("%-20s", f.idPlane);
	gotoxy(xKeyDisplay[2] + 3, Y_Display + 3 + position * 3); printf("%-5d", f.totalTickets);
	gotoxy(xKeyDisplay[3] + 3, Y_Display + 3 + position * 3); showDateTime(f.departureTime);
	gotoxy(xKeyDisplay[4] + 5, Y_Display + 3 + position * 3); printf("%-3d", f.totalTicketsSold);
	gotoxy(xKeyDisplay[5] + 5, Y_Display + 3 + position * 3); printf("%-3d", (f.totalTickets - f.totalTicketsSold));
}

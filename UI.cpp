#include "UI.h"
#include<iostream>
#include<conio.h>//getch()
#include<stdint.h>
#include<string.h>//char
#include<string>//string
#include<iomanip>// for setw va setfill
#include "MyLib.h"
#include "GlobalVariable.h"
#include "Plane.h"

using namespace std;

//Global var
PlaneList PList;


int xKeyDisplay[7] = { 1,20,45,63,83,95, 107 };// toa do X cac diem nut
char TenHocVien[100] = { "POST AND TELECOMUNICATIONS INSTITUTE OF TECHNOLOGY IN HO CHI MINH CITY" };


// nContent - so luong thanh phan co trong bang do
void RemoveExceedMember(int count, int nContent)
{
	if (count < NumberPerPage)
	{
		for (int i = count; i < NumberPerPage; i++)
		{
			for (int y = 0; y < nContent; y++)
			{
				gotoxy(xKeyDisplay[y] + 3, Y_Display + 3 + i * 3);
				printf("%-18s", " ");
			}
		}
	}
}

/* ========== Tao bang xuat thong tin ===============*/

/*Noi dung hien thi trong bang liet ke*/
string ContentAirplane[4] = { "So Hieu", "Loai", "Hang", "Cot"};
string ContentFlight[6] = { "MaChuyenBay","SanBayDen","SoHieuMayBay","ThoiGianDi","TongSoVe","TrangThai" };
string ContentTicket[2] = { "Ten Ve","TrangThai" };
string ContentPassenger[5] = { "STT","CMND","Ho","Ten","GioiTinh" };

void Display(string content[], int nContent)// ve bang 
{
	system("color 0E");
	SetColor(14);
	SetBGColor(0);
	//show key - the hien ra noi dung cua cac cot
	for (int i = 0; i < nContent; i++)
	{// Y_Display 4
		gotoxy(xKeyDisplay[i] + 3, Y_Display + 1);
		cout << content[i];
	}
	//ve cac duong thang de phan chia cac cot - kich thuoc toi da la 24 ve chieu dai
	for (int j = Y_Display; j <= Y_Display + 20; j++)
	{
		for (int i = 0; i < nContent + 1; i++)
		{
			gotoxy(xKeyDisplay[i], j);
			cout << char(176);
		}
	}
	//ve thanh ngang ben tren va duoi
	for (int i = xKeyDisplay[0]; i <= xKeyDisplay[nContent]; i++)
	{
		//ve thanh ngang ben tren so 1
		gotoxy(i, Y_Display);
		cout << char(176);

		// ve thanh ngang ben tren so 2
		gotoxy(i, Y_Display + 2);
		cout << char(176);

		//ve thanh ngang ben duoi
		gotoxy(i, Y_Display + 21);
		cout << char(176);
	}

	cout << endl;
	gotoxy(X_Tutorial, Y_Tutorial);
	cout << " Huong dan ";
	gotoxy(X_Tutorial, Y_Tutorial + 2);
	cout << " Page Up:Len || Page Down:Xuong ";
	gotoxy(X_Tutorial, Y_Tutorial + 3);
	cout << " Insert:Them || Del:Xoa ";
	gotoxy(X_Tutorial, Y_Tutorial + 4);
	cout << " Home:Chinh Sua || ESC : thoat";
	gotoxy(X_Notification, Y_Notification);
	cout << " Thong Bao ";
}
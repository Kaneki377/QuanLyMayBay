#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "iostream"
#include "ctime"
#include "UI.h"
#include "DateTime.h"

//So ngay cua moi thang
int nDayEachM[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

//Function khoi tao gia tri ngay gio hien tai
void initDateTime(dateTime &dt) {
	//Lay ngay gio hien tai theo may tinh
	time_t nowTime = time(0);
	//Con tror the hien ngay gio hien tai
	tm* localTime = localtime(&nowTime);

	dt.hour = localTime->tm_hour;
	dt.minutes = localTime->tm_min;
	dt.day = localTime->tm_mday;
	dt.month = 1 + localTime->tm_year;
	dt.year = 1900 + localTime->tm_year;
}

//Function kiem tra so ngay va thang co hop le va kiem tra nam nhuan
bool isDateTimeFormatRight(dateTime dt) {
	nDayEachM[2] = 28;
	if ((dt.year % 400 == 0) || (dt.year % 4 == 0 && dt.year % 100 != 0)) {
		nDayEachM[2] = 29;
	}
	if (dt.day > nDayEachM[dt.month]) {
		return false;
	}

	return true;
}

//
bool isDateTimeValid(dateTime dt) {
	if (!isDateTimeFormatRight(dt)) {
		return false;
	}

	nDayEachM[2] = 28;
	time_t nowTime = time(0);
	tm* localTime = localtime(&nowTime);

	dateTime dtNow;
	dtNow.year = 1900 + localTime->tm_year;
	dtNow.month = 1 + localTime->tm_mon;
	dtNow.day = localTime->tm_mday;
	dtNow.hour = localTime->tm_hour;
	dtNow.minutes = localTime->tm_min;

	if (dt.year < dtNow.year) {
		return false;
	}

	if ((dt.year == dtNow.year) && (dt.month < dtNow.month)) {
		return false;
	}

	if ((dt.year % 400 == 0) || (dt.year % 4 == 0 && dt.year % 100 != 0)) {
		nDayEachM[2] = 29;
	}

	if (dt.year == dtNow.year && dt.month == dtNow.month && dt.day < dtNow.day) {
		return false;
	}

	if (dt.year == dtNow.year && dt.month == dtNow.month && dt.day == dtNow.day && dt.hour < dtNow.hour) {
		return false;
	}

	if (dt.year == dtNow.year && dt.month == dtNow.month && dt.day == dtNow.day && dt.hour == dtNow.hour && dt.minutes <= dtNow.minutes) {
		return false;

	}

	return true;
}


void showDateTime(dateTime& dt) {
	cout << dt.hour << ":" << dt.minutes << " " << dt.day << "/" << dt.month << "/" << dt.year;
}

bool isSameDate(dateTime dt1, dateTime dt2) {
	return dt1.day == dt2.day && dt2.month == dt1.month && dt1.year == dt2.year;
}

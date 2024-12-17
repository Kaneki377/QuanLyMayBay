#pragma once

#include "ctime"

//Cau truc date time
// Year - Month - Day - Hour - Minutes

struct DateTime {
	int year;
	int month;
	int day;
	int hour;
	int minutes;
};
typedef struct DateTime dateTime;


void initDateTime(dateTime& dt);
bool isDateTimeFormatRight(dateTime dt);
bool isDateTimeValid(dateTime dt);
void showDateTime(dateTime& dt);
bool isSameDate(dateTime dt1, dateTime dt2);



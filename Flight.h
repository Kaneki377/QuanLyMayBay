#pragma once

#include "Plane.h"
#include "Ticket.h"
#include "GlobalVariable.h"
#include "DateTime.h"

//--- Cau truc thong tin 1 chuyen bay
struct Flight {
	char idFlight[10];
	dateTime departureTime;
	char airportTo[20];
	char idPlane[15];
	int status;
	int totalTickets;
	int totalTicketsSold;

	Ticket* TicketList;
};
typedef struct Flight flight;

//Danh sach chuyen bay - DSLK don
struct FlightNode {
	flight data;
	struct FlightNode *pNext;
};
typedef struct FlightNode flightNode;

struct FlightList {
	flightNode* pHead;
	flightNode* pTail;
	int numsOfFlight;
};
typedef struct FlightList flightList;

//Function 

void initFlightList(flightList &fl);
flightNode* createFlightNode(flight data);
void addBeginningList(flightList &fl, flight data);
void addEndingList(flightList &fl, flight data);
void insertFlightAfter(flightList &fl, flight data);
int findIndexFlightById(flightList fl, const char* idFlightToFind);
int findDestinationByAirPort(flightList fl, const char* airportToFind);
FlightNode* findFlightById(flightList fl, const char* idFlightToFind);
void inputDateTimeInfor(dateTime &dt, int ordinal);
bool removeHead(flightList &fl);
bool removeEnding(flightList &fl);
bool removeAfterAnother(flightList &fl, flightNode *tempFlight);
bool removeFlightById(flightList &fl, const char* idFlightToFind);
void updateFlightStatus(flightList &fl);
void showFlightInfor(flight f, int position);
void showFlightListInfor(flightList fl);
void showFlightListPerPage(flightList fl, int startIndex);
void changePageManageFlightList(flightList fl);
void inputFlightInFor(flightList &fl, bool editedOrNot = false, bool deleteOrNot = false);
void menuManageFlightList(flightList &fl);
int checkOutTicket(flight f, int x);
void showTicketChairBoard(flight f);
void effectTicketMenu(int index);
int chooseTicket(flight& f);
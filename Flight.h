#pragma once

#include "Plane.h"
#include "Ticket.h"
#include "GlobalVariable.h"
#include "Process.h"
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

void initFlight(flight &f);
void initFlightList(flightList &fL);
flightNode* createFlightNode(flight data);
void addBeginningList(flightList &fL, flight data);
void addEndingList(flightList &fL, flight data);

void insertFlightAfter();

int findIndexFlightById(flightList fL, const char* idFlight);
int findDestinationByAirPort(flightList fL, const char* airportTo);
FlightNode* findFlightById(flightList fL, const char* idFlight);
void inputDateTimeInfor(dateTime &dt, int ordinal);
bool removeHead(flightList &fL);
bool removeEnding(flightList &fL);
bool removeAfterAnother(flightList &fL, flightNode *temporFlight);
bool removeFlightById(flightList &fL, const char* idFlight);
bool cleanUpFlightList(flightList &fL);
void updateFlightStatus(flightList &fL);
void showTicketChairBoard(flight f);
void effectTicketMenu(int index, int PreColor);
int chooseTicket(flight &f);
void showFlightInfor(flight f, int position);
void showFlightList(flightList fL);
void showFlightListPerPage(flightList fL, int StartIndex);
void changePageManageFlightList(flightList fL);
bool isFlightDataEmpty(flight f);
void inputFlightInFor(flightList &fL, bool editedOrNot = false, bool deleteOrNot = false);
void MenuManageFlightList(flightList &fL);
int checkOutTicket(flight f, int x);
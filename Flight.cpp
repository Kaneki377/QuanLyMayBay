#pragma once

#include "Plane.h"
#include "GlobalVariable.h"
#include "Ticket.h"
#include "DateTime.h"
#include "Flight.h"
#include "Constraint.h"


/*Vi tri cua danh sach chuyen bay*/
int CurPosFlight = 0;
int CurPosPreFlight = 0;
int CurFlightPage = 1;
int TotalFlightPage = 0;

int CurPosTicket = 1;
int CurPosPreTicket = 1;

extern string ContentFlight[6];
extern planeList pl;

void initFlight(flight& f) {
	f.totalTickets = 0;
	f.totalTicketsSold = 0;
	f.TicketList = new Ticket[100];
	f.status = 2;
	//Status: 
}

void initFlightList(flightList& fl) {

}

flightNode* createFlightNode(flight data)
{
	flightNode* tempNode = new flightNode;
	if (tempNode == NULL)
	{
		return NULL;
	}
	tempNode->data = data;
	tempNode->pNext = NULL;

	return tempNode;
}

void addBeginningList(flightList &fl, flight data)
{
	flightNode* tempoNode = createFlightNode(data);

	tempoNode->pNext = fl.pHead;
	fl.pHead = tempoNode;
	fl.numsOfFlight++;
}

void addEndingList(flightList &fl, flight data)
{
	flightNode* tempo = createFlightNode(data);

	if (fl.pHead == NULL)
	{
		fl.pHead = fl.pTail = tempo;
	}
	else
	{
		fl.pTail->pNext = tempo;
		fl.pTail = tempo;
	}
	fl.numsOfFlight++;
}
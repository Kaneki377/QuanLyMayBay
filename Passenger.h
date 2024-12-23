#pragma once
#include"UI.h"
#include"Constraint.h"
#include"Flight.h"

/*Thong tin 1 hanh khach*/
struct Passenger
{
	char idCard[13];// day la key chinh
	char firstname[20];
	char lastName[10];
	int gender;// 1 la nam , 0 la nu
	bool booked;// kiem tra xem da mua ve chua
};
typedef struct Passenger passenger;

struct Passengernode
{
	passenger data;
	struct Passengernode* pLeft;
	struct Passengernode* pRight;
	int height;// chieu cao cua node
};
typedef struct Passengernode passengerNode;
typedef passengerNode* AVLTree;

void createAVLTree(AVLTree& root);
int maxi(int a, int b);
int height(AVLTree root);
AVLTree createTree(passenger data);
AVLTree rightRotate(AVLTree root);
AVLTree leftRotate(AVLTree root);
int getBalanceFactor(AVLTree root);
AVLTree addPassenger(AVLTree& root, passenger data);
AVLTree minValuePassenger(AVLTree root);
AVLTree removePassenger(AVLTree& root, passenger data);
bool findPassengerFollowID(AVLTree root, char* idCardToFind);
passengerNode* findPassenger(AVLTree root, char* idCardToFind);
void showPassenger(passenger P, int position);
void showListPassengerPerPage(AVLTree root, int beginIndex);
//void changePassengerMenuManagePerPage(AVLTree root);
void inputPassenger(AVLTree& root, bool editedOrNot, bool deleteOrNot, char* idPassenger);
void seePassengerList(AVLTree root);
void cancelFlightTicket(AVLTree root);
void bookTicket(AVLTree& root);
void watchUnbookedTicket();
void watchHowManyTimeFlightTookOff();
void watchFlightsWithDateTimeAndDestination();
void showSpecificFlight(flight f, int position);
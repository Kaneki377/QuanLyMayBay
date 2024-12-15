#pragma once
#include<stdint.h>
#include<string.h>//char
#include<string>//string
#include<iomanip>// for setw va setfill
#include "Plane.h"
#include "GlobalVariable.h"

using namespace std;

void NormalLine();
void HighlightLine();
int ScrollMenu(char Menu[MaxItem][70]);
void CreateRow(int x, int y, string content, int length);
void CreateForm(string content[], int StartIndex, int nContent, int length);
void TicketStack(int x, int y, int  text, int status);
int RemoveConfirm();
void FloatingEffectWord(char Content[], int x, int y, int Color);
void RemoveExceedMember(int count, int nContent);
void RemoveForm();
void RemoveFormComplete();
void RemoveOldData(int nContent, int locate);
void RemoveFormForFlight();
void RemoveNotification();
void Display(string content[], int nContent);
void DisplayForWatchOnly(string content[], int nContent, int count);
void CenterMenu();
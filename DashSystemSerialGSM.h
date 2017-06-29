#ifndef _DashSystemSerialGSM_H
#define _DashSystemSerialGSM_H
#include "Arduino.h"

#define SERIALTIMEOUT 2000
#define PHONESIZE 13
#define MAXMSGLEN 160
#define BOOTTIME 25

class DashSystemSerialGSM {
public:
  void FwdSMS2Serial();
  void SendSMS();
  void SendSMS(char * cellnumber,char * outmsg);
  void DeleteAllSMS();
  void Reset();
  void answer();
  void hungup();
  void dial(char * pnumber);
  void EndSMS();
  void StartSMS();
  int ReadLine();
  int ReceiveSMS();
  void Sender(char * var1);
  char * Sender();
  void Rcpt(char * var1);
  char * Rcpt();
  void Message(char * var1);
  char * Message();
  void Boot();

  char sendernumber[PHONESIZE + 1];
  char rcpt[PHONESIZE + 1];
  char outmessage[160];
  char inmessage[160];
  
protected:
  unsigned long lastrec;
  
};

#endif /* not defined _DashSystemSerialGSM_H */


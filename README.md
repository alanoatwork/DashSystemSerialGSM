# DashSystemSerialGSM
Library for communicating with GMS modem using the Hologram Dash in passthrough mode.

Derived from SerialGSM by Meir Michanie 
Released under GPL3

DashSystemSerialGSM is an Arduino library to be used with the Hologram Dash in passthrough mode.

The library allows you to send/receive SMS with simple OOP methods. The library also allows you to receive or make phone calls.

Install:
========

	* Create a folder named "DashSystemSerialGSM" under libraries.
	* Copy the content of this repository into it.


Samples:
========
Sample program to send and receive SMS messages:

```

#include <DashSystemSerialGSM.h>
DashSystemSerialGSM cell;

void setup() {
  Serial.begin();

  HologramCloud.enterPassthrough();

  cell.Boot();
  cell.DeleteAllSMS();
  cell.FwdSMS2Serial();

  cell.Rcpt("+15555555");
  cell.Message("hello world");
  cell.SendSMS();
}

void loop() {
   if (cell.ReceiveSMS()){
     Serial.print("Sender: ");
     Serial.println(cell.Sender());
     Serial.print("message: ");
     Serial.println(cell.Message());
     cell.DeleteAllSMS();
  }
}

```

#include <DashSystemSerialGSM.h>
DashSystemSerialGSM cell;

void setup() {
  Serial.begin();

  HologramCloud.enterPassthrough();

  cell.Boot();
  cell.DeleteAllSMS();
  cell.FwdSMS2Serial();

  cell.Rcpt("+19495472010");
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

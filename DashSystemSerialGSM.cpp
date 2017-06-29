// DashSystemSerialGSM version 1.0
// by Alan Ostroff


// error codes
// http://www.developershome.com/sms/resultCodes2.asp
#include <DashSystemSerialGSM.h>


void DashSystemSerialGSM::FwdSMS2Serial(){
  SerialSystem.println("AT+CMGF=1"); // set SMS mode to text
  delay(200);
  this->ReadLine();
  SerialSystem.println("AT+CNMI=2,2,0,0,0"); // set module to send SMS data to serial out upon receipt 
  delay(200);
  this->ReadLine();
}

void DashSystemSerialGSM::answer(){
  SerialSystem.println("ATA");
}

void DashSystemSerialGSM::hungup(){
  SerialSystem.println("ATH");
}

void DashSystemSerialGSM::dial(char * pnumber){
  this->Rcpt(pnumber);
  SerialSystem.print("ATD");
  SerialSystem.println(pnumber);
  //this->println('\r');
}

void DashSystemSerialGSM::SendSMS(char * cellnumber,char * outmsg){
  this->Rcpt(cellnumber);
  this->StartSMS();
  this->Message(outmsg);
  SerialSystem.print(outmessage);
  this->EndSMS();
  delay(500);
  this->ReadLine();
}

void DashSystemSerialGSM::SendSMS(){
  this->StartSMS();
  SerialSystem.print(outmessage);
  this->EndSMS();
  delay(500);
  this->ReadLine();
}

void DashSystemSerialGSM::DeleteAllSMS(){
  SerialSystem.println("AT+CMGD=1,4"); // delete all SMS
  delay(200);
  this->ReadLine();
}

void DashSystemSerialGSM::Reset(){
  SerialSystem.println("AT+CFUN=1,1"); // Reset Modem
  delay(200);
  this->ReadLine();
}


void DashSystemSerialGSM::EndSMS(){
  SerialSystem.print(char(26));  // ASCII equivalent of Ctrl-Z

  //delay(5 * 1000); // the SMS module needs time to return to OK status
}

void DashSystemSerialGSM::StartSMS(){

  SerialSystem.println("AT+CMGF=1"); // set SMS mode to text
  delay(200);
  this->ReadLine();

  SerialSystem.print("AT+CMGS=");

  SerialSystem.print(char(34)); // ASCII equivalent of "

  SerialSystem.print(rcpt);

  SerialSystem.println(char(34));  // ASCII equivalent of "

  delay(500); // give the module some thinking time
  this->ReadLine();

}

int DashSystemSerialGSM::ReadLine(){
  static int pos=0;
  char nc;
  while (SerialSystem.available()){
    nc=SerialSystem.read();
    if (nc == '\n' or (pos > MAXMSGLEN) or ((millis()> lastrec + SERIALTIMEOUT)and (pos > 0)) ){
      nc='\0';
      lastrec=millis();
      inmessage[pos]=nc;
     pos=0;
      return 1;
    }
    else if (nc=='\r') {
    }
    else{
      inmessage[pos++]=nc;
      lastrec=millis();
    }
  }
  return 0;
}


int DashSystemSerialGSM::ReceiveSMS(){
  static boolean insms=0;
  if (this->ReadLine()){
  // Get the number of the sms sender in order to be able to reply
	if ( strstr(inmessage, "CMT: ") != NULL ){
	    insms=1;
	    int sf=6;
	    if(strstr(inmessage, "+CMT:")) sf++; 
		    for (int i=0;i < PHONESIZE;i++){
		      sendernumber[i]=inmessage[sf+i];
		    }
		sendernumber[PHONESIZE]='\0';
		return 0;
	 }else{ 
		if(insms) {
			insms=0;
			return 1;
		}
	}
  }
  return 0;
}


boolean DashSystemSerialGSM::Verbose(){
	return verbose;
}

void DashSystemSerialGSM::Verbose(boolean var1){
	verbose=var1;
}

char * DashSystemSerialGSM::Sender(){
	return sendernumber;
}


char * DashSystemSerialGSM::Rcpt(){
	return rcpt;
}

char * DashSystemSerialGSM::Message(){
	return inmessage;
}


void DashSystemSerialGSM::Sender(char * var1){
	sprintf(sendernumber,"%s",var1);
}


void DashSystemSerialGSM::Rcpt(char * var1){
	sprintf(rcpt,"%s",var1);
}

void DashSystemSerialGSM::Message(char * var1){
	sprintf(outmessage,"%s",var1);
}

void DashSystemSerialGSM::Boot(){
  int counter=0;
  while(counter++ < BOOTTIME){
    delay(1000);
  }
}

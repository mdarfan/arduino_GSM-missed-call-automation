#include <GSM.h>

// PIN Number
#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess;
GSMVoiceCall vcs;

// Array to hold the number for the incoming call
char numtel[20];

#include "SIM900.h"
#include <SoftwareSerial.h> // tx to 2 rx to 3
#include "call.h"

#include "sms.h"

SMSGSM sms;


CallGSM call;
boolean started=false;
char sms_text[160];
int count=0;


void setup()
{
    
    Serial.begin(9600);
    Serial.println("started");
    pinMode(13,OUTPUT);
    if (gsm.begin(9600)) 
    {
        Serial.println("\nstatus=READY");
        started=true;
    } 
    else 
        Serial.println("\nstatus=IDLE");
}

void loop()
{
  
   String smsText ="";

  switch (call.CallStatus())
  {
    case CALL_NONE: // Nothing is happening

      break;

    case CALL_INCOM_VOICE : // Yes! Someone is calling us

      Serial.println("RECEIVING CALL");
      vcs.retrieveCallingNumber(numtel, 20);
      Serial.print("Number:");
      Serial.println(numtel);
       call.HangUp();
       Serial.print("cut the call");
       if(count==0)
       {
        digitalWrite(13,HIGH);
        count=1;
       }
       else
       {
       digitalWrite(13,LOW);
       count=0;
       }
       delay(2000);
      
       delay(2000);
      // smsText = "Temperature: "+String(temperature,1)+"C Humidity: "+String(humidity,1)+"%";
       //smsText.toCharArray(sms_text,160);
       //Serial.println(smsText);
      // sms.SendSMS("+306900000000",sms_text);
      break;

    case CALL_COMM_LINE_BUSY:  // In this case the call would be established

      Serial.println("TALKING. Line busy.");
      
      break;
  }
  delay(1000);
}

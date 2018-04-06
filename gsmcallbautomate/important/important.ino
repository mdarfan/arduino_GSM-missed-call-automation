/*
 Receive Voice Call

 This sketch, for the Arduino GSM shield, receives voice calls,
 displays the calling number, waits a few seconds then hangs up.

 Circuit:
 * GSM shield
 * Voice circuit. Refer to to the GSM shield getting started guide
   at http://www.arduino.cc/en/Guide/ArduinoGSMShield#toc11
 * SIM card that can accept voice calls

 With no voice circuit the call will connect, but will not send or receive sound

 created Mar 2012
 by Javier Zorzano

 This example is in the public domain.

 http://www.arduino.cc/en/Tutorial/GSMExamplesReceiveVoiceCall

 */

// Include the GSM library tx 2 rx 3
#include <GSM.h>

// PIN Number
#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess;
GSMVoiceCall vcs;

// Array to hold the number for the incoming call
char numtel[20];
char numtelnew[13];
char num[13] = "+919742266570";
char num1[13] = "+917259227246";
char num2[13] = "+918095832697";

int count =0;

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Receive Voice Call");

  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  // This makes sure the modem correctly reports incoming events
  vcs.hangCall();

  Serial.println("Waiting for a call");
  digitalWrite(13,HIGH);
}

void loop() {
  // Check the status of the voice call
  switch (vcs.getvoiceCallStatus()) {
    case IDLE_CALL: // Nothing is happening

      break;

    case RECEIVINGCALL: // Yes! Someone is calling us

      Serial.println("RECEIVING CALL");

      // Retrieve the calling number
      vcs.retrieveCallingNumber(numtel, 20);

      // Print the calling number
      Serial.print("Number:");
      Serial.println(numtel);
      numtelnew[0]=numtel[0];
      numtelnew[1]=numtel[1];
      numtelnew[2]=numtel[2];
      numtelnew[3]=numtel[3];
      numtelnew[4]=numtel[4];
      numtelnew[5]=numtel[5];
      numtelnew[6]=numtel[6];
      numtelnew[7]=numtel[7];
      numtelnew[8]=numtel[8];
      numtelnew[9]=numtel[9];
      numtelnew[10]=numtel[10];
      numtelnew[11]=numtel[11];
      numtelnew[12]=numtel[12];
      numtelnew[13]=numtel[13];
      Serial.println(numtelnew);
      if((numtelnew[3]==num[3] && numtelnew[4]==num[4] && numtelnew[5]==num[5] && numtelnew[12]==num[12]&& numtelnew[11]==num[11]&& numtelnew[10]==num[10]) ||
      (numtelnew[3]==num1[3] && numtelnew[4]==num1[4] && numtelnew[5]==num1[5] && numtelnew[12]==num1[12]&& numtelnew[11]==num1[11]&& numtelnew[10]==num1[10]) ||
      (numtelnew[3]==num2[3] && numtelnew[4]==num2[4] && numtelnew[5]==num2[5] && numtelnew[12]==num2[12]&& numtelnew[11]==num2[11]&& numtelnew[10]==num2[10]))
      {
        if(count==0)
        {
        Serial.println("turning on");
        digitalWrite(12,HIGH);
        delay(4000);
        vcs.hangCall();
        count=1;
        }
        else if(count==1)
        {
         Serial.println("turning oFF");
        digitalWrite(12,LOW);
        delay(8000);
        vcs.hangCall();
        count=0; 
        }
      }
      else
      {
        Serial.println("wrong number");
        vcs.hangCall();
      break;  
      }

      // Answer the call, establish the call
      //delay(4000);
      Serial.println("call hanged");
       // vcs.hangCall();
      //vcs.answerCall();
      break;

    case TALKING:  // In this case the call would be established

      Serial.println("TALKING. Press enter to hang up.");
      while (Serial.read() != '\n') {
        delay(100);
      }
      vcs.hangCall();
      Serial.println("Hanging up and waiting for the next call.");
      break;
  }
  delay(1000);
}



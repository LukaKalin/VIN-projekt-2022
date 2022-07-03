#include <SoftwareSerial.h>

SoftwareSerial sim800l(10,11);

#define SMS_send_button 7 
#define Call_button 6
#define SMS_recieve_button 5

//Button state
bool SMS_send_state; 
bool Call_button_state; 
bool SMS_recieve_state; 

void setup()
{

  //The buttons 1re always on LOW level, when pressed they go HIGH
  pinMode(SMS_send_button, INPUT);
  pinMode(Call_button, INPUT);
  pinMode(SMS_recieve_button, INPUT);
  
  sim800l.begin(9600);
  Serial.begin(9600);
     
  delay(1000);
}
 
void loop()
{

  //Constantly reading the button State
  int SMS_send_state = digitalRead(SMS_send_button);
  int Call_button_state = digitalRead(Call_button);
  int SMS_recieve_state = digitalRead(SMS_recieve_button);
 
  if (SMS_send_state == HIGH) {            
    Serial.println("Button pressed");   
    delay(200);                         
    
    SendSMS();                          
 }

 if (Call_button_state == HIGH) {            
    Serial.println("Button pressed");   
    delay(200);                         
    
    Call();                          
 }

 if (SMS_recieve_state == HIGH) {            
    Serial.println("Button pressed");   
    delay(200);                         
    
    RecieveMessage();                          
 }
 
  if (sim800l.available()){
    
    //Displays on the serial monitor if there's communication from the module
    Serial.write(sim800l.read()); 
  }
}
 
void SendSMS()
{
  Serial.println("Sending SMS...");               
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+38641838253\"\r");  //Your phone number with country code
  delay(500);
  sim800l.print("SIM800l works");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);                  // (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(500);
}

void RecieveMessage()
{
  Serial.println("SIM800L Read an SMS");
  delay (500);
  sim800l.println("AT+CMGF=1\r");
  delay (500);
  sim800l.println("AT+CNMI=2,2,0,0,0\r");     //AT Command to receive a live SMS
  delay(500);
}

void Call() {
  sim800l.println("AT\r");
  delay(500);
  sim800l.println("ATD+38641838253;\r");    //STF command to call number
  sim800l.println();
  Serial.println("Calling...");
  delay(500);
}
 

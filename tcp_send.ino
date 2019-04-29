#include <SoftwareSerial.h>
SoftwareSerial myGsm(7,8);
float temp;
int tempPin = 0;
void setup()
{
  myGsm.begin(4800);
  Serial.begin(4800);
  delay(500);
}
void loop()
{
    myGsm.println("AT+CIPSHUT");
  delay(1000);
  printSerialData();
  myGsm.println("AT+CIPMUX=0");
  delay(2000);
  printSerialData();
  myGsm.println("AT+CGATT=1");
  delay(1000);
  printSerialData();
  myGsm.println("AT+CSTT=\"www.vodafone.net.nz\",\"\",\"\"");//setting the APN,username & password
  delay(5000);
  printSerialData();
  myGsm.println();
  myGsm.println("AT+CIICR");
  delay(6000);
  printSerialData();
  myGsm.println("AT+CIFSR"); //get IP address
  delay(2000);
  printSerialData();
  myGsm.println("AT+CIPSTART=\"TCP\",\"141.0.23.158\",\"80\"");
  delay(5000);
  printSerialData();
  delay(5000);
  myGsm.println("AT+CIPSEND");
  delay(2000);
  printSerialData();
  sendtemp();
  delay(3000);
  myGsm.println("AT+CIPCLOSE");
  printSerialData();
  myGsm.println("AT+CIPSHUT");
  delay(1000);
  printSerialData();
}
void printSerialData()
{
while(myGsm.available()!=0)
Serial.write(myGsm.read());
}
 
void sendtemp()
{
temp = analogRead(tempPin);
temp = temp * 1.48828125;
Serial.print(24);
Serial.println();
delay(5000);
//this data will be sended to server
myGsm.println(24);
delay(3000);
printSerialData();
myGsm.write(30);
delay(3000);
printSerialData();
}

#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(7, 8);
void setup()
{
  gprsSerial.begin(4800);
  Serial.begin(4800);

  Serial.println("Con");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();


  // See if the SIM900 is ready
  gprsSerial.println("AT");
  delay(1000);
  toSerial();

  // SIM card inserted and unlocked?
  gprsSerial.println("AT+CPIN?");
  delay(1000);
  toSerial();

  // Is the SIM card registered?
  gprsSerial.println("AT+CREG?");
  delay(1000);
  toSerial();

  // Is GPRS attached?
  gprsSerial.println("AT+CGATT?");
  delay(1000);
  toSerial();

  // Check signal strength
  gprsSerial.println("AT+CSQ ");
  delay(1000);
  toSerial();

  // Set connection type to GPRS
  gprsSerial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(2000);
  toSerial();

  // Set the APN
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"web\"");
  delay(2000);
  toSerial();

  // Enable GPRS
  gprsSerial.println("AT+SAPBR=1,1");
  delay(10000);
  toSerial();

  // Check to see if connection is correct and get your IP address
  gprsSerial.println("AT+SAPBR=2,1");
  delay(2000);
  toSerial();

}


void loop()
{
   // initialize http service
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();

   // set http param value
   // ToDO : send dynamic value
   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://lennart-schiffers.de/index.php/?lat=788798");
   delay(4000);
   toSerial();

   //gprsSerial.println("");
   gprsSerial.println("AT+HTTPACTION=1");
   toSerial();
   delay(6000);

   gprsSerial.println("AT+HTTPREAD");
   toSerial();
   delay(300);

   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(300);
   
}

void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
}

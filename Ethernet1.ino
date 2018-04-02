#include <SPI.h>
#include <Ethernet.h>
int led = 6;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
char serverName[] = "www.arduino.php5.sk"; // zoomkat's test web page server
IPAddress ip(192, 168, 2, 40);
EthernetClient client;
boolean state = false;
String readString;
int x=0; //for counting line feeds
char lf=10; //line feed character
//////////////////////

void setup(){
pinMode(led, OUTPUT);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    while(true);
  }
  Serial.begin(9600); 
  Serial.println("Better client test 5/13/13"); // so I can keep track of what is loaded
  Serial.println("Send an e in serial monitor to test"); // what to do to test
}

void loop(){
  // check for serial input
  if (Serial.available() > 0) //if something in serial buffer
  {
    byte inChar; // sets inChar as a byte
    inChar = Serial.read(); //gets byte from buffer
    if(inChar == 'e') // checks to see byte is an e
    {
      sendGET(); // call sendGET function below when byte is an e
    }
  }  
} 

//////////////////////////

void sendGET() //client function to send/receive GET request data.
{
  if (client.connect(serverName, 80)) {  //starts client connection, checks for connection
    Serial.println("connected");
    client.println("GET /PHP_sk/preklady.txt HTTP/1.1"); //download text
    client.println("Host: www.arduino.php5.sk");
    client.println("Connection: close");  //close 1.1 persistent connection  
    client.println(); //end of get request
  } 
  else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }

  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
    Serial.print(c); //prints raw feed for testing
    if (c==lf) x++; //counting line feeds
    else if (x==12) readString += c; //building readString
 
   }
   Serial.println(); 
if(readString=="Vypni"){
  Serial.println("Vypnutie spotrebica");
  }else if(readString=="Zapni"){
  Serial.println("Zapnutie spotrebica");
  }else{
  Serial.println("Nespravna response - skontrolujte zadaný parameter");
  }
  readString = ("");
  x=0;
  client.stop(); //stop client
}

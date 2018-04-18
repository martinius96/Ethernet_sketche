#include <SPI.h>
#include <Ethernet.h>
int led = 6;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //fyzicka adresa MAC
char serverName[] = "www.arduino.php5.sk"; // webserver
IPAddress ip(192, 168, 2, 40);
EthernetClient client;
String readString;
int x=0; //pocitadlo riadkov
char lf=10; //line feed character
void setup(){
pinMode(led, OUTPUT);
 if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  Serial.begin(9600); 
}

void loop(){
if (client.connect(serverName, 80)) {  //starts client connection, checks for connection
    Serial.println("connected");
    client.println("GET /PHP_cz/preklady.txt HTTP/1.1"); //download text
    client.println("Host: www.arduino.php5.sk");
    client.println("Connection: close");  //close 1.1 persistent connection  
    client.println(); //end of get request
  } 
  else {
    Serial.println("Pripojenie neuspesne"); //chyba ak nie som pripojeny
    Serial.println();
  }

  while(client.connected() && !client.available()) delay(1); //cakaj na data
  while (client.connected() || client.available()) { //pramenna
    char c = client.read(); //dostan bity z buffera
    Serial.print(c); //cela http hlavicka
    if (c==lf) x=(x+1); //pocitaj 
    else if (x==12) readString += c; //nasa premenna

   } 
if(readString=="Zapni"){
  digitalWrite(led, HIGH); 
  }else if(readString=="Vypni"){
  digitalWrite(led, LOW);  
    }
    else{
 Serial.println("Nepodporovana premenna.");
 }
  
  readString = ("");
  x=0;
  client.stop(); //ukonc spojenie
  delay(5000); //pockaj 5s a vykonaj novu slucku loop
} 

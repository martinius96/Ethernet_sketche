#include <SPI.h>
#include <Ethernet.h>

const int relay = 10;
String relayState;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char server[] = "www.arduino.php5.sk";
IPAddress ip(192, 168, 1, 254);
EthernetClient client;

void setup() {
   
 
  Serial.begin(9600);
  while (!Serial) {
    ; }
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
 
  delay(1000);

  // if you get a connection, report back via serial:

}

void loop() {  


  
   if (client.connect("www.arduino.php5.sk", 80)) {

    
    client.println("GET /lumino/readme.txt"); //download text
    client.println(" HTTP/1.1");
    client.println("Host: www.arduino.php5.sk");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: ");
    client.println(relayState.length());
    client.println(relayState);
    Serial.println(relayState.length());
     Serial.println(relayState);
    
  } 
  if (client.connected()){
    Serial.println("odpojene");
    client.stop();
    } 
  }


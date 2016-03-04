// Arduino 1.0 sketch for controlling relay over ethernet whit ENC28J60
//
// Original author: Antonio Possidente
// Major write and API overhaul, 2016-04-03
// You can write for help or suggestions at possidenteantonio@icloud.com
//
// Copyright: GPL V3
// See http://www.gnu.org/licenses/gpl.html

// Please note that this code is intended to use with ENC28j60 only with the "ethercard-master" library (the link is down the line)
// https://github.com/jcw/ethercard/blob/master/README.md

// This code is also intended to use with "Tasker" and "Commandr" app for Android

// IT'S NORMAL THAT THE SKETCH GENERATE DURING COMPILATION TIME A LOT OF WARNING
// I HOPE THAT I CAN FIX IT IN NEXT RELASE 

#include <EtherCard.h>

// Declaration of the output pin

#define RELAY_1_PIN 2
#define RELAY_2_PIN 3
#define RELAY_3_PIN 4
#define RELAY_4_PIN 5
#define RELAY_5_PIN 6
#define RELAY_6_PIN 7

// Change the mac address with an unused address in your network

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];

char* on  = "ON";
char* off = "OFF";

// Boolean variables of the state of the digital out pins

boolean relayStatus_1;
boolean relayStatus_2;
boolean relayStatus_3;
boolean relayStatus_4;
boolean relayStatus_5;
boolean relayStatus_6;

void setup () {

  // Serial print of the debugging data of DHCP client implementation
  
  Serial.begin(57600);
  Serial.println(F("\n[testDHCP]"));

  Serial.print("MAC: ");
  for (byte i = 0; i < 6; ++i) {
    Serial.print(mymac[i], HEX);
    if (i < 5)
      Serial.print(':');
  }
  Serial.println();
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));

  Serial.println(F("Setting up DHCP"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));
  
  ether.printIp("My IP: ", ether.myip);
  ether.printIp("Netmask: ", ether.netmask);
  ether.printIp("GW IP: ", ether.gwip);
  ether.printIp("DNS IP: ", ether.dnsip);

  // Initialization of relays and definition of the pins
  
  pinMode(RELAY_1_PIN, OUTPUT);
  digitalWrite(RELAY_1_PIN, LOW);  
  relayStatus_1 = false;

  pinMode(RELAY_2_PIN, OUTPUT);
  digitalWrite(RELAY_2_PIN, LOW);  
  relayStatus_2 = false;

  pinMode(RELAY_3_PIN, OUTPUT);
  digitalWrite(RELAY_3_PIN, LOW);  
  relayStatus_3 = false;

  pinMode(RELAY_4_PIN, OUTPUT);
  digitalWrite(RELAY_4_PIN, LOW);  
  relayStatus_4 = false;

  pinMode(RELAY_5_PIN, OUTPUT);
  digitalWrite(RELAY_5_PIN, LOW);  
  relayStatus_5 = false;

  pinMode(RELAY_6_PIN, OUTPUT);
  digitalWrite(RELAY_6_PIN, LOW);  
  relayStatus_6 = false;
}

void loop () {

  // This commands is used to receive the packets from the network
  
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);

  // This code is used to change the state of the relays. "GET /?ON1" and "GET /?OFF1" are used as control of input from the url.
  // Example of an url to power on or off a relay: http://192.168.1.1/?ON1 http://192.168.1.1/?OFF1
  
  if(pos) {
  //---------------------------------------------------------------------------------------
    if(strstr((char *)Ethernet::buffer + pos, "GET /?ON1") != 0) {
      relayStatus_1 = true;
    } else if(strstr((char *)Ethernet::buffer + pos, "GET /?OFF1") != 0) {
      relayStatus_1 = false; 
    }
   digitalWrite(RELAY_1_PIN, relayStatus_1); 

  }  

   if(pos) {
  //---------------------------------------------------------------------------------------  
    if(strstr((char *)Ethernet::buffer + pos, "GET /?ON2") != 0) {
      relayStatus_2 = true;
    } else if(strstr((char *)Ethernet::buffer + pos, "GET /?OFF2") != 0) {
      relayStatus_2 = false;
    }
   digitalWrite(RELAY_2_PIN, relayStatus_2); 
  }  

  if(pos){
  //---------------------------------------------------------------------------------------     
    if(strstr((char *)Ethernet::buffer + pos, "GET /?ON3") != 0) {
      relayStatus_3 = true;
    } else if(strstr((char *)Ethernet::buffer + pos, "GET /?OFF3") != 0) {
      relayStatus_3 = false;
    }
   digitalWrite(RELAY_3_PIN, relayStatus_3); 
  }  

   if(pos) {
  //--------------------------------------------------------------------------------------- 
    if(strstr((char *)Ethernet::buffer + pos, "GET /?ON4") != 0) {
      relayStatus_4 = true;
    } else if(strstr((char *)Ethernet::buffer + pos, "GET /?OFF4") != 0) {
      relayStatus_4 = false; 
    }
   digitalWrite(RELAY_4_PIN, relayStatus_4);

  }  

   if(pos) {
  //---------------------------------------------------------------------------------------
     if(strstr((char *)Ethernet::buffer + pos, "GET /?ON5") != 0) {
      relayStatus_5 = true;
    } else if(strstr((char *)Ethernet::buffer + pos, "GET /?OFF5") != 0) {
      relayStatus_5 = false;
    }
   digitalWrite(RELAY_5_PIN, relayStatus_5);

  }  

   if(pos) {
  //---------------------------------------------------------------------------------------     
    if(strstr((char *)Ethernet::buffer + pos, "GET /?ON6") != 0) {
      relayStatus_6 = true;
    } else if(strstr((char *)Ethernet::buffer + pos, "GET /?OFF6") != 0) {
      relayStatus_6 = false;
    }
   digitalWrite(RELAY_6_PIN, relayStatus_6); 
  //---------------------------------------------------------------------------------------

  // Serial print of the debugging data state of relays
 
  Serial.println();
  Serial.print("\n Relay_1: ");
    if(relayStatus_1){
      Serial.print("Acceso");
    }else{
      Serial.print("Spento");
    }
  Serial.print("\n Relay_2: ");
    if(relayStatus_2){
      Serial.print("Acceso");
    }else{
      Serial.print("Spento");
    }
  Serial.print("\n Relay_3: ");
    if(relayStatus_3){
      Serial.print("Acceso");
    }else{
      Serial.print("Spento");
    }
  Serial.print("\n Relay_4: ");
    if(relayStatus_4){
      Serial.print("Acceso");
    }else{
      Serial.print("Spento");
    }
  Serial.print("\n Relay_5: ");
    if(relayStatus_5){
      Serial.print("Acceso");
    }else{
      Serial.print("Spento");
    }
  Serial.print("\n Relay_6: ");
    if(relayStatus_6){
      Serial.print("Acceso");
    }else{
      Serial.print("Spento");
    }

   // This code is added to make shure that the browser doesn't crash while charging the page
   
    BufferFiller bfill = ether.tcpOffset();
    bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html\r\nPragma: no-cache\r\n\r\n"
        "<html><head><title>WebLeds</title></head><body>"
        "   "));
      bfill.emit_p(PSTR("</body></html>"));
    ether.httpServerReply(bfill.position());

  }  
}

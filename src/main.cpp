#include <Arduino.h>
#include <IRremote.h>
#include <Ethernet3.h>

IRrecv irrecv(10); // IR receiver pin
decode_results results;

byte mac[] = { 0xDE, 0x1D, 0xBE, 0xE4, 0xFE, 0x5D };
IPAddress ip(10, 0, 1, 197);
IPAddress server(10, 0, 1, 26);
EthernetClient client;

void setup() {
  Serial.begin(9600);
  irrecv.blink13(true);
  irrecv.enableIRIn();
  Serial.println("Started");
  Ethernet.begin(mac, ip);
  delay(1000);
  Serial.println("connecting...");
  if (client.connect(server, 8088)) {
    Serial.println("connected");
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}

String key(long code) {
  switch(code) {
    case 0x3ec12dd2: return "up";
    case 0x3ec1cd32: return "down";
    case 0x3ec1ad52: return "left";
    case 0x3ec16d92: return "right";
    case 0x3ec11de2: return "enter";
    case 0x3EC1D12E: return "rec";
    case 0x3EC1A15E: return "stop";
    case 0x3EC1C13E: return "pause";
    case 0x3EC141BE: return "play";
    case 0x3EC1619E: return "back";
    case 0x3EC1E11E: return "forward";
    case 0x3EC19D62: return "prev";
    case 0x3EC15DA2: return "next";
    case 0x3EC129D6: return "1";
    case 0x3EC1A956: return "2";
    case 0x3EC16996: return "3";
    case 0x3EC1E916: return "4";
    case 0x3EC119E6: return "5";
    case 0x3EC19966: return "6";
    case 0x3EC159A6: return "7";
    case 0x3EC1D926: return "8";
    case 0x3EC139C6: return "9";
    case 0x3EC1C936: return "0";
    case 0x3EC1B946: return "plus10";
    case 0x3EC17986: return "ent";
  }
  return String(code, HEX);
}

void loop() {
  if (irrecv.decode(&results)) {
    if(results.bits &&
        results.value != 0xFDAC0152 &&
        results.value != 0xFCABFFBF &&
        results.value != 0xFCABFFBF &&
        results.value != 0xFEAC02E5) {
      Serial.println(key(results.value));
    }
    irrecv.resume();
  }
}

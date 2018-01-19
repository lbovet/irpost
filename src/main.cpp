//
// Includes
//
#include <IRremote.h>
#include <SPI.h>
#include <Ethernet.h>

//
// Globals
//
int RECV_PIN = 3;
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };    // Adapter MAC

//
// Inits
//
IRrecv irrecv(RECV_PIN);
decode_results results;

// Network settings for the Eth shield...
byte gateway[] = { 192,168,0,1 };
byte ip[] = { 192,168,0,223 };

// IP of the Raspi and the connection context
IPAddress server(192,168,0,234);  // Raspi DVR-IR Transmitter Server IP
EthernetClient client;


/**
 * Bit shitty, but get a String (char*) for a remote code.
 * lirc only likes textual names for commands, not codes -.-
 */
String get_rcode_name(long rcode)
{
  switch(rcode)
  {
    case  0x20DF30CF:
      return "STAND_BY";
    case  0x20DF50AF:
      return "LOGIN_LOCK";
    case  0x20DF807F:
      return "NUM_1";
    case  0x20DF40BF:
      return "NUM_2";
    case  0x20DFC03F:
      return "NUM_3";
    case  0x20DF20DF:
      return "NUM_4";
    case  0x20DFA05F:
      return "NUM_5";
    case  0x20DF609F:
      return "NUM_6";
    case  0x20DFE01F:
      return "NUM_7";
    case  0x20DF10EF:
      return "NUM_8";
    case  0x20DF906F:
      return "NUM_9";
    case  0x20DF18E7:
      return "NUM_0";
    case  0x20DF28D7:
      return "GRID";
    case  0x20DF08F7:
      return "MENU";
    case  0x20DF6897:
      return "PTZ";
    case 0x20DF7887:
      return "EXIT";
    case  0x20DF48B7:
      return "DIR_UP";
    case  0x20DFA857:
      return "DIR_RIGHT";
    case  0x20DFB847:
      return "DIR_DOWN";
    case  0x20DFF00F:
      return "DIR_LEFT";
    case  0x20DF00FF:
      return "OK";
    case  0x20DF9867:
      return "PLUS";
    case  0x20DF38C7:
      return "MINUS";
    case  0x20DF708F:
      return "REC";
    case  0x20DFB04F:
      return "STOP";
    case  0x20DFF807:
      return "EXTRA";
    case  0x20DFE817:
      return "RW";
    case  0x20DF8877:
      return "PLAY";
    case  0x20DF2AD5:
      return "FF";
    case  0x20DFD02F:
      return "END";
    case  0x20DFC837:
      return "PLAY_STOP";
    case  0x20DF58A7:
      return "AUDIO";
    case  0x20DFD827:
      return "MUTE";
  }

  return "NOP";
}

void setup()
{
  // Open serial for debugging
  Serial.begin(9600);

  // Start the receiver
  irrecv.enableIRIn();

  // Start ethernet
  Ethernet.begin(mac, ip, gateway);
}

/**
 * Transmit a code over the network.
 */
void tx_code(decode_results *results)
{
  if (results->decode_type == NEC && results->bits == 32)
  {

    // Diagnostics - serial
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");

    // Make request
    if (client.connect(server, 80))
    {
      client.print("GET /?code=");
      client.print(get_rcode_name(results->value));
      client.println(" HTTP/1.1");
      client.println("Host: 198.211.121.22");
      client.println();
      client.println();
      client.stop();
    }
  }
}

/**
 * Decode any received IR codes.
 */
void loop()
{
  if (irrecv.decode(&results))
  {
    tx_code(&results);
    irrecv.resume(); // Receive the next value
  }
}

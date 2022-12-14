
#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_config.h"
#include <SPI.h>

typedef struct  {
int valvula1;
int valvula2; 
bool extra1;
bool extra2;
}InfoMando;

unsigned long UltimaConexion = 0;
int packetCounts[10];
int packetCountIndex = 0;
int packetCountTotal = 0;
char ppsBuf[16];

InfoMando Mimando;

unsigned long packetsRead = 0;
unsigned long lastScreenUpdate = 0;
unsigned long lastRecvTime = 0;
unsigned long drops = 0;

const int pinCE = 9;
const int pinCSN = 10;
RF24 radio(pinCE, pinCSN);
 
// Single radio pipe address for the 2 nodes to communicate.
//const uint64_t pipe = 0xE8E8F0F0E1LL;
byte direccion[5] ={'c','a','n','a','l'};

void updateScreen()
{  
  unsigned long now = millis();
  if ( now - lastScreenUpdate < 100 )
    return;
    
  // moving average over 1 second
  packetCountTotal -= packetCounts[packetCountIndex];
  packetCounts[packetCountIndex] = packetsRead;
  packetCountTotal += packetsRead;

  packetCountIndex = (packetCountIndex + 1) % 10; // cada segundo llena el bufer y hace ciclos de 1 seg
  packetsRead = 0;                  //hace media y calcula si se pierden paquetes o no 

  Serial.println(Mimando.valvula1);
  Serial.print(" paquetes: ");
  Serial.println(packetCountTotal);
  sprintf(ppsBuf, "PPS: %d", packetCountTotal);  //pps = paquetes por segundo
  
  lastScreenUpdate = millis();  
}


void setup(void)
{
   Serial.begin(115200);
   radio.begin();
   radio.setDataRate(RF24_250KBPS);
   radio.setAutoAck(0);
   radio.openReadingPipe(1,direccion);
   radio.startListening();
   pinMode(3,OUTPUT);
   pinMode(5,OUTPUT);
   memset( packetCounts, 0, sizeof(packetCounts) );
}
 
void loop(void)
{
  //Variables control
  int c1;
  int c2;
  
   if (radio.available())
   {
    radio.read(&Mimando, sizeof  Mimando);
    packetsRead++;
    UltimaConexion = millis();
    c1=accion_1(Mimando.valvula1);
    c2=accion_2(Mimando.valvula2);
   }
   updateScreen();
 
   if(((millis()- UltimaConexion) > 3000) ){
      Mimando.valvula1 = 0;
      Mimando.valvula2 = 0;
      Mimando.extra1= 0;
      Mimando.extra2= 0;
      UltimaConexion = millis();
    }
}


int accion_1(bool a){
  //motor 1
  if(a==true ){
    digitalWrite(3,HIGH); 
  }
  else{ 
    digitalWrite(3,LOW);
  }
  return a;
}

int accion_2(bool a){
  //motor 1
  if(a==true ){
    digitalWrite(5,HIGH); 
  }
  else{ 
    digitalWrite(5,LOW);
  }
  return a;
}

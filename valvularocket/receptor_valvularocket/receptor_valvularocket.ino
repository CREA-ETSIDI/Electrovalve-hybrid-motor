
#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_config.h"
#include <SPI.h>


typedef struct  {
int JoyIzq;
bool boton1;
}InfoMando;

unsigned long UltimaConexion = 0;
int packetCounts[10];
int packetCountIndex = 0;
int packetCountTotal = 0;
//char ppsBuf[16];

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
char data[16];
 InfoMando Mimando;


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



  Serial.print(" lectura Joystick izq: ");
Serial.println(Mimando.JoyIzq);

Serial.print(" lectura botones: ");
Serial.print(Mimando.boton1);

Serial.println(packetCountTotal);
  //sprintf(ppsBuf, "PPS: %d", packetCountTotal);  //pps = paquetes por segundo
  
  lastScreenUpdate = millis();  
}


void setup(void)
{
   Serial.begin(115200);
   radio.begin();
   radio.setDataRate(RF24_250KBPS);
   radio.setAutoAck(0);
   radio.openReadingPipe(0,direccion);
   radio.startListening();

   memset( packetCounts, 0, sizeof(packetCounts) );
 
}
 
void loop(void)
{

  int velA;
  int velB;
  //Variables control
  int c1;
  int c2;
  
   if (radio.available())
   {
    radio.read(&Mimando, sizeof  Mimando);
    //radio.read(&data, sizeof data); 
    //Serial.print(" lectura Joystick izq: ");
    //Serial.println(Mimando.JoyIzq);
    //Serial.print(" lectura botones: ");
    packetsRead++;
    UltimaConexion = millis();
    //Serial.print(Mimando.boton1);
    //c1=motor1(Mimando.JoyIzq,Mimando.boton1);
    //c2=arma(Mimando.boton1);
   }
   updateScreen();
 
   
   if(((millis()- UltimaConexion) > 3000) ){
      Mimando.JoyIzq = 0;
      Mimando.boton1= 0;
      UltimaConexion = millis();
      
      radio.begin();
      radio.setAutoAck(0);
      radio.setDataRate(RF24_250KBPS);
      radio.openReadingPipe(0,direccion);
      radio.startListening();
  }
}

int motor1(int a, int c){
  //motor 1
  if(c==1 ){
    digitalWrite(pinPHA1,a); 
    digitalWrite(pinPHA2,LOW);
  }
  else if(c==0){
    analogWrite(pinPHA1,LOW); 
    digitalWrite(pinPHA2,a);
  }
  else{
    analogWrite(pinPHA1,LOW); 
    digitalWrite(pinPHA2,LOW);
  }

  return a;
}

bool arma(int c){
  //1 encendido, 0 apagado
}

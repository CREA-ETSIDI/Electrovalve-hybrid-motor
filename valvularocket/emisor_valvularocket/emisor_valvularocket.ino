#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_config.h"
#include <SPI.h>
 
#define puertoB1 2  //actuador

#define gat1 A0 //Sensor

typedef struct  {
int JoyIzq;
bool boton1;
}InfoMando;


const int pinCE = 9;
const int pinCSN = 10;

RF24 radio(pinCE, pinCSN);
 
// Single radio pipe address for the 2 nodes to communicate.
// const uint64_t pipe = 0xE8E8F0F0E1LL;
byte direccion[5] ={'c','a','n','a','l'};
 
char data[16]="Hola Mundo" ;
InfoMando Mimando;

 
void setup(void)
{
Serial.begin(115200);
pinMode(gat1,INPUT);
pinMode(puertoB1,INPUT);
radio.begin();
radio.setDataRate(RF24_250KBPS);
radio.setAutoAck(0);
radio.openWritingPipe(direccion);

 // el modo de funciona
   
}
 
void loop(void)
{
Mimando.JoyIzq = analogRead(A0);

Mimando.boton1  =  digitalRead(puertoB1);
  radio.write(&Mimando, sizeof Mimando);
   //radio.write(&data, sizeof data);
   Serial.print(Mimando.boton1);
}

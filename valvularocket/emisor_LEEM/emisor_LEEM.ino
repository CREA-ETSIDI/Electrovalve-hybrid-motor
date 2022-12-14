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

const int pinCE = 9;
const int pinCSN = 10;

RF24 radio(pinCE, pinCSN);
 
// Single radio pipe address for the 2 nodes to communicate.
// const uint64_t pipe = 0xE8E8F0F0E1LL;
byte direccion[5] ={'c','a','n','a','l'};

InfoMando Mimando;
String dato = String(3);
 
void setup(void)
{
  Serial.begin(115200);
  pinMode(3,INPUT);
  pinMode(5,INPUT);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(0);
  radio.openWritingPipe(direccion);
}
 
void loop(void)
{
  Mimando.valvula1 = digitalRead(3);
  //Mimando.valvula2 = digitalRead(5);  //segundo botón opcional
  recibir();
  radio.write(&Mimando, sizeof Mimando);
}
void recibir(void){
  if(Serial.available()){
    dato= Serial.readStringUntil('\n');
  } 
  if (dato.equals("TLH")) Mimando.valvula1=true;
  if (dato.equals("TLL")) Mimando.valvula1=false;
}

/*   joys1, joys2    -> 1 lecturas depotencometros cada 1  -> 2 int 8 bits*2 = 2 bytes 
 *   2 potenciometros ->2 lecturas -->  2 int       2 bytes 
 * 
 *   2 switches  2- bits   
 *   4 botones  --> 4 bits
 *   botones de joystic -> 2 bits
 */

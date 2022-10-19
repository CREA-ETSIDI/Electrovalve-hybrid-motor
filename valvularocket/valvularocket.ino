/********************************************
 ***PROGRAMA FUNCIONAMIENTO ELECTROVALVULA***
 ********************************************/

/*AUTORES (añadirse):
 * MARCELO LUNA
 * 
 */

void setup() {
  pinMode (9, OUTPUT);// pin salida solenoide (válvula)
  pinMode (2, INPUT);// pin opcional entrada botón
  pinMode (3, INPUT);// pin opcional entrada botón 2

  //declaramos estado inicial
  digitalWrite(9, LOW);//pin de la válvula

  //Algo de info por serial
  Serial.begin(9600);
  Serial.println("Arrancando motores...");
  delay(1000);
}

void loop () { 
  //botonera();
  tempura();
  //encendido();
}

//Opción funcionamiento botonera
void botonera(void){
  boolean apertura;
  boolean cierre;
  apertura=digitalRead(2);
  cierre=digitalRead(3);
  if (apertura && cierre) 
{ 
     Serial.println("ESTAMOS OFF");
     digitalWrite (9, LOW); 
     delay(1000); 
} 
else if(apertura)
{ 
     Serial.println("ESTAMOS ON");
     digitalWrite (9, HIGH); 
     delay(1000); 
} 
}

//Opción funcionamiento temporizado
void tempura(void){
  digitalWrite(9, HIGH);
  Serial.println("ESTAMOS ON");
  delay(1000);
  digitalWrite(9, LOW);
  Serial.println("ESTAMOS OFF");
  delay(1000);
}
//Opción siempre on
void encendido(void){
  digitalWrite(9, HIGH);
  Serial.println("ESTAMOS ON");
  delay(1000);
}
void input(void){
  
}

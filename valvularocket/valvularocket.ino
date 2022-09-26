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
  digitalWrite(9, LOW);
  delay(1000);

  //Algo de info por serial
  Serial.begin(9600);
  Serial.println("Arrancando motores...");
}

void loop () { 
  botonera();
  //tempura();
}

//Opción funcionamiento botonera
void botonera(void){
  if (digitalRead (2) == HIGH) 
{ 
     Serial.println("ESTAMOS ON");
     digitalWrite (9, HIGH); 
     delay(1000); 
} 
else if (digitalRead (3) == HIGH) 
{ 
     Serial.println("ESTAMOS OFF");
     digitalWrite (9, LOW); 
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

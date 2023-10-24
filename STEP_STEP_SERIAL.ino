#define pin2 2
#define pin3 3
#define pin4 4
#define pin5 5
#define MIN 800
#define MAX 2000

//Variables Globales//
typedef struct {
  volatile  uint8_t  estado;
  volatile  uint8_t  vueltas;
  volatile  uint16_t pasos;
  volatile  uint16_t velocidad;
}Step_t; 

Step_t Step;

// variables globales //
String inputString = "";
bool stringComplete = false;
const char separator = ',';
const uint8_t dataLength = 3;
uint16_t data[dataLength];

//Funciones//
void positivo(Step_t *Step){
  for (int16_t i=0; i < Step->pasos; i++)
  {
    giro_horario(Step->velocidad);
  }
}

void negativo(Step_t *Step){
  for (int16_t i=0; i < Step->pasos; i++)
  {
    giro_antihorario(Step->velocidad);
  }
}

void giro_antihorario(uint16_t v){
  //paso 1
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,HIGH);

  delayMicroseconds(v);

  //paso 2
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,HIGH);

  delayMicroseconds(v);

  //paso 3
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,HIGH);
  digitalWrite(pin5,HIGH);

  delayMicroseconds(v);

  //paso 4
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,HIGH);
  digitalWrite(pin5,LOW);

  delayMicroseconds(v);

  //paso 5
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,HIGH);
  digitalWrite(pin5,LOW);

  delayMicroseconds(v);

  //paso 6
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,LOW);

  delayMicroseconds(v);

  //paso 7
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,LOW);

  delayMicroseconds(v);

  //paso 8
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,LOW);

  delayMicroseconds(v);
}

void giro_horario(uint16_t v){
  //paso 1
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,LOW);
  
  delayMicroseconds(v);

  //paso 2
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,LOW);

  delayMicroseconds(v);
  
  //paso 3
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,LOW);

  delayMicroseconds(v);

  //paso 4
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,HIGH);
  digitalWrite(pin5,LOW);

  delayMicroseconds(v);
 

  //paso 5
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,HIGH);
  digitalWrite(pin5,LOW);

  delayMicroseconds(v);

  //paso 6
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,HIGH);
  digitalWrite(pin5,HIGH);

  delayMicroseconds(v);
  
  //paso 7
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,HIGH);

  delayMicroseconds(v);

  //paso 8
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,LOW);
  digitalWrite(pin5,HIGH);

  delayMicroseconds(v);
}

void serialEvent(){
  while(Serial.available()){
    char inChar = Serial.read();
    inputString += inChar;
    if(inChar == '-'){
      stringComplete = true;
    }
  }
}

void setup(){
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  pinMode(pin5,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  if(stringComplete){
    for(int i = 0; i < dataLength; i++){
      int index = inputString.indexOf(separator);
      data[i] = inputString.substring(0,index).toInt();
      inputString = inputString.substring(index + 1);
     }
     Step.estado = data[0];
     Step.vueltas = data[1];
     Step.velocidad = data[2];
     Step.pasos = Step.vueltas * 512;
     inputString = "";
     stringComplete = false;
   }
   if(Step.estado == 1){
    if((Step.velocidad >= MIN)&&(Step.velocidad <= MAX)){
      Serial.println("Sentido horario, Vuetas: " + String(Step.vueltas) + ", Velocidad: " + String(Step.velocidad) + "."); 
      positivo(&Step);
    }
    else{
        Serial.println("La velocidad debe estar entre 800 a 2000.");
      }
    Step.estado = 0;
    
   }
    else if(Step.estado == 2){
    if((Step.velocidad >= MIN)&&(Step.velocidad <= MAX)){
      Serial.println("Sentido antihorario, Vuetas: " + String(Step.vueltas) + ", Velocidad: " + String(Step.velocidad) + ".");
      negativo(&Step);
    }
    else{
        Serial.println("La velocidad debe estar entre 800 a 2000.");
      }
    Step.estado = 0;
    } 
}

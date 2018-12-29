#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t xSemaphore  = NULL;  //Cria Mutex do tipo semaforo na biblioteca FreeRTOS

//Pinagem
const int ledPin1 = 6; //Leds
const int ledPin2 = 7;
const int ledPin3 = 8;
const int ledPin4 = 9;
const int ledPin5 = 10;

const int pino = 7; //Buzzer

const int trigPin = 3; //Sensor Ultrasônico
const int echoPin = 4;

//Variáveis Auxiliares
long duration;
int distance;

// define as tarefas
void beep(void *pvParameters);
void leds(void *pvParameters);


void setup() {

  xTaskCreate(
      leds
      ,  (const portCHAR *)"Aciona Leds"
      ,  128 // This stack size can be checked & adjusted by reading Highwater
      ,  NULL
      ,  1  // prioridade 1
      ,  NULL );


  xTaskCreate(
    beep
    ,  (const portCHAR *)"Aciona Beep"   
    ,  128  // Stack size
    ,  NULL
    ,  1  // prioridade 1
    ,  NULL );
  // Configurações para que as tarefas rodem concorrentemente


  //Cria o mutex
  xSemaphore = xSemaphoreCreateMutex();

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Vazio
}

void leds(void *pvParameters){
  
  (void) pvParameters;
  
  for (;;) // Loop para tarefa número 1
  {

    distance = calculaDistance();
    
    if(distance > 19 && distance < 30){
        digitalWrite(ledPin4, HIGH);
    }
    else {
      digitalWrite(ledPin4, LOW);
    }
    
    if(distance > 15 && distance < 20){
        digitalWrite(ledPin5, HIGH);
    }
    else {
      digitalWrite(ledPin5, LOW);
    }
    
    if(distance > 10 && distance < 16){
        digitalWrite(ledPin3, HIGH);
    }
    else {
      digitalWrite(ledPin3, LOW);
    }
    
    if(distance > 1 && distance < 11){
        digitalWrite(ledPin1, HIGH);
    }
    else {
      digitalWrite(ledPin1, LOW);
    }
    vTaskDelay(1);
  }
}

void beep(void *pvParameters){

  (void) pvParameters;
  
  for (;;) // Loop para tarefa número 2
  {

    distance = calculaDistance();
    
    if(distance > 19 && distance < 30){
      digitalWrite(pino, HIGH);
      delay(500);
      digitalWrite(pino, LOW);
    }
    else if(distance > 15 && distance < 20){
      digitalWrite(pino, HIGH);
      delay(200);
      digitalWrite(pino, LOW);
    }
    else if(distance > 10 && distance < 16){
      digitalWrite(pino, HIGH);
      delay(70);
      digitalWrite(pino, LOW);
    }
    else if(distance > 1 && distance < 11){
      digitalWrite(pino, HIGH);
      delay(30);
      digitalWrite(pino, LOW);
    }
    vTaskDelay(1);
  }
}

int calculaDistance(){ 
  
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); 
    distance= duration*0.034/2;
    return distance;
}






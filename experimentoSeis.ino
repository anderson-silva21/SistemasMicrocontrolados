#include <OneWire.h>
#include <DallasTemperature.h>

//defines do display de sete seguimentos
#define seg_a  2
#define seg_b  3
#define seg_c  4
#define seg_d  5
#define seg_e  6
#define seg_f  7 
#define seg_g  8
#define disp_a 9
#define disp_b 10

//segmentos a b c d e f g 
int displayset[10][7]={{1,1,1,1,1,1,0}, //0
                       {0,1,1,0,0,0,0}, //1
                       {1,1,0,1,1,0,1}, //2
                       {1,1,1,1,0,0,1}, //3
                       {0,1,1,0,0,1,1}, //4
                       {1,0,1,1,0,1,1}, //5
                       {1,0,1,1,1,1,1}, //6
                       {1,1,1,0,0,0,0}, //7
                       {1,1,1,1,1,1,1}, //8
                       {1,1,1,1,0,1,1}  //9
                      };

void displaysete(void);
int dezena  = 0;
int unidade = 0;
int estado_displaysete=1;

#define dados 14
#define led 7

#define alarme 30

OneWire oneWire(dados);

DallasTemperature sensors(&oneWire);

void setup(void){

  pinMode(seg_a,  OUTPUT);
  pinMode(seg_b,  OUTPUT);
  pinMode(seg_c,  OUTPUT);
  pinMode(seg_d,  OUTPUT);
  pinMode(seg_e,  OUTPUT);
  pinMode(seg_f,  OUTPUT);
  pinMode(seg_g,  OUTPUT);
  pinMode(disp_a, OUTPUT);
  pinMode(disp_b, OUTPUT);
  pinMode(A1, INPUT); 
  pinMode(led, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Demonstração do funcionamento do sensor");
  sensors.begin();
}

int incomingByte = 0;
int count_disp=0;
unsigned long tempo_atual, tempo_anterior = 0;
int pot;
int temp;

void loop(void){
 // Serial.print(" Requerimento de temperatura...");
  sensors.requestTemperatures();
 // Serial.println("Pronto");
  //Serial.print("A temperatura é: ");
  Serial.println(sensors.getTempCByIndex(0));
  temp = sensors.getTempCByIndex(0);
  //Serial.println(temp);
  dezena = temp/10;
  unidade = temp%10;
  displaysete();
  /*delay(10);

  Serial.print(" Requerimento de temperatura...");
  sensors.requestTemperatures();
  Serial.println("Pronto");
  Serial.print("A temperatura é: ");
  Serial.print(sensors.getTempCByIndex(0));
  if(sensors.getTempCByIndex(0) > alarme){
    digitalWrite(led, HIGH);
  } else{
    digitalWrite(led, LOW);
  }*/
}

void displaysete(void) {

  switch(estado_displaysete) {
    case 1:
      digitalWrite(disp_a, HIGH);
      digitalWrite(seg_a, displayset[unidade][0]);
      digitalWrite(seg_b, displayset[unidade][1]);
      digitalWrite(seg_c, displayset[unidade][2]);
      digitalWrite(seg_d, displayset[unidade][3]);
      digitalWrite(seg_e, displayset[unidade][4]);
      digitalWrite(seg_f, displayset[unidade][5]);
      digitalWrite(seg_g, displayset[unidade][6]); 
      digitalWrite(disp_b, LOW);
      estado_displaysete=2;
      break; 
  
    case 2:
      digitalWrite(disp_b, HIGH);
      digitalWrite(seg_a, displayset[dezena][0]);
      digitalWrite(seg_b, displayset[dezena][1]);
      digitalWrite(seg_c, displayset[dezena][2]);
      digitalWrite(seg_d, displayset[dezena][3]);
      digitalWrite(seg_e, displayset[dezena][4]);
      digitalWrite(seg_f, displayset[dezena][5]);
      digitalWrite(seg_g, displayset[dezena][6]);
      digitalWrite(disp_a, LOW);
      estado_displaysete=1;
      break;
  }
}

#include <OneWire.h>
#include <DallasTemperature.h>

#include <EEPROM.h>


#define seg_a 2
#define seg_b 3
#define seg_c 4
#define seg_d 5
#define seg_e 6
#define seg_f 7
#define seg_g 8
#define disp_a 9
#define disp_b 10
#define addr 0

//segmentos a b c d e f g
int displaysete[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 1, 1, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1}, //3
  {0, 1, 1, 0, 0, 1, 1}, //4
  {1, 0, 1, 1, 0, 1, 1}, //5
  {1, 0, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1}  //9
};

int incomingByte = 0;
char ch;
void displaySet();
int unidade = 0;
int dezena = 0;
int estadoD = 1;

int count = 0;
unsigned long temp_at;
unsigned long temp_ante = 0;

//Exp6
#define dados 14 //porta onde dados serao lidos
#define led 7 //porta do led
#define alarme 30 //temperatura maxima que liga alarme
#define aquece 11


OneWire oneWire(dados);
DallasTemperature sensors(&oneWire);

void setup() {
  
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);
//  Serial.println("Inicio leitura sensores");
  
  sensors.begin();
  pinMode(seg_a, OUTPUT);
  pinMode(seg_b, OUTPUT);
  pinMode(seg_c, OUTPUT);
  pinMode(seg_d, OUTPUT);
  pinMode(seg_e, OUTPUT);
  pinMode(seg_f, OUTPUT);
  pinMode(seg_g, OUTPUT);
  pinMode(disp_a, OUTPUT);
  pinMode(disp_b, OUTPUT);
  pinMode(aquece, OUTPUT);

  //cr = EEPROM.read(addr);
}
float temp_atual=0;
float temp_anterior=0;
float saida_controle, erro_atual, erro_anterior;
float kp = 6;
float kd = 0;
float ki = 10;

void loop() {
  
  sensors.requestTemperatures();
  temp_anterior = temp_atual;
  temp_atual = sensors.getTempCByIndex(0);
  if (temp_atual<0){
    temp_atual=temp_anterior;
  }

  dezena = (int)temp_atual/10;
  unidade = (int)temp_atual%10;

  erro_atual = 40-temp_atual;
  erro_anterior = 40-temp_anterior;

  saida_controle=kp*(erro_anterior )+kd*(erro_atual - erro_anterior)+ki*(erro_atual + erro_anterior);

  if (saida_controle > 255){
    saida_controle = 255;
  }else if(saida_controle < 0){
    saida_controle = 0;
  }
  analogWrite(aquece, saida_controle);
  Serial.print("temp_atual:");
  Serial.print(temp_atual);
  Serial.print(" saida_controle:");
  Serial.println(saida_controle);
  
  displaySet();
  delay(1);

}

//Alterna entre os dois contadores tão rapido que parecem ligados ao mesmo tempo
void displaySet() {
  switch (estadoD) {
    case 1:
      digitalWrite(disp_a, HIGH);
      digitalWrite(seg_a, displaysete[unidade][0]);
      digitalWrite(seg_b, displaysete[unidade][1]);
      digitalWrite(seg_c, displaysete[unidade][2]);
      digitalWrite(seg_d, displaysete[unidade][3]);
      digitalWrite(seg_e, displaysete[unidade][4]);
      digitalWrite(seg_f, displaysete[unidade][5]);
      digitalWrite(seg_g, displaysete[unidade][6]);
      digitalWrite(disp_b, LOW);
      estadoD = 2;
      break;
      
    case 2:
      digitalWrite(disp_b, HIGH);
      digitalWrite(seg_a, displaysete[dezena][0]);
      digitalWrite(seg_b, displaysete[dezena][1]);
      digitalWrite(seg_c, displaysete[dezena][2]);
      digitalWrite(seg_d, displaysete[dezena][3]);
      digitalWrite(seg_e, displaysete[dezena][4]);
      digitalWrite(seg_f, displaysete[dezena][5]);
      digitalWrite(seg_g, displaysete[dezena][6]);
      digitalWrite(disp_a, LOW);
      estadoD = 1;
      break;
  }




}

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

#define addr 0
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
OneWire oneWire(dados);

#define aquece 22
DallasTemperature sensors(&oneWire);

void setup() {
  
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Inicio leitura sensores");
  
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


void loop() {
  Serial.print("Request para ler temperatura");
  sensors.requestTemperatures();
  Serial.println("Requerimento concluido.");

  Serial.print("Temperatura lida: ");
  int temp = sensors.getTempCByIndex(0);
  Serial.println(temp);
  if(temp> alarme){
      digitalWrite(led,HIGH);
    }else{
      digitalWrite(led,LOW);
      }
    
  dezena = temp/10;
  unidade = temp%10;
  displaySet();
  if(temp > 40){
      digitalWrite(aquece,LOW);
   }else{
      digitalWrite(aquece,HIGH);
    }
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

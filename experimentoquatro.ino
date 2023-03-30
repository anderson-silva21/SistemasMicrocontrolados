#define LED3 13
#define LED2 12
#define LED1 11
#define sobe 11
#define desce 22

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Serial.begin(115200);
}
int flag1 = sobe, flag2 = sobe, flag3 = sobe, cont_led = 0, cont1 = 0, cont2 = 0, cont3 = 0;
float tempo_alto1 = 0, tempo_baixo1 = 0, tempo_alto2 = 0, tempo_baixo2 = 0, tempo_alto3 = 0, tempo_baixo3 = 0;

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  if(cont_led < 42){
    cont_led++;  
  }
  if(cont_led > 0) {
    cont1++;
  }
  if(cont_led > 20){
    cont2++;
  }
  if(cont_led > 40){
    cont3++;
  }
  if(cont1>=3){
    cont1 = 0;
     if(flag1 == sobe){
      tempo_alto1 = tempo_alto1 + 25;
      analogWrite(LED1, tempo_alto1);
      if(tempo_alto1 >= 250){
        flag1 = desce;
      }
    }else{
      tempo_alto1 = tempo_alto1 - 25;
      analogWrite(LED1, tempo_alto1);  
      if(tempo_alto1 <= 0){
        flag1 = sobe;
      }
    }
  }
  if(cont2>=3){
    cont2 = 0;
     if(flag2 == sobe){
      tempo_alto2 = tempo_alto2 + 25;
      analogWrite(LED2, tempo_alto2);
      if(tempo_alto2 >= 250){
        flag2 = desce;
      }
    }else{
      tempo_alto2 = tempo_alto2 - 25;
      analogWrite(LED2, tempo_alto2);  
      if(tempo_alto2 <= 0){
        flag2 = sobe;
      }
    }
  }
  if(cont3>=3){
    cont3 = 0;
     if(flag3 == sobe){
      tempo_alto3 = tempo_alto3 + 25;
      analogWrite(LED3, tempo_alto3);
      if(tempo_alto3 >= 250){
        flag3 = desce;
      }
    }else{
      tempo_alto3 = tempo_alto3 - 25;
      analogWrite(LED3, tempo_alto3);  
      if(tempo_alto3 <= 0){
        flag3 = sobe;
      }
    }
  }
}

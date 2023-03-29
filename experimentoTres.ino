#define LED 13
#define sobe 11
#define desce 22

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

int flag = sobe, cont = 0;
float tempo_alto = 0, tempo_baixo = 0;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(tempo_alto);
  digitalWrite(LED, LOW);
  delay(tempo_baixo);
  cont++;
  if(cont>=3){
    cont = 0;
    if(flag == sobe){
      tempo_alto = tempo_alto + 1;
      tempo_baixo = 10 - tempo_alto;  
      if(tempo_alto >= 10){
        flag = desce;
      }
    }else{
      tempo_alto = tempo_alto - 1;
      tempo_baixo = 10 - tempo_alto;  
      if(tempo_alto <= 0){
        flag = sobe;
      }
    }
    
  }
}

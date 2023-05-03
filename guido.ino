
#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int x = 0; // To store value of the X axis
int y = 0; // To store value of the Y axis
#define lim_esq -1
#define lim_dir 8

#define lim_baix 15


//Espaco vazio
#define vazio 0
//Espaco ocupado
#define cheio 1

//Partes bordas peças
#define bAmbos 2
#define bEsq 3
#define bDir 4
#define nlado 5

//Matriz tela (Talvez mudar para uint8_t)
int Tela[16][8] = {  {0, 0, 0, 0, 0, 0, 0, 0}, //1
  {0, 0, 0, 0, 0, 0, 0, 0}, //2
  {0, 0, 0, 0, 0, 0, 0, 0}, //3
  {0, 0, 0, 0, 0, 0, 0, 0}, //4
  {0, 0, 0, 0, 0, 0, 0, 0}, //5
  {0, 0, 0, 0, 0, 0, 0, 0}, //6
  {0, 0, 0, 0, 0, 0, 0, 0}, //7
  {0, 0, 0, 0, 0, 0, 0, 0}, //8
  {0, 0, 0, 0, 0, 0, 0, 0}, //9
  {0, 0, 0, 0, 0, 0, 0, 0}, //10
  {0, 0, 0, 0, 0, 0, 0, 0}, //11
  {0, 0, 0, 0, 0, 0, 0, 0}, //12
  {0, 0, 0, 0, 0, 0, 0, 0}, //13
  {0, 0, 0, 0, 0, 0, 0, 0}, //14
  {0, 0, 0, 0, 0, 0, 0, 0}, //15
  {1, 1, 1, 1, 1, 0, 1, 1}
};//16

int formas[15][4][4] = {
  // T
  { {0, 0, 0, 0},
    {bEsq, nlado, bDir, 0},
    {0, bAmbos, 0, 0},
    {0, 0, 0, 0}
  },

  { {0, bAmbos, 0, 0},
    {bEsq, bDir, 0, 0},
    {0, bAmbos, 0, 0},
    {0, 0, 0, 0}
  },

  { {0, bAmbos, 0, 0},
    {bEsq, nlado, bDir, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },

  { {0, bAmbos, 0, 0},
    {0, bEsq, bDir, 0},
    {0, bAmbos, 0, 0},
    {0, 0, 0, 0}
  },
  // []
  { {0, bEsq, bDir, 0},
    {0, bEsq, bDir, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },
  // L
  { {0, bAmbos, 0, 0},
    {0, bAmbos, 0, 0},
    {0, bEsq, bDir, 0},
    {0, 0, 0, 0}
  },

  { {0, 0, 0, 0},
    {bEsq, nlado, bDir, 0},
    {bAmbos, 0, 0, 0},
    {0, 0, 0, 0}
  },

  { {0, bEsq, bDir, 0},
    {0, 0, bAmbos, 0},
    {0, 0, bAmbos, 0},
    {0, 0, 0, 0}
  },

  { {0, 0, bAmbos, 0},
    {bEsq, nlado, bDir, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },

  // _/-
  { {0, bEsq, bDir, 0},
    {bEsq, bDir, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },

  { {bAmbos, 0, 0, 0},
    {bEsq, bDir, 0},
    {0, bAmbos, 0, 0},
    {0, 0, 0, 0}
  },

  { {0, bAmbos, 0, 0},
    {bEsq, bDir, 0},
    {bAmbos, 0, 0, 0},
    {0, 0, 0, 0}
  },
  // -\_
  { {bEsq, bDir, 0, 0},
    {0, bEsq, bDir, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },

  // |
  { {0, bAmbos, 0, 0},
    {0, bAmbos, 0, 0},
    {0, bAmbos, 0, 0},
    {0, bAmbos, 0, 0}
  },

  { {0, 0, 0, 0},
    {bEsq, nlado, nlado, bDir},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  }
};

struct forma {
  int posx;
  int posy;
  int rot;
  int tam;
};
forma fs = {2, -4, 0, 4};

//index forma atual
int fi = 0;

void NovaForma() {}
void ChecaLinha() {}

int delai = 500;

void desenharF() {
  delay(delai);
  for (int i = 0; i < fs.tam; i++) {
    for (int j = 0; j < fs.tam; j++) {
      if (formas[fi][i][j] > 1) {
        //Tela[fs.posy + i][fs.posx + j] = formas[fi][i][j];
        //checa se ta dentro da tela
        if (fs.posy + i >= 0) {
          Tela[fs.posy + i][fs.posx + j] = 2;
        }
      } else {
        if (fs.posy + i >= 0 && Tela[fs.posy + i][fs.posx + j] > 1) {
          Tela[fs.posy + i][fs.posx + j] = 0;
        }
      }
    }
  }
  //LIMPAR LINHA DA TELA EMCIMA DA FORMA
  if (fs.posy > 0) {
    for (int i = 0; i < 8; i++) {
      if (Tela[fs.posy - 1][i] > 1) {
        Tela[fs.posy - 1][i] = 0;
      }
    }
  }

  //limpar lados a esquerda/direita da matriz
  for (int i = 0; i < 4; i++) {
    //dir
    if (fs.posx + 4 <= 7 && Tela[fs.posy + i][fs.posx + 4] > 1) {
      Tela[fs.posy + i][fs.posx + 4] = 0;
    }
    //esq
    if (fs.posx - 1 >= 0 && Tela[fs.posy + i][fs.posx - 1] > 1) {
      Tela[fs.posy + i][fs.posx - 1] = 0;
    }
  }
  printScr();
}




void movedown() {
  int move = 1;
  
  for (int i = 0; i < fs.tam; i++) {
 
    for (int j = 0; j < fs.tam; j++) {
         Serial.print(fs.posx);
      //Checa se embaixo tem peças ou se chegou no final da tela
      if (formas[fi][i][j] > 1) {
        //Serial.print(" DEBUG1 ");
        //Serial.print(Tela[fs.posy + i + 1][fs.posx + j]);
        if (Tela[fs.posy + i + 1][fs.posx + j] == 1 || fs.posy + i + 1 >= lim_baix) {
          move = 0;
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              if (formas[fi][i][j] > 1) {
                // Serial.print(j+fs.posx);
                 //Serial.print(fs.posx);
                Tela[fs.posy + i][fs.posx + j] = 1;
              }
            }
          }

          //Checar se fileira fez ponto(esperar proxima interação ou tocar animação)


          //Criar nova forma========
          if (fi >= 14) {
            fi = 0;
          } else {
            //Serial.print("DEBUG2");
            fi++;
          }
          //Serial.print("DEBUG3");
          fs.posy = -4;
          fs.posx = 3;
          break;
        }
      }
    }
    if (move == 0) {
      break;
    }
  }
  if (move == 1) {
    fs.posy += 1;
  }
  desenharF();
}

void printScr() {
  for (int j = 0; j < 8; j++) {
    Serial.print("=");
  }
  Serial.print("\n");

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 8; j++) {
      if (Tela[i][j] > 1) {
        Serial.print("X");
      } else if (Tela[i][j] == 1) {
        Serial.print("O");
      } else {
        Serial.print(" ");
      }
    }
    Serial.print("\n");
  }
}

void moveEsq() {
  int move = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (formas[fi][i][j] == bAmbos || formas[fi][i][j] == bEsq) {
        if ((j - 1 + fs.posx) < 0 || Tela[fs.posy + i][fs.posx + j - 1] != 0) {
          move = 0;
          break;
        }
      }
    }
  }
  if (move == 1) {
    fs.posx--;
    desenharF();
  }
  movedown();
}
void moveDir() {
  int move = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (formas[fi][i][j] == bAmbos || formas[fi][i][j] == bDir) {
        if ((j + 1 + fs.posx) > 7 || Tela[fs.posy + i][fs.posx + j + 1] != 0) {

          move = 0;
          break;
        }
      }
    }
  }
  if (move == 1) {
    fs.posx++;
    desenharF();
  }
  movedown();

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  x = analogRead(VRX_PIN);
  y = analogRead(VRY_PIN);

  // print data to Serial Monitor on Arduino IDE
  //Serial.print("x = ");
  //Serial.print(xValue);
  //Serial.print(", y = ");
  //Serial.println(yValue);
  //delay(200);
  //executar moveDire moveEsq ou modeDown

  if (y > 600 ) {
    moveDir();
  } else if (y < 400) {
    moveEsq();
  } else if (x < 400) {
    Serial.print("Baxo");
  }
  else {
    movedown();
  }

  //if(fi >=14){
  //  fi = 0;
  //}else{
  //  fi++;
  //}
}

#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



int buzzer = 6;
int numRandom = -1;
int gameStarted = 0;
int pontuation = 0;
int jumps = 3;
int seconds = 15;
char state = LOW;



String questionEasy[7] = {"A lua tem luz propria?", "O leao e rei da selva?", "O pinguim voa?", "Olho humano ve apenas 30Hz?", "O Isaac e Newton?", "Oxigenio envelhece?", "La e a nota perfeita?"};
String questionMedium[7] = {"Corvo imita voz humana?", "Atomo e 90% espaco vazio?", "Golfinho nao e peixe?", "Derivada de X = 0?", "C# significa C++++?", "Batata doce e raiz?", "Cafe + caro vem de passaro?"};
String questionHard[7] = {"Espaco pode ser curvo?", "Melhor cafe vem do Brasil?", "Jupiter tem 77 luas?", "tempo e uma dimensao?", "Resident Evil e de zumbi?", "inf/inf = 1?", "Japao tem + de 6000 ilhas?"};

int questionEasyAnswer[7] = {0, 0, 0, 1, 1, 1, 1};
int questionMediumAnswer[7] = {1, 1, 0, 0, 1, 0, 1};
int questionHardAnswer[7] = {1, 1, 0, 1, 0, 0, 1};



void setup(){  
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(13, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
  
  lcd.setCursor(1, 0);
  lcd.print(F("JOGO DO MILHAO"));
  lcd.setCursor(0, 1);
  lcd.print(F("por Babi & Bruno"));
}

void loop(){
  if(digitalRead(8) == LOW){
    if(gameStarted == 0){
      gameStarted = 1;
      sounds(3);
      int i;

      for(i = 0; i <= 15; i++){
        if(gameStarted == 1){
          if(i < 15){
            numRandom = random(7);
            showQuestion(numRandom);

            int peso = getWeight(numRandom);
            int quest = getQuest(numRandom);

            while(true){           
              if(digitalRead(13) == LOW){
                if(quest == 1){
                  pontuation = pontuation + peso;

                  lcd.clear();
                  lcd.setCursor(4,0);
                  lcd.print("Acertou!");
                  lcd.setCursor(2,1);
                  lcd.print("Pontuacao: ");
                  lcd.print(pontuation);

                  sounds(1);

                  seconds = 15;
                  delay(700);
                  break;
                }

                else if(quest == 0){
                  lcd.clear();
                  lcd.setCursor(5,0);
                  lcd.print("Errou!");
                  lcd.setCursor(2,1);
                  lcd.print("Pontuacao: ");
                  lcd.print(pontuation);

                  sounds(2);

                  delay(700);
                  finalGame();
                  break;
                }

              }

              if(digitalRead(10) == LOW){
                if(quest == 0){
                  pontuation = pontuation + peso;

                  lcd.clear();
                  lcd.setCursor(4,0);
                  lcd.print("Acertou!");
                  lcd.setCursor(2,1);
                  lcd.print("Pontuacao: ");
                  lcd.print(pontuation);

                  sounds(1);

                  seconds = 15;
                  delay(700);
                  break;
                }

                else if(quest == 1){
                  lcd.clear();
                  lcd.setCursor(5,0);
                  lcd.print("Errou!");
                  lcd.setCursor(2,1);
                  lcd.print("Pontuacao: ");
                  lcd.print(pontuation);

                  sounds(2);

                  delay(700);
                  finalGame();
                  break;
                }
              }

              if(digitalRead(9) == LOW){
                skipQuestion();
                if(jumps > 0){
                  break;
                }
                else{
                  showQuestion(numRandom);
                  continue;
                }
              }

              if(digitalRead(8) == LOW && gameStarted == 1){
                finalGame();
                break;
              }

              timer();
              if(seconds == -1 && jumps > 0){
                skipQuestion();
                break;
              }
              else if(seconds == -1 && jumps == 0){
                finalGame();
                break;
              }
            }
          }          
          if(i >= 15){
            showWinner();
          }
        }
      }
    }
  }
}



void showQuestion(int numRandom){
  lcd.clear();
  int indice;
  
  if(numRandom >= 0 && numRandom <= 6){
    if((questionEasy[numRandom].length()) > 16){
      String parte1 = questionEasy[numRandom].substring(0, 16);
      String parte2 = questionEasy[numRandom].substring(16);

      if(questionEasy[numRandom].substring(15, 16) != " "){
        parte1 = parte1 + "-";
      }

      lcd.setCursor(0,0);
      lcd.print(parte1);
      lcd.setCursor(0,1);
      lcd.print(parte2);
    }
    else{
      lcd.setCursor(0,0);
      lcd.print(questionEasy[numRandom]);
    }
  }
  
  else if(numRandom >= 7 && numRandom <= 13){ 
    indice = numRandom - 7;
    if((questionMedium[indice].length()) > 16){
      String parte1 = questionMedium[indice].substring(0, 16);
      String parte2 = questionMedium[indice].substring(16);
      
      if(questionMedium[indice].substring(15, 16) != " "){
        parte1 = parte1 + "-";
      }
      
      lcd.setCursor(0,0);
      lcd.print(parte1);
      lcd.setCursor(0,1);
      lcd.print(parte2);
    }
    else{
      lcd.setCursor(0,0);
      lcd.print(questionMedium[indice]);
    }
  }
  
  else if(numRandom >= 14 && numRandom <= 21){
    indice = numRandom - 14;

    if((questionHard[indice].length()) > 16){
      String parte1 = questionHard[indice].substring(0, 16);
      String parte2 = questionHard[indice].substring(16);

      lcd.setCursor(0,0);
      lcd.print(parte1);
      lcd.setCursor(0,1);
      lcd.print(parte2);
    }
    else{
      lcd.setCursor(0,0);
      lcd.print(questionHard[indice]);
    }
  }
}



int getWeight(int numRandom){
  int peso;
  
  if(numRandom >= 0 && numRandom <= 6){
    peso = 1;
  }
  else if(numRandom >= 7 && numRandom <= 13){
    peso = 2;
  }
  else if(numRandom >= 14 && numRandom <= 21){
    peso = 3;
  }
  
  return peso;
}



int getQuest(int numRandom){
  int quest;
  
  if(numRandom >= 0 && numRandom <= 6){
    quest = questionEasyAnswer[numRandom];
  }
  else if(numRandom >= 7 && numRandom <= 13){
    quest = questionMediumAnswer[(numRandom - 7)];
  }
  else if(numRandom >= 14 && numRandom <= 21){
    quest = questionHardAnswer[(numRandom - 14)];
  }
  
  return quest;
}
   


void skipQuestion(){
  if(jumps > 0){
    jumps--;

    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Pulou! Saltos");
    lcd.setCursor(2,1);
    lcd.print("restantes: ");
    lcd.print(jumps);
    
    sounds(5);

    delay(600);
    lcd.clear();
    seconds = 15;
  }

  else{
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Erro! 0 saltos");
    lcd.setCursor(3,1);
    lcd.print("restantes");

    delay(1000);
    lcd.clear();
  }
}



void finalGame(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Obrigado por");
  lcd.setCursor(5,1);
  lcd.print("jogar!");

  sounds(0);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Pontuacao total:");
  lcd.setCursor(7,1);
  lcd.print(pontuation);

  delay(5000);

  lcd.clear();

  delay(500);
  
  seconds = 15;
  jumps = 3;
  pontuation = 0;
  gameStarted = 0;

  lcd.setCursor(1, 0);
  lcd.print(F("JOGO DO MILHAO"));
  lcd.setCursor(0, 1);
  lcd.print(F("por Babi & Bruno"));
}



void showWinner(){
  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print("...");
  
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Parabens, voce");
  lcd.setCursor(1,1);
  lcd.print("acertou todas!");
  
  sounds(4);

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Pontuacao total:");
  lcd.setCursor(7,1);
  lcd.print(pontuation);

  delay(5000);

  lcd.clear();

  delay(500);
  
  seconds = 15;
  jumps = 3;
  pontuation = 0;
  gameStarted = 0;

  lcd.setCursor(1, 0);
  lcd.print(F("JOGO DO MILHAO"));
  lcd.setCursor(0, 1);
  lcd.print(F("por Babi & Bruno"));
}



void sounds(int typeSound){   
  if(typeSound == 1){
    tone(buzzer, 350);
    delay(150);
    noTone(buzzer);
    
    tone(buzzer, 220);
    delay(150);
    noTone(buzzer);
    
    tone(buzzer, 262);
    delay(150);
    noTone(buzzer);
    
    tone(buzzer, 350);
    delay(300);
    noTone(buzzer);
    
    tone(buzzer, 262);
    delay(150);
    noTone(buzzer);
    
    tone(buzzer, 350);
    delay(300);
    noTone(buzzer);
  }
  
  else if(typeSound == 0){
    tone(buzzer, 523);
    delay(300);
    noTone(buzzer);
    
    tone(buzzer, 392);
    delay(350);
    noTone(buzzer);
    
    tone(buzzer, 330);
    delay(300);
    noTone(buzzer);
    
    tone(buzzer, 440);
    delay(200);
    noTone(buzzer);
    
    tone(buzzer, 494);
    delay(200);
    noTone(buzzer);
    
    tone(buzzer, 440);
    delay(200);
    noTone(buzzer);
    
    tone(buzzer, 415);
    delay(400);
    noTone(buzzer);
    
    tone(buzzer, 466);
    delay(200);
    noTone(buzzer);
    
    tone(buzzer, 415);
    delay(200);
    noTone(buzzer);
    
    tone(buzzer, 392);
    delay(400);
    noTone(buzzer);
  }
  
  else if(typeSound == 2){
    tone(buzzer, 415);
    delay(500);
    noTone(buzzer);
    
    tone(buzzer, 392);
    delay(500);
    noTone(buzzer);
    
    tone(buzzer, 370);
    delay(500);
    noTone(buzzer);
    
    tone(buzzer, 350);
    delay(600);
    noTone(buzzer);
  }
  
  else if(typeSound == 3){
    tone(buzzer, 262);
    delay(200);
    noTone(buzzer);
    
    tone(buzzer, 330);
    delay(200);
    noTone(buzzer);
    
    tone(buzzer, 392);
    delay(200);
    noTone(buzzer);
    
    tone(buzzer, 524);
    delay(370);
    noTone(buzzer);
    
    delay(80);
    
    tone(buzzer, 524);
    delay(170);
    noTone(buzzer);
    
    delay(35);
    
    tone(buzzer, 524);
    delay(170);
    noTone(buzzer);
  }
  
  else if(typeSound == 4){
    tone(buzzer, 98);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 131);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 165);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 196);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 262);
    delay(170);
    noTone(buzzer);
       
    tone(buzzer, 330);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 392);
    delay(400);
    noTone(buzzer);
    
    delay(50);
    
    tone(buzzer, 330);
    delay(400);
    noTone(buzzer);
    
    delay(107);
    
    tone(buzzer, 103);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 131);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 156);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 208);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 262);
    delay(170);
    noTone(buzzer);
       
    tone(buzzer, 312);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 415);
    delay(400);
    noTone(buzzer);
    
    delay(50);
    
    tone(buzzer, 312);
    delay(400);
    noTone(buzzer);
    
    delay(107);
    
    tone(buzzer, 117);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 147);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 175);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 233);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 294);
    delay(170);
    noTone(buzzer);
       
    tone(buzzer, 350);
    delay(170);
    noTone(buzzer);
    
    tone(buzzer, 467);
    delay(400);
    noTone(buzzer);
    
    delay(107);
    
    tone(buzzer, 467);
    delay(100);
    noTone(buzzer);
    
    delay(50);
    
    tone(buzzer, 467);
    delay(100);
    noTone(buzzer);
    
    delay(50);
    
    tone(buzzer, 467);
    delay(100);
    noTone(buzzer);
    
    delay(50);
    
    tone(buzzer, 523);
    delay(607);
    noTone(buzzer);
  }
  
  else if(typeSound == 5){
    tone(buzzer, 262);
    delay(200);
    noTone(buzzer);
    
    tone(buzzer, 392);
    delay(200);
    noTone(buzzer);
  }
}



void led(char STATE){
  digitalWrite(7, STATE);
}



void timer(){ 
  if(seconds >= 10){
    lcd.setCursor(14, 1);
  }
  else if(seconds < 10){
    lcd.setCursor(14, 1);
    lcd.print(0);
  }

  lcd.print(seconds);
  seconds--;
  delay(1000);

  if(seconds <= 5){
    led(state);

    if(state == LOW){
      state = HIGH;
    }

    else if(state == HIGH){
      state = LOW;
    }
  }

  if(seconds == -1){
    state = LOW;
    return;
  }
}

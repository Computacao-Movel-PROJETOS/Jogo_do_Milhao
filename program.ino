// COMPUTAÇÃO MÓVEL - PROJETO 1 - FEITO POR: GABRIELA E BRUNO

// Esse projeto tem como objetivo criar um jogo de perguntas e respostas. As perguntas foram armazenadas na memória do programa e classificadas em fácil, médio e difícil. O jogador deve responder
// corretamente a 15 perguntas para vencer o jogo.

// Para começar nosso programa, primeiro incluímos as bibliotecas necessárias para o programa.
// LiquidCrystal.h: utilizamos um LCD 16x2 para mostrar as perguntas.

#include<LiquidCrystal.h>

// Colocamos suas expecificações

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Variáveis necessárias para funcionamento do programa:

// buzzer: entrada do buzzer no arduíno;
// numRandom: variável responsável por armazenar qual será a questão. Como seu nome diz, ela será uma variável que guardará um número randômico entre 0 e 21;
// gameStarted: variável responsável por informar ao programa se o jogo está em andamento ou não;
// pontuation: variável responsável por armazenar o total de pontos do jogador;
// jumps: variável responsável por armazenar a quantidade de saltos que o jogador poderá fazer;
// seconds: variável responsável por armazenar quantos segundos cada questão terá para ser respondida;
// state: variável responsável por armazenar o estado em que o LED se encontra;

int buzzer = 6;
int numRandom = -1;
int gameStarted = 0;
int pontuation = 0;
int jumps = 3;
int seconds = 15;
char state = LOW;


// Aqui estão as listas que contém as perguntas e respostas do jogo, classificadas como fácil, médio e difícil.
// Por conta do tamanho do programa, não foi possível adicionar mais questões ao jogo.

String questionEasy[7] = {"A lua tem luz propria?", "O leao e rei da selva?", "O pinguim voa?", "Olho humano ve apenas 30Hz?", "O Isaac e Newton?", "Oxigenio envelhece?", "La e a nota perfeita?"};
String questionMedium[7] = {"Corvo imita voz humana?", "Atomo e 90% espaco vazio?", "Golfinho nao e peixe?", "Derivada de X = 0?", "C# significa C++++?", "Batata doce e raiz?", "Cafe + caro vem de passaro?"};
String questionHard[7] = {"Espaco pode ser curvo?", "Melhor cafe vem do Brasil?", "Jupiter tem 77 luas?", "tempo e uma dimensao?", "Resident Evil e de zumbi?", "inf/inf = 1?", "Japao tem + de 6000 ilhas?"};

// Listas que contém as respostas de cada pergunta, também classificadas em suas respectivas dificuldades.

int questionEasyAnswer[7] = {0, 0, 0, 1, 1, 1, 1};
int questionMediumAnswer[7] = {1, 1, 0, 0, 1, 0, 1};
int questionHardAnswer[7] = {1, 1, 0, 1, 0, 0, 1};


// Onde inicializamos as entradas de cada objeto no arduíno.

void setup(){  
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(13, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Para que o programa não ficasse criando sempre os mesmos valores randômicos, utilizamos essa função.
  
  randomSeed(analogRead(0));
  
  lcd.setCursor(1, 0);
  lcd.print(F("JOGO DO MILHAO"));
  lcd.setCursor(0, 1);
  lcd.print(F("por Babi & Bruno"));
}

void loop(){

  // Aqui ocorre o funcionamento do jogo, quando o botão de início/zerar for pressionado, então o jogo deverá iniciar ou zerar. Para isso, foi utilizado a variável gameStarted, que, quando o botão for pressionado,
  // irá informar se o jogo está em andamento ou não. Se gameStarted = 0, então o jogo ainda não começou e por isso deverá iniciar, colocando a variável para 1 e assim, rodando o jogo.
  
  if(digitalRead(8) == LOW){
    if(gameStarted == 0){
      gameStarted = 1;
      sounds(3);
      int i;

      // O jogo terá um total de 15 questões.

      for(i = 0; i <= 15; i++){

        // Aqui também comparamos se a variável gameStarted = 1, pois, se o jogador errar uma questão ou decidir parar o jogo no meio, então o jogo deve parar instantaneamente, saindo então do seu laço de repetição.
        
        if(gameStarted == 1){
          if(i < 15){

            // Criamos o número randômico e apresentamos na tela do LCD
            numRandom = random(21);
            showQuestion(numRandom);

            // Essas são funções criadas para armazenar o peso da questão e a resposta da questão. Essa e outras funções serão explicadas futuramente.
            int peso = getWeight(numRandom);
            int quest = getQuest(numRandom);

            // Entramos em um loop infinito que, enquanto o tempo não acabar, ficará esperando alguma ação do jogador.
            // Ele irá comparar a resposta da questão com o botão pressinado, se estiver correto, então ele irá parar o loop e assim ir para a próxima questão, tocando uma música, resetando os segundos e adicionando
            // os pontos. Se estiver incorreto, ele também tocará uma música e então irá para o final do jogo, o qual é uma função que será explicada futuramente.
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

              // Se o jogador quiser parar no meio, também chamamos a função de final de jogo.
              if(digitalRead(8) == LOW && gameStarted == 1){
                finalGame();
                break;
              }

              // Se o tempo acabar, a questão será pulada e você perderá um salto. Se a quantidade de saltos = 0, então o jogo acaba.
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
          // Se todas as respostas forem corretas, então o jogador terá ganhado o jogo.
          if(i >= 15){
            showWinner();
          }
        }
      }
    }
  }
}


// Essa função é responsável por mostrar qual é a questão atual do jogo.
void showQuestion(int numRandom){
  // Limpamos o LCD e criamos uma variável chamada íncice. Essa variável foi necessária pois, em cada dificuldade, temos 7 questões, e no total, temos 21 questões.
  // Por isso, quando o número randômico cair entre 0 e 6, significa que a questão desejada é uma fácil. Entre 7 e 13, uma média. Entre 14 e 20/21, uma difícil.
  // Mas, como cada lista tem apenas 7 valores, precisamos subtrair do valor do número randômico a quantidade de vezes que aquele número cabe em 7, deixando apenas seu resto e assim, obtendo a questão corretamente.
  lcd.clear();
  int indice;
  
  if(numRandom >= 0 && numRandom <= 6){
    if((questionEasy[numRandom].length()) > 16){
      // Se a questão tiver um número maior de caracteres do que uma linha do LCD pode apresentar, então ela será partida em 2 partes.
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


// Essa função é responsável por informar o peso de cada questão com base no número que cair.
// Para perguntas fáceis, o peso será igual a 1;
// Para perguntas médias, o peso será igual a 2;
// Para perguntas difíceis, o peso será igual a 3;
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


// Essa função é responsável por armazenar a resposta da questão atual do programa na lista de respostas das questões.
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
   

// Essa função é responsável por pular a questão.
// Se a qualtidade de pulos for > 0, então o jogo irá pular a questão, resetando o tempo e tocando uma música.
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

  // Se não, o jogo informará que você não tem mais saltos e nada ocorre.
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


// Essa função é responsável por apresentar o menú do jogo e resetar as variáveis.
void startMenu(){
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


// Essa função é responsável por apresentar a pontuação final.
void showPontuation(){
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Pontuacao total:");
  lcd.setCursor(7,1);
  lcd.print(pontuation);

  delay(5000);
}


// Essa função é responsável por apresentar o final do jogo.
void finalGame(){
  // Agradecimento.
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Obrigado por");
  lcd.setCursor(5,1);
  lcd.print("jogar!");

  // Música de derrota.
  sounds(0);

  // Mostra a pontuação e o menú inicial
  showPontuation();  
  startMenu();
}


// Essa função é responsável por apresentar a tela de vitória do jogo.
void showWinner(){
  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print("...");
  
  delay(2000);

  // Parabenização.
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Parabens, voce");
  lcd.setCursor(1,1);
  lcd.print("acertou todas!");

  // Música de vitória.
  sounds(4);

  // Mostra a pontuação e o menú inicial
  showPontuation();  
  startMenu();
}


// Função responsável pelas músicas do jogo.
// Ela recebe um valor do tipo inteiro que irá informar qual é a música desejada para ser tocada.
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


// Função responsável por mudar o estado do led
void led(char STATE){
  digitalWrite(7, STATE);
  
  if(state == LOW){
    state = HIGH;
  }

  else if(state == HIGH){
    state = LOW;
  }
}


// Função responsável pelo tempo de cada questão.
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

  // Se o tempo for igual ou menor que 5, então o led piscará, mudando a cada segundo seu estado.
  if(seconds <= 5){
    led(state);
  }

  // Se o tempo acabar, então ele retornará.
  if(seconds == -1){
    state = LOW;
    return;
  }
}

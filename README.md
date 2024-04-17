---------------------------------------------------- COMPUTAÇÃO MÓVEL - JOGO DO MILHÃO ----------------------------------------------------

- Introdução:
  
  Bem-vindo ao JOGO DO MILHÃO! Você está preparado para testar seus conhecimentos e habilidades neste jogo de perguntas eletrizante? Se sim, então você está prestes a embarcar em uma jornada emocionante!

  O desafio é simples, mas não se engane, pois a dificuldade está à altura do prêmio. Aqui está o que você precisa saber:
    1) O jogo consiste em 21 perguntas no total: 7 fáceis valendo 1 ponto cada, 7 médias valendo 2 pontos cada e 7 difíceis valendo 3 pontos cada.
    2) A cada jogo, serão selecionadas aleatoriamente 15 perguntas de qualquer nível de dificuldade.
    3) Você terá à disposição 3 pulos que podem ser usados a qualquer momento durante o jogo.
    4) Cada pergunta terá um tempo limite de 15 segundos para ser respondida. Se o tempo se esgotar, você perderá um dos seus pulos. E lembre-se, se todos os pulos forem usados, o jogo acaba!
    5) Se errar qualquer pergunta, o jogo será encerrado e sua pontuação será exibida. Mas não se preocupe, você pode sempre tentar novamente e superar seu próprio recorde.

  Agora é hora de provar sua inteligência e habilidade. Está pronto para o desafio? Então, boa sorte e que a jornada rumo ao prêmio milionário comece agora!

- Metodologia:

  1) Plataforma de desenvolvimento: TinkerCad
  2) Linguagem utilizada: C++
  3) Microcontrolador: Arduino Uno
  4) Placa de circuito para montagem do projeto
  5) Cabos e resistores, conforme necessário para conexões e limitação de corrente
  6) LED para indicar quando o tempo está acabando
  7) Display LCD para exibir o programa, pontuações e mensagens do jogo
  8) Buzzer para reproduzir músicas e sons para cada ação dentro do jogo
  9) Botões para interação do jogador, como responder perguntas e acionar os pulos
  10) Potenciômetro para ajustar o contraste ou brilho do Display LCD

- Código:

  O código está no arquivo 'program.ino', totalmente comentado e explicado.

- Vídeos e imagens do projeto:

  1) O vídeo do projeto em funcionamento está no arquivo 'Projeto Montado.mp4'.
  2) A imagem 'system.png' é uma print do sistema montado no Tinkercad.

- Conclusão:

  Para realizar o programa, primeiro analisamos cada requisito do trabalho. Para fazer as questões, separamos elas em 3 listas diferentes, para separa-las por dificuldade, e mais 3 listas contendo
  a resposta de cada pergunta. 
  Após isso, fizemos para cada requisito uma função , para otimização do nosso jogo. 
  Separamos as funções da seguinte forma:

  1) uma função para cada menu
  2) "Mostrar pontuação"
  3) "Timer/Temporizador"
  4) "Pular questão"
  5) "Resetar variáveis iniciais"
  6) "Iniciar o jogo"
  7) "Finalizar o jogo"
  8) "Músicas e efeitos sonoros"
  9) "Mostrar as questões no LCD"
  10) "Pegar o peso da questão"
  11) "Pegar a resposta correta da questão"

  Durante o desenvolvimento, tivemos pequenos problemas em relação a analisar se o jogo estava em andamento ou não. Pois, sempre que apertávamos o botão, a função "Iniciar jogo" era chamada e
  as perguntas eram chamadas todas de uma vez porque estava tudo dentro da funçaõ "Loop". Com isso, não conseguiamos tentar responder as perguntas. Após o entendimento desse nosso problema,
  conseguimos ajeitar o programa e deixar ele rodando corretamente.
  Tivemos um outro problema relacionado à parte de memória dentro do TinkerCad, pois o foco era fazer 20 perguntas de cada nível (e fizemos, porém tivemos que tirar por conta desse problema).
  Contudo, o trabalhar proposto pelo Prof. Isaac Jesus foi feito corretamente dentro do que foi pedido à nós!

  Esperamos que gostem do nosso jogo, até breve!! 
  

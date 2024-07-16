#include<stdio.h> //biblioteca padrão.
#include<locale.h> //possibilita que a acentuação seja exibida normalmente no programa. 
#include<conio2.h> //para os comandos de personalização: textcolor, textbackground, gotoxy.
#include<stdlib.h> //para os comandos system("pause") e system("cls").
#include<time.h> //para o comando srand.
#include<windows.h> //para o comando Sleep().

//Variáveis globais:
int c[300][300], pontos=1, cx=2, cy=2;
int comida[2], velocidade, velocidade_inicial;
int gameover=0, nivel=1, cont_nivel=0;
int pontuacao=0;

void apagarcaracter(int x, int y){
    gotoxy(x,y);printf(" "); //quando a função apagarcaracter for chamada posteriormente, será escrito na coordenada x,y um espaço vazio (printf(" ");) que irá "apagar" aquele caracter.
}
int dificuldade (){ //LAYOUT DO MENU DE DIFICULDADE; 
    int linha=13; //variável "linha" é usada para determinar a posição da linha;atribuimos o valor 15 a ela pois a primeira linha de opção é a 15. 
    char tecla =' ';
    //logo();
    do
    {
    	gotoxy(38,10);printf("E S C O L H A   A   D I F I C U L D A D E:");
        gotoxy(54,13);printf("FÁCIL");
        gotoxy(54,15);printf("MÉDIO");
        gotoxy(54,17);printf("DIFÍCIL");
        gotoxy(54,19);printf("SEMI-DEUS");
        gotoxy(52,linha); //posicionando o caracter triângulo na coluna 35. Este caracter vai ser usado para mostrar para o usuário qual opção está selecionada.
        textcolor(3); //colorir o caracter triângulo.
        printf("%c",16);// caracter triangulo.
        textcolor(15);//colorir de branco os outros elementos da tela.
        gotoxy(1,30);
        tecla = getch(); //getch() armazena a tecla que foi clicada e a variável "tecla" recebe o valor de getch().
        if (tecla == 72){//72 é a tecla de seta para cima.
            apagarcaracter(52,linha);//vai apagar o rastro do triângulo que seleciona a opção.
            if(linha == 13){  //se o triângulo de seleção estiver na primeira opção(linha 15) e o user apertar a tecla 72: 
                linha = 21; //o triângulo de seleção vai para a última linha de opção para fazer um efeito de loop.
        	}
            linha = linha - 2;
        }
        else{
            if(tecla == 80)//80 é a tecla de seta para baixo.
            {
                apagarcaracter(52,linha);//vai apagar o rastro do triângulo que seleciona a opção.
                if(linha == 19){ //se o triângulo de seleção estiver na última opção(linha 23) e o user apertar a tecla 80: 
					linha = 11;  //o triângulo de seleção vai para a primeira linha de opção para fazer um efeito de loop.
				}
                linha = linha + 2;
            }
        }
    }while(tecla != '\r');
    switch(linha){ //de acordo com a dificuldade que o user escolher, a velocidade do jogo muda.
        case 13: // se o user escolher "fácil" (linha 15), a velocidade do jogo é 130;
			velocidade = 130;
			velocidade_inicial = 130;
            break;
        case 15: // se o user escolher "médio" (linha 17), a velocidade do jogo é 95;
			velocidade = 95;
			velocidade_inicial = 95;
            break;
        case 17: // se o user escolher "difícil" (linha 19), a velocidade do jogo é 55;
			velocidade = 55;
			velocidade_inicial = 55;
	    	break;
        case 19: // se o user escolher "semi-deus" (linha 21), a velocidade do jogo é 20;
			velocidade = 20;
			velocidade_inicial = 0;
            break;
    }
    return 0;
}
int menu(){ //LAYOUT DO MENU INICIAL;
	setlocale(LC_ALL, "Portuguese"); //adaptando para a escrita da língua portuguesa.
    int linha=12;
    char tecla =' ';
    do
    {
        textcolor(15);
        gotoxy(53,12);printf("JOGAR");
        gotoxy(53,14);printf("MOMENTO CONTO DE FADAS");
        gotoxy(53,16);printf("COMO JOGAR?");
        gotoxy(53,18);printf("CREDITOS");
        gotoxy(53,20);printf("SAIR");
        gotoxy(43, 24);printf("UTILIZE     PARA MOVER-SE PELO MENU E", 287, 286);
        textcolor(3);
        gotoxy(51, 24);printf("%c %c", 287, 286);
        textcolor(7);
        gotoxy(45, 25);printf("PRESSIONE         PARA SELECIONAR");
        textcolor(3);
        gotoxy(55,25);printf("<ENTER>");
        gotoxy(51,linha);
        textcolor(3);
        printf("%c",16);
        textcolor(15);
        gotoxy(1,30);
        tecla = getch();
        if (tecla == 72){
            apagarcaracter(51,linha);
            if(linha == 12){
                linha = 22;
        	}
            linha = linha - 2;
        }
        else
        {
            if(tecla == 80){
                apagarcaracter(51,linha);
                if(linha == 20){
					linha = 10;
				}
                linha = linha + 2;
            }
        }
    }while(tecla != '\r');
    return(linha);
}
int rankings(){ //LISTAR OS MAIORES RECORDES JOGADOS;
	printf("estamos em reforma ainda!\n ps: faltou a verba das desenvolvedoras :()\n\n\n\n\n");
	gotoxy(1,30);
    return 0;
}
int como_jogar(){ //INSTRUÇÕES DE COMO JOGAR;
	gotoxy(46,3);printf("===========================");
	gotoxy(46,4);printf("R E G R A S   D O   J O G O");  
	gotoxy(46,5);printf("===========================");
 	textcolor(3);
	gotoxy(8, 9);printf("OBJETIVO:");
	textcolor(7);
	gotoxy(8,10);printf("Coma o máximo de maçãs que conseguir sem morrer para ter a maior cobra!");
    textcolor(3);
	gotoxy(8,12);printf("CONTROLES:");
	textcolor(7);
	gotoxy(8,13);printf("Utilize as setas direcionais (%c %c %c %c) ou A, W, S, D para se movimentar no jogo.", 273, 272, 287, 286);
	textcolor(3);
	gotoxy(8,15);printf("VITÓRIA:");
	textcolor(7);
	gotoxy(8,16);printf("Consiga comer 20 maças sem morrer e a sua cobra será a maior e mais forte!");
    textcolor(3);	
	gotoxy(8,18);printf("DERROTAS:");
	textcolor(7);
	gotoxy(8,19);printf("Encostar na margem do mapa e praticar canibalismo resultará na sua morte!!");
	gotoxy(8,20);printf("Tenha cuidado.");
	gotoxy(1,30);
	return 0;
}
int creditos(){ //MOSTRAR OS CRÉDITOS DE DESENVOLVIMENTO;
	gotoxy(42,3);printf("====================================");
	gotoxy(42,4);printf("O B R I G A D A   P O R   J O G A R!");
	gotoxy(42,5);printf("====================================");
	gotoxy(17,9);printf("Agradeço a todos que dedicaram um pouco do seu tempo para prestigiar o nosso projeto!");
	gotoxy(6,10);printf("Este jogo foi desenvolvido em 2024 como trabalho de conclusão do 1° período do curso de Ciência da Computação.");
	gotoxy(8,14);printf("=========================");
	textcolor(3);
	gotoxy(8,15);printf("AGRADECIMENTOS ESPECIAIS:");
	textcolor(7);
	gotoxy(8,16);printf("=========================");
	gotoxy(8,17);printf("Clara Cauane Oliveira Silva (   )");
	textcolor(3);
	gotoxy(37,17);printf("dev");
	textcolor(7);
	gotoxy(8,18);printf("Sthefanny Barbosa de Lima Costa (   )");
	textcolor(3);
	gotoxy(41,18);printf("dev");
	textcolor(7);
	gotoxy(8,19);printf("Ceres Germanna Braga Morais (como                 )");
	textcolor(3);
	gotoxy(42,19);printf("Prof. Orientador");
	textcolor(7);
	gotoxy(57,26);printf("%c2024", 169);
	gotoxy(1,30);
}
void desenha(){ // Desenha a cobrinha
    int i;
    for(i=0; i<pontos; i++){
        gotoxy(c[i][0],c[i][1]);
		textcolor(3);
		printf("%c",156);
		textcolor(7);
    }
}
void atualiza(){ // Atualiza a posição da cobrinha
    int i;
    gotoxy(c[pontos][0],c[pontos][1]);printf(" "); //à medida que a cobra vai andando, o último caracter precisa ser apagado para não duplicar o tamanho original da cobra.
    for(i=pontos; i>=0; i--){
        c[i+1][0] = c[i][0];
        c[i+1][1] = c[i][1];
    }
}
int analiza(){ // Vê se a cobrinha enconstou em seu próprio corpo
    int i, retorno=0;
    for(i=1; i<pontos; i++){
        if(cx==c[i][0] && cy==c[i][1]){
            retorno=1;
        }
    }
    return retorno;
}
void geraComida(){ // Gera comida em local aleatório
	int xmin = 2, ymin = 2, xmax = 58, ymax = 18;
	
    gotoxy(comida[0],comida[1]);printf(" ");
    srand(time(NULL));
    int randomX = xmin + rand() % (xmax - xmin + 1);//concertar o erro de gerar comida na borda.
	int randomY = ymin + rand() % (ymax - ymin + 1);//concertar o erro de gerar comida na borda.
	comida[0] = randomX;
    comida[1] = randomY;
    textcolor(4);
    gotoxy(comida[0],comida[1]);printf("%c",245);
    textcolor(7);
}

//----------------------------------------------------------------------------  
int main(){
	int opcao, tam=0;
	char nome[30],nome_sujo[5000];
    setlocale(LC_ALL, "Portuguese");
	do{
		inicio:
		system("cls");
		gotoxy(51,5);printf("==================");
		textcolor(3);
		gotoxy(51,6);printf("S T A R T Ê N I A");
		textcolor(7);
		gotoxy(51,7);printf("==================");
		opcao = menu();
		switch(opcao){
			case 12:do
                    {
                        system("cls");
                        gotoxy(30,15);printf("DIGITE SEU NOME: \n");
                        gotoxy(47,15);gets(nome_sujo);
                        for(int i=0;i<30;i++)
                        tam=strlen(nome_sujo);
                    }while(tam>30);
                system("cls");
                dificuldade();
                system("cls");
                //--------------------------------------------------JOGO    
				char tecla, nome[12];
				//Delimitar a borda do mapa:
				for(int i=0;i<60;i++){//borda superior
					gotoxy(i,0);printf("%c", 61);
					//Sleep(7);
				}
				for(int i=1;i<21;i++){//borda direita
					gotoxy(60,i);printf("%c", 61);
					//Sleep(7);
				}
				for(int i=60;i>=0;i--){//borda inferior
					gotoxy(i,20);printf("%c", 61);
					//Sleep(7);
				}
				for(int i=20;i>=2;i--){//borda esquerda
					gotoxy(1,i);printf("%c", 61);
					//Sleep(7);
				}
				//system("pause");
				geraComida();
			    tecla='d'; //define que a cobra já vai iniciar andando para direção "s"(para baixo).
			    while(gameover==0){ // Enquanto o usuário não perder:
			    	gotoxy(2,22);printf("NOME: ");
			    	textcolor(3);
			    	gotoxy(8,22);printf("%s", nome_sujo);
			    	textcolor(7);
					gotoxy(2,24);printf("PONTOS: %d\t",pontuacao);
				    gotoxy(23,24);printf("NÍVEL: %d", nivel);
			        //gotoxy(41,24);printf("TEMPO: ---");
					c[0][0]=cx;
			        c[0][1]=cy;
			        if(kbhit()) // Se alguma tecla for apertada, o valor 
			            tecla=getch(); // vai para a variável 'tecla'
			
			        if(tecla=='w' || tecla=='W' || tecla==72){
			            cy--;
			            if(cy==0) break; // Se a cabeça da cobra estiver na parede superior, o jogo acaba.
			        }                  
			        if(tecla=='a' || tecla=='A' || tecla==75){
			            cx--;
			            if(cx==0) break; // Se a cabeça da cobra estiver na parede da esquerda, o jogo acaba.
			        }                    
			        if(tecla=='s' || tecla=='S' || tecla==80){
			            cy++;
			            if(cy==21) break; // Se a cabeça da cobra estiver na parede de baixo, o jogo acaba.
			        }                     
			        if(tecla=='d' || tecla=='D' || tecla==77){
			            cx++;
			            if(cx>=61  ) break; // Se a a cabeça da cobra estiver na parede da direida, o jogo acaba.
			        }
			        if(pontos-1 == 20){ //determina o final do jogo quando o jogador atingir 20 pontos.
						gotoxy(23,13);printf("VOCE GANHOU!!");
						gotoxy(1,30);printf(".");
						Sleep(1000);  
						system("pause");	
					}
			        if(cx==comida[0] && cy==comida[1]){ // Se a cobra comer a comida
			            pontuacao++;
			            pontos++;
						geraComida();
			            if(velocidade_inicial == 130){
							velocidade-=5;
							if(pontuacao % 3 == 0){
				            	nivel++;
							}
						} 
			            if(velocidade_inicial == 95){
			            	velocidade-=10;
							if(pontuacao % 5 == 0){
				            	nivel++;
							}	
						} 
			            if(velocidade_inicial == 55){
							velocidade-=15;
							if(pontuacao % 7 == 0){
				            	nivel++;
							}
						} 
			            if(velocidade_inicial == 10) velocidade-=10;
			        }
					 
			        gameover=analiza();
			        atualiza(); //chamando a função atualiza().
			        desenha(); //chamando a função desenha().
					gotoxy(1,30);
			        Sleep(velocidade);//vai garantir que a movimentação vai ser de acordo com a velocidade escolhida. 
			    }
			    //system("cls"); // Quando o usuário perder, limpa a tela e exibe uma mensagem final
			    gotoxy(23,13);printf("VOCÊ É UM LOSEER!");
				gotoxy(26,14);printf("Abestado véi");
				gotoxy(1,30);
			    system("pause");
			    system("cls");
				return 0;
				
				//-------------------------------------------------------------
				system("cls");          
                goto inicio;
            case 14:
            	system("cls");
            	rankings();
            	system("pause");
            	goto inicio;
            case 16: 
            	system("cls");
            	como_jogar();
            	system("pause");
            	goto inicio;
            case 18:
            	system("cls");
            	creditos();
            	system("pause");
            	goto inicio;
            case 20:
            	exit(0);
		}
	}while(opcao != 20);
	return 0;
}

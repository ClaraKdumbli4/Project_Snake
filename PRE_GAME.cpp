#include<stdio.h>
#include<locale.h>
#include<ctype.h>
#include<windows.h>
#include<conio.c>
#include<stdlib.h>
#include<time.h>
int c[300][2], pontos=1, cx=2, cy=2;
int comida[2], velocidade;

void apagarcaracter(int x, int y){
    gotoxy(x,y);printf(" "); //quando a função apagarcaracter for chamada posteriormente, será escrito na coordenada x,y um espaço vazio (printf(" ");) que irá apagar aquele caracter.
}
int dificuldade (){ //LAYOUT DO MENU DE DIFICULDADE; 
    int linha=15; //variável linha=15: vai iniciar na primeira linha, que é a 15.
    char tecla =' ';
    //logo();
    do
    {
        gotoxy(37,15);printf("TUTORIAL");
        gotoxy(37,17);printf("FÁCIL");
        gotoxy(37,19);printf("MÉDIO");
        gotoxy(37,21);printf("DIFÍCIL");
        gotoxy(37,23);printf("HARDCORE");
        gotoxy(35,linha); //posicionando o caracter triângulo na coluna 35. Este caracter vai ser usado para mostrar para o usuário qual opção está selecionada.
        textcolor(9);
        printf("%c",16);// caracter triangulo.
        textcolor(15);
        tecla = getch();
        if (tecla == 72)//72 é a tecla de seta para cima.
        {
            apagarcaracter(35,linha);//vai apagar o rastro do triângulo que seleciona a opção.
            if(linha == 15){  //se o triângulo de seleção estiver na primeira opção(linha 15) e o user apertar a tecla 72: 
                linha = 25; //o triÂngulo de seleção vai para a última linha de opção para fazer um efeito de loop.
        	}
            linha = linha - 2;
        }
        else
        {
            if(tecla == 80)//80 é a tecla de seta para baixo.
            {
                apagarcaracter(35,linha);//vai apagar o rastro do triângulo que seleciona a opção.
                if(linha == 23){ //se o triângulo de seleção estiver na última opção(linha 23) e o user apertar a tecla 80: 
					linha = 13;  //o triângulo de seleção vai para a primeira linha de opção para fazer um efeito de loop.
				}
                linha = linha + 2;
            }
        }
    }while(tecla != '\r');
    switch(linha){ //de acordo com a dificuldade que o user escolher, o tempo de jogo muda.
        case 15: velocidade = 160;// se o user escolher "tutorial" (linha 15), o tempo de jogo é 160;
                 break;
        case 17: velocidade = 130;// se o user escolher "fácil" (linha 17), o tempo de jogo é 130;
                 break;
        case 19: velocidade = 95;// se o user escolher "médio" (linha 19), o tempo de jogo é 95;
                 break;
        case 21: velocidade = 55;// se o user escolher "difícil" (linha 21), o tempo de jogo é 55;
                 break;
        default: velocidade = 25;// se o user escolher "hardcore", o tempo de jogo é 25;
    }
    return 0;
}
int menu(){ //LAYOUT DO MENU INICIAL;
	setlocale(LC_ALL, "Portuguese");
    int linha=10;
    char tecla =' ';
    do
    {
        textcolor(15);
        gotoxy(45,10);printf("JOGAR");
        gotoxy(45,12);printf("RANKINGS");
        gotoxy(45,14);printf("COMO JOGAR?");
        gotoxy(45,16);printf("CRÉDITOS");
        gotoxy(45,18);printf("SAIR");
        gotoxy(43,linha);
        textcolor(9);
        printf("%c",16);
        textcolor(15);
        tecla = getch();
        if (tecla == 72){
            apagarcaracter(43,linha);
            if(linha == 10){
                linha = 20;
        	}
            linha = linha - 2;
        }
        else
        {
            if(tecla == 80){
                apagarcaracter(43,linha);
                if(linha == 18){
					linha = 8;
				}
                linha = linha + 2;
            }
        }
    }while(tecla != '\r');
    return(linha);
}
int rankings(){ //LISTAR OS MAIORES RECORDES JOGADOS;
	printf("estamos em reforma ainda :)");
    return 0;
}
int como_jogar(){  //INSTRUÇÕES DE COMO JOGAR;
	gotoxy(46,6);printf("R E G R A S\tD O\tJ O G O");
	gotoxy(11,10);printf("[1] USE AS SETAS DO TECLADO PARA DIRECIONAR A COBRA!");
	gotoxy(11,12);printf("[2] COMA AS FRUTAS PARA SE TORNAR A MAIOR COBRA QUE EXISTE!!");
	return 0;
    //FALTA DEFINIR O RESTO DAS REGRAS;
}
int creditos(){ //MOSTRAR OS CRÉDITOS DE DEVENVOLVIMENTO;
	gotoxy(51,6);printf("C R É D I T O S");
	gotoxy(6, 10);printf("Agradeço a todos que dedicaram um pouco do seu tempo para prestigiar o nosso projeto.");
	gotoxy(6, 11);printf("Este jogo foi desenvolvido como conclusão do 1 período de Computação na UERN Mossoró.");
	gotoxy(8,15);printf("AGRADECIMENTOS ESPECIAIS:\n");
	gotoxy(10,16);printf("Clara Cauane O. Silva e Sthefanny Barbosa de L. Costa (devs)\n");
	gotoxy(10,17);printf("Ceres Germanna (como Prof. Orientador)\n");
	gotoxy(10,18);printf("Matheus Brasileiro Aguiar - Matuê (como efeitos sonoros)\n\n\n\n\n");
    return 0;
}

void desenha(){ // Desenha a cobrinha
    int i;
    for(i=0; i<pontos; i++){
        gotoxy(c[i][0],c[i][1]);printf("%c", 2);
    }
}
void atualiza(){ // Atualiza a posição da cobrinha
    int i;
    gotoxy(c[pontos][0],c[pontos][1]);printf(" ");
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
    gotoxy(comida[0],comida[1]);printf("%c",174);
}

int jogo(){ //MECÂNICA DO JOGO
	int gameover=0;
	char tecla;
	
	for(int i=0;i<60;i++){//linha superior
		gotoxy(i,0);printf("%c", 351);
		Sleep(7);
	}
	for(int i=1;i<20;i++){//lado direito
		gotoxy(60,i);printf("%c", 124);
		Sleep(7);
	}
	for(int i=60;i>=0;i--){//linha inferior
		gotoxy(i,20);printf("%c", 351);
		Sleep(7);
	}
	for(int i=20;i>=0;i--){//lado esquerdo
		gotoxy(1,i);printf("%c", 124);
		Sleep(7);
	}
	//goto NOME
	gotoxy(22, 22);printf("PONTUACAO: %d", pontos);
	gotoxy(39,22);printf("NIVEL: --");
	geraComida();
	//desenha(); // Desenha a cobra
    tecla='d'; // A direção é para a direita
    while(gameover==0){ // Enquanto o usuário não perder
        c[0][0]=cx;
        c[0][1]=cy;
        if(kbhit()) // Se alguma tecla for apertada, o valor 
            tecla=getch(); // vai para a variável 'tecla'

        if(tecla=='w' || tecla=='W' || tecla==72){
            cy--;
            if(cy==0) break; // Se a cabeçaa da cobra estiver na parede superior,
        }                    // O jogo acaba
        if(tecla=='a' || tecla=='A' || tecla==75){
            cx--;
            if(cx==0) break; // Se a cabeça da cobra estiver na parede da esquerda,
        }                    // O Jogo acaba
        if(tecla=='s' || tecla=='S' || tecla==80){
            cy++;
            if(cy==20) break; // Se a cabeça da cobra estiver na parede de baixo,
        }                     // O jogo acaba
        if(tecla=='d' || tecla=='D' || tecla==77){
            cx++;
            if(cx>=60) break; // Se a a cabeça da cobra estiver na parede da direida,
        }                     // O jogo acaba

        if(cx==comida[0] && cy==comida[1]){ // Se a cobra comer a comida
            geraComida();
			pontos++;
            //if(velo>50) velo-=10; // Velocidade em milissegundos abaixa
        }
        gameover=analiza();
        atualiza(); // Atualiza a cobra
        desenha(); // Desenha a cobra
        gotoxy(50,20);
        Sleep(velocidade);//vai garantir que a movimentação vai ser de acordo com a velocidade escolhida.
    }
    //system("cls"); // Quando o usuário perder, limpa a tela e exibe uma mensagem final
    //printf("Voce perdeu! Fez %d pontos.\n",pontos);
    system("pause");
    return 0;
}
//----------------------------------------------------------------------------  
int main(){
	int opcao, tam=0;
	char nome[15], nome_sujo[5000];;
	do{
		system("cls");
		gotoxy(38,6);
		printf("J O G O\tD A\tC O B R I N H A");
		opcao = menu();
		switch(opcao){
			case 10:
				do{
	                system("cls");
	                gotoxy(30,15);printf("Digite seu nome: \n");
	                gotoxy(47,15); gets(nome);
	                gotoxy(47,15);gets(nome_sujo);
	                for(int i=0;i<15;i++)
	                tam=strlen(nome_sujo);
                   }while(tam>15);
	                for(int i=0;i<15;i++){
	                    nome[i]=nome_sujo[i];
	                    nome[i]=toupper(nome[i]);
	                }//*/
                system("cls");
                dificuldade();
                system("cls");
                //falta colocar o jogo!;
                jogo();              
                break;
            case 12:
            	system("cls");
            	rankings();
            	system("pause");
            	break;
            case 14: 
            	system("cls");
            	como_jogar();
            	system("pause");
            	break;
            case 16:
            	system("cls");
            	creditos();
            	system("pause");
            	break;
            default: 
				exit(0);
		}
	}while(opcao != 18);
	return 0;
}

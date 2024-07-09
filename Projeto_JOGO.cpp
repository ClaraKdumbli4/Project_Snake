#include<stdio.h>
#include<windows.h>
#include<conio2.h>
#include<stdlib.h>
#include<time.h>

int c[300][2], pontos=1, cx=2, cy=2;
int comida[2], velo=150;

void gotoxy(int x, int y){ // Função 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void desenha(){ // Desenha a cobrinha
    int i;
    for(i=0; i<pontos; i++){
        gotoxy(c[i][0],c[i][1]);
        printf("%c",219);
    }
}

void atualiza(){ // Atualiza a posição da cobrinha
    int i;
    gotoxy(c[pontos][0],c[pontos][1]);
    printf(" ");
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

    gotoxy(comida[0],comida[1]);
    printf(" ");
    srand(time(NULL));
    int randomX = xmin + rand() % (xmax - xmin + 1);//concertar o erro de gerar comida na borda.
	int randomY = ymin + rand() % (ymax - ymin + 1);//concertar o erro de gerar comida na borda.
	comida[0] = randomX;
    comida[1] = randomY;
    gotoxy(comida[0],comida[1]);
    printf("%c",169);
}

int main(){
	int gameover=0;
	char tecla;
	//Delimitação da área do mapa (bordas) em que a cobra poderá movimentar-se: (inicio)
	for(int i=0;i<60;i++){//linha superior
		gotoxy(i,0);
		printf("%c", 219);
		Sleep(7);
	}
	for(int i=0;i<20;i++){//lado direito
		gotoxy(60,i); 
		printf("%c", 219);
		Sleep(7);
	}
	for(int i=60;i>=0;i--){//linha inferior
		gotoxy(i,20);
		printf("%c", 219);
		Sleep(7);
	}
	for(int i=20;i>=0;i--){//lado esquerdo
		gotoxy(1,i);
		printf("%c", 219);
		Sleep(7);
	}//(fim da delimitação das bordas);
	//gotoxy(2,22);printf("%s", nome);
	gotoxy(22, 22);printf("PONTUACAO: %d", pontos);
	gotoxy(39,22);printf("NIVEL: --");
	
	
	geraComida(); // Gera a primeira comida
    desenha(); // Desenha a cobra
    tecla='d'; // A direção é para a direita
    while(gameover==0){ // Enquanto o usuário não perder
        c[0][0]=cx;
        c[0][1]=cy;
        if(kbhit()) // Se alguma tecla for apertada, o valor 
            tecla=getch(); // vai para a variável 'tecla'

        if(tecla=='w' || tecla=='W' || tecla==72){
            cy--;
            if(cy==0) break; // Se a cabeça da cobra estiver na parede superior,
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
            if(velo>50) velo-=10; // Velocidade em milissegundos abaixa
        }
        gameover=analiza();
        atualiza(); // Atualiza a cobra
        desenha(); // Desenha a cobra
        gotoxy(50,20);
        Sleep(velo);
    }
    gotoxy(30,10);printf("Voce perdeu! Fez %d pontos.\n",pontos);
    system("pause");
}

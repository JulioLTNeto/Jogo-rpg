#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX 30

typedef struct inimi{
    int id;
    int pX;
    int pY;
    int level;
}inimi;

int recebe() {
    char ch;
    struct termios oldt, newt;

    tcgetattr ( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

    return ch;
}

int main()
{
    char entrada = '1';
    int posicao[2];
    posicao[0] = 14;
    posicao[1] = 14;

    int existe = 0;
    //Atributos do persona
    int vida = 5;
    int forca = 2;
    int xp = 0;
    int nivel = 1;

    int pontuacao = 0;

    char tela[MAX][MAX];

    int v1 = 0;
    int v2 = 0;

    //Dados dos inimi
    inimi in[20];
    for(int cont = 0; cont < 20; cont++){
        in[cont].id = -1;
    }

    int totalIni = 0;
    int proximoInserir = 0;

    int tick = 0;

    while(entrada != '0'){

        if(!existe){
            v1 = rand()%29;
            while(v1 == 0){
                v1 = rand()%29;
            }
            v2 = rand()%29;
            while(v2 == 0){
                v2 = rand()%29;
            }
            tela[v1][v2] = '°';
            existe = 1;
        }

        if(tick >= 10){
            int po = rand()%100;
            if(po <= 20){
                int p2 = rand()%100;
                in[proximoInserir].id = proximoInserir;
                in[proximoInserir].pX = rand()%29;
                while(in[proximoInserir].pX == 0 || in[proximoInserir].pX == v1 || in[proximoInserir].pX == posicao[0]){
                    in[proximoInserir].pX = rand()%29;
                }

                in[proximoInserir].pY = rand()%29;
                while(in[proximoInserir].pY == 0 || in[proximoInserir].pY == v2 || in[proximoInserir].pY == posicao[1]){
                    in[proximoInserir].pY = rand()%29;
                }
                if(p2 >= 90){
                    in[proximoInserir].level = 5;
                }
                if(p2 < 90 && p2 >= 80){
                    in[proximoInserir].level = 4;
                }
                if(p2 >= 60 && p2 < 80){
                    in[proximoInserir].level = 3;
                }
                if(p2 >= 40 && p2 < 60){
                    in[proximoInserir].level = 2;
                }
                if(p2 < 40){
                    in[proximoInserir].level = 1;
                }
                tick = 0;
            }
            for(int cc = 0; cc < 20; cc++){
                if(in[cc].id == -1){
                    proximoInserir = cc;
                    break;
                }
            }
            totalIni++;
        }

        for(int cont = 0; cont < MAX; cont++){
            for(int cont2 = 0; cont2 < MAX; cont2++){

                int podeInserir = 1;
                int level = 0;
                if(cont != v1 || cont2 != v2){
                    for(int co = 0; co < 20; co++){
                        if(in[co].id != -1){
                            if(cont == in[co].pX && cont2 == in[co].pY){
                                podeInserir = 0;
                                level = in[co].level;
                            }
                        }
                    }
                    if(podeInserir){
                        tela[cont][cont2] = ' ';
                    }else{
                        if(level == 5){
                            tela[cont][cont2] = '5';
                        }
                        if(level == 4){
                            tela[cont][cont2] = '4';
                        }
                        if(level == 3){
                            tela[cont][cont2] = '3';
                        }
                        if(level == 2){
                            tela[cont][cont2] = '2';
                        }
                        if(level == 1){
                            tela[cont][cont2] = '1';
                        }
                    }
                }

                if((cont2 == 0) || (cont2 == MAX-1)){
                    tela[cont][cont2] = '|';
                }
                if((cont == 0) || (cont == MAX-1)){
                    tela[cont][cont2] = '-';
                }

                tela[posicao[0]][posicao[1]] = 'I';
                printf("%c", tela[cont][cont2]);
                if(cont2 == MAX-1){
                    if(cont == MAX/2){
                        printf("             PONTUAÇÃO: %i", pontuacao);
                    }
                    if(cont == (MAX/2)+1){
                        printf("             W: Cima");
                    }
                    if(cont == (MAX/2)-1){
                        printf("             VIDA: %i", vida);
                    }
                    if(cont == (MAX/2)-2){
                        printf("             LEVEL: %i", nivel);
                    }
                    if(cont == (MAX/2)-3){
                        printf("             FORCA: %i", forca);
                    }
                    if(cont == (MAX/2)-4){
                        printf("             EXPERIENCIA: %i", xp);
                    }
                    if(cont == (MAX/2)+2){
                        printf("             S: Baixo");
                    }
                    if(cont == (MAX/2)+3){
                        printf("             A: Direita");
                    }
                    if(cont == (MAX/2)+4){
                        printf("             D: Esquerda");
                    }
                    printf("\n");
                }
            }
        }

        if(vida <= 0){
                printf("Você perdeu!\n");
                break;
        }

        entrada = recebe();
        if(entrada == 'w'){
            if(posicao[0] <= 1){
            }else{
                posicao[0] = posicao[0]-1;
            }
        }
        if(entrada == 's'){
            if(posicao[0] >= 28){
            }else{
                posicao[0] = posicao[0]+1;
            }
        }
        if(entrada == 'a'){
            if(posicao[1] <= 1){
            }else{
                posicao[1] = posicao[1]-1;
            }
        }
        if(entrada == 'd'){
            if(posicao[1] >= 28){
            }else{
                posicao[1] = posicao[1]+1;
            }
        }

        int encontrou = 0;
        if(tela[posicao[0]][posicao[1]] == '1'){
            vida = vida - 2;
            encontrou = 1;
            xp = xp+10;
        }

        if(tela[posicao[0]][posicao[1]] == '2'){
            vida = vida - 4;
            encontrou = 1;
            xp = xp+40;
        }

        if(tela[posicao[0]][posicao[1]] == '3'){
            vida = vida - 6;
            encontrou = 1;
            xp = xp+80;
        }

        if(tela[posicao[0]][posicao[1]] == '4'){
            vida = vida - 8;
            encontrou = 1;
            xp = xp+140;
        }

        if(tela[posicao[0]][posicao[1]] == '5'){
            vida = vida - 10;
            encontrou = 1;
            xp = xp+200;
        }

        if(xp >= 0 && xp <= 100){
            nivel = 1;
        }
        if(xp > 100 && xp <= 400){
            nivel = 2;
        }
        if(xp > 400 && xp <= 800){
            nivel = 3;
        }
        if(xp > 800 &&  xp <= 1200){
            nivel = 4;
        }
        if(xp > 1200){
            nivel = 5;
        }

        if(encontrou){
            for(int cont = 0; cont < 20; cont++){
                if((posicao[0] == in[cont].pX) && (posicao[1] == in[cont].pY)){
                    in[cont].id = -1;
                    in[cont].pX = -30;
                    in[cont].pY = -30;
                }
            }
        }

        if(posicao[0] == v1 && posicao[1] == v2){
            pontuacao++;
            existe = 0;
            vida++;
        }
        system("clear");
        tick++;

    }
    printf("Obrigado por jogar\n");
    return 0;
}

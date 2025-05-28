// Leia o PDF ou MD antes de iniciar este exercício!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Variável GLOBAL para armazenar o valor de PI aproximado
double pi = 0.0;

// Função que gera um numero aleatorio uniformemente entre 0.0 e 1.0
// Você não deve alterar esta função
double random_zero_one() {
    return (double)random()/(double)RAND_MAX;
}

// Função que calcula o valor de pi por simulação (Monte Carlo)
// Você não deve alterar esta função
double aproxima_pi() {
    long dentro = 0;
    long total_pontos = 0;

    double x,y,d;
    while (1) {
        x = random_zero_one();
        y = random_zero_one();
        d = x*x + y*y;
        if (d<=1) {
            dentro++;
        }
        total_pontos++;
        pi = 4.0 * ((double)dentro/(double)total_pontos);
        if (random_zero_one() < 0.008) {
            sleep(1);
        }
    }
}

// Crie AQUI a função que exporta o valor de pi para um arquivo chamado pi.txt


void exporta_pi() {
    char buffer[64];
    int len = snprintf(buffer, sizeof(buffer), "%lf\n", pi);
    int fd = open("pi.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1) {
        write(fd, buffer, len);
        close(fd);
        fflush(stdout);
    } else {
        perror("Erro ao abrir o arquivo pi.txt");
    }
}
// Esta função deve ser chamada pelo handler quando este for acionado

// Crie AQUI a função que será o handler do sinal
void sigint_handler(int signum) {
    // Exibe o valor de pi
    printf("Valor aproximado de PI: %lf\n", pi);
    
    // Exporta o valor de pi para o arquivo pi.txt
    exporta_pi();
    
    // Finaliza o processo
    exit(0);
}

int main() {

    // Exiba o PID deste processo
    printf("PID do processo: %d\n", getpid());

    // Registre AQUI seu handler para o sinal SIGINT!
    signal(SIGINT, sigint_handler);


    srand(time(NULL));
    aproxima_pi();



    // Limpa o buffer de saída
    

    return 0;



}
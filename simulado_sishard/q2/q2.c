// Leia o PDF ou MD antes de iniciar este exercício!

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ret;
    int wst;

    do
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            // Processo filho: executa o siscoin
            execv("./siscoin", argv);
            perror("Erro ao executar siscoin");
            exit(-1);
        }
        else if (pid > 0)
        {
            // Processo pai: espera o filho terminar
            wait(&wst);

            if (WIFEXITED(wst))
            {
                ret = WEXITSTATUS(wst);
                if (ret == 0)
                {
                    printf("Transferência realizada com sucesso!\n");
                }
                else if (ret > 0 && ret <= 4)
                {
                    printf("Falha na rede. Tentando novamente...\n");
                }
                else
                {
                    fprintf(stderr, "Erro: parâmetros incorretos ou valor negativo.\n");
                    return -1;
                }
            }
            else
            {
                fprintf(stderr, "Erro: processo filho terminou de forma inesperada.\n");
                return -1;
            }
        }
        else
        {
            perror("Erro ao criar processo filho");
            return -1;
        }
    } while (ret > 0);

    return 0;
}
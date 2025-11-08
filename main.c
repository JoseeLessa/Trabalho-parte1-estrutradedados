#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "campeonato.h"
#include "utils.h"

int main() {

    BDTeams *bdt = (BDTeams *)malloc(sizeof(BDTeams));
    BDPartidas *bdp = (BDPartidas *)malloc(sizeof(BDPartidas));

    char teams_path[] = "times.csv";

    int f;

    printf("Qual arquivo deseja utilizar?\n");
    printf("1 - Completo | 2 - Parcial | 3 - Vazio\n");
    scanf("%d", &f);
    
    char matches_path[64];

    if (f==1) {
        strcpy(matches_path, "partidas_completo.csv");
    } else if (f==2) {
        strcpy(matches_path, "partidas_parcial.csv");
    } else {
        strcpy(matches_path, "partidas_vazio.csv");
    }

    printf("Carregando os times...\n");
    bdteams_load_csv(bdt, teams_path);
    printf("Times carregados: %d\n", bdt->n);

    printf("Carregando as partidas...\n");
    bdpartidas_load_csv(bdp, matches_path);
    printf("Partidas carregadas: %d\n", bdp->n);

    printf("Calculando as estatísticas...\n");
    bdpartidas_increase_in_team(bdp, bdt);

    
    char option[8];
    do {
        show_menu();
        fgets(option, sizeof(option), stdin);
        if (!fgets(option, sizeof(option), stdin)) break;
        option[strcspn(option, "\r\n")] = 0;

        switch (toupper(option[0])) {
            case '1':
                consult_team(bdt);
                break;
            case '2':
                consult_matches(bdp, bdt);
                break;
            case '6': 
                printf("\nTabela de classificação:\n");
                bdteams_print_table(bdt);
                break;
            case 'Q':
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção não aceita.\n");
                break;
        }
    } while (toupper(option[0]) != 'Q');

    free(bdp);
    free(bdt);

    return 0;
}
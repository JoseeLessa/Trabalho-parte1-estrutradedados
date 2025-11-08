#include "campeonato.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// ***** USER INTERFACE FUNCTIONS *****

// --- Show Menu Options ---
void show_menu() {
    printf("\n===================== ======================\n");
    printf("   Sistema de Gerenciamento de Partidas\n");
    printf("======================= ====================\n");
    printf("1 - Consultar time\n");
    printf("2 - Consultar partidas\n");
    printf("6 - Imprimir tabela de classificação\n"); 
    printf("Q - Sair\n");
    printf("Opção: ");
}

// --- Relative to Option 1 ---
void consult_team(BDTeams *bdt) {
    char prefix[128];
    printf("\nDigite o nome ou prefixo do time: ");
    if (!fgets(prefix, sizeof(prefix), stdin)) return;
    prefix[strcspn(prefix, "\r\n")] = 0;
    str_trim(prefix);

    if (prefix[0] == '\0') {
        printf("Prefixo vazio.\n");
        return;
    }

    int indices[64];
    int total = bdteams_search_by_prefix(bdt, prefix, indices, 64);
    if (total <= 0) {
        printf("Nenhum time encontrado para prefixo '%s'.\n", prefix);
        return;
    }

    // formato para as tabelinhas
    printf("\n| ID | Time                | V | E | D | GM | GS | S | PG |\n");
    printf("|----|---------------------|---|---|---|----|----|---|----|\n");

    for (int i = 0; i < total && i < 64; i++) {
        
        Team *t = &bdt->teams[indices[i]];
        printf("| %2d | %-19s | %d | %d | %d | %2d | %2d | %2d | %2d |\n",
               t->id, t->name, t->v, t->e, t->d, t->gm, t->gs,
              
               team_balance(t), team_points(t));
    }
}

// --- Relative to Option 2 ---
void consult_matches(const BDPartidas *bdp, const BDTeams *bdt) {
    char prefix[128];
    printf("\nDigite o nome ou prefixo do time: ");
    if (!fgets(prefix, sizeof(prefix), stdin)) return;
    prefix[strcspn(prefix, "\r\n")] = 0;
    str_trim(prefix);

    if (prefix[0] == '\0') {
        printf("Prefixo vazio.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < bdp->n; i++) {
        const Partida *m = &bdp->partidas[i];
        const Team *t1 = bdteams_search_by_id((BDTeams *)bdt, m->time1);
        const Team *t2 = bdteams_search_by_id((BDTeams *)bdt, m->time2);

        if (!t1 || !t2) continue;

        if (str_starts_with_case_insensitive(t1->name, prefix) ||
            str_starts_with_case_insensitive(t2->name, prefix)) {

            printf("%3d: %-15s %2d x %-2d %-15s\n",
                   m->id, t1->name, m->goals_time1, m->goals_time2, t2->name);
            found = 1;
        }
    }

    if (!found)
        printf("Nenhuma partida encontrada para '%s'.\n", prefix);
}

// ---  Relative to Option 6 ---
void bdteams_print_table(const BDTeams *bd){

    const int W_ID   = 3;
    const int W_TIME = 20;
    const int W_V    = 3, W_E = 3, W_D = 3, W_GM = 4, W_GS = 4, W_S = 4, W_PG = 4;

    printf("| "); print_utf8_padded("ID", W_ID);
    printf(" | "); print_utf8_padded("Time", W_TIME);
    printf(" | "); print_utf8_padded("V", W_V);
    printf(" | "); print_utf8_padded("E", W_E);
    printf(" | "); print_utf8_padded("D", W_D);
    printf(" | "); print_utf8_padded("GM", W_GM);
    printf(" | "); print_utf8_padded("GS", W_GS);
    printf(" | "); print_utf8_padded("S", W_S);
    printf(" | "); print_utf8_padded("PG", W_PG);
    printf(" |\n");

    printf("|-"); for (int i=0;i<W_ID;i++) putchar('-');
    printf("-|-"); for (int i=0;i<W_TIME;i++) putchar('-');
    printf("-|-"); for (int i=0;i<W_V;i++) putchar('-');
    printf("-|-"); for (int i=0;i<W_E;i++) putchar('-');
    printf("-|-"); for (int i=0;i<W_D;i++) putchar('-');
    printf("-|-"); for (int i=0;i<W_GM;i++) putchar('-');
    printf("-|-"); for (int i=0;i<W_GS;i++) putchar('-');
    printf("-|-"); for (int i=0;i<W_S;i++) putchar('-');
    printf("-|-"); for (int i=0;i<W_PG;i++) putchar('-');
    printf("-|\n");

    for (int id = 0; id < 10000; id++) {
        for (int i = 0; i < bd->n; i++) {
            if (bd->teams[i].id == id) {
                const Team *t = &bd->teams[i];
                char tmp[32];

                printf("| ");
                snprintf(tmp, sizeof(tmp), "%d", t->id);
                print_utf8_padded(tmp, W_ID);

                printf(" | ");
                print_utf8_padded(t->name, W_TIME);

                printf(" | ");
                snprintf(tmp, sizeof(tmp), "%d", t->v);
                print_utf8_padded(tmp, W_V);

                printf(" | ");
                snprintf(tmp, sizeof(tmp), "%d", t->e);
                print_utf8_padded(tmp, W_E);

                printf(" | ");
                snprintf(tmp, sizeof(tmp), "%d", t->d);
                print_utf8_padded(tmp, W_D);

                printf(" | ");
                snprintf(tmp, sizeof(tmp), "%d", t->gm);
                print_utf8_padded(tmp, W_GM);

                printf(" | ");
                snprintf(tmp, sizeof(tmp), "%d", t->gs);
                print_utf8_padded(tmp, W_GS);

                printf(" | ");
                snprintf(tmp, sizeof(tmp), "%d", team_balance(t));
                print_utf8_padded(tmp, W_S);

                printf(" | ");
                snprintf(tmp, sizeof(tmp), "%d", team_points(t));
                print_utf8_padded(tmp, W_PG);

                printf(" |\n");
            }
        }
    }
}



// ***** ARCHIVE LOADING FUNCTIONS *****

// ---  Loads from path to *BDTeams ---
void bdteams_load_csv(BDTeams *bd, const char path[]) { 
    FILE *file = fopen(path, "r");                  // Loads file from path

    if (file == NULL)                               // Verify file
    {
        printf("Error opening file\n");
        return;                                     // Return if error
    }
    
    int line_count = 0;
    char line[200];                                 // Sequence of non-blank characters
    
    fgets(line, 200, file);                         // Eliminate the header
    
    while (fgets(line, 200, file) != NULL)          // Returns line or NULL (if reach the end of file)
    {
        Team t;
        t = team_create();
        sscanf(line, "%d,%s", &t.id, t.name);       // Comma separated Values
        bd->teams[line_count++] = t;
    }
    
    bd->n = line_count;
    
    printf("\nTotal lines in the source code: %d\n", line_count);

    fclose(file);
}

// ---  Loads from path to *BDPartidas ---
void bdpartidas_load_csv(BDPartidas *bd, const char path[]) { 
    FILE *file = fopen(path, "r");                   // Loads file from path
    
    if (file == NULL)                                // Verify file
    {
        printf("Error opening file\n");
        return;                                      // Return if error
    }

    int line_count = 0;
    char line[200];                                  // sequence of non-blank characters
    
    fgets(line, 200, file);                          // Eliminate header
    
    while (fgets(line, 200, file) != NULL)           // returns line or NULL (if reach the end of file)
    {
        Partida p;
        sscanf(line, "%d,%d,%d,%d,%d",               // Comma separated Values
        &p.id, &p.time1, &p.time2, &p.goals_time1, &p.goals_time2);
        bd->partidas[line_count++] = p;
    }
    
    bd->n = line_count;
    
    printf("\nTotal lines in the source code: %d\n", line_count);

    fclose(file);
}



// ***** VAR INITIATION FUNCTIONS *****

// ---  allocate value to int n ---
void bdteams_start(BDTeams *bd){ // inicia vazio, acho que nao podia por nulo
    bd->n = 0;
}

// --- return a Team var with 0 in all values ---
Team team_create(){
    Team t;
    t.v = 0;   // victories
    t.e = 0;   // draws
    t.d = 0;   // losses
    t.gm = 0;
    t.gs = 0;
    
    return t;
}



// ***** SEARCH FUNCTIONS *****

// ---  Search using ID ---
Team* bdteams_search_by_id(BDTeams *bd, int id) { // vai fazer a busca de acordo com o ID do time
    for (int i = 0; i < bd->n; i++) {
        if (bd->teams[i].id == id) return &bd->teams[i];
    }
    return NULL;
}

// ---  Search using a prefix string (case-insensitive) ---
int bdteams_search_by_prefix(BDTeams *bd, const char *prefixo, int *indices, int max_indices){ //  semelhante a busca de id, mas funciona de acordo com o prefixo do time JAVA = JAVAlis etc
    int found = 0;
    for (int i = 0; i < bd->n; i++) {
        if (str_starts_with_case_insensitive(bd->teams[i].name, prefixo)) {
            if (found < max_indices) indices[found] = i;
            found++;
        }
    }
    return found;
}



// ***** OPERATIONAL FUNCTIONS *****

// --- set Team values to 0 ---
void team_reset_stats(Team *t){ 
    t->v = 0; t->e = 0; t->d = 0; t->gm = 0; t->gs = 0;
}

// --- Add values to goals and match result ---
void team_add_match(Team *t, int goals_scored, int goals_conceded) { // creio que nao tenha nada pra mexer aqui
    t->gm += goals_scored;
    t->gs += goals_conceded; 

    if (goals_scored > goals_conceded) {
        t->v++;
    } else if (goals_scored == goals_conceded) {
        t->e++;
    } else {
        t->d++;
    }
}

// --- Return total points made by a team ---
int team_points(const Team *t){     
    return t->v * 3 + t->e;
}

// --- Return team goal balance ---
int team_balance(const Team *t) {
    return t->gm - t->gs;
}



// ***** BD UPDATE FUNCTIONS *****

// --- Updates every team info in BDteams using all matches ---
void bdpartidas_increase_in_team(const BDPartidas *bdp, BDTeams *bdt) { // atualiza as estatísticas dos times
    for (int i = 0; i < bdp->n; i++) {
        const Partida *m = &bdp->partidas[i];
        Team *t1 = bdteams_search_by_id(bdt, m->time1);
        Team *t2 = bdteams_search_by_id(bdt, m->time2);

        if (!t1 || !t2) {
            fprintf(stderr, "Partida %d referencia time não encontrado (%d vs %d)\n",
                    m->id, m->time1, m->time2);
            continue;
        }

        team_add_match(t1, m->goals_time1, m->goals_time2);
        team_add_match(t2, m->goals_time2, m->goals_time1);
    }
}

// ***** STATIC FUNCTIONS *****

// --- Removes string's \n and \r ---
/*
static void chomp(char *s) { // essa função é pra remover o \n e \r do final da string, tive auxilio de um colega pra fazer e pensar nela
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) s[--n] = '\0';
}


static int parse_match_line(char *line, Partida *m) { // essa aqui le a estrtura e preenche os dados de acordo com as tabelas csv
    chomp(line);
    str_trim(line);
    char *tok = strtok(line, ",");
    if (!tok) return 0;
    if (!safe_atoi(tok, &m->id)) return 0;

    tok = strtok(NULL, ","); if (!tok) return 0;
    if (!safe_atoi(tok, &m->time1)) return 0;

    tok = strtok(NULL, ","); if (!tok) return 0;
    if (!safe_atoi(tok, &m->time2)) return 0;

    tok = strtok(NULL, ","); if (!tok) return 0;
    if (!safe_atoi(tok, &m->goals_time1)) return 0;

    tok = strtok(NULL, ","); if (!tok) return 0;
    if (!safe_atoi(tok, &m->goals_time2)) return 0;

    return 1;
}
*/



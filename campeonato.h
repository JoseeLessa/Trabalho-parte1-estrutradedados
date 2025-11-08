#ifndef CAMPEONATO_H
#define CAMPEONATO_H

// ***** STRUCTS DECLARATION *****

// --- TEAMS STRUCTS ---
// TAD Team info
typedef struct team {          
    int id;                    // Team ID int
    char name[64];             // Team name
    int v;                     // Victories
    int e;                     // Draws
    int d;                     // Losses
    int gm;                    // Goals scored
    int gs;                    // Goals conceded (scored é a palavra certa?)
} Team;

// TAD BDTeam
typedef struct bdteams {        
    Team teams[10];             // Array of Team
    int n;                      // Number of elements in Array
} BDTeams;

// --- MATCHES STRUCTS ---
// TAD Match info
typedef struct partida {        
    int id;                     // Match ID int
    int time1;                  // Team1 ID int
    int time2;                  // Team2 ID int
    int goals_time1;            // Team1 goals in match int
    int goals_time2;            // Team2 goals in match int
} Partida;

// TAD BDMatches
typedef struct bdpartidas {     
    Partida partidas[256];      // Array of Matchs
    int n;                      // Number of elements in Array
} BDPartidas;



// ***** USER INTERFACE FUNCTIONS *****

// --- Show Menu Options ---
void show_menu();

// --- Relative to Option 1 ---
void consult_team(BDTeams *bdt);

// --- Relative to Option 2 ---
void consult_matches(const BDPartidas *bdp, const BDTeams *bdt);

// ---  Relative to Option 6 ---
void bdteams_print_table(const BDTeams *bd);



// ***** ARCHIVE LOADING FUNCTIONS *****

// ---  Loads from path to *BDTeams ---
void bdteams_load_csv(BDTeams *bd, const char *path);

// ---  Loads from path to *BDPartidas ---
void bdpartidas_load_csv(BDPartidas *bd, const char *path);



// ***** VAR INITIATION FUNCTIONS *****

// ---  allocate value to int n ---
void bdteams_start(BDTeams *bd);

// --- return a Team var with 0 in all values ---
Team team_create();



// ***** SEARCH FUNCTIONS *****

// ---  Search using ID ---
Team* bdteams_search_by_id(BDTeams *bd, int id);

// ---  Search using a prefix string (case-insensitive) ---
int bdteams_search_by_prefix(BDTeams *bd, const char *prefix, int *indices, int max_indices);



// ***** OPERATION FUNCTIONS *****

// set Team values to 0
void team_reset_stats(Team *t);

// Add values to goals and match result
void team_add_match(Team *t, int goals_scored, int goals_conceded);

// Return total points made by a team
int team_points(const Team *t);

// Return team goal balance
int team_balance(const Team *t);



// ***** BD UPDATE FUNCTIONS *****

// Updates every team info in BDteams using all matches
void bdpartidas_increase_in_team(const BDPartidas *bdp, BDTeams *bdt);

#endif
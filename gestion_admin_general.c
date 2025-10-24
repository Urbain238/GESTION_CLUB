#include "gestion_club.h"

// Helper: declaration du fichier  en mode lecture
int file_exists(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f) { fclose(f); return 1; }
    return 0;
}

// Fonction pour generer un matricule unique à un admin commençant par "ADM" et se terminant par trois carractères numériques aleatoires
void generer_matricule_admin(char out[8]){
    int n = rand() % 9000 + 1000;
    snprintf(out, 8, "ADM%04d", n);
}

// Fonction pour ajouter admin
void ag_ajouter_admin(){
    Admin a;
    generer_matricule_admin(a.matricule);
    printf("Nom: "); fgets(a.nom, sizeof(a.nom), stdin); a.nom[strcspn(a.nom, "\n")] = 0;
    printf("Prenom: "); fgets(a.prenom, sizeof(a.prenom), stdin); a.prenom[strcspn(a.prenom, "\n")] = 0;
    printf("Username: "); fgets(a.username, sizeof(a.username), stdin); a.username[strcspn(a.username, "\n")] = 0;
    FILE *f = fopen(ADMIN_FILE, "a");
    if (!f) { perror("Erreur ouverture fichier admins"); return; }
    fprintf(f, "%s|%s|%s|%s\n", a.matricule, a.nom, a.prenom, a.username);
    fclose(f);
    printf("Admin ajouté. Matricule: %s\n", a.matricule);
}

// Fonction pour afficher tous les admins
void ag_afficher_tous_admins(){
    if (!file_exists(ADMIN_FILE)) { printf("Aucun admin enregistré.\n"); return; }
    FILE *f = fopen(ADMIN_FILE, "r");
    char line[MAX_LINE];
    printf("Liste des admins:\n");
    while (fgets(line, sizeof(line), f)){
        char *m = strtok(line, "|");
        char *nom = strtok(NULL, "|");
        char *prenom = strtok(NULL, "|");
        char *username = strtok(NULL, "\n");
        if (m && nom && prenom && username)
            printf("%s - %s %s (%s)\n", m, nom, prenom, username);
    }
    fclose(f);
}

// Fonction pour rechercher admin par matricule
void ag_rechercher_admin_par_matricule(){
    char mat[16];
    printf("Entrer matricule: "); fgets(mat, sizeof(mat), stdin); mat[strcspn(mat, "\n")] = 0;
    if (!file_exists(ADMIN_FILE)) { printf("Aucun admin enregistré.\n"); return; }
    FILE *f = fopen(ADMIN_FILE, "r");
    char line[MAX_LINE];
    int found = 0;
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        if (m && strcmp(m, mat)==0){
            char *nom = strtok(NULL, "|");
            char *prenom = strtok(NULL, "|");
            char *username = strtok(NULL, "\n");
            printf("Trouvé: %s - %s %s (%s)\n", m, nom, prenom, username);
            found = 1; break;
        }
    }
    if (!found) printf("Non trouvé.\n");
    fclose(f);
}

// Fonction pour supprimer admin
void ag_supprimer_admin(){
    char mat[16];
    printf("Entrer matricule à supprimer: "); fgets(mat, sizeof(mat), stdin); mat[strcspn(mat, "\n")] = 0;
    if (!file_exists(ADMIN_FILE)) { printf("Aucun admin enregistré.\n"); return; }
    FILE *f = fopen(ADMIN_FILE, "r");
    FILE *tmp = fopen("tmp_admins.txt", "w");
    char line[MAX_LINE];
    int found = 0;
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        if (m && strcmp(m, mat)==0) { found = 1; continue; }
        fputs(line, tmp);
    }
    fclose(f); fclose(tmp);
    if (found) {
        remove(ADMIN_FILE);
        rename("tmp_admins.txt", ADMIN_FILE);
        printf("Admin supprimé.\n");
    } else {
        remove("tmp_admins.txt");
        printf("Matricule introuvable.\n");
    }
}

// Fonction pour modifier admin (par matricule)
void ag_modifier_admin(){
    char mat[16];
    printf("Entrer matricule à modifier: "); fgets(mat, sizeof(mat), stdin); mat[strcspn(mat, "\n")] = 0;
    if (!file_exists(ADMIN_FILE)) { printf("Aucun admin enregistré.\n"); return; }
    FILE *f = fopen(ADMIN_FILE, "r");
    FILE *tmp = fopen("tmp_admins.txt", "w");
    char line[MAX_LINE];
    int found = 0;
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        char *nom = strtok(NULL, "|");
        char *prenom = strtok(NULL, "|");
        char *username = strtok(NULL, "\n");
        if (m && strcmp(m, mat)==0){
            found = 1;
            Admin a;
            strcpy(a.matricule, m);
            printf("Nouveau nom: "); fgets(a.nom, sizeof(a.nom), stdin); a.nom[strcspn(a.nom, "\n")] = 0;
            printf("Nouveau prenom: "); fgets(a.prenom, sizeof(a.prenom), stdin); a.prenom[strcspn(a.prenom, "\n")] = 0;
            printf("Nouveau username: "); fgets(a.username, sizeof(a.username), stdin); a.username[strcspn(a.username, "\n")] = 0;
            fprintf(tmp, "%s|%s|%s|%s\n", a.matricule, a.nom, a.prenom, a.username);
        } else {
            fputs(line, tmp);
        }
    }
    fclose(f); fclose(tmp);
    if (found){ remove(ADMIN_FILE); rename("tmp_admins.txt", ADMIN_FILE); printf("Admin modifié.\n"); }
    else { remove("tmp_admins.txt"); printf("Matricule introuvable.\n"); }
}

// Fonction pour la connexion admin général : on vérifie existence username+matricule
int ag_connexion(const char *username, const char *matricule){
    if (!file_exists(ADMIN_FILE)) return 0;
    FILE *f = fopen(ADMIN_FILE, "r");
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        char *nom = strtok(NULL, "|");
        char *prenom = strtok(NULL, "|");
        char *user = strtok(NULL, "\n");
        if (m && user && strcmp(matricule, m)==0 && strcmp(username, user)==0){ fclose(f); return 1; }
    }
    fclose(f); return 0;
}

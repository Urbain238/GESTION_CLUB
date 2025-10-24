#include "gestion_club.h"

// Fonction pour la génération matricule utilisateur : USE + 4 chiffres
void generer_matricule_user(char out[8]){
    int n = rand() % 9000 + 1000;
    snprintf(out, 8, "USE%04d", n);
}

// Fonction pour ajouter utilisateur
void a_ajouter_utilisateur(){
    Utilisateur u;
    generer_matricule_user(u.matricule);
    printf("Nom: "); 
    fgets(u.nom, sizeof(u.nom), stdin); 
    u.nom[strcspn(u.nom, "\n")] = 0;
    printf("Prenom: "); 
    fgets(u.prenom, sizeof(u.prenom), stdin); 
    u.prenom[strcspn(u.prenom, "\n")] = 0;
    printf("Username: "); 
    fgets(u.username, sizeof(u.username), stdin); 
    u.username[strcspn(u.username, "\n")] = 0;
    u.montantCotisation = 0.0f;
    strcpy(u.typeCotisation, "Aucun");
    strcpy(u.statut, "Non");
    FILE *f = fopen(USER_FILE, "a");
    if (!f) { perror("Erreur ouverture fichier users"); return; }
    fprintf(f, "%s|%s|%s|%s|%.2f|%s|%s\n", u.matricule, u.nom, u.prenom, u.username, u.montantCotisation, u.typeCotisation, u.statut);
    fclose(f);
    printf("Utilisateur ajouté. Matricule: %s\n", u.matricule);
}

// Fonction pour afficher tous les utilisateurs
void a_afficher_tous_utilisateurs(){
    if (!file_exists(USER_FILE)) { printf("Aucun utilisateur.\n"); return; }
    FILE *f = fopen(USER_FILE, "r");
    char line[MAX_LINE];
    printf("Liste des utilisateurs:\n");
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        char *nom = strtok(NULL, "|");
        char *prenom = strtok(NULL, "|");
        char *user = strtok(NULL, "|");
        char *mont = strtok(NULL, "|");
        char *type = strtok(NULL, "|");
        char *stat = strtok(NULL, "\n");
        if (m && nom && prenom && user && mont && type && stat)
            printf("%s - %s %s (%s) Montant: %s Type: %s Statut: %s\n", m, nom, prenom, user, mont, type, stat);
    }
    fclose(f);
}

// Fonction pour rechercher utilisateur par matricule
void a_rechercher_utilisateur_par_matricule(){
    char mat[16];
    printf("Entrer matricule: "); 
    fgets(mat, sizeof(mat), stdin); 
    mat[strcspn(mat, "\n")] = 0;
    if (!file_exists(USER_FILE)) { 
    printf("Aucun utilisateur.\n"); 
    return; 
    	}
    FILE *f = fopen(USER_FILE, "r");
    char line[MAX_LINE]; int found=0;
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        if (m && strcmp(m, mat)==0){
            char *nom = strtok(NULL, "|");
            char *prenom = strtok(NULL, "|");
            char *user = strtok(NULL, "|");
            char *mont = strtok(NULL, "|");
            char *type = strtok(NULL, "|");
            char *stat = strtok(NULL, "\n");
            printf("%s - %s %s (%s) Montant: %s Type: %s Statut: %s\n", m, nom, prenom, user, mont, type, stat);
            found=1; 
            break;
        }
    }
    if (!found) printf("Non trouvé.\n");
    fclose(f);
}

// Fonction pour supprimer utilisateur
void a_supprimer_utilisateur(){
    char mat[16];
    printf("Entrer matricule à supprimer: "); 
    fgets(mat, sizeof(mat), stdin); 
    mat[strcspn(mat, "\n")] = 0;
    if (!file_exists(USER_FILE)) { printf("Aucun utilisateur.\n"); 
    return; 
    	}
    FILE *f = fopen(USER_FILE, "r");
    FILE *tmp = fopen("tmp_users.txt", "w");
    char line[MAX_LINE]; int found=0;
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        if (m && strcmp(m, mat)==0) { found=1; 
        continue; 
        }
        fputs(line, tmp);
    }
    fclose(f); 
    fclose(tmp);
    if (found){ 
    remove(USER_FILE); 
    rename("tmp_users.txt", USER_FILE); 
    printf("Utilisateur supprimé.\n"); 
    }else { 
    remove("tmp_users.txt"); 
    printf("Matricule introuvable.\n"); 
    }
}

// Fonction pour modifier utilisateur (par matricule)
void a_modifier_utilisateur(){
    char mat[16];
    printf("Entrer matricule à modifier: "); 
    fgets(mat, sizeof(mat), stdin); 
    mat[strcspn(mat, "\n")] = 0;
    if (!file_exists(USER_FILE)) { 
    printf("Aucun utilisateur.\n"); 
    return; 
    }
    FILE *f = fopen(USER_FILE, "r");
    FILE *tmp = fopen("tmp_users.txt", "w");
    char line[MAX_LINE]; int found=0;
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        char *nom = strtok(NULL, "|");
        char *prenom = strtok(NULL, "|");
        char *user = strtok(NULL, "|");
        char *mont = strtok(NULL, "|");
        char *type = strtok(NULL, "|");
        char *stat = strtok(NULL, "\n");
        if (m && strcmp(m, mat)==0){
            found=1;
            Utilisateur u;
            strcpy(u.matricule, m);
            printf("Nouveau nom: "); 
            fgets(u.nom, sizeof(u.nom), stdin); 
            u.nom[strcspn(u.nom, "\n")] = 0;
            printf("Nouveau prenom: "); 
            fgets(u.prenom, sizeof(u.prenom), stdin); 
            u.prenom[strcspn(u.prenom, "\n")] = 0;
            printf("Nouveau username: "); 
            fgets(u.username, sizeof(u.username), stdin); 
            u.username[strcspn(u.username, "\n")] = 0;
            printf("Montant cotisation actuel (%.2f). Entrer nouveau montant ou 0 pour garder: ", atof(mont));
            float newmont; 
            if (scanf("%f", &newmont)==1){ 
            u.montantCotisation = newmont; 
            while(getchar()!= '\n'); 
            } else { 
            u.montantCotisation = atof(mont); 
            while(getchar()!= '\n'); 
            }
            printf("Type de cotisation: "); 
            fgets(u.typeCotisation, sizeof(u.typeCotisation), stdin); 
            u.typeCotisation[strcspn(u.typeCotisation, "\n")] = 0;
            printf("Statut (Entièrement/Partiellement/Non): "); 
            fgets(u.statut, sizeof(u.statut), stdin); u.statut[strcspn(u.statut, "\n")] = 0;
            fprintf(tmp, "%s|%s|%s|%s|%.2f|%s|%s\n", u.matricule, u.nom, u.prenom, u.username, u.montantCotisation, u.typeCotisation, u.statut);
        } else {
            fputs(line, tmp);
        }
    }
    fclose(f); 
    fclose(tmp);
    if (found){ 
    remove(USER_FILE); 
    rename("tmp_users.txt", USER_FILE); 
    printf("Utilisateur modifié.\n"); 
    }
    else { 
    remove("tmp_users.txt"); 
    printf("Matricule introuvable.\n"); 
    }
}

// Fonction pour consulter matricule(s) par nom (affiche tous les noms similaires)
void a_consulter_matricule_par_nom(){
    char nomsearch[64];
    printf("Entrer nom (ou prefixe) : "); 
    fgets(nomsearch, sizeof(nomsearch), stdin); 
    nomsearch[strcspn(nomsearch, "\n")] = 0;
    if (!file_exists(USER_FILE)) { printf("Aucun utilisateur.\n"); 
    return; 
    }
    FILE *f = fopen(USER_FILE, "r");
    char line[MAX_LINE]; int found=0;
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        char *nom = strtok(NULL, "|");
        char *prenom = strtok(NULL, "|");
        char *user = strtok(NULL, "|");
        if (m && nom && strncmp(nom, nomsearch, strlen(nomsearch))==0){
            printf("%s - %s %s (%s)\n", m, nom, prenom, user);
            found=1;
        }
    }
    if (!found) printf("Aucun résultat.\n");
    fclose(f);
}

// Fonction pour afficher utilisateurs par statut
void a_afficher_utilisateurs_par_statut(){
    char statsearch[32];
    printf("Entrer statut à filtrer (Entièrement/Partiellement/Non) : "); 
    fgets(statsearch, sizeof(statsearch), stdin); statsearch[strcspn(statsearch, "\n")] = 0;
    if (!file_exists(USER_FILE)) { printf("Aucun utilisateur.\n"); return; }
    FILE *f = fopen(USER_FILE, "r");
    char line[MAX_LINE]; int found=0;
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        char *nom = strtok(NULL, "|");
        char *prenom = strtok(NULL, "|");
        char *user = strtok(NULL, "|");
        char *mont = strtok(NULL, "|");
        char *type = strtok(NULL, "|");
        char *stat = strtok(NULL, "\n");
        if (stat && strcmp(stat, statsearch)==0){
            printf("%s - %s %s (%s) Montant: %s Type: %s Statut: %s\n", m, nom, prenom, user, mont, type, stat);
            found=1;
        }
    }
    if (!found) printf("Aucun utilisateur avec ce statut.\n");
    fclose(f);
}

// Fonction pour connexion admin simple : username+matricule existants
int a_connexion(const char *username, const char *matricule){
    if (!file_exists(ADMIN_FILE)) 
    return 0;
    FILE *f = fopen(ADMIN_FILE, "r");
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        char *nom = strtok(NULL, "|");
        char *prenom = strtok(NULL, "|");
        char *user = strtok(NULL, "\n");
        if (m && user && strcmp(matricule, m)==0 && strcmp(username, user)==0){ fclose(f); 
        return 1; 
        }
    }
    fclose(f); 
    return 0;
}

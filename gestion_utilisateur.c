#include "gestion_club.h"

// Fonction pour vérification de connexion utilisateur

int utilisateur_connexion(const char *username, const char *matricule){
    if (!file_exists(USER_FILE)) 
    return 0;
    FILE *f = fopen(USER_FILE, "r");
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)){
        char copy[MAX_LINE]; strcpy(copy, line);
        char *m = strtok(copy, "|");
        char *nom = strtok(NULL, "|");
        char *prenom = strtok(NULL, "|");
        char *user = strtok(NULL, "|");
        if (m && user && strcmp(matricule, m)==0 && strcmp(username, user)==0){ 
        fclose(f); 
        return 1; 
        }
    }
    fclose(f); 
    return 0;
}

// Fonction pour consulter statut
void u_consulter_statut(const char *matricule){
    if (!file_exists(USER_FILE)) { 
    printf("Aucun utilisateur.\n"); 
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
        char *mont = strtok(NULL, "|");
        char *type = strtok(NULL, "|");
        char *stat = strtok(NULL, "\n");
        if (m && strcmp(m, matricule)==0){
            printf("Matricule: %s\nNom: %s %s\nUsername: %s\nMontant: %s\nType: %s\nStatut: %s\n", m, nom, prenom, user, mont, type, stat);
            found=1; 
            break;
        }
    }
    if (!found) printf("Profil non trouvé.\n");
    fclose(f);
}

// Fonction pour ajouter montant de cotisation (modifie l'enregistrement utilisateur)
void u_ajouter_cotisation(const char *matricule){
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
        if (m && strcmp(m, matricule)==0){
            found=1;
            Utilisateur u;
            strcpy(u.matricule, m);
            strcpy(u.nom, nom);
            strcpy(u.prenom, prenom);
            strcpy(u.username, user);
            u.montantCotisation = atof(mont);
            strcpy(u.typeCotisation, type);
            strcpy(u.statut, stat);
            printf("Montant actuel: %.2f\nEntrer montant à ajouter: ", u.montantCotisation);
            float add; if (scanf("%f", &add)==1) { 
            u.montantCotisation += add; 
            while(getchar()!= '\n'); 
            } else { 
            printf("Montant invalide.\n"); 
            while(getchar()!= '\n'); 
            }
            
            // Fonction pour la mise à jour du statut (exemple simple): si montant>0 mais <100 => Partiellement, >=100 => Entièrement
            
            if (u.montantCotisation <= 0.0f) strcpy(u.statut, "Non");
            else if (u.montantCotisation < 100.0f) strcpy(u.statut, "Partiellement");
            else strcpy(u.statut, "Entièrement");
            printf("Entrer type de cotisation (ex: Mensuelle/Annuelle): "); 
            fgets(u.typeCotisation, sizeof(u.typeCotisation), stdin); 
            u.typeCotisation[strcspn(u.typeCotisation, "\n")] = 0;
            fprintf(tmp, "%s|%s|%s|%s|%.2f|%s|%s\n", u.matricule, u.nom, u.prenom, u.username, u.montantCotisation, u.typeCotisation, u.statut);
        } else {
            fputs(line, tmp);
        }
    }
    fclose(f); fclose(tmp);
    if (found){ remove(USER_FILE); 
    rename("tmp_users.txt", USER_FILE); 
    printf("Cotisation ajoutée et profil mis à jour.\n"); 
    }
    else { 
    remove("tmp_users.txt"); 
    printf("Profil introuvable.\n"); 
    }
}

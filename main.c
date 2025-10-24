// déclaration de la bibliotheque des fonctions
#include "gestion_club.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Fonctions pour initialiser un admin
void initialiser_super_admin() {
    FILE *f = fopen("admins.txt", "r");
    if (f == NULL) {
        // Le fichier n'existe pas, on le crée avec un admin général par défaut
        f = fopen("admins.txt", "w");
        if (f != NULL) {
            fprintf(f, "ADM0001 Admin General admin\n");
            fclose(f);
            printf("\n✅ Fichier 'admins.txt' créé avec un super admin par défaut :\n");
            printf("   Nom d'utilisateur : admin\n");
            printf("   Matricule : ADM0001\n\n");
        } else {
            printf("❌ Erreur : impossible de créer le fichier 'admins.txt'.\n");
        }
    } else {
        fclose(f);
    }
}

void menu_admin_general();
void menu_admin();
void menu_utilisateur();

int main() {
initialiser_super_admin();
    srand((unsigned int)time(NULL));
    int choix;
    do {
        system("clear||cls");
        printf("******************** MENU ********************\n");
        printf("1. ADMIN GÉNÉRAL\n");
        printf("2. ADMIN\n");
        printf("3. UTILISATEUR\n");
        printf("0. Quitter\n");
        printf("Choix: ");
        if (scanf("%d", &choix) != 1) { 
        while(getchar()!= '\n'); 
        choix = -1; 
        }
        while(getchar()!= '\n');
        switch(choix) {
            case 1: 
            menu_admin_general(); 
            break;
            case 2: 
            menu_admin(); 
            break;
            case 3: 
            menu_utilisateur(); 
            break;
            case 0: 
            printf("Au revoir!\n"); 
            break;
            default: 
            printf("Choix invalide!\n"); 
            break;
        }
        if (choix != 0) { 
        printf("Appuyez sur Entrée pour continuer..."); 
        getchar(); 
        }
    } while(choix != 0);
    return 0;
}

void menu_admin_general() {
    char username[50], matricule[16];
    printf("--- Connexion ADMIN GÉNÉRAL ---\n");
    printf("Entrer votre nom d'utilisateur: "); 
    fgets(username, sizeof(username), stdin); 
    username[strcspn(username, "\n")] = 0;
    printf("Entrer votre matricule: "); 
    fgets(matricule, sizeof(matricule), stdin); 
    matricule[strcspn(matricule, "\n")] = 0;
    if (!ag_connexion(username, matricule)) { 
    printf("Connexion échouée!\n"); 
    return; 
    }
    int c;
    do {
        system("clear||cls");
        printf("===== MENU ADMIN GÉNÉRAL =====\n");
        printf("1. AJOUTER UN ADMIN\n");
        printf("2. MODIFIER UN ADMIN\n");
        printf("3. SUPPRIMER UN ADMIN\n");
        printf("4. AFFICHER TOUT LES ADMINS\n");
        printf("5. RECHERCHER UN ADMIN PAR MATRICULE\n");
        printf("0. Retour\n");
        printf("Choix: "); 
        if (scanf("%d", &c)!=1){ 
        while(getchar()!= '\n'); 
        c=-1; 
        }
        while(getchar()!= '\n');
        switch(c){
            case 1: 
            ag_ajouter_admin(); 
            break;
            case 2: 
            ag_modifier_admin(); 
            break;
            case 3: 
            ag_supprimer_admin(); 
            break;
            case 4: 
            ag_afficher_tous_admins(); 
            break;
            case 5: 
            ag_rechercher_admin_par_matricule(); 
            break;
            case 0: 
            break;
            default: 
            printf("Choix invalid !\n"); 
            break;
        }
        if (c!=0) { 
        printf("Appuyez sur Entrée..."); 
        getchar(); 
        }
    } while(c!=0);
}

void menu_admin() {
    char username[50], matricule[16];
    printf("--- Connexion ADMIN ---\n");
    printf("Entrer votre nom d'utilisateur: "); 
    fgets(username, sizeof(username), stdin); 
    username[strcspn(username, "\n")] = 0;
    printf("Entrer votre matricule: "); 
    fgets(matricule, sizeof(matricule), stdin); 
    matricule[strcspn(matricule, "\n")] = 0;
    if (!a_connexion(username, matricule)) { 
    printf("Connexion échouée!\n"); 
    return; 
    }
    int c;
    do {
        system("clear||cls");
        printf("===== MENU ADMIN =====\n");
        printf("1. CONSULTER LE MATRICULE\n");
        printf("2. AJOUTER UN UTILISATEUR\n");
        printf("3. MODIFIER UN UTILISATEUR\n");
        printf("4. SUPPRIMER UN UTILISATEUR\n");
        printf("5. AFFICHER TOUT LES UTILISATEURS\n");
        printf("6. RECHERCHER UN UTILISATEUR\n");
        printf("7. AFFICHER LES UTILISATEURS PAR STATUT DE COTISATION\n");
        printf("0. Retour\n");
        printf("Choix: "); 
        if (scanf("%d", &c)!=1){ 
        while(getchar()!= '\n'); 
        c=-1; 
        }
        while(getchar()!= '\n');
        switch(c){
            case 1: 
            a_consulter_matricule_par_nom(); 
            break;
            case 2: 
            a_ajouter_utilisateur(); 
            break;
            case 3: 
            a_modifier_utilisateur(); 
            break;
            case 4: 
            a_supprimer_utilisateur(); 
            break;
            case 5: 
            a_afficher_tous_utilisateurs(); 
            break;
            case 6: 
            a_rechercher_utilisateur_par_matricule(); break;
            case 7: 
            a_afficher_utilisateurs_par_statut(); break;
            case 0: 
            break;
            default: 
            printf("Choix invalide!\n"); break;
        }
        if (c!=0) { 
        printf("Appuyez sur Entrée..."); 
        getchar(); 
        }
    } while(c!=0);
}

void menu_utilisateur() {
    char username[50], matricule[16];
    printf("--- Connexion UTILISATEUR ---\n");
    printf("Entrer votre nom d'utilisateur: "); 
    fgets(username, sizeof(username), stdin); 
    username[strcspn(username, "\n")] = 0;
    printf("Entrer votre matricule: "); 
    fgets(matricule, sizeof(matricule), stdin); 
    matricule[strcspn(matricule, "\n")] = 0;
    if (!utilisateur_connexion(username, matricule)) { 
    printf("Connexion échouée!\n"); 
    return; 
    }
    int c;
    do {
        system("clear||cls");
        printf("===== MENU UTILISATEUR =====\n");
        printf("1. CONSULTER MON STATUT DE COTISATION\n");
        printf("2. AJOUTER UN MONTANT DE COTISATION\n");
        printf("0. Retour\n");
        printf("Choix: "); 
        if (scanf("%d", &c)!=1){ 
        while(getchar()!= '\n'); 
        c=-1; 
        }
        while(getchar()!= '\n');
        char mat[8]; 
        strncpy(mat, matricule, 8); 
        mat[7]='\0';
        switch(c){
            case 1: 
            u_consulter_statut(matricule); 
            break;
            case 2: 
            u_ajouter_cotisation(matricule); 
            break;
            case 0: 
            break;
            default: 
            printf("Choix invalide!\n"); 
            break;
        }
        if (c!=0) { 
        printf("Appuyez sur Entrée..."); 
        getchar(); }
    } while(c!=0);
}

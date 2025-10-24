// definition de la bibliotheque
#ifndef GESTION_CLUB_H
#define GESTION_CLUB_H

// definition des bibliotheques standards
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// declaration des fichiers textes à utiliser dans les fonctions
#define ADMIN_FILE "admins.txt"
#define USER_FILE  "users.txt"

#define MAX_LINE 512

// declaration structures pour les admins
typedef struct {
    char matricule[8];   // appelle la fonction pour generer le matricule
    char nom[30];
    char prenom[30];
    char username[30];
} Admin;

// declaration structures pour les utilisateurs
typedef struct {
    char matricule[8];   // appelle la fonction pour generer les matricules
    char nom[30];
    char prenom[30];
    char username[30];
    float montantCotisation;
    char typeCotisation[30];
    char statut[20]; // "Entièrement", "Partiellement", "Non"
} Utilisateur;

// Prototypes - admin general
void ag_ajouter_admin();
void ag_modifier_admin();
void ag_supprimer_admin();
void ag_afficher_tous_admins();
void ag_rechercher_admin_par_matricule();
int ag_connexion(const char *username, const char *matricule);

// Prototypes - admin simple
int a_connexion(const char *username, const char *matricule);
void a_consulter_matricule_par_nom();
void a_ajouter_utilisateur();
void a_modifier_utilisateur();
void a_supprimer_utilisateur();
void a_afficher_tous_utilisateurs();
void a_rechercher_utilisateur_par_matricule();
void a_afficher_utilisateurs_par_statut();

// Prototypes - utilisateur
int utilisateur_connexion(const char *username, const char *matricule);
void u_consulter_statut(const char *matricule);
void u_ajouter_cotisation(const char *matricule);

// Utilitaires
void generer_matricule_admin(char out[8]);
void generer_matricule_user(char out[8]);
int file_exists(const char *filename);

#endif // GESTION_CLUB_H

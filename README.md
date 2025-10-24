***************************************
## PROJET PERSONNEL DE GESTION D'UN CLUB EN C
**************************************
### 🧩 DESCRIPTION DU PROJET 

L’application GESTION_CLUB est un programme en langage C conçu pour assurer la gestion complète d’un club à travers une interface en console. Elle repose sur une organisation hiérarchique composée d’un administrateur général, d’administrateurs et d’utilisateurs.

L’administrateur général représente le responsable principal du système. Il gère les administrateurs en pouvant les ajouter, les modifier, les supprimer ou les consulter. Les administrateurs, quant à eux, assurent la gestion des membres du club en effectuant des opérations comme l’ajout, la modification, la suppression ou la recherche d’utilisateurs. Enfin, les utilisateurs sont les membres du club qui peuvent se connecter, consulter leur statut de cotisation et effectuer des versements.

Toutes les informations sont enregistrées dans des fichiers texte afin d’assurer la persistance des données. Le projet illustre ainsi la mise en œuvre d’une programmation modulaire en C appliquée à un système de gestion simple, structuré et fonctionnel.
**************************************
### 🧩 DESCRIPTION DES FONCTIONNALITÉS 
**************************************
#### 1. ADMINISTRATEUR GÉNÉRAL
L'administrateur général dans cette application est celui qui a le plus de pouvoir il aura les droit suivant 

#### a. 🔐 Authentification de l’administrateur général

Cette fonctionnalité permet à l’administrateur général d’accéder à son espace sécurisé dans le logiciel.
L’authentification se fait à partir de son nom d’utilisateur et de son matricule enregistrés dans un fichier (super_admin.txt).
Le programme vérifie la correspondance des informations saisies avec celles présentes dans le fichier avant de donner accès au menu de gestion.
En cas d’erreur, un message indique que la connexion a échoué.

🧠 Principe de fonctionnement

Lors du lancement du programme, l’administrateur général choisit l’option correspondante dans le menu principal.
Le système lui demande ensuite de saisir son nom d’utilisateur et son matricule.
Les données sont comparées ligne par ligne à celles contenues dans le fichier super_admin.txt.
Si les deux informations correspondent, la connexion est validée et le menu de l’administrateur général s’affiche.

💻 Code en C

'''
#include <stdio.h>
#include <string.h>

// Fonction d’authentification de l’administrateur général
int ag_connexion() {
    char username[50], matricule[10];
    char file_username[50], file_matricule[10];
    FILE *f = fopen("super_admin.txt", "r");

    if (f == NULL) {
        printf("\n[ERREUR] Fichier super_admin.txt introuvable.\n");
        return 0;
    }

    printf("\n=== CONNEXION ADMINISTRATEUR GENERAL ===\n");
    printf("Nom d'utilisateur : ");
    scanf("%s", username);
    printf("Matricule : ");
    scanf("%s", matricule);

    // Lecture du fichier et comparaison
    while (fscanf(f, "%s %s", file_username, file_matricule) != EOF) {
        if (strcmp(username, file_username) == 0 && strcmp(matricule, file_matricule) == 0) {
            fclose(f);
            printf("\n[SUCCÈS] Connexion réussie !\n");
            return 1; // Connexion réussie
        }
    }

    fclose(f);
    printf("\n[ÉCHEC] Nom d'utilisateur ou matricule incorrect.\n");
    return 0; // Connexion échouée
}
'''
🗂️ Exemple de contenu du fichier super_admin.txt

admin_general ADM0002

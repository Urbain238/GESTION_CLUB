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

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ag_connexion() {
    char username[50], matricule[10];
    char file_username[50], file_matricule[10];
    FILE *f;

    // Ouverture du fichier contenant les informations du super admin
    f = fopen("super_admin.txt", "r");
    if (f == NULL) {
        printf("\n[ERREUR] Le fichier 'super_admin.txt' est introuvable.\n");
        printf("Veuillez d'abord initialiser le super administrateur.\n");
        return 0;
    }

    printf("\n============================\n");
    printf("   CONNEXION ADMIN GÉNÉRAL  \n");
    printf("============================\n");

    printf("Nom d'utilisateur : ");
    scanf("%s", username);
    printf("Matricule : ");
    scanf("%s", matricule);

    // Lecture ligne par ligne du fichier pour vérifier les identifiants
    int trouve = 0;
    while (fscanf(f, "%s %s", file_username, file_matricule) != EOF) {
        if (strcmp(username, file_username) == 0 && strcmp(matricule, file_matricule) == 0) {
            trouve = 1;
            break;
        }
    }
    fclose(f);

    if (trouve) {
        printf("\n[SUCCÈS] Connexion réussie ! Bienvenue %s.\n", username);
        return 1;
    } else {
        printf("\n[ÉCHEC] Nom d'utilisateur ou matricule incorrect.\n");
        return 0;
    }
}

int main() {
    // Exemple de test
    if (ag_connexion()) {
        printf("\nAccès au menu de l'administrateur général...\n");
    } else {
        printf("\nFin du programme.\n");
    }

    return 0;
}
```
🗂️ Exemple de contenu du fichier super_admin.txt

admin_general ADM0002

#### b. AJOUTER UN ADMIN 

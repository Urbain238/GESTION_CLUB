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

*************************************
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

*************************************
#### b. 👤 Ajout d’un administrateur

Cette fonctionnalité permet à l’administrateur général d’ajouter un nouvel administrateur dans le système.
Chaque administrateur est identifié par son nom, prénom, nom d’utilisateur et un matricule généré automatiquement composé de sept caractères commençant par “ADM”.
Les informations sont enregistrées dans un fichier texte appelé admins.txt afin de garantir la sauvegarde et la persistance des données.

Lorsqu’un administrateur est ajouté, son matricule est généré aléatoirement, puis l’ensemble des informations est sauvegardé dans le fichier sous la forme :

nom prénom username matricule

💻 Code complet de la fonctionnalité

```
#include <stdio.h> #include <string.h> #include <stdlib.h> #include <time.h>

void genererMatriculeAdmin(char matricule[]) { int i; char lettres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; strcpy(matricule, "ADM"); for (i = 3; i < 7; i++) { matricule[i] = lettres[rand() % strlen(lettres)]; } matricule[7] = '\0'; }

void ag_ajouter_admin() { FILE *f; char nom[50], prenom[50], username[50], matricule[8];

f = fopen("admins.txt", "a");
if (f == NULL) {
    printf("\n[ERREUR] Impossible d'ouvrir le fichier 'admins.txt'.\n");
    return;
}

srand(time(NULL));

printf("\n=== AJOUT D'UN NOUVEL ADMINISTRATEUR ===\n");
printf("Nom : ");
scanf("%s", nom);
printf("Prénom : ");
scanf("%s", prenom);
printf("Nom d'utilisateur : ");
scanf("%s", username);

genererMatriculeAdmin(matricule);

fprintf(f, "%s %s %s %s\n", nom, prenom, username, matricule);
fclose(f);

printf("\n[SUCCÈS] Administrateur ajouté avec succès !\n");
printf("Matricule attribué : %s\n", matricule);

}

int main() { ag_ajouter_admin(); return 0; 
}
```

💾 Exemple du fichier admins.txt après ajout :

URBAIN URBAIN Urbain ADM3F6A
*************************************
#### b. 🛠️ Modification d’un administrateur

Cette fonctionnalité permet à l’administrateur général de modifier les informations d’un administrateur existant.
La recherche se fait à partir du matricule de l’administrateur, qui est unique.
Une fois trouvé, le programme permet de mettre à jour son nom, prénom et nom d’utilisateur.
Les modifications sont ensuite enregistrées dans le fichier admins.txt, garantissant ainsi la mise à jour des données sans perte.

Le système parcourt tout le fichier, recopie les administrateurs dans un fichier temporaire, met à jour celui correspondant au matricule saisi, puis remplace l’ancien fichier par le nouveau.

💻 Code complet de la fonctionnalité

```
#include <stdio.h> #include <string.h> #include <stdlib.h>

void ag_modifier_admin() { FILE *f, *temp; char nom[50], prenom[50], username[50], matricule[8]; char nom_f[50], prenom_f[50], username_f[50], matricule_f[8]; int trouve = 0;

f = fopen("admins.txt", "r");
temp = fopen("temp.txt", "w");

if (f == NULL || temp == NULL) {
    printf("\n[ERREUR] Impossible d'ouvrir le fichier.\n");
    return;
}

printf("\n=== MODIFICATION D'UN ADMINISTRATEUR ===\n");
printf("Entrez le matricule de l'administrateur à modifier : ");
scanf("%s", matricule);

while (fscanf(f, "%s %s %s %s", nom_f, prenom_f, username_f, matricule_f) != EOF) {
    if (strcmp(matricule, matricule_f) == 0) {
        trouve = 1;
        printf("\nAdministrateur trouvé !\n");
        printf("Nouveau nom : ");
        scanf("%s", nom);
        printf("Nouveau prénom : ");
        scanf("%s", prenom);
        printf("Nouveau nom d'utilisateur : ");
        scanf("%s", username);
        fprintf(temp, "%s %s %s %s\n", nom, prenom, username, matricule_f);
        printf("\n[SUCCÈS] Les informations ont été mises à jour.\n");
    } else {
        fprintf(temp, "%s %s %s %s\n", nom_f, prenom_f, username_f, matricule_f);
    }
}

fclose(f);
fclose(temp);

if (!trouve) {
    printf("\n[AUCUN] Aucun administrateur trouvé avec ce matricule.\n");
    remove("temp.txt");
} else {
    remove("admins.txt");
    rename("temp.txt", "admins.txt");
}

}

int main() { ag_modifier_admin(); return 0; 
}
```

💾 Avant modification (admins.txt)

Nana Elise enana ADMZ7KQ

💾 Après modification

Nana Elise nana ADMZ7KQ

*************************************
#### c. 🗑️ Suppression d’un administrateur

Cette fonctionnalité permet à l’administrateur général de supprimer un administrateur existant du système à l’aide de son matricule.
Le programme recherche dans le fichier admins.txt l’administrateur correspondant au matricule saisi, puis réécrit toutes les autres lignes dans un fichier temporaire.
Une fois la suppression confirmée, le fichier temporaire remplace l’ancien fichier, garantissant ainsi une mise à jour sûre et propre des données.

Cette méthode évite la perte accidentelle d’autres enregistrements et maintient la cohérence du fichier.

💻 Code complet de la fonctionnalité

```
#include <stdio.h> #include <string.h> #include <stdlib.h>

void ag_supprimer_admin() { FILE *f, *temp; char nom[50], prenom[50], username[50], matricule[8]; char nom_f[50], prenom_f[50], username_f[50], matricule_f[8]; int trouve = 0;

f = fopen("admins.txt", "r");
temp = fopen("temp.txt", "w");

if (f == NULL || temp == NULL) {
    printf("\n[ERREUR] Impossible d'ouvrir le fichier.\n");
    return;
}

printf("\n=== SUPPRESSION D'UN ADMINISTRATEUR ===\n");
printf("Entrez le matricule de l'administrateur à supprimer : ");
scanf("%s", matricule);

while (fscanf(f, "%s %s %s %s", nom_f, prenom_f, username_f, matricule_f) != EOF) {
    if (strcmp(matricule, matricule_f) == 0) {
        trouve = 1;
        printf("\n[INFO] Administrateur trouvé et supprimé avec succès.\n");
        continue; // on saute l’écriture de cet admin
    }
    fprintf(temp, "%s %s %s %s\n", nom_f, prenom_f, username_f, matricule_f);
}

fclose(f);
fclose(temp);

if (!trouve) {
    printf("\n[AUCUN] Aucun administrateur trouvé avec ce matricule.\n");
    remove("temp.txt");
} else {
    remove("admins.txt");
    rename("temp.txt", "admins.txt");
}

}

int main() { ag_supprimer_admin(); return 0; 
}
```

💾 Exemple avant suppression (admins.txt)

Nana Elise enana ADMZ7KQ
Tchoumba Paul tchoumba ADM3F6A

💾 Exemple après suppression

Nana Elise enana ADMZ7KQ
*************************************
#### d. 📋 Affichage de tous les administrateurs

Cette fonctionnalité permet à l’administrateur général d’afficher la liste complète de tous les administrateurs enregistrés dans le fichier admins.txt.
Chaque ligne du fichier contient les informations d’un administrateur, à savoir son nom, prénom, nom d’utilisateur et matricule.
Le programme parcourt le fichier et affiche le contenu de manière lisible à l’écran.
Si aucun administrateur n’est enregistré, un message d’avertissement s’affiche.

Cette fonctionnalité permet donc à l’administrateur général d’avoir une vue d’ensemble sur la structure administrative du club.

💻 Code complet de la fonctionnalité

```
#include <stdio.h> #include <stdlib.h>

void ag_afficher_tous_admins() { FILE *f; char nom[50], prenom[50], username[50], matricule[8]; int compteur = 0;

f = fopen("admins.txt", "r");
if (f == NULL) {
    printf("\n[ERREUR] Impossible d'ouvrir le fichier 'admins.txt'.\n");
    return;
}

printf("\n=== LISTE DE TOUS LES ADMINISTRATEURS ===\n");

while (fscanf(f, "%s %s %s %s", nom, prenom, username, matricule) != EOF) {
    compteur++;
    printf("\nAdministrateur %d\n", compteur);
    printf("Nom           : %s\n", nom);
    printf("Prénom        : %s\n", prenom);
    printf("Nom d'utilisateur : %s\n", username);
    printf("Matricule     : %s\n", matricule);
    printf("-------------------------------");
}

if (compteur == 0) {
    printf("\n[AUCUN] Aucun administrateur enregistré pour le moment.\n");
}

fclose(f);

}

int main() { ag_afficher_tous_admins(); return 0; }
```

💾 Exemple du fichier admins.txt

Nana Elise enana ADMZ7KQ
Tchoumba Paul tchoumba ADM3F6A
Moukoko Henri hmouk ADM8R2T

🖥️ Affichage à l’écran

=== LISTE DE TOUS LES ADMINISTRATEURS ===

Administrateur 1
Nom           : Nana
Prénom        : Elise
Nom d'utilisateur : enana
Matricule     : ADMZ7KQ

Administrateur 2
Nom           : Tchoumba
Prénom        : Paul
Nom d'utilisateur : tchoumba
Matricule     : ADM3F6AQ
*************************************
#### e. 🍳 Rechercher un admin

Cette fonctionnalité permet de rechercher un administrateur spécifique dans la base de données (admins.txt) en saisissant son matricule.
Le programme parcourt le fichier ligne par ligne, compare le matricule saisi à ceux enregistrés et, en cas de correspondance, affiche les informations complètes de l’administrateur trouvé.
Si aucun administrateur ne correspond, un message indique que le matricule est introuvable.

Cette recherche est utile pour identifier rapidement un administrateur sans devoir afficher toute la liste.

💻 Code complet

```
#include <stdio.h> #include <stdlib.h> #include <string.h>

void ag_rechercher_admin_par_matricule() { FILE *f; char nom[50], prenom[50], username[50], matricule[8]; char recherche[8]; int trouve = 0;

f = fopen("admins.txt", "r");
if (f == NULL) {
    printf("\n[ERREUR] Impossible d'ouvrir le fichier 'admins.txt'.\n");
    return;
}

printf("\n=== RECHERCHE D'UN ADMINISTRATEUR PAR MATRICULE ===\n");
printf("Entrez le matricule à rechercher : ");
scanf("%s", recherche);

while (fscanf(f, "%s %s %s %s", nom, prenom, username, matricule) != EOF) {
    if (strcmp(matricule, recherche) == 0) {
        trouve = 1;
        printf("\nAdministrateur trouvé !\n");
        printf("Nom           : %s\n", nom);
        printf("Prénom        : %s\n", prenom);
        printf("Nom d'utilisateur : %s\n", username);
        printf("Matricule     : %s\n", matricule);
        break;
    }
}

if (!trouve) {
    printf("\n[AUCUN] Aucun administrateur trouvé avec le matricule '%s'.\n", recherche);
}

fclose(f);

}

int main() { ag_rechercher_admin_par_matricule(); return 0; 
}
```

🧩 Exemple d’exécution

=== RECHERCHE D'UN ADMINISTRATEUR PAR MATRICULE ===
Entrez le matricule à rechercher : ADM3F6A

Administrateur trouvé !
Nom           : Tchoumba
Prénom        : Paul
Nom d'utilisateur : tchoumba
Matricule     : ADM3F6A

ou, si aucun résultat :

[AUCUN] Aucun administrateur trouvé avec le matricule 'ADM9K4X'.

*************************************
#### 4. ADMINISTRATEUR SIMPLE 
Ce dernier dispose également des mêmes droits que l'administrateur général.
#### b. 🍳 Consulter son matricule 

Cette fonctionnalité permet à un administrateur simple connecté d’afficher son nom d’utilisateur et son matricule enregistrés dans le fichier admins.txt.
Cela permet de rappeler son identité système sans modifier les données.

💻 Code complet

```
#include <stdio.h> #include <stdlib.h> #include <string.h>

void admin_consulter_matricule(char username_connecte[]) { FILE *f; char nom[50], prenom[50], username[50], matricule[8]; int trouve = 0;

f = fopen("admins.txt", "r");
if (f == NULL) {
    printf("\n[ERREUR] Impossible d'ouvrir le fichier 'admins.txt'.\n");
    return;
}

while (fscanf(f, "%s %s %s %s", nom, prenom, username, matricule) != EOF) {
    if (strcmp(username_connecte, username) == 0) {
        printf("\n=== INFORMATIONS ADMINISTRATEUR ===\n");
        printf("Nom d'utilisateur : %s\n", username);
        printf("Matricule         : %s\n", matricule);
        trouve = 1;
        break;
    }
}

if (!trouve)
    printf("\n[AUCUNE DONNÉE] Administrateur non trouvé.\n");

fclose(f);

}
```
*************************************
#### a. 👥 Ajouter un utilisateur 

Cette fonctionnalité permet à un administrateur simple d’enregistrer un nouvel utilisateur du club dans le fichier utilisateurs.txt.
Chaque utilisateur possède un nom, un prénom, un matricule unique (généré automatiquement) et un statut de cotisation (entière, partielle ou aucune).
Elle permet ainsi d’assurer la traçabilité des membres du club et de suivre leurs cotisations.

💻 Code complet

```
#include <stdio.h> #include <stdlib.h> #include <string.h> #include <time.h>

struct Utilisateur { char nom[50]; char prenom[50]; char matricule[8]; char statut[15]; };

void generer_matricule_utilisateur(char matricule[]) { srand(time(NULL)); sprintf(matricule, "U%04d", rand() % 10000); }

void ajouter_utilisateur() { FILE *f; struct Utilisateur u; char choix;

f = fopen("utilisateurs.txt", "a");
if (f == NULL) {
    printf("\n[ERREUR] Impossible d'ouvrir le fichier 'utilisateurs.txt'.\n");
    return;
}

do {
    printf("\n=== AJOUT D'UN NOUVEL UTILISATEUR ===\n");
    printf("Nom : ");
    scanf("%s", u.nom);
    printf("Prénom : ");
    scanf("%s", u.prenom);

    generer_matricule_utilisateur(u.matricule);

    printf("Statut de cotisation (entière/partielle/aucune) : ");
    scanf("%s", u.statut);

    fprintf(f, "%s %s %s %s\n", u.nom, u.prenom, u.matricule, u.statut);
    printf("\n[SUCCÈS] Utilisateur ajouté avec matricule : %s\n", u.matricule);

    printf("\nVoulez-vous ajouter un autre utilisateur ? (o/n) : ");
    scanf(" %c", &choix);

} while (choix == 'o' || choix == 'O');

fclose(f);

}
```
*************************************
#### c. 🛠️ Modifier un utilisateur 

Cette fonctionnalité permet à un administrateur simple de mettre à jour les informations d’un utilisateur déjà enregistré dans le fichier utilisateurs.txt.
L’administrateur peut rechercher l’utilisateur grâce à son matricule puis modifier son nom, prénom ou statut de cotisation.
C’est une fonction essentielle pour corriger ou actualiser les données des membres du club.

💻 Code complet

```
#include <stdio.h> #include <stdlib.h> #include <string.h>

struct Utilisateur { char nom[50]; char prenom[50]; char matricule[8]; char statut[15]; };

void modifier_utilisateur() { FILE *f, *temp; struct Utilisateur u; char matricule[8]; int trouve = 0;

f = fopen("utilisateurs.txt", "r");
temp = fopen("temp.txt", "w");

if (f == NULL || temp == NULL) {
    printf("\n[ERREUR] Impossible d'ouvrir les fichiers.\n");
    return;
}

printf("\n=== MODIFICATION D'UN UTILISATEUR ===\n");
printf("Entrez le matricule de l'utilisateur à modifier : ");
scanf("%s", matricule);

while (fscanf(f, "%s %s %s %s", u.nom, u.prenom, u.matricule, u.statut) != EOF) {
    if (strcmp(u.matricule, matricule) == 0) {
        trouve = 1;
        printf("\nUtilisateur trouvé : %s %s (%s)\n", u.nom, u.prenom, u.matricule);
        printf("Nouveau nom : ");
        scanf("%s", u.nom);
        printf("Nouveau prénom : ");
        scanf("%s", u.prenom);
        printf("Nouveau statut de cotisation (entière/partielle/aucune) : ");
        scanf("%s", u.statut);
        printf("\n[SUCCÈS] Informations mises à jour.\n");
    }
    fprintf(temp, "%s %s %s %s\n", u.nom, u.prenom, u.matricule, u.statut);
}

fclose(f);
fclose(temp);

remove("utilisateurs.txt");
rename("temp.txt", "utilisateurs.txt");

if (!trouve)
    printf("\n[AUCUN RÉSULTAT] Aucun utilisateur trouvé avec ce matricule.\n");

}
```
*************************************
#### e. 🗑️ Supprimer un utilisateur



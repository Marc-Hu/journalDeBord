#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include"saisieM.c"
#include"couleurs_terminal.c"

typedef struct{
    char ** intitule;
    char ** nomEntreprise;
    char ** siteTrouve;
    char ** contact;
    char ** dateEnvoie;
    char * reponse;
    int * type;
    int nbLigne;

} journal;

typedef struct{
	char *fleche;
	int *menu;
	int nbChoix;
	char **choix;
} menu;

//Fonction qui initie la journal de bord en allouant dynamiquement le journal qui contient une liste de chaine de caractère
void initialiseJournal(journal *jDeBord){
    int i;
    char * incre = malloc(21*sizeof(char));
    jDeBord->intitule=malloc((jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->intitule[i]=incre;
    jDeBord->nomEntreprise=malloc((jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->nomEntreprise[i]=incre;
    jDeBord->siteTrouve=malloc((jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->siteTrouve[i]=incre;
    jDeBord->contact=malloc((jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->contact[i]=incre;
    jDeBord->dateEnvoie=malloc((jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->dateEnvoie[i]=incre;
    jDeBord->reponse=malloc((jDeBord->nbLigne+1)*sizeof(char));
    jDeBord->type=malloc((jDeBord->nbLigne+1)*sizeof(int));
    jDeBord->nbLigne=0;
}

/*
* On va libérer la mémoire alloué à la fin des opérations.
*/

void libereMemoire(journal *p){
    free(p->intitule);
    free(p->nomEntreprise);
    free(p->siteTrouve);
    free(p->contact);
    free(p->dateEnvoie);
    free(p->reponse);
    free(p->type);
}

/*
* On ouvre le journal et on récupère toutes les données à l'intérieur.
* Si le journal ne contient aucune donnée alors on retourne 0 sinon on récupère les données
* et on renvoie 1
*/

int ouvertureJournal(journal *p){
    FILE* fichsave;
    fichsave=fopen("journal.bin", "r+b");
    if (fichsave==NULL){
        printf("Impossible d'atteindre le journal.\n");
        return 0;
    }
    fread(&p->nbLigne, sizeof(int), 1, fichsave);
    if(&p->nbLigne==0){
        printf("Il n'y a aucune ligne dans le fichier. Redirection au menu\n");
        sleep(2);
        return 0;
    }
    fread(&p->intitule, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fread(&p->nomEntreprise, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fread(&p->siteTrouve, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fread(&p->contact, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fread(&p->dateEnvoie, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fread(&p->reponse, sizeof(char [21]), 1, fichsave);
    fread(&p->type, p->nbLigne * sizeof(int), 1, fichsave);
    fclose(fichsave);
    return 1;
}

/*
* Fonction qui va sauvegarder le journal de bord dans un fichier binaire
*/

int sauvegardeOffre (journal *p){
    FILE* fichsave;
    fichsave=fopen("journal.bin", "w+b");
    if (fichsave==NULL){
        printf("Impossible d'atteindre le journal.\n");
        return 0;
    }
    fwrite(&p->nbLigne, sizeof(int), 1, fichsave);
    fwrite(&p->intitule, sizeof(char [21]), p->nbLigne, fichsave);
    fwrite(&p->nomEntreprise, sizeof(char [21]), p->nbLigne, fichsave);
    fwrite(&p->siteTrouve, sizeof(char [21]), p->nbLigne, fichsave);
    fwrite(&p->contact, sizeof(char [21]), p->nbLigne, fichsave);
    fwrite(&p->dateEnvoie, sizeof(char [21]), p->nbLigne, fichsave);
    fwrite(&p->reponse, sizeof(char [21]), p->nbLigne, fichsave);
    fwrite(&p->type, sizeof(int), p->nbLigne, fichsave);
    fclose(fichsave);
    return 1;
}

/*
* On viens de créer ligne dans le journal, on doit donc reallouer les tableaux
* Afin d'en sauvegarder d'autre
*/

void reallocation(journal *jDeBord){
    int i;
    char * incre = malloc(21*sizeof(char));
    jDeBord->intitule=realloc(jDeBord->intitule, (jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->intitule[i]=incre;
    jDeBord->nomEntreprise=realloc(jDeBord->nomEntreprise, (jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->nomEntreprise[i]=incre;
    jDeBord->siteTrouve=realloc(jDeBord->siteTrouve, (jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->siteTrouve[i]=incre;
    jDeBord->contact=realloc(jDeBord->contact, (jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->contact[i]=incre;
    jDeBord->dateEnvoie=realloc(jDeBord->dateEnvoie, (jDeBord->nbLigne+1)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne+1; i++)
        jDeBord->dateEnvoie[i]=incre;
    jDeBord->reponse=realloc(jDeBord->reponse, (jDeBord->nbLigne+1)*sizeof(char));
    jDeBord->type=realloc(jDeBord->type, (jDeBord->nbLigne+1)*sizeof(int));
}

/*
* Cette fonction va créer l'offre puis va sauvegarder le nouveau journal
* La personne peut saisir plusieurs offre d'un seule coup avant de sauvegarder.
*/

int creationOffre(journal *p, int type){
    char sur;
    clear_terminal();
    printf("=====> Saisie de la candidature avec des cases de 20 mots maximum\nSaisissez l'intitulé de la candidature :\n");
    scanf("%s", p->intitule[p->nbLigne]);
    printf("Saisissez le nom de l'entreprise :\n");
    scanf("%s", p->nomEntreprise[p->nbLigne]);
    if (type==1){
        printf("Saisissez le nom du site ou vous avez trouvé l'offre :\n");
        scanf("%s", p->siteTrouve[p->nbLigne]);
    }
    else{
        printf("Saisissez le nom du DRH ou vous avez envoyé le dossier :\n");
        scanf("%s", p->contact[p->nbLigne]);
    }
    printf("Saisissez la date d'envoie du dossier de candidature (exemple : 1 janv 2017) :\n");
    scanf("%s", p->dateEnvoie[p->nbLigne]);
    printf("Etes-vous sûr de la saisie de votre offre?[O/n] (Vous pourrez la supprimer ultérieurement)\n");
    scanf("%c", &sur);
    if (sur=='n' || sur=='N'){
        printf("Voulez-vous quitter?[O/n]");
        scanf("%c", &sur);
        if (sur=='n' || sur=='N')
            creationOffre(p, type);
        return 0;
    }
    p->nbLigne++;
    reallocation(p);
    printf("Voulez-vous saisir une autre offre?[O/n]");
    if (sur=='o' || sur=='O')
        creationOffre(p, type);
    sauvegardeOffre(p);
    return 1;
}

/*
* Affichage du journal
*/

void affichage(journal *p){
    char quit;
    printf("======>Votre Journal :\n Intitulé du dossier\tNom de l'entreprise\tNom du site du dossier\tLe contact RH\tLa date d'envoie\tOffre (1), spontanné (2)\n");
    int i;
    for(i=0; i<p->nbLigne; i++)
        printf("%s\t%s\t%s\t%s\t%s\t%d\n",p->intitule[i], p->nomEntreprise[i], p->siteTrouve[i], p->contact[i], p->dateEnvoie[i], p->type[i]);
    printf("Nombre de candidature : %d\nRetour menu principal?[O/n]", (p->nbLigne));
    scanf("%c", &quit);
    while(quit!='O' && quit!='o'){
        printf("Retour menu principal?[O/n]");
        scanf("%c", &quit);
    }
}

int saisieD(){
    debutTerminalSansR();               // On débute le terminal sans retour chariot 
    Key saisieDir = NO_KEY;             // On définie une structure saisiDir qui sera initié à NO_KEY 
    while (saisieDir==NO_KEY){          // Boucle tant que c'est égale à NO_KEY
        saisieDir=lectureFleche();      // on va affecter la direction de la flèche dans saisiDir
    }
    switch (saisieDir){                 // Switch selon la direction de la flèche (bas, droite, haut ou gauche);  
        case KEY_DOWN:                  // On arrête le terminal sans retour chariot et on retourne 0, 1, 2 ou 3 selon la direction et -1 ou -2 si c'est la touche echap ou autre
            finTerminalSansR();         // On arrête me terminal sans retour chariot
            return 0;           
            break;
        case KEY_RIGHT: 
            finTerminalSansR();
            return 1;
            break;
        case KEY_UP: 
            finTerminalSansR();
            return 2;
            break;
        case KEY_LEFT: 
            finTerminalSansR();
            return 3;
            break;
        case KEY_ESCAPE: 
            finTerminalSansR();
            return -1;
            break;
        default :
            finTerminalSansR();
            return -2;
            break;
    }
}
/*
* Fonction qui va initialiser un menu 
* Affecte le nombre de choix pour le menu
* Alloue dynamiquement le menu et la flèche
* Affecte une flèche à la première ligne du menu
*/

void initialisationMenu(menu *p, int nb){
    p->nbChoix=nb;
    p->menu=malloc((p->nbChoix)*sizeof(int)); 
    p->fleche=malloc((p->nbChoix)*sizeof(char));
    p->choix=malloc((p->nbChoix)*sizeof(char *));
    int i;
    for (i=0; i<(p->nbChoix); i++)
        p->choix[i]=malloc(40*sizeof(char));
    for (i=0; i<(p->nbChoix); i++)
        p->menu[i]=i+1;
    p->fleche[0]='>';
    p->choix[0]="Enregistrer une offre";
    p->choix[1]="Enregistrer une candidature spontanée";
    p->choix[2]="Supprimer une ligne";
    p->choix[3]="Afficher le journal";
    p->choix[4]="Afficher le journal(seulement offre)";
    p->choix[5]="Afficher le journal(seulement spontanée)";
    p->choix[6]="Quitter";
}

//Libère la mémoire alloué pour le menu et la flèche

void libereMemoireMenu(menu *p){
    free(p->menu);
    free(p->fleche);
    free(p->choix);
}

/*
* Fonction qui va vérifié si la flèche est présente dans la case d'indice a 
* Retourne 1 si la flèche est bien à l'indice a
* 0 Sinon
*/

int flecheValide(menu *p, int a){
    if (p->fleche[a]=='>')
        return 1;
    return 0;
}

/*
* Fonction qui va afficher le menu
* \33[34;01m    \33[00m  sont les couleurs pour la sélection
* Il va afficher en blanc si la flèche n'est pas devant la sélection 
* Il va afficher en bleu si la flèche pointe la sélection
*/

void affichageMenu(menu *p){
    int i; 
    printf("Monter/descendre : flèche haut/bas; selectionner : flèche droite\n");
    for (i=0; i<(p->nbChoix); i++){
        if (flecheValide(p, i))
            printf(" %c \33[34;01m%d  %s\33[00m\n", p->fleche[i], p->menu[i], p->choix[i]);
        else
            printf("     %d  %s\n", p->menu[i], p->choix[i]);
    }
}


/*
* Fonction qui va retourné la position de la flèche dans flèche
*/

int getFleche(menu *p){
    int i, j=0;
    for (i=0; i<(p->nbChoix); i++){
        if (p->fleche[i]=='>')
            return j;
        j++;
    }
    return 0;
}

/*
* Fonction qui va lancer le menu 
* Si on appuie sur flèche du bas ou du haut alors la flèche dans p->flèche bouge selon la direction
* Si la flèche atteint la limite (haut ou bas) alors la flèche ne bouge plus
* On retourne le menu selectionné (1, 2, 3, 5, 6 ou 7)
*/

int lanceMenu (menu *p){
    int saisie, j;
    while (saisie!=1){
        clear_terminal();
        affichageMenu(p);
        saisie=saisieD();
        switch (saisie){
            case 0 : 
                j=getFleche(p);
                if (j==(p->nbChoix-1))
                    j=(p->nbChoix-2);
                p->fleche[j+1]='>';
                p->fleche[j]=' ';
                break;
            case 2 :
                j=getFleche(p);
                if (j==0)
                    j=1;
                p->fleche[j-1]='>';
                p->fleche[j]=' ';
                break;
            case 1 :
                return getFleche(p)+1;
        }
    }
    return 0;
}

/*
* Fonction menu qui va gérer le menu
* Initialise un menu
* Il va afficher le menu
* Et il va retourné le choix opté par l'utilisateur
*/

int menuD(){
    menu p;
    int i;
    initialisationMenu(&p, 7);
    affichageMenu(&p);
    i=lanceMenu(&p);
    libereMemoireMenu(&p);
    return i;
}

int journalD(journal *p){
    int menu;
    ouvertureJournal(p);
    initialiseJournal(p);
    while(menu!=6){
        menu=menuD();
        switch (menu){
            case 1:
                creationOffre(p, 1);
                break;
            case 2:
                creationOffre(p, 1);
                break;
            case 3:
                break;
            case 4:
                affichage(p);
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                libereMemoire(p);
                return 0;
                break;
        }
    }
    return 1;
}

int main(void){
    journal jDeBord;
    journalD(&jDeBord);
    return 0;
}
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

//Fonction qui initie la journal de bord en allouant dynamiquement le journal qui contient une liste de chaine de caractère
void initialiseJournal(journal *jDeBord){
    int i;
    char * incre = malloc(21*sizeof(char));
    jDeBord->intitule=malloc((jDeBord->nbLigne)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne; i++)
        jDeBord->intitule[i]=incre;
    jDeBord->nomEntreprise=malloc((jDeBord->nbLigne)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne; i++)
        jDeBord->nomEntreprise[i]=incre;
    jDeBord->siteTrouve=malloc((jDeBord->nbLigne)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne; i++)
        jDeBord->siteTrouve[i]=incre;
    jDeBord->contact=malloc((jDeBord->nbLigne)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne; i++)
        jDeBord->contact[i]=incre;
    jDeBord->dateEnvoie=malloc((jDeBord->nbLigne)*sizeof(char *));
    for (i=0; i<jDeBord->nbLigne; i++)
        jDeBord->dateEnvoie[i]=incre;
    jDeBord->reponse=malloc((jDeBord->nbLigne)*sizeof(char));
    jDeBord->type=malloc((jDeBord->nbLigne)*sizeof(int));
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
* Cette fonction permettra de saisir l'intitulé du dossier de candidature
* L'utilisateur va saisir 1 si c'est une réponse à une offre de stage 
* Et 2 si c'est une candidature spontanée, On retourne 1 pour offre de stage
* et 2 pour une candidature spontanée
*/

int saisieIntitule(char **typeOffre){
    int type;
    do{
    printf("Réponse à une offre de stage? Taper 1 ou candidature spontanée? Taper 2");
    scanf("%d", &type);
    }while (type==1 || type==2);
    return type;
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
    fwrite(&p->intitule, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fwrite(&p->nomEntreprise, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fwrite(&p->siteTrouve, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fwrite(&p->contact, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fwrite(&p->dateEnvoie, p->nbLigne * sizeof(char [21]), 1, fichsave);
    fwrite(&p->reponse, sizeof(char [21]), 1, fichsave);
    fwrite(&p->type, p->nbLigne * sizeof(int), 1, fichsave);
    fclose(fichsave);
    return 1;
}


/*
* Cette fonction va créer l'offre puis va sauvegarder le nouveau journal
* La personne peut saisir plusieurs offre d'un seule coup avant de sauvegarder.
*/

int creationOffre(journal *p){
    char check, sur;
    clear_terminal();
    printf("=====> Saisie de la candidature avec des cases de 20 mots maximum\nSaisissez l'intitulé de la candidature :\n");
    scanf("%s", p->intitule[p->nbLigne]);
    printf("Saisissez le nom de l'entreprise :\n");
    scanf("%s", p->nomEntreprise[p->nbLigne]);
    if (p->type[p->nbLigne]==1){
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
            creationOffre(p);
        return 0;
    }
    p->nbLigne++;
    printf("Voulez-vous saisir une autre offre?[O/n]");
    if (sur=='o' || sur=='O')
        creationOffre(p);
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
    printf("Nombre de candidature : %d\nRetour menu principal?[O/n]", (p->nbLigne)+1);
    scanf("%c", &quit);
    while(quit!='O' || quit!='o'){
        printf("Retour menu principal?[O/n]");
        scanf("%c", &quit);
    }
}



int main(void){
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>

typedef struct{
    char ** intitule;
    char ** nomEntreprise;
    char ** siteTrouve;
    char ** contact;
    char ** dateEnvoie;
    char * reponse;
    int nbLigne;
} journal;

//Fonction qui initie la journal de bord en allouant dynamiquement le journal qui contient une liste de chaine de caractère
void initialiseJournal(journal *jDeBord){
    int i;
    char * incre = malloc(20*sizeof(char));
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
    jDeBord->nbLigne=0;
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
    fread(&p->intitule, p->nbLigne * sizeof(char [20]), 1, fichsave);
    fread(&p->nomEntreprise, p->nbLigne * sizeof(char [20]), 1, fichsave);
    fread(&p->siteTrouve, p->nbLigne * sizeof(char [20]), 1, fichsave);
    fread(&p->contact, p->nbLigne * sizeof(char [20]), 1, fichsave);
    fread(&p->dateEnvoie, p->nbLigne * sizeof(char [20]), 1, fichsave);
    fread(&p->reponse, sizeof(char [20]), 1, fichsave);
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

/**
int sauvegardeOffre (char[20] intitule, char[20] nomEntreprise, char[20] nomSite, char[20] dateEnvoie){

}
**/


void creationOffre(journal *p){
    char check, sur;
    printf("Saisissez l'intitulé de l'offre :\n");
    scanf("%s", intitule);
    printf("Saisissez le nom de l'entreprise :\n");
    scanf("%s", nomEntreprise);
    printf("Saisissez le nom du site ou vous avez trouvé l'offre :\n");
    scanf("%s", nomSite);
    printf("Saisissez la date d'envoie du dossier de candidature (exemple : 1 janv 2017) :\n");
    scanf("%s", dateEnvoi);
    printf("Etes-vous sûr de la saisie de votre offre?[O/n] (Vous pourrez la supprimer ultérieurement)\n");
    scanf("%c", &sur);
    if (sur=='n' || sur=='N')
        creationOffre(p);
    //sauvegardeOffre(intitule, nomEntreprise, nomSite, dateEnvoie);
}

void creationSpontanee(journal *p){

}

void libereMemoire(journal *p){
    free(p->intitule);
    free(p->nomEntreprise);
    free(p->siteTrouve);
    free(p->contact);
    free(p->dateEnvoie);
    free(p->reponse);
}

int main(void){
    journal jDeBord;
    initialiseJournal(&jDeBord);
    char** typeOffre;
    typeOffre[0]="Offre";
    typeOffre[1]="Spontanée";
    int type;
    ouvertureJournal(&jDeBord);
    if (saisieIntitule(typeOffre)==1){
        creationOffre(&jDeBord);
    }
    else{
        creationSpontanee(&jDeBord);
    }
    libereMemoire(&jDeBord);
    return 0;
}
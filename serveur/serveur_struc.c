/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dgrammont
 *
 * Created on 8 septembre 2020, 10:50
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

/*
 * 
 */
int main(int argc, char** argv) {
        typedef struct{
        unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];
    }datePerso;
    int soc; //la socket
    int socClient; //la socket client
    struct sockaddr_in infoClient;
    struct sockaddr_in infoServeur;
    datePerso donneAEnvoyer;
    datePerso donneRecue;
    int retour;
    int taille;
    

    // creation de la socket en mode datagram
    soc = socket(PF_INET, SOCK_STREAM, 0/*IPROTO_UDP*/);
    if (soc == -1) {
        printf("pb creation socket : %s \n", strerror(errno));
        exit(errno);
    }
    //initialisation de la structure contenatn les infos du serveur
    infoServeur.sin_family = AF_INET;
    infoServeur.sin_port = htons(7777);
    infoServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    //infoServeur.sin_zero =0;
    retour=bind(soc, (struct sockaddr *)&infoServeur, sizeof(infoServeur));
     if(retour==-1){
         printf("pb bind : %s \n",strerror(errno));
        exit(errno);
    }
    //écoute la connection du client 
     retour=listen(soc,1);
     if(retour==-1){
         printf("pb listen : %s \n",strerror(errno));
        exit(errno);
    }
     
     //recevoir les info client 
     socClient=accept(soc,(struct sockaddr *)&infoClient,&taille);
      if(socClient==-1){
         printf("pb accept : %s \n",strerror(errno));
        exit(errno);
    } 
    //recevoir la donnee en provenance du client
    retour=read(socClient,&donneRecue,sizeof(donneRecue));   
    if(retour==-1){
         printf("pb read : %s \n",strerror(errno));
         exit(errno);
    }
     // afficher la donnee
   printf("Donne recue  de %s/%u : %d/%d/%d le %s \n", inet_ntoa(infoClient.sin_addr),infoClient.sin_port,donneRecue.jour,donneRecue.mois,donneRecue.annee,donneRecue.jourDeLaSemaine);
    //fermer la socket
     close(socClient);
    close(soc);
   
    return (EXIT_SUCCESS);
}


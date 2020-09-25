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
/*
 * 
 */
int main(int argc, char** argv) {
    int soc; //la socket
    struct sockaddr_in infoServeur;
    int donneAEnvoyer;
    int donneRecue;
    int retour;
  //  int taille;
    
    // creation de la socket en mode datagram
    soc=socket(PF_INET,SOCK_STREAM,0/*IPROTO_UDP*/);
    if (soc ==-1)
    {
        printf("pb creation socket : %s \n",strerror(errno));
        exit(errno);
    }
    //initialisation de la structure contenatn les infos du serveur
    infoServeur.sin_family = AF_INET;
    infoServeur.sin_port =htons(5556);
    infoServeur.sin_addr.s_addr=inet_addr("172.18.58.143");
    //infoServeur.sin_zero =0;
    //conection au serveur
    retour=connect(soc,(struct sockaddr *)&infoServeur , sizeof(infoServeur));
   
    //envoyer la donnee au serveur 
    donneAEnvoyer=101;
    retour=write(soc,&donneAEnvoyer,sizeof(donneAEnvoyer));
     if(retour==-1){
         printf("pb write : %s \n",strerror(errno));
        exit(errno);
    }
    //recevoir la donnee en provenance du serveur
    retour=read(soc,&donneRecue,sizeof(donneRecue));   
    if(retour==-1){
         printf("pb read : %s \n",strerror(errno));
         exit(errno);
    }
    // afficher la donnee
    printf("Donne recue : %d \n",donneRecue);
    //fermer la socket
    close(soc);
    return (EXIT_SUCCESS);
}


/*!
 *  @author   Chamil José Cruz Razeq
 *  
 *  @version  0.0.0.0
 *  @date     04-05-23
 *
 *  @abstract Operative Systems Fundamentals Lab 2
*/

#include <stdio.h>
#include "../headers/sala.h"
//FILE
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
//ERROR
#include <errno.h>
#include <string.h>
#include "../headers/error_control.h"

/** ----------------------------------------------------------------------------
 *  MAIN
 *  --------------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
    printf("Imprime valores en posiciones impares:\n");
    int* pos = malloc(sizeof(int)*5);
    *pos = 0;
    *(pos + 1) = 2;
    *(pos + 2) = 4;
    *(pos + 3) = 6;
    *(pos + 4) = 8;
    
    crea_sala(10);
    recupera_estadoparcial_sala("file", 5, pos);
    print_asientos();

    printf("Guarda nuevos valores en posiciones impares:\n");
    libera_asiento(0);
    libera_asiento(2);
    libera_asiento(4);
    libera_asiento(6);
    libera_asiento(8);
    reserva_asiento_concreto(65, 0);
    reserva_asiento_concreto(66, 2);
    reserva_asiento_concreto(67, 4);
    reserva_asiento_concreto(68, 6);
    reserva_asiento_concreto(69, 8);
    //guarda_estado_sala("file");
    guarda_estadoparcial_sala("file", 6, pos);
    print_asientos();
    return 0;
}
/*!
 *  @author   Chamil José Cruz Razeq
 *  
 *  @version  1.0.0.0
 *  @date     18-04-23
 *
 *  @abstract Operative Systems Fundamentals Lab 2
 *
 *  Removed unnecessary libraries.
 *  Removed commented code.
 *  Added free before callocs in main method.
 *  Reduced code using set_err method.
 *  Commented set_err method.
 *  Finished guarda_estadoparcial_sala method.
 *  Solved freeing memory;
 *  Solved "anula" calloc.
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

void leaves(int* ptr, int exit_value) {
  free(ptr);

  exit(exit_value);
}

int main(int argc, char *argv[]) {

  // variables
  int arg, value, i;
  arg = value = i = 0;
  char file[32];
  int* tmp_data = malloc(sizeof(char));
  
  
  int flag_f, flag_fo, flag_c, flag_n, flag_a, flag_crea, flag_reserva, flag_anula, flag_estado;
  flag_f = flag_fo = flag_c = flag_n = flag_a = flag_crea = flag_reserva = flag_anula = flag_estado = 0;
  
  if (strcmp(argv[1], "crea") == 0) {
    flag_crea = 1;

    if (set_err(argc != 6,
              "Missing arguments",
               22) == -1) leaves(tmp_data, -1);
  } else if (strcmp(argv[1], "reserva") == 0) {
    flag_reserva = 1;

    if (set_err(argc < 7,
              "Missing arguments",
               22) == -1) leaves(tmp_data, -1);
  } else if (strcmp(argv[1], "anula") == 0) {
    flag_anula = 1;

    if (set_err(argc < 6,
              "Missing arguments",
               22) == -1) leaves(tmp_data, -1);
  } else if (strcmp(argv[1], "estado") == 0) {
    flag_estado = 1;

    if (set_err(argc < 4,
              "Missing arguments",
               22) == -1) leaves(tmp_data, -1);
  }
  
  if (set_err(flag_crea == flag_reserva == flag_anula == flag_estado,
              "Missing command such as; crea, reserva, anula or estado",
               22) == -1) leaves(tmp_data, -1);
      
  // loops over command arguments
  while((arg=getopt(argc, argv, ":f:c:n:a:")) != -1) {
    switch(arg) {
      case 'f':                                                                 // file name argument
        strcpy(file, optarg);
        
        // checks if override argument was written
        if (!strcmp(file, "o")) {
          strcpy(file, argv[optind]);
          flag_fo = 1;
        } else {
          flag_f = 1;
        }
        
        break;

      case 'c':                                                                 // room capacity argument
        flag_c = 1;
        value = atoi(optarg);
        
        break;
      
      case 'n':                                                                 // book chairs argument
        flag_n = 1;
        value = atoi(optarg);
        free(tmp_data);
        tmp_data = calloc(atoi(optarg), sizeof(int));
        i = optind;
        int as = 0;
        
        while ((argc > i) && (strncmp(argv[i], "-", 1) != 0)) {        
          *(tmp_data + as++) = atoi(argv[i++]);
        }

        if (set_err(as != value,
              "Arguments doesn't match number given",
               22) == -1) leaves(tmp_data, -1);

        break;
      
      case 'a':                                                                 // free chairs argument
        flag_a = 1;  
        free(tmp_data);
        tmp_data = calloc((argc - optind) + 1, sizeof(int));
        i = optind - 1;
        
        while ((argc > i) && (strncmp(argv[i], "-", 1) != 0)) {
          *(tmp_data + value++) = atoi(argv[i++]);
        }
        
        break;
      
      case ':':
        printf("Arguments missing! : %c \n", optopt);
        
        leaves(tmp_data, -1);;

      case '?':
        printf("Unexpected option! : %c \n", optopt);
        
        leaves(tmp_data, -1);
        
      default:
        leaves(tmp_data, -1);
    }
  }

  if (flag_crea && flag_f && flag_c) {                                          // create room option
    if (set_err(access(file, F_OK) == 0, "File already exists or is not accesible", 17)) leaves(tmp_data, -1);;
    
    crea_sala(value);
    
    if (set_err(guarda_estado_sala(file) == -1, "Saving room state didn't work", 1)) leaves(tmp_data, -1);
    
  } else if (flag_crea && flag_fo && flag_c) {                                  // override room option
    if (set_err((access(file, R_OK | W_OK) == -1), "File not accessible", 17)) leaves(tmp_data, -1);
    
    crea_sala(value);
    
    if (set_err(guarda_estado_sala(file) == -1, "Saving room state didn't work", 1)) leaves(tmp_data, -1);

  } else if (flag_reserva && flag_f && flag_n) {                                // book chairs option
    if (set_err(reserva_asientos(file, value, tmp_data) == -1, "Chairs reservation failed", 1)) leaves(tmp_data, -1);
    
  } else if (flag_anula && flag_f && flag_a) {                                  // free chairs option
    if (set_err(libera_asientos(file, value, tmp_data) == -1, "Chairs freeing failed", 1)) leaves(tmp_data, -1);
    
  } else if (flag_estado && flag_f) {                                           // state of room option
    if (set_err(recupera_estado_sala(file) == -1, "Recovering room state didn't work", 1)) leaves(tmp_data, -1);
    
    print_asientos();
  }

  free(tmp_data);
  elimina_sala();
  return 0;
}

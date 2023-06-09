/*!
 *  @author   Chamil José Cruz Razeq
 *  
 *  @version  1.0.0.0
 *  @date     09-03-23
 *
 *  @abstract Operative Systems Fundamentals Lab 2
*/

#include <stdio.h>
//FILE
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
// ERROR
#include <errno.h>
#include <string.h>
#include "../../headers/error_control.h"

struct {
	int* asientos;
	int n_asientos, o_asientos;
} sala;

/*!
 * @function   existe_id
 * @abstract   Checks if client ID exists.
 * @discussion Checks if client ID exists and returns 1, if not returns 0.
 *                
 *
 * @param      id       Client ID to check.     
 *
 * @return     Returns 0 if not found and 1 if found..
*/
int existe_id(int id) {
	int existe = 0;

	if (id >= 0) {
		for (int i = 0; i < sala.n_asientos; i++) {
			if (*(sala.asientos + i) == id) {
				existe = 1;
			}
		}
	}

	return existe; 
}

/*!
 * @function   reserva_asiento_concreto
 * @abstract   Books a chair for given client ID in given chair.
 * @discussion Books a chair for given client ID in given chair, if successful
 *             returns 0, if not returns -1.
 *                
 *
 * @param      id       Client ID.
 * @param      pos      Chair index.
 *
 * @return     Chair assigned or -1 if not successful.
*/
int reserva_asiento_concreto(int id, int pos) {
	int success = -1;
      
        // checks if id is greater than 0 and if room is not empty
	if ((!existe_id(id)) && (sala.o_asientos < sala.n_asientos) && (id >= 0)) {
	  if((*(sala.asientos + pos) == -1)) {
	    *(sala.asientos + pos) = id;
	    success = 0;
	    sala.o_asientos++;
	  }
	}

	return success;
}

/*!
 * @function   reserva_asiento
 * @abstract   Books a chair for given client ID.
 * @discussion Books a chair for given client ID, if successful returns the
               first available chair found, if not returns -1.
 *                
 *
 * @param      id       Client ID.
 *
 * @return     Chair assigned or -1 if not successful.
*/
int reserva_asiento(int id) {
	int asiento = -1;
      
        // checks if id is greater than 0 and if room is not empty
	for (int i = 0; i < sala.n_asientos; i++) {
	  if(reserva_asiento_concreto(id, i) == 0) {
	    asiento = i;
	    break;
	  }
	}

	return asiento;
}

/*!
 * @function   libera_asiento
 * @abstract   Frees given chair.    
 * @discussion Frees given chair, if successful returns the ID of the client that
               had booked the chair, if not returns -1.
 *                
 *
 * @param      id       Client ID.
 *
 * @return     ID of client or -1 if not successful.
*/
int libera_asiento(int asiento) {
	int id = -1;
        
        // checks if chair is in the interval [chair, capacity] and if the room
        // is not empty
	if ((asiento >= 0) && (asiento < sala.n_asientos) && (*(sala.asientos + asiento) != -1)) {
		id = *(sala.asientos + asiento);
		*(sala.asientos + asiento) = -1;
		sala.o_asientos--;
	}

	return id;
}

/*!
 * @function   estado_asiento
 * @abstract   Checks if the chair is booked and by whom.
 * @discussion Checks if the chair is booked and returns ID of client or -1 if
               unsuccessful or available.
 *                
 *
 * @param      asiento   Chair to check.
 *
 * @return     ID of client or -1 if available or unsuccessful.
*/
int estado_asiento(int asiento) {
	int id = -1;
      
        // checks if asiento is in the interval [chair, capacity]
	if ((asiento < sala.n_asientos) && (asiento >= 0)) {
		id = *(sala.asientos + asiento);
	}

	return id;
}

/*!
 * @function   asientos_libres
 * @abstract   Checks the number of available chairs.
 *
 * @return     Number of available chairs.
*/
int asientos_libres() {
	return sala.n_asientos - sala.o_asientos;
}

/*!
 * @function   asientos_ocupados
 * @abstract   Checks the number of booked chairs.
 *
 * @return     Number of booked chairs.
*/
int asientos_ocupados() {
	return sala.o_asientos;
}

/*!
 * @function   capacidad
 * @abstract   Checks the capacity of room.
 *
 * @return     Capacity of room.
*/
int capacidad() {
	return sala.n_asientos;
}

/*!
 * @function   crea_sala
 * @abstract   Creates new room.
 * 
 * @param      capacidad       The capacity of the room.
*/
void crea_sala(int capacidad) {
        // checks if capacidad is positive. if not sets to 0
	if (capacidad < 0) capacidad = 0;
	
	sala.asientos = calloc(capacidad, sizeof(int));

	sala.n_asientos = capacidad;
	sala.o_asientos = capacidad;
        
        // sets each chair to default value (-1)
	for (int i = 0; i < capacidad; i++) {
		libera_asiento(i);
	}
}

/*!
 * @function   elimina_sala
 * @abstract   Removes room.
*/
void elimina_sala() {
	free(sala.asientos);
	sala.asientos = NULL;
	sala.n_asientos = 0;
	sala.o_asientos = 0;
}

/*!
 * @function   print_asientos
 * @abstract   Prints chairs and clients id as a table.
*/
void print_asientos() {
  //  prints the header of the table
  printf("-------------------\n"
         "| Asie |    ID    |\n"
         "-------------------\n");
  
  for(int i = 0; i < capacidad(); i++) {
    int id = estado_asiento(i);
   
    //  checks if chair has client assigned
    if (id != -1) {
      //  prints each row of the table
      printf("| %4d | %8d |\n"
             "-------------------\n", i, id);
    } 
  }
}


// ------------------------------------------------------------------------------------------------
// FILE MANAGEMENT METHODS
// ------------------------------------------------------------------------------------------------


/*!
 * @function   write_file_line
 * @abstract   Writes line given string on given file.
 *                
 *
 * @param      fd       File.
 * @param      char_aux String.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int write_file_line(const int fd, const char* char_aux) {
  int i = 0;
  
  // writes character by character
  while (*(char_aux + i) != '\0') {
    if (write(fd, char_aux + i, sizeof(char)) == -1) {
      print_error("Write room failed");
      return -1;
    }
          
    i++;
  }
      
  // writes jump line
  if (write(fd, "\n", sizeof(char)) == -1) {
    print_error("Write jump line failed");
    return -1;
  }
      
  return 0;
}

/*!
 * @function   read_file_line
 * @abstract   reads line on given file.
 *                
 *
 * @param      fd       File.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int read_file_line(const int fd) {
  char* char_aux = calloc(sizeof(int), sizeof(char));
  sprintf(char_aux, "%d", -1);                                                  // id is -1 by default
  int i = 0;
  
  // writes character by character
  while (0 < read(fd, char_aux + i, sizeof(char)) != '\0') {
    print_error("Read line failed");
    
    if (*(char_aux + i) == '\n') break;
    i++;
  }
      
  int result = atoi(char_aux);
  free(char_aux);
      
  return result;
}


/*!
 * @function   guarda_estado_sala
 * @abstract   Saves current room state on a file.
 *                
 *
 * @param      fd       File name.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int  guarda_estado_sala (const	char* ruta_fichero) {
    // variables
    int fd = open(ruta_fichero, O_TRUNC | O_CREAT | O_RDWR, 0777);              // opens a file or creates it if is nonexistent
    int state = 0;
    
    if (fd == -1) {
      print_error("Opening file failed on writing context");
      
      return -1;
    }
    
    // saves capacity
    char* char_aux = calloc(sizeof(int), sizeof(char));                         // frees a byte for each possible unit of a integer
    sprintf(char_aux, "%d", capacidad());
    
    if (write_file_line(fd, char_aux) == -1) {
      free(char_aux);
      return -1;
    }
    
    // saves reservations
    for (int i = 0; i < capacidad(); i++) {
      sprintf(char_aux, "%d", estado_asiento(i));
      if (write_file_line(fd, char_aux) == -1) {
        free(char_aux);
        return -1;
      }
    }
    
    free(char_aux);
    
    if(close(fd) == -1) {
      print_error("Closing file failed on writing context");
      
      return -1;
    }
    
    return state;
}

/*!
 * @function   recupera_estado_sala
 * @abstract   Recovers data from file and uploads it into the room structure.
 *                
 *
 * @param      fd       File.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int recupera_estado_sala (const char* ruta_fichero) {
    // variables
    int fd = open(ruta_fichero, O_RDONLY);                                      // opens an existing file
    
    if (fd == -1) {
      print_error("Opening file failed on reading context");
      
      return -1;
    }
    
    // saves capacity
    crea_sala(read_file_line(fd));
    
    // saves reservations
    for (int i = 0; i < capacidad(); i++) {
        reserva_asiento_concreto(read_file_line(fd), i);
    }
    
    if(close(fd) == -1) {
      print_error("Closing file failed on reading context");
      
      return -1;
    }
    
    return 0;
}

/*!
 * @function   reserva_asientos
 * @abstract   Makes reservations for given clients in room given by file.
 *                
 *
 * @param      fd           File.
 * @param      num_asientos Number of chairs.
 * @param      id_personas  Set of client ids.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int reserva_asientos(const char* ruta_fichero, size_t num_asientos, int* id_personas) {
  if (set_err(recupera_estado_sala(ruta_fichero) != 0,
              "Recovering room state didn't work",
               1) == -1) return -1;
  
  if (set_err(num_asientos > capacidad(),
              "Room capacity exceeded",
               1) == -1) return -1;
  
  if (set_err(num_asientos > asientos_libres(),
              "Not enough free chairs",
               1) == -1) return -1;
               
  for (int i = 0; i < num_asientos; i++) {
    if (set_err(reserva_asiento(*(id_personas + i)) == -1,
              "Chair reservation failed",
               1) == -1) return -1;
  }
  
  if (set_err(guarda_estado_sala(ruta_fichero) != 0,
              "Saving room state didn't work",
               1) == -1) return -1;
  
  return 0;
}

/*!
 * @function   libera_asientos
 * @abstract   Frees chairs for room given by file.val
 *                
 *
 * @param      fd           File.
 * @param      num_asientos Number of chairs.
 * @param      id_asientos  Set of chair ids.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int libera_asientos(const char* ruta_fichero, size_t num_asientos, int* id_asientos) {
  if (set_err(recupera_estado_sala(ruta_fichero) != 0,
              "Recover room state didn't work",
               1) == -1) return -1;
  
  for (int i = 0; i < num_asientos; i++) {
    if (set_err(libera_asiento(*(id_asientos + i)) == -1,
              "Freeing chair failed",
               1) == -1) return -1;
  }
  
  if (set_err(guarda_estado_sala(ruta_fichero) != 0,
              "Saving room state didn't work",
               1) == -1) return -1;
  
  return 0;
}

/**
 * @function  size_of_char
 * 
 * @param     number        value to be count
 * 
 * @return    Returns the count of chars.
*/
int size_of_char(char* number) {
    int size = 0;
    while (*(number + size) != '\0') {
        size++;
    }
    
    return size;
}

/*!
 * @function   guarda_estadoparcial_sala
 * @abstract   Saves state of given chairs in room given by file.
 *                
 *
 * @param      fd           File.
 * @param      num_asientos Number of chairs.
 * @param      id_asientos  Set of chair ids.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int guarda_estadoparcial_sala(const char* ruta_fichero, size_t num_asientos, int* id_asientos) {
    if (num_asientos >= capacidad()) return -1; 
    // variables
    int fd = open(ruta_fichero, O_RDONLY);                                      // opens a file on read only mode
    int fd2 = open("tmp_file", O_TRUNC | O_CREAT | O_RDWR, 0755);               // opens a file or creates it if is nonexistent
    char* char_aux = calloc(sizeof(int), sizeof(char));                         // frees a byte for each possible unit of a integer
    
    if (fd == -1) {
      print_error("Opening file failed on writing context");
      return -1;
    }
    
    // saves capacity
    sprintf(char_aux, "%d", read_file_line(fd));
    if(write_file_line(fd2, char_aux) == -1) return -1;
    
    // saves reservations
    for (int i = 0; i < capacidad(); i++) {
      sprintf(char_aux, "%d", read_file_line(fd));
      if(write_file_line(fd2, char_aux) == -1) return -1;

      for (int j = 0; j < num_asientos; j++) {
          if (*(id_asientos + j) == i) {
            lseek(fd2, (-size_of_char(char_aux) - 1), SEEK_CUR);                // shifts pointer to position of last written number
            sprintf(char_aux, "%d", estado_asiento(i));
            if(write_file_line(fd2, char_aux) == -1) return -1;                 // overwrites last written number
          }
      }
    }
    
    free(char_aux);
    if(close(fd) == -1) {
      print_error("Closing file failed on writing context");
      return -1;
    }
    
    unlink(ruta_fichero);
    link("tmp_file", ruta_fichero);
    unlink("tmp_file");
    
    return 0;
    
  return 0;
}

/*!
 * @function   recupera_estaparcial_sala
 * @abstract   Recover state of given chair in room given by file.
 *                
 *
 * @param      fd           File.
 * @param      num_asientos Number of chairs.
 * @param      id_asientos  Set of chair ids.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int recupera_estadoparcial_sala(const char* ruta_fichero, size_t num_asientos, int* id_asientos) {
    // variables
    int fd = open(ruta_fichero, O_RDONLY);                                      // opens an existing file
    int int_aux;
    
    if (fd == -1) {
      print_error("Opening file failed on reading context");
      return -1;
    }
    crea_sala(read_file_line(fd));
    // saves reservations
    for (int i = 0; i < capacidad(); i++) {
        int_aux = read_file_line(fd);
        for (int j = 0; j < num_asientos; j++) {
          if (*(id_asientos + j) == i) {
            reserva_asiento_concreto(int_aux, i);
          }
        }
    }
    
    if(close(fd) == -1) {
      print_error("Closing file failed on reading context");
      return -1;
    }
    
    return 0;
}
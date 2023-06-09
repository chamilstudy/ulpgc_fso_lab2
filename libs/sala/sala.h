/*!
 *  @author   Chamil José Cruz Razeq
 *  
 *  @version  1.0.0.0
 *  @date     09-03-23
 *
 *  @abstract Operative Systems Fundamentals Lab 2
*/

/*!
 * @function   existe_id
 * @abstract   Checks if client ID exists.
 * @discussion Checks if client ID exists and returns 1, if not returns 0.
 *                
 *
 * @param      id       Client ID to check.     
 *
 * @return     Returns 0 if not found and 1 if found.
*/
int existe_id(int id);

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
int reserva_asiento_concreto(int id, int pos);

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
int reserva_asiento(int id);

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
int libera_asiento(int asiento);

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
int estado_asiento(int asiento);

/*!
 * @function   asientos_libres
 * @abstract   Checks the number of available chairs.
 *
 * @return     Number of available chairs.
*/
int asientos_libres();

/*!
 * @function   asientos_ocupados
 * @abstract   Checks the number of booked chairs.
 *
 * @return     Number of available chairs.
*/
int asientos_ocupados();

/*!
 * @function   capacidad
 * @abstract   Checks the capacity of room.
 *
 * @return     Capacity of room.
*/
int capacidad();

/*!
 * @function   crea_sala
 * @abstract   Creates new room.
 * 
 * @param      capacidad       The capacity of the room.
*/
void crea_sala(int capacidad);

/*!
 * @function   elimina_sala
 * @abstract   Removes room.
*/
void elimina_sala();

/*!
 * @function   print_asientos
 * @abstract   Prints chairs and clients id as a table.
*/
void print_asientos();

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
int write_file_line(const int fd, const char* char_aux);

/*!
 * @function   read_file_line
 * @abstract   reads line on given file.
 *                
 *
 * @param      fd       File.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int read_file_line(const int fd);

/*!
 * @function   guarda_estado_sala
 * @abstract   Saves current room state on a file.
 *                
 *
 * @param      fd       File name.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int  guarda_estado_sala (const	char* ruta_fichero);

/*!
 * @function   recupera_estado_sala
 * @abstract   Recovers data from file and uploads it into the room structure.
 *                
 *
 * @param      fd       File.
 *
 * @return     Returns 0 if successful and -1 if not.
*/
int recupera_estado_sala (const char* ruta_fichero);

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
int reserva_asientos(const char* ruta_fichero, size_t num_asientos, int* id_personas);

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
int libera_asientos(const char* ruta_fichero, size_t num_asientos, int* id_asientos);

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
int guarda_estadoparcial_sala(const char* ruta_fichero, size_t num_asientos, int* id_asientos);

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
int recupera_estadoparcial_sala(const char* ruta_fichero, size_t num_asientos, int* id_asientos);
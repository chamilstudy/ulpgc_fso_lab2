
/*!
 * @function   print_error
 * @abstract   Prints error.
 * @discussion If there is a error passed by errno, prints given message and
 +             perror message.
 *                
 *
 * @param      err_msg  Error message.     
 *
 * @return     Returns 0 if an error was caught and prints message and perror,
 *             if there are no errors returns -1.
*/
int print_error(const char* err_msg);

/*!
 * @function   set_err
 * @abstract   Sets error.
 * @discussion If state is 1, sets given error and prints given message.
 *                
 *
 * @param      state      Result of condition evaluated.
 * @param      err_msg    Error message.
 * @param      err_number Error number.
 *
 * @return     Returns -1 if an error was caught, sets errno and prints message
 *             and perror, if there are no errors returns 0.
*/
int set_err(const int state, const char* err_msg, const int err_number);
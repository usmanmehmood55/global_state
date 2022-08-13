#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Errors for indicating results of various operations
 * performed on the global state.
 */
typedef enum
{
    STATE_ERR           = -1,
    STATE_OK            = 0,
    STATE_ACCESS_DENIED = 1,
    STATE_PORT_BUSY     = 2,
} state_error_t;

/**
 * @brief External code should be able to read this counter as is, so it will be decreased by one
 * since the act of accessing the counter itself increments it.
 * 
 * @return uint16_t number of times the global state has been accessed
 */
uint16_t get_access_count();

/**
 * @brief Function to check if the device is connected.
 * 
 * @return true if the device is connected.
 */
bool get_is_connected();

/**
 * @brief Function to check if the port is open.
 * 
 * @return true if the port is open.
 */
bool get_is_open();

/**
 * @brief This function shows how middleware can perform error reporting and prevent multiple
 * operations on a resource when multiple options shouldn't happen. In this case, opening a 
 * port that is already open should indicate that the port is busy.
 * 
 * @return state_error_t STATE_OK if successful, STATE_PORT_BUSY if the port is already open.
 */
state_error_t port_open();

/**
 * @brief This function shows how middleware can automate some of the behaviors of a system. In
 * this case, closing the port should also disconnect the device.
 */
void port_close();

/**
 * @brief This function shows how middleware can work and guard the global port_state from being 
 * mutated recklessly by other code. In order to connect to a 'port', clearly it must be
 * opened first, using the port_open() function. In case the port isn't open, and some other 
 * code tries to connect to it, the function will simply return an exception, indicating that 
 * the port's access was denied.
 * 
 * @return state_error_t STATE_OK if connection was available, STATE_ACCESS_DENIED otherwise
 */
state_error_t port_connect();

/**
 * @brief The function allows the device to disconnect in any condition.
 */
void port_disconnect();


#endif // _CONTEXT_H_
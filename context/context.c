#include "context.h"

/**
 * @brief The structure used to store the global port_state, and has restricted access 
 * because it is places in the .c file. 
 */
typedef struct
{
    uint16_t access_counter; // A counter used to track the number of times the port_state is accessed
    bool     is_open;        // Indicates if the port is open
    bool     is_connected;   // Indicates if the port is connected
} port_state;

/**
 * @brief A static function is declared here to prevent any other code, including the .h 
 * file, from seeing this function or using it. Only the functions inside this .c file 
 * can access this function. 
 * 
 * Inside it is the struct containing the global port_state, and is declared static, to allow it 
 * to maintain its values even after the function returns.
 * 
 * This can have the effect of being a global variable without giving other functions access
 * to the struct itself directly.
 * 
 * Having such an arrangement allows use of middleware code to perform checks or to prevent 
 * access.
 * 
 * @return port_state* pointer to the struct containing the global port_state
 */
static port_state * get_state()
{
    static port_state global_state;
    return &global_state;
}

/**
 * @brief External code should be able to read this counter as is, so it will be decreased by one
 * since the act of accessing the counter itself increments it.
 * 
 * @return uint16_t number of times the global state has been accessed
 */
uint16_t get_access_count()
{
    port_state *_state = get_state();
    return _state->access_counter;
}

/* ==============================================================================================
 * Every time a value is get or set, the relevant counter is increased. This shows 
 * how access to global port_state variables can be monitored or even controlled.
 ============================================================================================== */

/**
 * @brief Function to check if the device is connected.
 * 
 * @return true if the device is connected.
 */
bool get_is_connected()
{
    port_state *_state = get_state();
    _state->access_counter++;
    return _state->is_connected;
}

/**
 * @brief Function to check if the port is open.
 * 
 * @return true if the port is open.
 */
bool get_is_open()
{
    port_state *_state = get_state();
    _state->access_counter++;
    return _state->is_open;
}

/**
 * @brief This function shows how middleware can perform error reporting and prevent multiple
 * operations on a resource when multiple options shouldn't happen. In this case, opening a 
 * port that is already open should indicate that the port is busy.
 * 
 * @return state_error_t STATE_OK if successful, STATE_PORT_BUSY if the port is already open.
 */
state_error_t port_open()
{
    port_state *_state = get_state();
    state_error_t err = STATE_ERR;

    if (!_state->is_open)
    {
        _state->access_counter++;
        _state->is_open = true;
        err = STATE_OK;
    }
    else
    {
        err = STATE_PORT_BUSY;
    }

    return err;
}

/**
 * @brief This function shows how middleware can automate some of the behaviors of a system. In
 * this case, closing the port should also disconnect the device.
 */
void port_close()
{
    port_state *_state = get_state();
    _state->access_counter++;
    _state->is_connected = false;
    _state->is_open = false;
}

/**
 * @brief This function shows how middleware can work and guard the global port_state from being 
 * mutated recklessly by other code. In order to connect to a 'port', clearly it must be
 * opened first, using the port_open() function. In case the port isn't open, and some other 
 * code tries to connect to it, the function will simply return an exception, indicating that 
 * the port's access was denied.
 * 
 * @return state_error_t STATE_OK if connection was available, STATE_ACCESS_DENIED otherwise
 */
state_error_t port_connect()
{
    port_state *_state = get_state();
    state_error_t err = STATE_ERR;

    if (_state->is_open)
    {
        _state->access_counter++;
        _state->is_connected = true;
        err = STATE_OK;
    }
    else
    {
        err = STATE_ACCESS_DENIED;
    }

    return err;
}

/**
 * @brief The function allows the device to disconnect in any condition.
 */
void port_disconnect()
{
    port_state *_state = get_state();
    _state->access_counter++;
    _state->is_connected = false;
}

char * err_str(state_error_t err)
{
    switch (err)
    {
        case STATE_OK:
            return "STATE_OK";
        case STATE_ERR:
            return "STATE_ERR";
        case STATE_ACCESS_DENIED:
            return "STATE_ACCESS_DENIED";
        case STATE_PORT_BUSY:
            return "STATE_PORT_BUSY";
        default:
            return "UNKNOWN";
    }
}
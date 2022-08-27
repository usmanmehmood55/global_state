#include <stdio.h>
#include <stdint.h>
#include "context/context.h"

/**
 * @brief Example code to demonstrate use of the context library along with its error reporting.
 * 
 * @return state_error_t STATE_OK if successful.
 */
state_error_t read_port(void)
{
    state_error_t err = STATE_OK;

    // Check if the port is open. If not, use the port_open function to open it.
    bool is_open = get_is_open();
    if (!is_open)
    {
        err = port_open();

        // If the port could not be opened, print an error message, and return.
        if (err != STATE_OK)
        {
            printf("Error opening port: %s\n", err_str(err));
            return err;
        }
    }

    // Check if the device is connected. If not, use the connect function to connect it.
    bool is_connected = get_is_connected();
    if (!is_connected)
    {
        err = port_connect();

        // If the device could not be connected, print an error message, and return.
        if (err != STATE_OK)
        {
            printf("Error connecting to port: %s\n", err_str(err));
            return err;
        }
    }

    {
        // Code to read the port should go here.
    }

    return err;
}

void main(void)
{
    state_error_t err = STATE_OK;

    // first try to connect without opening a port
    err = port_connect();

    // then open a port
    err = port_open();

    // then connect to it
    err = port_connect();

    // then try to open the port again
    err = port_open();

    // then close the port
    port_close();

    // Example code for reading data from the hypothetical port
    err = read_port();
    if (err == STATE_OK)
    {
        printf("Successfully read data from the port.\n");
    }
}

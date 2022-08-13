#include <stdio.h>
#include "context/context.h"

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

    // Example code
    if (!get_is_open())
    {
        port_open();
    }
    if (!get_is_connected())
    {
        port_connect();
    }
}

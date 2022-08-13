# Global State

C code showing global state management of a hypothetical system port. This is achieved by using a static structure inside a static function, 
along with getters and setters to access that structure.

The structure can contain any number of variables that make up the global state.
```c
typedef struct
{
    uint16_t access_counter; // A counter used to track the number of times the port_state is accessed
    bool     is_open;        // Indicates if the port is open
    bool     is_connected;   // Indicates if the port is connected
} port_state;
```
And can be declared as follows:
```c
static port_state * get_state()
{
    static port_state global_state;
    return &global_state;
}
```

Which can be accessed as follows:
```c
bool get_is_connected()
{
    port_state *_state = get_state();
    _state->access_counter++;
    return _state->is_connected;
}
```

The full working has been explained in detail inside the [context.c](context/context.c) and [context.h](context/context.h) files, while
some example codes are written in [main.c](main.c).
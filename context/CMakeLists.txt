# Indicate the source files
set(LIB_SRCS context.h  context.c)

# Set the library type as static
SET (LIB_TYPE STATIC)

add_library (context ${LIB_TYPE} ${LIB_SRCS})
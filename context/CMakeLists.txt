set(INTERFACES_SRCS context.h  context.c)

SET (LIB_TYPE STATIC)

add_library (context ${LIB_TYPE} ${INTERFACES_SRCS})
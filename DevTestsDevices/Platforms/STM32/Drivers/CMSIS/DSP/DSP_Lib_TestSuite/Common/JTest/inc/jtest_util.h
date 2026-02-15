#pragma once

/*--------------------------------------------------------------------------------*/
/* Includes */
/*--------------------------------------------------------------------------------*/

#include "util/util.h"

/*--------------------------------------------------------------------------------*/
/* Macros and Defines */
/*--------------------------------------------------------------------------------*/

/* Define boolean values for the framework. */
#define JTEST_TRUE  1           /**< Value used for TRUE in JTEST. */
#define JTEST_FALSE 0           /**< Value used for FALSE in JTEST. */

/**
 *  Set the value of the attribute in the struct to by struct_ptr to value.
 */
#define JTEST_SET_STRUCT_ATTRIBUTE(struct_ptr, attribute, value)    \
    do                                                              \
    {                                                               \
        (struct_ptr)->attribute = (value);                          \
    } while (0)


#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct Customers {
    char *email;    //email
    char *name;   // the name/nickname
    char *fav_food;  // values
    int shoe_size; // values
    struct Customers *next;
} Customers;

typedef struct Table {
    // the actual buckets
    Customers **buckets;
    // num_buckets
    int num_buckets;
} Table;


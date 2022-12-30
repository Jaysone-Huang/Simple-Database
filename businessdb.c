#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "businessdb.h"
#define BUF_SIZE 1024


unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while (*str != '\0') {
    c = *str;
    hash = ((hash << 5) + hash) + (unsigned char)c; /* hash * 33 + c */
    str++;
  }
  return hash;
}

Customers *add_to_list(char * email, char *name, char *food, int shoe, Customers *bucket) {
  Customers* new_friend;
  new_friend = calloc(1, sizeof(Customers));
  new_friend->email = strdup(email);
  new_friend->name = strdup(name);
  new_friend->fav_food = strdup(food);
  new_friend->shoe_size = shoe;
  new_friend->next = bucket;

  return new_friend;
}

void add_to_table(char * email, char *name, char *food, int shoe, Table *table) {
  unsigned long hashvalue = hash(email);
  size_t which_bucket = hashvalue % table->num_buckets;

  Customers *linkedlist = table->buckets[which_bucket];
  table->buckets[which_bucket] = add_to_list(email, name, food, shoe, linkedlist);
  return;
}

bool look_up(char *email, Table *table) {
  unsigned long hashvalue = hash(email);
  unsigned long which_bucket = hashvalue % table->num_buckets;

  Customers *here = table->buckets[which_bucket];

  while(here) {
    if (!strcmp(here->email, email)) {
      printf("Your user information: \n");
      printf("Email: %s\n", here->email);
      printf("Name: %s\n", here->name);
      printf("Favorite Food: %s\n", here->fav_food);
      printf("Shoe Size: %d\n", here->shoe_size);
      printf("\n");
      return true;
    }
    here = here->next;
  }
  return false;
}

bool email_check(char *email, Table *table) {
  unsigned long hashvalue = hash(email);
  unsigned long which_bucket = hashvalue % table->num_buckets;

  Customers *here = table->buckets[which_bucket];

  while(here) {
    if (!strcmp(here->email, email)) {

      return true;
    }
    here = here->next;
  }
  return false;
}

Customers* delete_user_from_list(char *email, Customers *linkedlist) {
  if (!linkedlist) {
    return NULL;
  } else if (!strcmp(email, linkedlist->email)) {
    // match!!

    // need to free this node!
    Customers *next = linkedlist->next;
    // now delete this node.
    free(linkedlist->name);
    free(linkedlist->fav_food);
    free(linkedlist->email);
    free(linkedlist);
    return next;
  } else {
    // recursive case!!
    linkedlist->next = delete_user_from_list(email, linkedlist->next);
    return linkedlist;
  }
}

bool byebye_user(char *email, Table *table) {
  unsigned long hashvalue = hash(email);
  size_t which_bucket = hashvalue % table->num_buckets;

  Customers *linkedlist = table->buckets[which_bucket];

  bool found = false;
  Customers *here = linkedlist;
  while(here) {
    if (!strcmp(here->email, email)) {
      found = true;
      break;
    }
    here = here->next;
  }
  if (!found) {
    return false;
  } 

  table->buckets[which_bucket] = delete_user_from_list(email, linkedlist);
  return true;
}

void delete_table(Table *table) {
  // for each bucket, delete everything in that bucket
  for (int i=0; i < table->num_buckets; i++) {
    Customers *here = table->buckets[i];
    while(here) {
      free(here->name);
      free(here->fav_food);
      free(here->email);
      Customers *freethis = here;
      here = here->next;
      free(freethis);
    }
  }
  free(table->buckets);
  free(table);
}

void remove_new_lines(char *s){
    if(s == NULL){
        return;
    }
    char *newline;
    newline = strchr(s, '\n');
    if (newline){
        *newline = '\0';
    }
}

Table *build_table(size_t num_buckets) {
  Table* output = calloc(1, sizeof(Table));
  output->num_buckets = num_buckets;

  // allocate space for num_buckets FriendNode pointers.
  // THEY ARE ALREADY NULL POINTERS.
  output->buckets = calloc(num_buckets, sizeof(Customers *));

  return output;
}

void list_user(Table *table) {
  // for each bucket, delete everything in that bucket
  printf("Here are the information\n");
  for (int i=0; i < table->num_buckets; i++) {
    Customers *here = table->buckets[i];
    while(here) {
      printf("Email: %s\n", here->email);
      printf("Name: %s\n", here->name);
      printf("Favorite Food: %s\n", here->fav_food);
      printf("Shoe Size: %d\n", here->shoe_size);
      printf("\n");
      here = here->next;
    }
  }
  return;
}

void save_file(Table *table){
  FILE *saveme;
  saveme = fopen("customers.tsv", "w");
  for (int i=0; i < table->num_buckets; i++) {
    Customers *here = table->buckets[i];
    while(here) {
    char *save = "%s\t%s\t%d\t%s\n";
    fprintf(saveme, save, here->email, here->name, here->shoe_size, here->fav_food);
    here = here->next;
    }
  }
  fclose(saveme);
  printf("File has been saved.\n");
  printf("\n");
}

int main(void){
    Table *Database = build_table(10);
    FILE *infile;
    infile = fopen("customers.tsv", "r");
    char buff[BUF_SIZE];
    char *email;
    char *food;
    char *shoe;
    char *name;
    int shoe_num = 0;
    while (fgets(buff, BUF_SIZE, infile) != NULL){
        remove_new_lines(buff);
        email = strtok(buff, "\t");

        name  = strtok(NULL, "\t");

        shoe = strtok(NULL, "\t");
        shoe_num = atoi(shoe);

        food = strtok(NULL, "\t");
        add_to_table(email, name, food, shoe_num, Database);
        //look_up(email, Database);
    }
    fclose(infile);

    //open_up_your_hole();
    //printf("loaded\n");
    char buffer[BUF_SIZE];
    char *command;
    while (true){
        printf("|Here are a list of commands|\n");
        printf("add:\n");
        printf("lookup:\n");
        printf("delete:\n");
        printf("list:\n");
        printf("save:\n");
        printf("quit:\n");
        printf("Commands here: ");
        command = fgets(buffer, 100, stdin);
        if (!command){
            break;
        }
        remove_new_lines(buffer);
        //quit command
        if (!strcmp(buffer, "quit")){
            printf("Ok, see you later.\n");
            delete_table(Database);
            break;
        //add command
        } else if (!strcmp(buffer, "add")){
            //do add command code
            char *A_email;
            char *A_name;
            char *A_shoe;
            char *A_food;
            printf("Please enter your email: ");
            fgets(buffer, BUF_SIZE, stdin);
            remove_new_lines(buffer);
            A_email = strdup(buffer);
            if (email_check(A_email, Database)){
              printf("Email exists, time to replace.\n");
              byebye_user(A_email, Database);
            }
            printf("Please enter your name: ");
            fgets(buffer, BUF_SIZE, stdin);
            remove_new_lines(buffer);
            A_name = strdup(buffer);
            printf("Please enter your favorite food: ");
            fgets(buffer, BUF_SIZE, stdin);
            remove_new_lines(buffer);
            A_food = strdup(buffer);
            printf("Please enter your shoe size: ");
            fgets(buffer, BUF_SIZE, stdin);
            remove_new_lines(buffer);
            A_shoe = strdup(buffer);
            shoe_num = atoi(A_shoe);      
            add_to_table(A_email, A_name, A_food, shoe_num, Database);
            //printf("Your information Master:\n");
            look_up(A_email, Database);
            free(A_email);
            free(A_name);
            free(A_shoe);
            free(A_food);
        //lookup command 
        } else if (!strcmp(buffer, "lookup")){
            //ask for emailaddress then look for it and display the contents 
            printf("Please enter your email: \n");
            fgets(buffer, BUF_SIZE, stdin);
            remove_new_lines(buffer);
            if (look_up(buffer, Database) == 0){
                printf("Sorry, couldn't find your email. :(\n");
            }
            //if not found, say they dont exist and that they have no essence in this world
        

        //delete command
        } else if (!strcmp(buffer, "delete")){
            //ask for emailaddress then look for it and delete it from linked list in the bucket
            printf("Please enter the user's email you want to delete: \n");
            fgets(buffer, BUF_SIZE, stdin);
            remove_new_lines(buffer);
            if (byebye_user(buffer, Database)){
              printf("User is now gone.\n");
            } else {
              printf("Sorry, couldn't find your email. :(\n");
            }
          
            

            //if not found, say they dont exist and that they have no essence in this world

        } else if (!strcmp(buffer, "list")){
            list_user(Database);

        } else if (!strcmp(buffer, "save")){
          save_file(Database);

        } else {
            printf("Error that is not a valid command, please try again.\n");
            printf("\n");
        }

    }   

}

/* FUBAS - FUnctional BASic
 * Copyright (C) 2020 Mike Warot <chezmike@gmail.com>
 * 
 * STOICAL is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 * 
 * STOICAL is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with STOICAL; see the file COPYING.  If not,write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. 
 */


#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int done = 0;                  
int command_input_count = 0;    // every line the user types in has a serial number, so they can use it later
char command_line_buffer[500];  // reasonably long input buffer, hopefully never actually filled

/*
  Put previous command lines into a doubly linked list
*/
typedef struct linkedstring{
   struct linkedstring *prev, *next;
   char key[20];
   char value[500];
} linkedstring;

linkedstring* headlinkedstring = NULL;
linkedstring* lastlinkedstring = NULL;
linkedstring* newlinkedstring = NULL;
linkedstring* foundstring = NULL;

linkedstring* findkey(char* searchkey) {
   linkedstring* currentkey = headlinkedstring;  // start at first key/value pair in the list
   while ((currentkey != NULL) && (strcasecmp(currentkey->key,searchkey)!=0)) {
      currentkey = currentkey->next;
   }
   return currentkey;
}

linkedstring* addkeyvalue(char* key, char* value) {
   linkedstring* tmplinkedstring;
   tmplinkedstring = (linkedstring*) malloc(sizeof(linkedstring));
   if (tmplinkedstring != NULL) {
      tmplinkedstring->prev = lastlinkedstring;
      if (tmplinkedstring->prev == NULL) {
         headlinkedstring = tmplinkedstring;
      } else {
         tmplinkedstring->prev->next = tmplinkedstring;
      }
      tmplinkedstring->next = NULL; 
      lastlinkedstring = tmplinkedstring;
      strcpy(tmplinkedstring->key,key);
      strcpy(tmplinkedstring->value,value);
   }
   return tmplinkedstring;
}

int main() {
   do {
      printf("\033[0;32m$$%d\033[0m ",++command_input_count);        // start off the user with a nice prompt

      fgets(command_line_buffer,500,stdin);
      int len = strlen(command_line_buffer);
      if ((len > 0) && (command_line_buffer[len-1] == '\n')) command_line_buffer[len-1] = '\0';

      char newkey[20];
      sprintf(newkey,"$i%i",command_input_count);
      if (addkeyvalue(newkey,command_line_buffer) == NULL) done=1;

      foundstring = findkey(command_line_buffer);
      if (foundstring != NULL) {
         strcpy(command_line_buffer,foundstring->value);
      }

      sprintf(newkey,"$o%i",command_input_count);
      if (addkeyvalue(newkey,command_line_buffer) == NULL) done=1;

      printf("You said: >>%s<<\n",command_line_buffer);


      if (strlen(command_line_buffer) == 0) done=1;
   } while(done == 0);

   newlinkedstring = headlinkedstring;
   while (newlinkedstring != NULL)
   {
      /* code */
      printf("Key: %s\tValue: %s\n",newlinkedstring->key,newlinkedstring->value);
      newlinkedstring = newlinkedstring->next;
   }
   
   return 0;
}
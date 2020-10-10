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

int main() {
   do {
     printf("\033[0;32m$$%d\033[0m ",++command_input_count);        // start off the user with a nice prompt
     fgets(command_line_buffer,500,stdin);
       printf("You said: r%s\n",command_line_buffer);
       newlinkedstring = (linkedstring*) malloc(sizeof(linkedstring));
       if (newlinkedstring == NULL) {
          printf("Ran out of memory\n");
          done = 1;
       } 
       else {
          newlinkedstring->prev = lastlinkedstring;
          if (newlinkedstring->prev == NULL) {
             headlinkedstring = newlinkedstring;
          } else {
             newlinkedstring->prev->next = newlinkedstring;
          }
          newlinkedstring->next = NULL; 
          lastlinkedstring = newlinkedstring;

          sprintf(newlinkedstring->key,"$$%i",command_input_count);
          strcpy(newlinkedstring->value,command_line_buffer);
          if (command_line_buffer[0] == '\n') {
             done=1; 
          };
       }
   } while(done == 0);

   newlinkedstring = headlinkedstring;
   while (newlinkedstring != NULL)
   {
      /* code */
      printf("Key: %s  Value: %s",newlinkedstring->key,newlinkedstring->value);
      newlinkedstring = newlinkedstring->next;
   }
   
   return 0;
}
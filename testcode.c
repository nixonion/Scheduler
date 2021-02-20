#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clock.h"
#include "structs.h"
#include "constants.h"


int schedule_count(Process *list) 
{
	Process *walker = list;
	int count=0;
	while(walker != NULL) 
	{
		count++;
	    walker = walker->next;
	}
  /* Complete this Function */
  return count;
}

/* Schedule Insert
 * - Insert the Process into the List with the Following Constraints
 *   list is a pointer to the head pointer for a singly linked list.
 *   It may begin as NULL
 *   1) Insert in the order of Ascending PIDs
 *   (eg. 1, 13, 14, 20, 32, 55)
 * Remember to set list to the new head if it changes!
 */
void schedule_insert(Process **list, Process *node) 
{
  /* Complete this Function */
	Process *walker = *list;
	if(node == NULL) 
	{
		return;	
	}
	if(walker == NULL) 
	{
		*list = node;
		return;
	}
	  // Case 2: Check if we insert up front
	if(node->pid < (*list)->pid) 
	{
		node->next = *list;
		*list = node;
		return;
	}
	  // Case 3: Find where we should insert (we know there is at least one node)
	while(walker != NULL && walker->next != NULL) 
	{
		if(walker->next->pid >= node->pid) 
		{
	    	node->next = walker->next;
	      	walker->next = node;
	      	return;
	    }
	}
	walker->next=node;
	node->next=NULL;
}

/* Schedule Terminate
 * - Unallocate the Memory for the given Node
 */
void schedule_terminate(Process *node) 
{
  /* Complete this Function */
	node->next=NULL;
	free(node); 
  	return;
}

/* Schedule Generate
 * - Allocate the Memory and Create the Process from the given Variables
 *   Remember to initialize all values, including next!
 */
Process *schedule_generate(const char *name, int pid, int time_remaining, int time_last_run) 
{
  /* Complete this Function */
	Process *new=malloc(sizeof(Process));
	if(new == NULL)
	{
		return NULL;
	}
	new->next=NULL;
	strncpy(new->name, name, strlen(name) + 1);
	new->pid=pid;
	new->time_remaining=time_remaining;
	new->time_last_run=time_last_run;
  	return new;
}

/* Schedule Select
 * - Select the next Process to be run using the following conditions:
 *   1) The Process with the lowest time_remaining should run next.
 *   - If there are any ties, select the Process with the lowest PID
 *   2) If there is a Process that has not run in >= TIME_STARVATION, then
 *      select that one instead.
 *      (Use the function clock_get_time() to get the current time)
 *   - If there are any ties, select the Process with the lowest PID
 *   3) If the list is NULL, return NULL
 * - Remove the selected Process from the list
 * - Return the selected Process
 */
Process *schedule_select(Process **list) 
{
/* Complete This Function */

	Process *walker = *list;
	if (walker == NULL)
	{
		return NULL;
	}
	Process *reaper= walker;
	//int time = walker->time_remaining;
	Process *remover= NULL;
	Process *node_to_remove= walker;

	while(walker->next != NULL) 
	{
		node_to_remove=walker;
		walker=walker->next;
		if((walker->time_remaining) < (reaper->time_remaining))
		{
			reaper=walker;
			remover=node_to_remove;
		}
		
	}
	walker=*list;
	Process *starved_remover=NULL;
	Process *starved_reaper=NULL;
	int time_check;

	while(walker!=NULL)
	{
		time_check=clock_get_time();
		time_check=time_check-(walker->time_last_run);
		if (time_check>=TIME_STARVATION)
		{
			/* code */
			starved_reaper=walker;
			break;
		}
		starved_remover=walker;
		walker=walker->next;
	}
	if (starved_reaper != NULL)
	{
		reaper=starved_reaper;
		remover=starved_remover;
	}
	if (reaper->pid == (*list)->pid)
	{
		*list=*list->next;
		reaper->next=NULL;
		return reaper;	
	}
	remover=(remover->next)->next;
	reaper->next=NULL;
	return reaper;
}

void main()
{
	Process *head=NULL;
	//head=malloc(sizeof(Process));
	/*if(walker->time_remaining <= reaper->time_remaining)
		{
			if (walker->time_remaining == reaper->time_remaining)
			{
				if ((walker->pid)<(reaper->pid))
				{
					reaper=walker;
					remover=node_to_remove;
				}
			}
			else
			{
				reaper=walker;
				remover=node_to_remove;
			}
		}*/
	    //reaper = walker;
	    //walker = walker->next;
	    //free(reaper);
	    //reaper = NULL;





}








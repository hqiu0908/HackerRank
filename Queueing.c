/*

To get some exercise with queues, we’ll run a queueing simulation. “Queueing
theory” is the mathematical study of waiting in line -- one sees different
results depending on the arrival rate of people or things to service, their
strategies for choosing a line, and the time it takes to provide service. Here
we’ll just look at one happens in one slow line.

You’ll run a simulation of a line at an amusement park. Your program takes as an
input one integer, the number of people arriving in line per time step. (Assume
the input is a positive integer.)

The queue starts out empty. For twenty time steps, do the following:

Add a number of people (structs) equal to the arrival rate to the queue. (You
should be using a pointer to the end, so you don’t have to search to the end of
the queue.)

The person at the front of the queue is served and disappears.

Everybody else in line, including the new arrivals, has their patience decrease
by 1. New arrivals have a patience of 4 (3 after this happens).

Print the condition of the line as a string with a H for each “happy” customer
(patience > 0) and a U for each “unhappy” customer (patience <= 0). Thus an
happy person at the front of the line followed by two unhappy people would look
like this:

HUU

Your final output should have 20 lines, one per time step of the simulation.

Note that you must use linked-list based queues for this exercise, even if you
see a general way to predict the number of unhappy people; the point is giving
you some practice using queue data structures.

Input Format

A single positive integer.

Output Format

Twenty lines consisting of an H or U for each person in line at that time step,
depending on whether the person is happy or not. The front of the line is on the
left.

Sample Input

2

Sample Output

H HH HHH HHHH HHHHH HHHHHH UHHHHHH UUHHHHHH UUUHHHHHH UUUUHHHHHH UUUUUHHHHHH
UUUUUUHHHHHH UUUUUUUHHHHHH UUUUUUUUHHHHHH UUUUUUUUUHHHHHH UUUUUUUUUUHHHHHH
UUUUUUUUUUUHHHHHH UUUUUUUUUUUUHHHHHH UUUUUUUUUUUUUHHHHHH UUUUUUUUUUUUUUHHHHHH

Explanation

On the first time step, the second to arrive doesn't get served, but is still
happy. On the second time step, that person is served, but the two new arrivals
are not. Nevertheless, they will remain happy until they are served on turns 3
and 4, respectively. The first unhappy person, on line 7, was the third person
in line on line 4, and had 2 patience left on line 5, 1 left on line 6, and none
left on line 7, even though by that time he or she had made it to the front of
the line.

*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define COUNTER 4

/* queue.c:  a simple demo for showing enqueueing and dequeueing values */

struct person {
    int val;
    struct person *next;
};

struct queue {
    struct person *head;
    struct person *last;
};

struct queue *enqueue (int val, struct queue *q) {
    if (q->head == NULL) {
        q->head = malloc(sizeof(struct person));
        q->last = q->head;
        q->head->val = val;
        q->head->next = NULL;
    } else {
        q->last->next = malloc(sizeof(struct person));
        q->last = q->last->next;
        q->last->val = val;
        q->last->next = NULL;
    }
    return q;
}

struct queue *enqueueAtRate(int rate, struct queue *q) {
	for (int i = 0; i < rate; i++) {
		q = enqueue(COUNTER, q);
	}
	return q;
}

struct queue *decreasePatience(struct queue *q) {
    for (struct person *p = q->head; p != NULL; p = p->next) {
    	p->val -= 1;
	}
	return q;
}

struct queue *dequeue (struct queue *q) {
    if (q->head == NULL) {
        /* Should probably error here but we'll just return */
        return q;
    }
    struct person *old_head = q->head;
    q->head = q->head->next;
    free(old_head);
    if (q->head == NULL) {
        q->last = NULL;
    }
    q = decreasePatience(q);
    return q;
}

void print_queue(struct queue *q) {
    for (struct person *p = q->head; p != NULL; p = p->next) {
    	if (p->val <= 0) {
	        printf("U");
    	} else {
    		printf("H");
    	}
    }
    printf("\n");
}

int main() {
	int rate;
    scanf("%d", &rate);
    
    struct queue *q = malloc(sizeof(struct queue));
    q->head = NULL;
    q->last = NULL;
    
    for (int i = 0; i < 20; i++) {
        q = enqueueAtRate(rate, q);
        q = dequeue(q);
        print_queue(q);
    }
}
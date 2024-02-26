#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include "queue.h"

char * m_strcat(char * s1, char * s2) {
	int l1 = strlen(s1);
	int l2 = strlen(s2);

	char * s3 = malloc(sizeof(char) * (l1 + l2 + 1));
	
	memcpy(s3, s1, l1);
	memcpy(s3 + l1, s2, l2 + 1);
	
	return s3;
}

char * readline() {
	char s[82] = {0};
	char * res = malloc(sizeof(char) * 1);
	res[0] = '\0';

	int in = scanf("%81[^\n]", s);
	if (in == 0) {
		scanf("%*c");
		in = scanf("%81[^\n]", s);
	}
	while (in > 0) {
		char * tmp = res;
		res = m_strcat(s, res);
		free(tmp);
		in = scanf("%81[^\n]", s);
	}
	return res;
}

enum event_type {
	IN,
	OUT
};

typedef struct passenger {
	char * id;	
	int dur;
	int queue_assigned_idx;
} passenger_t;

typedef struct event {
	int timestamp;
	enum event_type e_type;
	passenger_t * passenger;
} event_t;

int compare_events(const void * p1, const void * p2) {
	event_t * e1 = (event_t *) p1;
	event_t * e2 = (event_t *) p2;
	if (e1->timestamp == e2->timestamp) {
		return 0;
	}
	return (e1->timestamp > e2->timestamp ? 1 : -1);
}

void output_queue_state(const void * p) {
	passenger_t * e = (passenger_t *) p;
	printf("%s ", e->id);
}

void out(const void * p) {
	event_t * event = (event_t *) p;
	printf("%s ", event->passenger->id);
}

int main() {

	srand(time(NULL));

	char * s = readline();

	char * outer_save_ptr = NULL;
	char * token = strtok_r(s, " ", &outer_save_ptr);
	if (token == NULL) {
		free(s);
		printf("Invalid input.\n");
		return 0;
	}

	int queue_count = atoi(token);
	if (queue_count < 2) {
		free(s);
		printf("Invalid input. Queue count must be > 2.\n");
		return 0;
	}

	printf("\n");

	queue_t * process_queues = malloc(sizeof(queue_t) * queue_count);

	// Forming event queue

	queue_t event_queue = create_new_queue();

	char * inner_save_ptr = NULL;

	token = strtok_r(NULL, " ", &outer_save_ptr);
	while (token != NULL) {
	
		char * id = strtok_r(token, "/", &inner_save_ptr);
		char * st_time_str = strtok_r(NULL, "/", &inner_save_ptr);
		char * st_time_dur = strtok_r(NULL, "/", &inner_save_ptr);

		event_t * st_event = (event_t *) malloc(sizeof(event_t) * 1);
		
		st_event->passenger = malloc(sizeof(passenger_t) * 1);
		st_event->passenger->id = id;
		st_event->passenger->dur = atoi(st_time_dur);
		st_event->timestamp = atoi(st_time_str);
		st_event->e_type = IN;

		printf("Adding event: id: %s timestamp: %d type: %d\n", st_event->passenger->id, st_event->timestamp, st_event->e_type);
		insert(event_queue, st_event);
		
		token = strtok_r(NULL, " ", &outer_save_ptr);
	}

	printf("\n");

	for_each(event_queue, out);

	printf("\n");

	// Event queue is formed

	// Sorting event_queue

	sort(event_queue, compare_events);

	for_each(event_queue, out);
	printf("\n");

	// Processing

	printf("Allocating %d queues.\n\n", queue_count);
	for (int i = 0; i < queue_count; i++) {
		process_queues[i] = create_new_queue();
	}

	while (!is_queue_empty(event_queue)) {

		event_t * event = (event_t *) pop(event_queue);
	
		
		printf("Processing event: id - %s, timestamp - %d, type - %d\n", event->passenger->id, event->timestamp, event->e_type);

		printf("\n");


		if (event->e_type == IN) {
			
			printf("Passenger (id: %s) came.\n", event->passenger->id);
			int f_idx = rand() % queue_count;

			int s_idx = f_idx;
			while (s_idx == f_idx) {
				s_idx = rand() % queue_count;
			}

			queue_t f_q = process_queues[f_idx];
			queue_t s_q = process_queues[s_idx];
			int res_idx = (size(f_q) > size(s_q) ? s_idx : f_idx);
			
			event->passenger->queue_assigned_idx = res_idx;
			printf("Assigned to queue # %d.\n", res_idx);
			
			insert( (size(f_q) > size(s_q) ? s_q : f_q) , event->passenger);

			for (int i = 0; i < queue_count; i++) {
				queue_t q = process_queues[i];
				printf("# %d: ", i);
				for_each(q, output_queue_state);
				printf("\n");
			}

			event_t * end_event = (event_t *) malloc(sizeof(event_t) * 1);
			end_event->passenger = event->passenger;
			end_event->timestamp = event->timestamp + event->passenger->dur;
			end_event->e_type = OUT;

			printf("Adding event: id: %s timestamp: %d type: %d\n", end_event->passenger->id, end_event->timestamp, end_event->e_type);
			insert(event_queue, end_event);

			
		} else {
			
			queue_t assigned = process_queues[event->passenger->queue_assigned_idx];
			printf("Passenger (id: %s) processed by queue # %d.\n", event->passenger->id, event->passenger->queue_assigned_idx);
			free(event->passenger);
			pop(assigned);
		}
		
		free(event);
	}

	// Main processing is done

	printf("\n");

	erase_queue(event_queue);

	printf("Freeing %d queues.\n\n", queue_count);
	for (int i = 0; i < queue_count; i++) {
		queue_t queue = process_queues[i];
		erase_queue(queue);
	}
	
	free(process_queues);
	
	free(s);
	return 0;
	
}

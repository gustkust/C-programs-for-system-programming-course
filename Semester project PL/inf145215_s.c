#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    struct msgbuf
    {
        long type;
        char message[50];
        char name[50];
        int option;
        int tid;
        int cid;
        int sub_type;
        int ms_number;
        int priority;
    } my_msg;

    struct client {
        char name[25];
    };

    struct message {
        char content[50];
        int thread_id;
        int priority;
    };

    struct subscriber {
        int subbed_threads[25];
        struct message messages[1000];
        int mi;
    };

    struct client clients[25];
    struct subscriber subscribers[25];
    for (int i = 0; i < 25; i++) {
        memset(subscribers[i].subbed_threads, 0, 25 * sizeof(int));
    }
    int threads[25];
    memset(threads, 0, 25 * sizeof(int));
    int users[25];
    memset(threads, 0, 25 * sizeof(int));


    int queue_id = msgget(0x660, 0644 | IPC_CREAT);
    printf("Serwer rozpoczyna pracę.\n");
    while (1) {
        msgrcv(queue_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0, 0);
        switch(my_msg.option) {
            case 0:
                strcpy(clients[my_msg.cid].name, my_msg.name);
                users[my_msg.cid] = 1;
                printf("Zalogowano klienta.\n");
                fflush(stdout);
                break;
            case 1:
                if (threads[my_msg.tid] == 1) {
                    my_msg.tid = 0;
                    int as_id = msgget(0x1000 + my_msg.cid, 0644 | IPC_CREAT);
                    strcpy(my_msg.message, " Wątek już istnieje.\n");
                    msgsnd(as_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                    printf("Wątek już istnieje.\n");
                    fflush(stdout);
                } else {
                    threads[my_msg.tid] = 1;
                    sprintf(my_msg.message, " Inny klient zarejestrował właśnie wątek %d.\n", my_msg.tid);
                    my_msg.tid = 0;
                    for (int i = 0; i < 25; i++) {
                        if (users[i] == 1 && i != my_msg.cid) {
                            int as_id = msgget(0x1000 + i, 0644 | IPC_CREAT);
                            msgsnd(as_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                        }
                    }
                    printf("Zarejestrowano wątek.\n");
                    fflush(stdout);
                }
                break;
            case 2:
                if (threads[my_msg.tid] == 0) {
                    my_msg.tid = 0;
                    int as_id = msgget(0x1000 + my_msg.cid, 0644 | IPC_CREAT);
                    strcpy(my_msg.message, " Wątek nie istnieje.\n");
                    msgsnd(as_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                    printf("Wątek nie istnieje.\n");
                    fflush(stdout);
                } else if (subscribers[my_msg.cid].subbed_threads[my_msg.tid] != 0) {
                    my_msg.tid = 0;
                    int as_id = msgget(0x1000 + my_msg.cid, 0644 | IPC_CREAT);
                    strcpy(my_msg.message, " Wątek jest już subskrybowany.\n");
                    msgsnd(as_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                    printf("Wątek jest już subskrybowany.\n");
                    fflush(stdout);
                } else {
                    if (my_msg.sub_type == 1) {
                        subscribers[my_msg.cid].subbed_threads[my_msg.tid] = my_msg.ms_number;
                    } else {
                        subscribers[my_msg.cid].subbed_threads[my_msg.tid] = -1;
                    }
                    printf("Zasubskrybowano wątek.\n");
                    fflush(stdout);
                }
                break;
            case 3:
                if (threads[my_msg.tid] == 0) {
                    my_msg.tid = 0;
                    int as_id = msgget(0x1000 + my_msg.cid, 0644 | IPC_CREAT);
                    strcpy(my_msg.message, " Wątek nie istnieje.\n");
                    msgsnd(as_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                    printf("Wątek nie istnieje.\n");
                    fflush(stdout);
                } else {
                    for (int i = 0; i < 25; i++) {
                        if (subscribers[i].subbed_threads[my_msg.tid] > 0) {
                            strcpy(subscribers[i].messages[subscribers[i].mi].content, my_msg.message);
                            subscribers[i].messages[subscribers[i].mi].thread_id = my_msg.tid;
                            subscribers[i].messages[subscribers[i].mi].priority = my_msg.priority;
                            subscribers[i].mi++;
                        }
                    }

                    for (int i = 0; i < 25; i++) {
                        if (subscribers[i].subbed_threads[my_msg.tid] == -1) {
                            int as_id = msgget(0x1000 + i, 0644 | IPC_CREAT);
                            msgsnd(as_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                            printf("Wysłano wiadomość asynchronicznie do klienta o numerze %d.\n", i);
                        }
                    }
                    printf("Wysłano wiadomość.\n");
                }
                break;
            case 4:
                if (threads[my_msg.tid] == 0) {
                    my_msg.tid = 0;
                    int as_id = msgget(0x1000 + my_msg.cid, 0644 | IPC_CREAT);
                    strcpy(my_msg.message, " Wątek nie istnieje.\n");
                    msgsnd(as_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                    msgsnd(queue_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                    printf("Wątek nie istnieje.\n");
                    fflush(stdout);
                } else if (subscribers[my_msg.cid].subbed_threads[my_msg.tid] == 0) {
                    my_msg.tid = 0;
                    int as_id = msgget(0x1000 + my_msg.cid, 0644 | IPC_CREAT);
                    strcpy(my_msg.message, " Nie ma już wiadomości lub nie subskrybujesz danego wątku.\n");
                    msgsnd(as_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                    msgsnd(queue_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                    printf("Klient nie subskrybuje danego wątku.\n");
                    fflush(stdout);
                } else {
                    int h_priority = 0;
                    int final_i = 0;
                    for (int i = 0; i < 1000; i++) {
                        if (subscribers[my_msg.cid].messages[i].thread_id == my_msg.tid && subscribers[my_msg.cid].messages[i].priority > h_priority) {
                            h_priority = subscribers[my_msg.cid].messages[i].priority;
                            strcpy(my_msg.message, subscribers[my_msg.cid].messages[i].content);
                            final_i = i;
                        }
                    }
                    subscribers[my_msg.cid].subbed_threads[my_msg.tid]--;
                    subscribers[my_msg.cid].messages[final_i].priority = -1;
                    my_msg.option = 5;
					msgsnd(queue_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
					printf("Odebrano wiadomość.\n");
					fflush(stdout);
                    memset(my_msg.message, ' ', 50 * sizeof(char));
                }
                break;
            case 5:
                break;
            case 6:
                return 0;
        }
    }
}

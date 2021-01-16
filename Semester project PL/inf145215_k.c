#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


//DZIALA

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

    int wrong_value = 1;
    char new_line[2];
    char id[3];
    char cid[3];
    int cid_i;

    int queue_id = msgget(0x660, 0644 | IPC_CREAT);

    while (wrong_value == 1) {
        printf("\nPodaj id klienta (liczba 1 - 25):\n>");
        fgets(cid, 3, stdin);
        if (cid[0] == '\n') {
            fgets(cid, 3, stdin);
        }
        cid_i = atoi(cid);
        my_msg.cid = cid_i;
        if (my_msg.cid > 25 || my_msg.cid < 1) {
            printf("Podano złą warość.\n");
        } else {
            wrong_value = 0;
        }
    }
    wrong_value = 1;

    int as_id = msgget(0x1000 + cid_i, 0644 | IPC_CREAT);

    if (fork() == 0) {
        while (1) {
            msgrcv(as_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0, 0);
            if (my_msg.tid != 0) {
                printf("\n\nNowa wiadomość z wątku %d:\n%s\n", my_msg.tid, my_msg.message);
            } else {
                printf("%s\n", my_msg.message);
            }
        }
    }

    printf("\nPodaj nazwę:\n>");
    fgets(new_line, 3, stdin);
    fgets(my_msg.name, 25, stdin);

    my_msg.type = 10;
    msgsnd(queue_id, &my_msg, sizeof(my_msg) - sizeof(long), 0);

    printf("\nCo chcesz zrobic (wpisz liczbe)?\n");
    printf("1 - Rejestracja nowego wątku.\n");
    printf("2 - Rejestracja do subskrybcji wątku.\n");
    printf("3 - Wysłanie wiadomości.\n");
    printf("4 - Odebranie wiadomości.\n");
    printf("5 - Wyjście.\n>");
    char option[2];
    my_msg.cid = cid_i;
    while (1) {
        queue_id = msgget(0x660, 0644 | IPC_CREAT);
        fgets(option, 2, stdin);
        option[0] = option[0] - '0';
        my_msg.option = option[0];
        int tmp4 = 0;
        switch (option[0]) {
            case 1:
                while (wrong_value == 1) {
                    printf("\nPodaj id wątku (liczba 1 - 25):\n>");
                    fgets(new_line, 2, stdin);
                    fgets(id, 3, stdin);
                    if (id[1] == '\n') {
                        id[1] = id[0];
                        id[0] = '0';
                        id[2] = '\0';
                    }
                    my_msg.tid = atoi(id);

                    if (my_msg.tid > 25 || my_msg.tid < 1) {
                        printf("Podano złą warość.\n");
                    } else {
                        wrong_value = 0;
                    }
                }
                wrong_value = 1;

                my_msg.type = 10;
                msgsnd(queue_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                break;
            case 2:
                while (wrong_value == 1) {
                    printf("\nPodaj id wątku (liczba 1 - 25):\n>");
                    fgets(new_line, 2, stdin);
                    fgets(id, 3, stdin);
                    if (id[1] == '\n') {
                        id[1] = id[0];
                        id[0] = '0';
                        id[2] = '\0';
                    }
                    my_msg.tid = atoi(id);

                    if (my_msg.tid > 25 || my_msg.tid < 1) {
                        printf("Podano złą warość.\n");
                    } else {
                        wrong_value = 0;
                    }
                }
                wrong_value = 1;
                while (wrong_value == 1) {
                    printf("\nPodaj rodzaj subskrybcji:\n");
                    printf("1 - przejściowa\n");
                    printf("2 - trwała\n>");
                    fgets(new_line, 2, stdin);
                    if (new_line[0] == '1' || new_line[0] == '2') {
                        id[0] = new_line[0];
                    } else {
                        fgets(id, 3, stdin);
                    }
                    if (id[0] == '1' || id[0] == '2') {
                        my_msg.sub_type = id[0] - '0';
                        wrong_value = 0;
                    } else {
                        printf("Podano złą warość.\n");
                    }
                }
                wrong_value = 1;

                if (id[0] == '1') {
                    printf("\nIle wiadomości chesz otrzymać (1 - 99)?\n>");
                    fgets(new_line, 2, stdin);
                    fgets(id, 3, stdin);
                    my_msg.ms_number = atoi(id);
                }

                my_msg.type = 10;
                msgsnd(queue_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                break;
            case 3:
                while (wrong_value == 1) {
                    printf("\nPodaj id wątku (liczba 1 - 25):\n>");
                    fgets(new_line, 2, stdin);
                    fgets(id, 3, stdin);
                    if (id[1] == '\n') {
                        id[1] = id[0];
                        id[0] = '0';
                        id[2] = '\0';
                        tmp4 = 1;
                    }
                    my_msg.tid = atoi(id);

                    if (my_msg.tid > 25 || my_msg.tid < 1) {
                        printf("Podano złą warość.\n");
                    } else {
                        wrong_value = 0;
                    }
                }
                wrong_value = 1;

                printf("\nPodaj wiadomość:\n>");
                if (tmp4 == 0) {
                    fgets(new_line, 2, stdin);
                }
                fgets(my_msg.message, 25, stdin);

                char priority[3];
                while (wrong_value == 1) {
                    printf("\nPodaj priorytet wiadomości (liczba 1 - 10):\n>");
                    fgets(priority, 3, stdin);
                    if (priority[1] == '\n') {
                        priority[1] = priority[0];
                        priority[0] = '0';
                        priority[2] = '\000';
                    }
                    my_msg.priority = atoi(priority);

                    if (my_msg.priority > 10 || my_msg.priority < 0) {
                        printf("Podano złą warość.\n");
                        fgets(new_line, 2, stdin);
                    } else {
                        wrong_value = 0;
                    }
                }
                wrong_value = 1;

                my_msg.type = 10;
                msgsnd(queue_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                break;
            case 4:
                my_msg.cid = cid_i;
                while (wrong_value == 1) {
                    printf("\nPodaj id wątku (liczba 1 - 25):\n>");
                    fgets(new_line, 2, stdin);
                    fgets(id, 3, stdin);
                    if (id[1] == '\n') {
                        id[1] = id[0];
                        id[0] = '0';
                        id[2] = '\0';
                    }
                    my_msg.tid = atoi(id);

                    if (my_msg.tid > 25 || my_msg.tid < 1) {
                        printf("Podano złą warość.\n");
                    } else {
                        wrong_value = 0;
                    }
                }
                wrong_value = 1;
                my_msg.type = 10;

                msgsnd(queue_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0);
                msgrcv(queue_id, &my_msg, sizeof(struct msgbuf) - sizeof(long), 0, 0);
                if (my_msg.tid != 0) {
                    printf("\nNowa wiadomość:\n");
                    printf("%s\n", my_msg.message);
                }
                break;
            case 5:
                return 0;
        }
        if (option[0] == 1 || option[0] == 2 || option[0] == 3 || option[0] == 5) {
            printf("\n");
        }
        if (option[0] == 1 || option[0] == 2 || option[0] == 3 || option[0] == 4 || option[0] == 5) {
            printf("Co chcesz zrobic (wpisz liczbe)?\n");
            printf("1 - Rejestracja nowego wątku.\n");
            printf("2 - Rejestracja do subskrybcji wątku.\n");
            printf("3 - Wysłanie wiadomości.\n");
            printf("4 - Odebranie wiadomości.\n");
            printf("5 - Wyjście.\n>");
        }
    }
}

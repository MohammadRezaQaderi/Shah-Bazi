#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


int people = 50, court = 50, found = 50;
int  node_counter = 0;


struct problems_node {
    int problem_id;
    char problem1[200];
    char decision1[200];
    int efpeople1, efcourt1, effound1;
    char decision2[200];
    int efpeople2, efcourt2, effound2;
    int problem_counter;
    struct problems_node *next;
};


struct player {
    char player_name[100];
    int condition;
    //char probelity_of_problems[100];
    int probelity_of_problems[100];
    int people;
    int court;
    int found;
};


struct player_ranking {
    char player_namae[100];
    int people;
    int court;
    int found;
};



void print(struct problems_node p) {
    printf("%s \n", p.problem1);
    printf("1)%s \n", p.decision1);
    //  printf("%d %d %d \n", p.efpeople1, p.efcourt1, p.effound1);
    printf("2)%s \n", p.decision2);
    // printf("%d %d %d \n", p.efpeople2, p.efcourt2, p.effound2);
}



void print_player(struct player p,int problem_number) {
    printf("\n %s \n", p.player_name);
    printf("\n player condition %d", p.condition);
    int i;
	for ( i = 0; i < problem_number; i++) {
        printf("\n qouestion %dth probeblity is: %d", (i + 1), p.probelity_of_problems[i]);
    }
    printf("\n people : %d", p.people);
    printf("\n court : %d", p.court);
    printf("\n found : %d", p.found);
}



//this function make a linked list
struct problems_node *create_node(struct problems_node p);




//this function read information fro our files and give the information to create node
struct problems_node *read_problems(int *problem_number) {
    (*problem_number) = 0;
    char prob_file_name[100];
    FILE *fpfileName = fopen("CHOICES.txt", "r");


    if (fpfileName == NULL) {
        printf("couldnt open file");
        exit(-1);
    }


    int id_counter = 0;
    struct problems_node *list = NULL, *current = NULL;
    while (fgets(prob_file_name, 200, fpfileName) != NULL) {

        if (prob_file_name[strlen(prob_file_name) - 1] == '\n') {
            prob_file_name[strlen(prob_file_name) - 1] = '\0';
        }


        FILE *fpProblem;
        fpProblem = fopen(prob_file_name, "r");
        if (fpProblem == NULL) {
            printf("couldnt open problem file");
            exit(-1);
        }


        struct problems_node p;
        fgets(p.problem1, 201, fpProblem);
        fgets(p.decision1, 201, fpProblem);
        fscanf(fpProblem, "%d%d%d\n", &p.efpeople1, &p.efcourt1, &p.effound1);
        fgets(p.decision2, 200, fpProblem);
        fscanf(fpProblem, "%d%d%d\n", &p.efpeople2, &p.efcourt2, &p.effound2);
        p.problem_counter = 3;
        p.problem_id = id_counter;

        if (list == NULL) {
            list = create_node(p);
            current = list;
        } else {
            current->next = create_node(p);
            current = current->next;
        }
        (*problem_number)++;

        fclose(fpProblem);
        id_counter++;

    }
    fclose(fpfileName);
    return list;
}



struct problems_node *create_node(struct problems_node p) {
    struct problems_node *nn;
    nn = (struct problems_node *) malloc(sizeof(p));
    strcpy(nn->problem1, p.problem1);
    strcpy(nn->decision1, p.decision1);
    nn->efpeople1 = p.efpeople1;
    nn->efcourt1 = p.efcourt1;
    nn->effound1 = p.effound1;
    strcpy(nn->decision2, p.decision2);
    nn->efpeople2 = p.efpeople2;
    nn->efcourt2 = p.efcourt2;
    nn->effound2 = p.effound2;
    nn->problem_counter = 3;
    nn->problem_id = p.problem_id;
    nn->next = NULL;
    return nn;
}


// this function remove a particular node from the linked list
struct problems_node *remove_node(struct problems_node *removable, struct problems_node **list) {
    struct problems_node *curent;
    curent = *list;
    if (curent == removable) {
        (*list) = (*list)->next;
        free(removable);
        return (*list);
    }

    while (curent->next != removable) {
        curent = curent->next;
    }
    curent->next = curent->next->next;
    free(removable);
    return curent;
}
// this function check linked list if any node need to be deleted it pass it to function remove node
void check_linked_listed(struct problems_node **list, int *problem_number) {

    struct problems_node *current;
    for (current = (*list); current != NULL;) {
        if (current->problem_counter == 0) {
            current = remove_node(current, list);
            (*problem_number)--;
            node_counter++;
        } else
            current = current->next;

    }
    return;

}


// this function just clean our buffer
void
clear(void) {
    while (getchar() != '\n');
}


// this function checks our 3 parameters if they have particular amount say player loss or no
int check_parametrs() {
    if (people <= 0 || court <= 0 || found <= 0 || people + court + found < 30) {
        printf("you lost the game");
        return 0;
    }
    return 1;
}


//this function checks if any of our parameters be more than 100 or below the 0
int make_it_correct(int a) {
    if (a > 100) {
        a = 100;
        return a;
    } else if (a < 0) {
        a = 0;
        return a;
    }
}



void save_game(struct player p) {
    FILE *fp_save;
    fp_save = fopen(p.player_name, "wb");
    fwrite(&p, sizeof(p),1, fp_save);
    fclose(fp_save);
    FILE *fpall_save = fopen("allSave", "ab");
    fwrite(p.player_name, sizeof(p.player_name), 1, fpall_save);
    fwrite(&p.people, sizeof(int), 1, fpall_save);
    fwrite(&p.court, sizeof(int), 1, fpall_save);
    fwrite(&p.found, sizeof(int), 1, fpall_save);
}

void ranking() {
    struct player_ranking arp[100];
    FILE *fpread_all_save = fopen("allSave", "rb");
    int i = 0;
    while (!feof(fpread_all_save)) {
        fread(&arp[i], sizeof(arp[0]), 1, fpread_all_save);
        i++;
    }
    puts("\n if you want normal ranking  press 1 \n");
    puts("\n if you want professional rankin press 2 \n");

    clear();
    char choise;
    scanf("%c", &choise);
    clear();
    switch (choise) {

        case '1' : {
            struct player_ranking temp;
            int t,j;
			for ( t = 0; t < i; t++) {
                for ( j = t+1; j < i; j++) {
                    if ((arp[t].found) + (arp[t].people) + (arp[t].court) >
                        (arp[j].found) + (arp[j].people) + (arp[j].court)) {
                        temp = arp[t];
                        arp[t] = arp[j];
                        arp[j] = temp;
                    }

                }
            }
            int p;
            for ( p = 0; p < i; p++) {
                int w = 0;
                for (t = p + 1; t < i; t++) {
                    if (strcmp(arp[p].player_namae, arp[t].player_namae) == 0)
                        w = 1;
                }
                if (w == 0)
                    printf(" \n %s  :%d \n ", arp[p].player_namae, (arp[p].people) + (arp[p].court) + (arp[p].found));

            }
            break;
        }
        case '2': {

            struct player_ranking temp;
            int t,j;
			for ( t = 0; t < i; t++) {
                for ( j = t+1; j < i; j++) {
                    if ((arp[t].people) > (arp[j].people)) {
                        temp = arp[t];
                        arp[t] = arp[j];
                        arp[j] = temp;

                    } else if ((arp[t].people) == (arp[j].people)) {

                        if ((arp[t].court) > (arp[j].court)) {
                            temp = arp[t];
                            arp[t] = arp[j];
                            arp[j] = temp;
                        } else if ((arp[t].court) == (arp[j].court)) {
                            if ((arp[t].found) > (arp[j].found)) {
                                temp = arp[t];
                                arp[t] = arp[j];
                                arp[j] = temp;
                            }

                        }
                    }
                }

            }

		int p;
            for ( p = 0; p < i; p++) {
                int w = 0;
                for ( t = p + 1; t < i; t++) {
                    if (strcmp(arp[p].player_namae, arp[t].player_namae) == 0)
                        w = 1;
                }
                if (w == 0)
                    printf(" \n %s  ==> people :%d || court : %d || found : %d \n ", arp[p].player_namae, (arp[p].people),(arp[p].court),(arp[p].found));


            }
            break;
        }
    }

}


void color(int people ,int court,int found){
    if(people < 20 || court < 20 || found < 20)
        system("color 67");
    else if(people == 0 || court ==0 || found==0)
        system("color 47");

}

void playGame(struct problems_node **list, int *problem_number, struct player *p) {
    int number_of_total_problem = 0;


    struct problems_node *current;
    while (1) {
        srand(time(NULL));
        current = (*list);

        int random = rand() % (*problem_number);
		int i;
        for ( i = 0; i < random; i++) {
            if (current->next == NULL)
                current = (*list);
            if ((*list)->next != NULL)
                current = current->next;
        }

        printf("\n problem id: %d \n", current->problem_id);
        print(*current);
        printf(" \n problem counter: %d \n", current->problem_counter);

        char answer;
        clear();

        int flag2=1;
        while(flag2) {
            scanf("%c", &answer);
            flag2=0;
            if (answer != '1' && answer != '2') {
                printf("\n you entered false key  \n");
                printf("\n if you want finish the game press q \n");
                printf("\n  if you want continue press 1 or 2 \n");

                char exit_charechter;
                clear();
                scanf("%c", &exit_charechter);
                if (exit_charechter == 'q') {
                    printf(" \n people: %d \n court: %d \n found: %d \n", people, court, found);
                    p->condition = 1;
                    printf("\n you leave the game \n");
                    printf("\n do you want save the game (y/n) \n");
                    char save_game_char;
                    clear();
                    scanf("%c", &save_game_char);
                    if (save_game_char == 'y')
                        save_game(*p);
                    return;
                } else if(exit_charechter=='1' ||exit_charechter == '2' ) {
                    answer=exit_charechter;
                }
                else{
                    clear();
                    flag2=1;
                    continue;
                }

            }  if (answer == '2') {
                people += current->efpeople2;
                people = make_it_correct(people);
                p->people = people;
                court += current->efcourt2;
                court = make_it_correct(court);
                p->court = court;
                found += current->effound2;
                found = make_it_correct(found);
                p->found = found;
            } else if (answer == '1') {
                people += current->efpeople1;
                people = make_it_correct(people);
                p->people = people;
                court += current->efcourt1;
                court = make_it_correct(court);
                p->court = court;
                found += current->effound1;
                found = make_it_correct(found);
                p->found = found;
            }
        }
        current->problem_counter--;
        p->probelity_of_problems[current->problem_id]--;


        color(people,court,found);
        printf("people : %d\ncourt : %d\nfound : %d\n", people, court, found);


        check_linked_listed(list, problem_number);
        //printf(" node hazf shode :%d", node_counter);
        //printf("***********problem number : %d", (*problem_number));

        if ((*problem_number) == 0) {
            (*list) = read_problems(problem_number);
            int i;
			for ( i = 0; i < (*problem_number); i++)
                p->probelity_of_problems[i] = 3;
            node_counter = 0;
        }
        if (!check_parametrs()) {
            color(people,court,found);
            p->condition = 0;
            printf("\n do you want save the game (y/n) \n");
            char save_game_char;
            clear();
            scanf("%c", &save_game_char);
            if (save_game_char == 'y')
                save_game(*p);
            return;
        }
        number_of_total_problem++;
        //printf("\n number of total problem\n\n\n : %d", number_of_total_problem);


    }

}
void create_qouestion(){
    printf("\n how many qouestion do you want add? \n");
    clear();
    int numberof_added_qouestions;
    scanf("%d",&numberof_added_qouestions);
    clear();
int i;
    for( i=0; i<numberof_added_qouestions;i++){
        char qouestion_file_name[100];
        printf("\n please enter your qouestion file name \n");
        gets(qouestion_file_name);

        FILE*add_to_choices=fopen("CHOICES.txt","a+");
        if(add_to_choices==NULL)
            printf("coudent open CHOICES file");

        // printf("*****%s",qouestion_file_name);
        fprintf(add_to_choices,"\n%s",qouestion_file_name);
        fclose(add_to_choices);

        char problem1[200];
        printf("\n please enter your problem \n");
        gets(problem1);


        char decision1[200];
        printf("\n please enter your first decision \n");
        gets(decision1);


        int efpeople1, efcourt1, effound1;
        printf("\n please enter your decision effect on people ,court & people  \n");
        scanf("%d%d%d",&efpeople1,&efcourt1,&effound1);
        clear();

        char decision2[200];
        printf("\n please enter your second decision \n");
        gets(decision2);


        int efpeople2, efcourt2, effound2;
        printf("\n please enter your decision effect on people ,court & people  \n");
        scanf("%d%d%d",&efpeople2,&efcourt2,&effound2);
        clear();
        printf(" ====%s",qouestion_file_name);

        FILE*fpAdded_qouestion=fopen(qouestion_file_name,"w");
        if(fpAdded_qouestion==NULL)
            printf("couldnt open question file");
        fprintf(fpAdded_qouestion,"%s\n",problem1);
        fprintf(fpAdded_qouestion,"%s\n",decision1);
        fprintf(fpAdded_qouestion,"%d\n",efpeople1);
        fprintf(fpAdded_qouestion,"%d\n",efcourt1);
        fprintf(fpAdded_qouestion,"%d\n",effound1);
        fprintf(fpAdded_qouestion,"%s\n",decision2);
        fprintf(fpAdded_qouestion,"%d\n",efpeople2);
        fprintf(fpAdded_qouestion,"%d\n",efcourt2);
        fprintf(fpAdded_qouestion,"%d",effound2);
        printf("\n question file created \n");
        fclose(fpAdded_qouestion);
    }
}
void guid(){
    puts("this game is so easy\n in every level system ask you one question \nthis question have 2 answer \n");
    puts("which of them have different effect on your parameters \n this parameters are people,court,found\n");
    puts("you just need think about questions and make correct decision\n ");
    puts("you can exit the game whenever you want\n its just need press any key but 1 & 2 when you are answering");
    puts("questions \n how you loss the game ? \n if ne of your parameters be 0 or average of them be under 10");

}


void print_start(){
    printf("******************************************************************************\n"
           "***            ***            ***            ***            ***            ***\n"
           "***  ******************  ********   ******   ***  ********  ********  ********\n"
           "***  ******************  ********  ********  ***  ********  ********  ********\n"
           "***  ******************  ********  ********  ***  ********  ********  ********\n"
           "***  ******************  ********  ********  ***  ********  ********  ********\n"
           "***            ********  ********            ***           *********  ********\n"
           "*************  ********  ********  ********  ***  ***  *************  ********\n"
           "*************  ********  ********  ********  ***  ****  ************  ********\n"
           "*************  ********  ********  ********  ***  *****  ***********  ********\n"
           "*************  ********  ********  ********  ***  ******  **********  ********\n"
           "***            ********  ********  ********  ***  *******  *********  ********\n"
           "***********************  ********  ********  ***  ********  ********  ********\n"
           "******************************************************************************\n");
}


void print_finish(){
    printf("*************************************************************************************************\n"
           "***            ***            *** ***********  ****            ***            ****  ********  ***\n"
           "***  ******************  ********  **I*******  *********  ********  **************  ********  ***\n"
           "***  ******************  ********   *********  *********  ********  **************  ********  ***\n"
           "***  ******************  ********  * ********  *********  ********  **************  ********  ***\n"
           "***  ******************  ********  ** *******  *********  ********  **************  ********  ***\n"
           "***            ********  ********  *** ******  *********  ********            ****            ***\n"
           "***  ******************  ********  **** *****  *********  ******************  ****  ********  ***\n"
           "***  ******************  ********  ***** ****  *********  ******************  ****  ********  ***\n"
           "***  ******************  ********  ****** ***  *********  ******************  ****  ********  ***\n"
           "***  ******************  ********  ******* **  *********  ******************  ****  ********  ***\n"
           "***  ******************  ********  ******** *  *********  ******************  ****  ********  ***\n"
           "***  *************            ***  *********   ***             ***            ****  ********  ***\n"
           "*************************************************************************************************\n");
}
int main() {
    system("color 27");
    print_start();
    printf("\n\n\n\t\t\t\t\t\t\t\t\t===========================\n");
    puts("\t\t\t\t\t\t\t\t\t||welcome to your kingdom || \n");
    printf("\t\t\t\t\t\t\t\t\t===========================\n");



    struct player p;
    struct player *pp = &p;
    int problem_number;
    int *pproblem_number = &problem_number;
    struct problems_node *list = read_problems(pproblem_number);
    struct problems_node *current;
    int i;
	for ( i = 0; i < (*pproblem_number); i++) {
        p.probelity_of_problems[i] = 3;
    }
    puts("\n please enter your profile name \n");
    gets(p.player_name);

    puts("if you want start a new game press 1");
    puts("if you want continue your game press 2 ");
    puts("if you want ranking press 3 ");
    puts("if you want add new question press 4");
    puts("if you want read guide press 5");

    int flag=1;
    char make_decision;
    while (flag) {
        flag=0;
        scanf("%c", &make_decision);
        switch (make_decision) {

            case '1': {
                int i;
				for ( i = 0; i < (*pproblem_number); i++) {
                    printf("\n qouestion %dth probeblity is: %d", (i + 1), p.probelity_of_problems[i]);
                }
                printf("\n people= 50 \n court= 50 \n found= 50 \n");
                playGame(&list, pproblem_number, pp);
                printf("\n======================================\n");
                print_player(p, (*pproblem_number));
                printf("\n======================================\n");
                break;
            }
            case '2': {
                FILE *load = fopen(p.player_name, "rb");
                if (load == NULL) {
                    printf("\nsory king there is not any save by this profile name\n");
                    flag=1;
                    printf("\n select other option");
                    continue;
                }


                fread(p.player_name, sizeof(p.player_name), 1, load);
                fread(&p.condition, sizeof(p.condition), 1, load);
                if (p.condition == 0) {
                    p.people = 50;
                    p.found = 50;
                    p.court = 50;
                } else {
                    fread(p.probelity_of_problems, sizeof(p.probelity_of_problems), 1, load);
                    fread(&p.people, sizeof(int), 1, load);
                    fread(&p.court, sizeof(int), 1, load);
                    fread(&p.found, sizeof(int), 1, load);
                    int i = 0;
                    for (current = list; current != NULL; i++, current = current->next) {
                        current->problem_counter = p.probelity_of_problems[i];
                    }
                    check_linked_listed(&list, pproblem_number);
                    people = p.people;
                    court = p.court;
                    found = p.found;
                }
                print_player(p, (*pproblem_number));
                printf("\n=========================================\n");
                playGame(&list, pproblem_number, pp);
                print_player(p, (*pproblem_number));
                printf("\n=========================================\n");
                break;

            }
            case '3': {
                ranking();
                break;


            }
            case '4': {
                create_qouestion();
                break;
            }
            case '5':{
                guid();
                break;
            }
            default:{
                printf("\n you press wrong key please try again \n");
                flag=1;

            }
        }
    }
printf("\n");
print_finish();

    /*   for (current = list; current != NULL; current = current->next) {
            print(*current);


        }*/

getchar();
getchar();
//1/24/2019 6;41 be ghabl
    return 0;
}

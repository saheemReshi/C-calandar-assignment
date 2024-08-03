#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct venue{
    struct venue * next;
    char name[100],loc[100],cap[100];//,eventName[100];//assuming max length of these strings can be 100
    char*date[30][24];//maybe here i'll need [31][24]!!!!


};

char * separateCommand(char x[]){
    //need a function to separate out the first word of the input
    // printf("%s","i'm inside\n");

    int i=0;
    char * a=malloc(1000);//assuming the first word won't be more than 1000 chars long 
    while(x[i]!=' ' && x[i]!='\n'){
        // printf("%d ",x[i]);
        a[i]=x[i];
        i++;
    }
    a[i]='\0';
    return a;
}

void addVenue(struct venue *head, int *venueCount, char userInput[])
{
    char name[100], loc[100], cap[100];
    // need to get the "name"
    int i = sizeof("addVenue"); // i'll start to search for "name", its index will definetely be after "addVenue"
    while (userInput[i] != '"')
        i++;
    i++;
    int j = 0; // index to point to name array for writing
    while (userInput[i] != '"')
        name[j++] = userInput[i++];
    i++;
    name[j] = '\0'; // to make it a string

    // now I need to find the location

    while (userInput[i] != '"')
        i++;
    i++;
    int k = 0; // index to point to loc array for writing
    while (userInput[i] != '"')
        loc[k++] = userInput[i++];
    i++;
    loc[k] = '\0';

    // now I need the capacity
    int m = 0; // index to point to write the capacity array

    while (userInput[i] != '\n')
    { //\n because fgets has it before \0
        if (userInput[i] >= '0' && userInput[i] <= '9')
        {
            cap[m++] = userInput[i];
        }
        i++;
    }
    cap[m] = '\0';

    printf("name:%s , loc:%s , cap:%s\n",name,loc,cap);
    // if (head != NULL)
    // {
    //     // we already have some venues, so have to check if this venue already exists. If yes, then raise an error
    //     struct venue *temp = head;
    //     while ()
    // }
    // else
    // {
    //     //
    // }
}

int main(){
    char userInput[1000];//assuming that the ip given will never be more than 1000 chars
    fgets(userInput,sizeof(userInput),stdin);
    int venueCount=0;
    struct venue * head=NULL;//this is the linked list that will store the venues

    while(strcmp(userInput,"End\n")!=0){
        char * command=separateCommand(userInput);
        if(!strcmp(command,"addVenue")){
                addVenue(head,&venueCount,userInput);


        }
        else if(!strcmp(command,"showVenues")){

        }
        else if(!strcmp(command,"deleteVenue")){

        }
        else if(!strcmp(command,"addEvent")){

        }
        else if(!strcmp(command,"deleteEvent")){

        }
        else if(!strcmp(command,"showEvents")){

        }
        else if(!strcmp(command,"showCalendar")){

        }
        else{
            //no such command exists
            printf("%s","no such command exists\n");
        }

        free(command);//don't want memory leaks!
        fgets(userInput,sizeof(userInput),stdin);
    }


    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct venue{

};

struct llVenues{
    //i'll use this linked list to store the venues and their capacities
    struct venue v;
    struct venue * p;
    int capacity;
};

char * separateCommand(char x[]){
    //need a function to separate out the first word of the input
    printf("%s","i'm inside\n");
    int i=0;
    char * a=malloc(1000);//assuming the first word won't be more than 1000 chars long 
    while(x[i]!=' ' && x[i]!='\n'){
        printf("%d ",x[i]);
        a[i]=x[i];
        i++;
    }
    a[i]='\0';
    return a;
}

int main(){
    char userInput[1000];//assuming that the ip given will never be more than 1000 chars
    fgets(userInput,sizeof(userInput),stdin);
    int venueCount=0;
    while(strcmp(userInput,"End\n")!=0){
        char * command=separateCommand(userInput);

        if(!strcmp(command,"addVenue")){

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
            printf("%s","no such command exists");
        }

        free(command);//don't want memory leaks!
        fgets(userInput,sizeof(userInput),stdin);
    }


    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct venue{
    struct venue * next;
    char name[100],loc[100],cap[100];//,eventName[100];//assuming max length of these strings can be 100
    char*date[30][24];//maybe here i'll need [31][24]!!!!


};

// struct llVenues{
//     //i'll use this linked list to store the venues and their capacities
//     struct venue v;
//     struct venue * p;
// };

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

int main(){
    char userInput[1000];//assuming that the ip given will never be more than 1000 chars
    fgets(userInput,sizeof(userInput),stdin);
    int venueCount=0;

    while(strcmp(userInput,"End\n")!=0){
        char * command=separateCommand(userInput);

        if(!strcmp(command,"addVenue")){
                //need to get the "name"
                int i=sizeof("addVenue");//i'll start to search for "nameOfVenue", its index will definetely be after "addVenue"
                char name[100],loc[100];
                int cap=0;//for the capacity
                while(userInput[i]!='"') i++;
                i++;
                int j=0;//index to point to name array for writing
                while(userInput[i]!='"') name[j++]=userInput[i++];
                i++;

                //now I need to find the location

                while(userInput[i]!='"') i++;
                i++;
                int k=0;//index to point to loc array for writing
                while(userInput[i]!='"') loc[k++]=userInput[i++];
                i++;

                //now I need the capacity
                while(userInput[i]!='\n'){//\n because fgets has it before \0

                }

            if(venueCount==0){
                struct venue * head=malloc(sizeof(struct venue));
            }
            else{
                //i'll traverse the whole venue list and raise an error if the venue already exists
            }
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
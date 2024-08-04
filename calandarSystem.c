#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VENUE_NAME_SIZE 100
#define MAX_LOC_SIZE 100
#define MAX_CAP_SIZE 100
#define MAX_INPUT_SIZE 1000

struct venue{
    struct venue * next;
    char name[MAX_VENUE_NAME_SIZE],loc[MAX_LOC_SIZE],cap[MAX_CAP_SIZE];//,eventName[100];//assuming max length of these strings can be 100
    char*date[30][24];//maybe here i'll need [31][24]!!!!


};

struct venue * defaultVenue(){//so that the date pointer array will be filled with NULL in the beginning
    struct venue* a=malloc(sizeof(struct venue));
    a->next=NULL;
    for(int i=0; i<30; i++){
        for(int j=0; j<24; j++){
            a->date[i][j]=NULL;
        }
    }
    return a;
}

char * separateCommand(char x[]){
    //need a function to separate out the first word of the userInput
    // printf("%s","i'm inside\n");
    //assuming no leading spaces, tabs etc in the userInput!!!!!!
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

struct venue * addVenue(struct venue *head, int *venueCount, char userInput[])
{
    char name[MAX_VENUE_NAME_SIZE],loc[MAX_LOC_SIZE],cap[MAX_CAP_SIZE];
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

    // printf("name:%s , loc:%s , cap:%s\n",name,loc,cap);

    if (head != NULL)
    {
        // we already have some venues, so have to check if this venue already exists. If yes, then raise an error
        struct venue *temp = head;
        while(temp){
            if(strcmp(name,temp->name)==0){
                //this means that this venue already exists!
                //error
                printf("-1\nDuplicate venue name\n");
                fflush(stdout);
                return head;
            }
            temp=temp->next;
        }
    }
    //now , we know that venue of same name isn't there already, so i'll add it
    struct venue * a=defaultVenue();
    strcpy(a->name,name);
    strcpy(a->loc,loc);
    strcpy(a->cap,cap);
    a->next=head;
    (*venueCount)++;
    printf("0\n");//0 printed for success
    return a;

}

void showVenues(struct venue * head, int venueCount){
    printf("%d\n",venueCount);
    
    while(head){
        // printf("hola ");
        printf("%s %s %s\n",head->name,head->loc,head->cap);
        fflush(stdout);
        head=head->next;
    }
}

struct venue* delVenue(int * venueCount, struct venue * head,char userInput[]){
    if(head==NULL){
        printf("-1\nError: no such venue\n");
        return head;
    }

    //delVenue "nameOfVenue"
    //I need to extract the name of Venue from the userInput
    char name[MAX_VENUE_NAME_SIZE];
    int i=sizeof("delVenue");//i will look for first '"' only after this index
    while (userInput[i] != '"')
        i++;
    i++;
    int j = 0; // index to point to name array for writing
    while (userInput[i] != '"')
        name[j++] = userInput[i++];
    i++;
    name[j] = '\0';

    //now I'll search for the this venue in my linked list
    //only 2 cases here- either the venue is present in the LL, if not-then error(-1)

    //code for deleting from linkedList
    if(strcmp(head->name,name)==0){//dealing with the case when the venue is in the head itself!
        struct venue * temp=head->next;
        free(head);
        (*venueCount)--;
        printf("0\n");//0 printed for success
        return temp;
    }
    
    while(head->next){
        if(strcmp(head->next->name,name)==0){
            struct venue*temp=head->next;
            head->next=temp->next;
            free(temp);
            printf("0\n");//0 printed for success
            (*venueCount)--;
            return head;
        }
        head=head->next;
    }
    printf("-1\nError: no such venue\n");
    return head;
}

int main(){
    char userInput[MAX_INPUT_SIZE];//assuming that the ip given will never be more than 1000 chars
    fgets(userInput,sizeof(userInput),stdin);
    int venueCount=0;
    struct venue * head=NULL;//this is the linked list that will store the venues

    while(strcmp(userInput,"End\n")!=0){
        char * command=separateCommand(userInput);
        if(!strcmp(command,"addVenue")){
            head=addVenue(head,&venueCount,userInput);

        }
        else if(!strcmp(command,"showVenues")){
            showVenues(head,venueCount);
        }
        else if(!strcmp(command,"delVenue")){
            head=delVenue(&venueCount,head,userInput);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VENUE_NAME_SIZE 100
#define MAX_LOC_SIZE 100
#define MAX_CAP_SIZE 100
#define MAX_EVENT_NAME_SIZE 100
#define MAX_INPUT_SIZE 1000
#define MAX_DATE 100
#define MAX_HOURS 100


struct event{
    char name[MAX_EVENT_NAME_SIZE];
    int s,e;//start and end time of event
    struct event *next;
};

struct venue{
    int totalEvents;
    struct venue * next;
    char name[MAX_VENUE_NAME_SIZE],loc[MAX_LOC_SIZE],cap[MAX_CAP_SIZE];//,eventName[100];//assuming max length of these strings can be 100
    struct event * date[30];//here i'll arrange the events in ascending order of from-to hours
    int eventsOnDate[30];//stores the no. of events on each date
};

struct venue * defaultVenue(){//so that the date pointer array will be filled with NULL in the beginning
    struct venue* a=malloc(sizeof(struct venue));
    a->totalEvents=0;
    a->next=NULL;
    for(int i=0; i<30; i++){
        a->date[i]=NULL;
        a->eventsOnDate[i]=0;
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

void insertEventInVenue(struct venue* v,char eName[],int d,int f,int t){
    //i have to insert event "eName" in venue 'v' at date 'd'. from-time:f and to-time:t

    d--;//doing this because struct event*date[30] in struct venue. Index of array starts from 0
    if(v->date[d]==NULL){
        //means no events for this date, so can easily insert
        struct event * a=malloc(sizeof(struct event));
        a->s=f;
        a->e=t;
        strcpy(a->name,eName);
        a->next=NULL;
        v->date[d]=a;
        v->totalEvents++;
        v->eventsOnDate[d]++;
        printf("0\n");
        return;
    }
    //if that date already has some events, then I have to check if an event is already there bw from-time till end-time
    struct event* x=v->date[d];//this is the head of the linked list

    //first i'll check if the head of this linked list satisfies the insertion condition
    if(t < x->s){
        struct event * a=malloc(sizeof(struct event));
        a->s=f;
        a->e=t;
        strcpy(a->name,eName);
        a->next=x;
        v->date[d]=a;
        v->totalEvents++;
        v->eventsOnDate[d]++;
        printf("0\n");
        return;
    }
    else if(x->e < f){//now here i'll check for x->next so that i can easily insert in the linkedList
        struct event * p=x;
        x=x->next;
        while(x){
            if(t < x->s){
                //insert condition
                struct event * a=malloc(sizeof(struct event));
                a->s=f;
                a->e=t;
                strcpy(a->name,eName);
                a->next=x;
                v->date[d]=a;
                v->totalEvents++;
                v->eventsOnDate[d]++;
                p->next=a;
                printf("0\n");
                return;
            }
            else if(x->e < f){
                //move on condition
                p=x;
                x=x->next;
            }
            else{
                //error
                printf("-1\nError: time slot is occupied by another event\n");
                return;
            }
        }
        //if we exit this while loop, it means that we encountered null
        //we also have to insert here
        struct event * a=malloc(sizeof(struct event));
        a->s=f;
        a->e=t;
        strcpy(a->name,eName);
        a->next=NULL;
        v->date[d]=a;
        v->totalEvents++;
        v->eventsOnDate[d]++;
        p->next=a;
        printf("0\n");
        return;

    }
    else{
        //error--clashes with the head event itself
        printf("-1\nError: time slot is occupied by another event\n");
    }

}

void addEvent(struct venue * head,char userInput[]){
    //addEvent "venueName" date from to "eventName" <---i'll need to separate all these things here
    char vName[MAX_VENUE_NAME_SIZE],eName[MAX_EVENT_NAME_SIZE];
    char date[MAX_DATE],from[MAX_HOURS],to[MAX_HOURS];//first i'll extract these from the input as strings and then later change them to integers

    //first need "venueName"
    int i=sizeof("addEvent");
    while(userInput[i]!='"') i++;
    i++;
    int a=0;//will point to vName array for filling
    while(userInput[i]!='"'){
        vName[a++]=userInput[i++];
    }
    i++;
    vName[a]='\0';

    //now need date
    while(!(userInput[i]>='0' && userInput[i]<='9')) i++;
    a=0;//will point to date array for writing
    while(userInput[i]>='0' && userInput[i]<='9') date[a++]=userInput[i++];
    date[a]='\0';

    //now need from-time
    while(!(userInput[i]>='0' && userInput[i]<='9')) i++;
    a=0;//will point to from array for writing
    while(userInput[i]>='0' && userInput[i]<='9') from[a++]=userInput[i++];
    from[a]='\0';

    //now need to-time
    while(!(userInput[i]>='0' && userInput[i]<='9')) i++;
    a=0;//will point to to array for writing
    while(userInput[i]>='0' && userInput[i]<='9') to[a++]=userInput[i++];
    to[a]='\0';

    //now need event-name
    while(userInput[i]!='"') i++;
    i++;
    a=0;//will point to eName array for writing
    while(userInput[i]!='"'){
        eName[a++]=userInput[i++];
    }
    i++;
    eName[a]='\0';

    // printf("%s %s %s %s %s\n",vName,date,from,to,eName);

    if(strlen(date)>2 || strlen(from)>2 || strlen(to)>2){
            printf("-1\nError: Invalid date or time\n");
            return;
    }
    int d=atoi(date),f=atoi(from),t=atoi(to);//these are date, from-time, to-time in integer format for error checking

    if(d<1 || d>30 || f<0 || f>23 || t<0 || t>23 || f>t){
        printf("-1\nError: Invalid date or time\n");
        return;
    }

    // printf("%d %d %d\n",d,f,t);
    
    //now, everything is valid(fornow!)

    //now i'll search for the venue in the linkedList
    struct venue* temp=head;
    while(temp){
        if(strcmp(temp->name,vName)==0){
            //new function for this
            insertEventInVenue(temp,eName,d,f,t);
            return;
        }
        temp=temp->next;
    }
    //if such a venue doesn't exist
    printf("-1\nError: no such venue\n");
    return;
}

void showEvents(struct venue * head, char userInput[]){
    // printf("hola");
    if(head==NULL){
        printf("-1\nError: no such venue\n");
        return;
    }

    //format: showEvents “Place de la Concorde” 8
    char vName[MAX_VENUE_NAME_SIZE],date[MAX_DATE];
    
    //first i'll get the "venueName"
    int i=sizeof("showEvents");//i'll search for first " after this index
    while(userInput[i]!='"') i++;
    i++;
    int a=0;//will point to vName array for writing
    while(userInput[i]!='"') vName[a++]=userInput[i++];
    vName[a]='\0';

    //now need the date
    while(!(userInput[i]>='0' && userInput[i]<='9')) i++;
    a=0;//will now point to date array for writing
    while(userInput[i]>='0' && userInput[i]<='9') date[a++]=userInput[i++];
    date[a]='\0';

    //now first i'll check if the date given is valid or not
    if(strlen(date)>2){
        printf("-1\nError: date is invalid\n");
        return;
    }
    int d=atoi(date);//this inbuilt-function converts date-string to date-integer
    if(d<1 || d>30){
        printf("-1\nError: date is invalid\n");
        return;
    } 
    //now i'll search for the venue in the linked list
    d--;//because date array is 0-indexed
    while(head){
        if(strcmp(head->name,vName)==0){
            printf("%d\n",head->eventsOnDate[d]);
            //i just have to iterate through the linked list head->date[d] and print
            struct event* a=head->date[d];
            while(a){
                printf("%s %d %d\n",a->name,a->s,a->e);
                a=a->next;
            }
            return;
        }
        head=head->next;
    }
    //if we exit the while loop, it means that the given venue doesn't exist
    printf("-1\nError: no such venue\n");

}

void showCalendar(struct venue * head, char userInput[]){
    //format: showCalendar <venueName-string>
    if(head==NULL){
        printf("-1\nError: no such venue\n");
        return;
    }
    //i have to extract the venue name string 
    char vName[MAX_VENUE_NAME_SIZE];
    
    //first i'll get the "venueName"
    int i=sizeof("showCalendar");//i'll search for first " after this index
    while(userInput[i]!='"') i++;
    i++;
    int a=0;//will point to vName array for writing
    while(userInput[i]!='"') vName[a++]=userInput[i++];
    vName[a]='\0';
    //now i'll search for the venue in the linked list
    while(head){
        if(strcmp(head->name,vName)==0){
            printf("%d\n",head->totalEvents);
            for(int d=0; d<30; d++){
                printf("%d %d\n",d+1,head->eventsOnDate[d]);//d+1 bcz the array is 0-indexed
                struct event* temp=head->date[d];
                while(temp){
                    printf("%s %d %d\n",temp->name,temp->s,temp->e);
                    temp=temp->next;
                }
            }
            return;
        }
        head=head->next;
    }
    //if we exit the while loop, it means that the given venue doesn't exist
    printf("-1\nError: no such venue\n");
}

void deleteEventInVenue(struct venue* v,char eName[],int d,int f){

}

void delEvent(struct venue * head, char userInput[]){
    //deleteEvent <venueName-string> <date-integer> <fromHour-integer> <eventName-string>
    //delEvent “Rolland-Garros” 5 15 “Womens Tennis”

    char vName[MAX_VENUE_NAME_SIZE], eName[MAX_EVENT_NAME_SIZE], date[MAX_DATE], from[MAX_HOURS];
    int i=sizeof("delEvent");
    while(userInput[i]!='"'){
        i++;
    }
    i++;
    int a=0;//it will point to vName array for filling
    while(userInput[i]!='"'){
        vName[a++]=userInput[i++];
    }
    vName[a]='\0';
    i++;

    //now need date
    while(!(userInput[i]>='0' && userInput[i]<='9')) i++;
    a=0;//will point to date array for writing
    while(userInput[i]>='0' && userInput[i]<='9') date[a++]=userInput[i++];
    date[a]='\0';

    //now need from-time
    while(!(userInput[i]>='0' && userInput[i]<='9')) i++;
    a=0;//will point to from array for writing
    while(userInput[i]>='0' && userInput[i]<='9') from[a++]=userInput[i++];
    from[a]='\0';

    //now need event-name
    while(userInput[i]!='"') i++;
    i++;
    a=0;//will point to eName array for writing
    while(userInput[i]!='"'){
        eName[a++]=userInput[i++];
    }
    i++;
    eName[a]='\0';

    if(strlen(date)>2 || strlen(from)>2 ){
                printf("-1\nError: Invalid date or time\n");
                return;
        }
    int d=atoi(date),f=atoi(from);//these are date, from-time in integer format for error checking

    if(d<1 || d>30 || f<0 || f>23){
        printf("-1\nError: Invalid date or time\n");
        return;
    }

    //now i'll search for the venue in the linkedList
    struct venue* temp=head;
    while(temp){
        if(strcmp(temp->name,vName)==0){
            //new function for this
            deleteEventInVenue(temp,eName,d,f);
            return;
        }
        temp=temp->next;
    }
    //if such a venue doesn't exist
    printf("-1\nError: no such venue\n");
    return;
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
            addEvent(head,userInput);
        }
        else if(!strcmp(command,"delEvent")){

        }
        else if(!strcmp(command,"showEvents")){
            showEvents(head,userInput);
        }
        else if(!strcmp(command,"showCalendar")){
            showCalendar(head,userInput);
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
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

int main(){
    char userInput[1000];//assuming that the ip given will never be more than 1000 chars
    fgets(userInput,sizeof(userInput),stdin);
    while(strcmp(userInput,"End\n")!=0){
        printf("%s\n","hello");
        fgets(userInput,sizeof(userInput),stdin);

    }


    return 0;
}
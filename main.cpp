#include "List.h"

using namespace std;


int main(){
    bool loop=true;
    while(loop){
        int option;
        printf("\nChoose option\n");
        printf("1. Tab\n");
        printf("2. List\n");

        printf("3. \n");
        printf("4. Delete last element\n");
        printf("5. Delete element at given position\n");

        printf("6. Show list\n");
        printf("7. Go back to main menu\n");

        scanf("%i", &option);
    }
    List list;
    list.menu_list();
    return 0;
}

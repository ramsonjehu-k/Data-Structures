/*
MIT License

Copyright (c) 2021 velai_illa_programmer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum main_menu{
    ADD_MAIN_MENU=1,
    DISPLAY_MAIN_MENU,
    EXIT_MAIN_MENU
};

enum add_menu{
    ADD_AT_START=1,
    ADD_AT_POS,
    ADD_AT_END,
    EXIT_ADD_MENU
};

typedef struct node {
    int data;
    struct node* next;
}Linked_List;

void displayList(Linked_List* list)
{
    printf("The elements in the Linked List are:\n");
    while (list != NULL) {
        printf("   ( %p )\n",list);
        printf("| %3d | %p |", list->data,list->next);
        list = list->next;
        if(list){
            printf(" \n %*c | \n %*c V \n",8,' ',8,' ');
        }
    }
}

bool addAtStart(Linked_List** list)
{
    int data = 0;
    Linked_List * new_node = NULL;
    new_node = (Linked_List*)malloc(sizeof(Linked_List));
    if(!new_node){
        printf("Linked list new_node allocation Failed\n");
        return false;
    }
    printf(" Enter the data to be added: ");
    scanf("%d",&data);
    new_node->data = data;
    new_node->next = *list;
    *list = new_node; 
    return true;
}

bool addAtEnd(Linked_List** list)
{
    if(!*list){
        if(addAtStart(list)){
            return true;
        }else{
            return false;
        }
    }
    int data = 0;
    Linked_List * head = *list;
    Linked_List * new_node = NULL;
    printf(" Enter the data to be added: ");
    scanf("%d",&data);
    while (head->next!=NULL)
    {
        head = head->next;
    }
    new_node = (Linked_List*)malloc(sizeof(Linked_List));
    if(!new_node){
        printf("Linked list new_node allocation Failed\n");
        return false;
    }
    new_node->data = data;
    new_node->next = NULL;
    head->next = new_node;
    return true;
}

bool addAtPos(Linked_List** list)
{
    int data=0,pos=0;
    int cnt=0;
    Linked_List * head = *list;
    Linked_List * new_node = NULL;
    printf("NOTE: The list is zero-indexed list.\n");
    printf(" Enter the postion: ");
    scanf("%d",&pos);
    if(pos<0){
        printf("Error: Invalid Position Entered!!\n");
        return false;
    }
    if(pos==0){
        if(addAtStart(list)){
            return true;
        }else{
            return false;
        }
    }

    while(cnt<pos-1 && head->next){
        head = head->next;
        cnt++;
    }
    if(cnt==pos-1 && head->next==NULL){
        if(addAtEnd(&head)){
            return true;
        }else{
            return false;
        }
    }else if(cnt==pos-1){
        printf(" Enter the data to be added: ");
        scanf("%d",&data);  
        new_node = (Linked_List*)malloc(sizeof(Linked_List));
        if(!new_node){
            printf("Linked list new_node allocation Failed\n");
            return false;
        }
        new_node->data = data;
        new_node->next = head->next;
        head->next = new_node;
    }else{
        printf("Error: Position not found!!\n");
        return false;
    }
    return true;
}

void addNewNode(Linked_List** list)
{
    int option=-1;
    while(true){
        printf("\nAdd New Node Menu:\
                \n 1.Add at start \
                \n 2.Add at position \
                \n 3.Add at end \
                \n 4.Back to main menu \
                \n Enter your option:");
        scanf("%d",&option);
        
        switch (option)
        {
        case ADD_AT_START:
            if(addAtStart(list)){
                printf("The data has been added successfully.\n");
                displayList(*list);
            }else{
                printf("The data has not been added.\n");
            }
            break;
        case ADD_AT_POS:
            if(addAtPos(list)){
                printf("The data has been added successfully.\n");
                displayList(*list);
            }else{
                printf("The data has not been added.\n");
            }
            break;
        case ADD_AT_END:
            if(addAtEnd(list)){
                printf("The data has been added successfully.\n");
                displayList(*list);
            }else{
                printf("The data has not been added.\n");
            }
            break;
        case EXIT_ADD_MENU:
            break;
        default:
            printf("Invalid option selected!!");
            break;
        }
        if(option==EXIT_ADD_MENU){
            break;
        }
    }
}

void clearList(Linked_List** list){
    Linked_List* head = *list;
    Linked_List* next_node = head;
    while(next_node!=NULL){
        head=next_node;
        next_node=next_node->next;
        free(head);
    }
}

int main(int argc, char const *argv[])
{
    int option= -1;
    Linked_List * list = NULL;
    while(true){
        printf("\nLinked List Main Menu:\
                \n 1.Add New Node \
                \n 2.Display the List \
                \n 3.Exit \
                \n Enter your option:");
        scanf("%d",&option);
        switch (option)
        {
            case ADD_MAIN_MENU:
                addNewNode(&list);
                break;
            case DISPLAY_MAIN_MENU:
                displayList(list);
                break;
            case EXIT_MAIN_MENU:
                break;         
            default:
                printf("Invalid option selected!!");
                break;
        }
        if(option==EXIT_MAIN_MENU){
            break;
        }
    }
    clearList(&list);
    return 0;
}

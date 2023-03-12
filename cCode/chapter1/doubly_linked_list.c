#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//*******NULL IS THE VALUE FOR null IN OTHER LANGUAGES, IMPORTANT*****
/*WE ARE CONSTRUCTING AN UNORDERED STRING LINKED LIST JTLYK*/

//define struct node
struct node{

struct node* prev;
struct node* next;
//just dont allow the string to be larger than 19 characters long(need /0 escape character at end)
char randomString[20];
};
//determine the paramenters necessary for this fucntion
//the naming of parameters n not necessary
void insertNode(struct node* HEAD, struct node* node);
//this function takes in two nodes, the head node and the node to delete, this allows it to search the entire
//linked list and find the node to delete if it exists, else returns -1
//**see if using ENUM can expedite this process
int deleteNode(struct node* HEAD, char string[]);
struct node* findNode(struct node* HEAD, char string[]);
void printAllNodesForward(struct node* HEAD);
void printAllNodesBackward(struct node* TAIL);
void printForwardAndBackward(struct node* HEAD, struct node* TAIL);

int main(){

//initialize some nodes into memory(malloc)
//we will use the sentinal method so there is a guaranteed node on each end
//of the linked list, and the linked list is never 'empty'
struct node* HEAD = NULL;
struct node* TAIL = NULL;

//load into memory
HEAD = malloc(sizeof(struct node));
TAIL = malloc(sizeof(struct node));

//assign them string values of "HEAD" and "TAIL"
strcpy(HEAD->randomString, "HEAD");
strcpy(TAIL->randomString, "TAIL");


//link head to tail and tail to head
//link heads pointing to TAIL

HEAD -> next = TAIL;
HEAD -> prev = NULL;


//link TAIL pointing to HEAD
TAIL -> prev = HEAD;
TAIL-> next = NULL;


//one test!
//implement a testnode to insert, delete and search for
struct node* testNode;
//load into memory
testNode = malloc(sizeof(struct node));
//make value a string
strcpy(testNode->randomString, "string");
//call insert function to insert it into the linked list
insertNode(HEAD, testNode);

//implement a testnode to insert, delete and search for
struct node* anotherNode;
//load into memory
anotherNode = malloc(sizeof(struct node));
//make value a string
strcpy(anotherNode->randomString, "anotherString");
printf("%s\n",anotherNode->randomString);
//call insert function to insert it into the linked list
insertNode(HEAD, anotherNode);

printForwardAndBackward(HEAD, TAIL);

//findNode also works perfectly, can move onto next chapter!!!!
struct node* discoveredNode = findNode(HEAD, testNode->randomString);
printf("returned node optics:\n node's string %s\n previous string: %s\n next string: %s\n", discoveredNode->randomString, discoveredNode->prev->randomString, discoveredNode->next->randomString);

//delete node works, were gonna comment them out to test the findNode functionality
//
//printForwardAndBackward(HEAD, TAIL);
////insert node's functionality works!!!
//
////now to test delete node
////we will perform a test to delete the testNode we created
////remember sentinel nodes must remain for the entire program to work
//printf("string value we will be searching for to delete: %s\n", testNode->randomString);
////call delete node method
//deleteNode(HEAD, testNode->randomString);
//printForwardAndBackward(HEAD, TAIL);
//
//deleteNode(HEAD, anotherNode->randomString);
//printForwardAndBackward(HEAD, TAIL);
//
////deleteNode's functionality works!!!

return 0;
}


void printForwardAndBackward(struct node* HEAD, struct node* TAIL){
printAllNodesForward(HEAD);
printf("\n");
printAllNodesBackward(TAIL);

}
//testing method to print out all node's values
void printAllNodesForward(struct node* HEAD){
struct node* currentNode = HEAD;

while(currentNode != NULL){
printf("current Node's randomString value: %s\n", currentNode->randomString);
currentNode = currentNode->next;
}


}

void printAllNodesBackward(struct node* TAIL){
struct node* currentNode = TAIL;

while(currentNode != NULL){
printf("current Node's randomString value: %s\n", currentNode->randomString);
currentNode = currentNode->prev;
}


}

//Tested and works perfectly, move onto testing other methods
//for a heap allocated HEAD and TAIL, there should be no need to pass them into a function,
//figure out why C is forcing passed heap allocated structs
void insertNode(struct node* HEAD, struct node* node){
//we will insert a string based off nothing related to its order or length, simply add the next node w/
//the string right after the HEAD sentinal node and before the HEAD's next pointer
printf("passed node's string: %s\n",node->randomString);
//assign the node's next node value to the head's previous next value
node->next = HEAD->next;
//assign the head's next value to the new node
HEAD->next = node;
//assign the new node's prev pointer value to the HEAD
node->prev = HEAD;
//assign the next node's prev to this node
node->next->prev = node;
//we should be done w/ inserting after this!
printf("The node has been inserted between the HEAD and its 'next' value\n");

}

//Tested and works perfectly, move onto testing other methods
//search for node that contains the specified char string, if no matches occur, return -1, else return 1
int deleteNode(struct node* HEAD, char string[]){
//may be wrong, check later
struct node* currentNode = HEAD;
//while the current node's string does not match the string comparison, keep moving along the linked list

while(currentNode != NULL){

//if the string of the node searched matches a nodes string(first), delete node, and notify user
//no garbage collection, so must remove that memory manually,
if(strcmp(string, currentNode->randomString) == 0){
printf("Node found, will promptly be deleted");
printf("matched strings: %s, %s\n", string, currentNode->randomString);
//if node matches, set the previous node's next pointer to the currentNode's next value
//and set the next node's previous node pointer to the current node's previous pointer
printf("current->randomString string: %s\n",currentNode->randomString);
printf("current->prev->next->randomString string: %s\n",currentNode->prev->next->randomString);
currentNode->prev->next = currentNode -> next;
printf("current->next->prev->randomString string: %s\n",currentNode->next->prev->randomString);
currentNode->next->prev = currentNode -> prev;
//free the memory the current node is taking up
free(currentNode);
printf("Node deleted, memory reclaimed by OS, returning now\n");
break;
}
currentNode  = currentNode-> next;

}

return -1;
}


//Tested and works perfectly, move onto testing other methods

//this method will search through the entire linked list and try and find the node the user is searching for
struct node* findNode(struct node* HEAD, char string[]){
struct node* currentNode = HEAD;
//while there are still nodes to search for the string
while(strcmp(currentNode->randomString, "TAIL") != 0){
//if a match is found, exit from the loop and return the node
if(strcmp(string, currentNode->randomString) == 0){
    printf("A match has been found!");
    printf("search string: %s, matched string: %s\n", string, currentNode->randomString);
    return currentNode;
}
//continue to next node
currentNode = currentNode->next;
}

//if no match is found, the tail sentinal node will be returned
return currentNode;
}
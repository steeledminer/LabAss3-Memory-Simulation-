/*
Created by Andrew Hingst (5043535).
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

const int MIN_LEASE = 40;		//Constant Variables
const int MAX_LEASE = 70;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const long TIME_LIMIT = 1000;
const int MEMORY_SIZE = 1000;

/************************Structures*******************************************/
struct range {
	int start;		// the starting address of the range
	int size;		// size of the range
}

struct freeNode {
	struct range hole;
	struct freeNode *next;	// pointer to next node
}

struct allocNode {
	struct range allocated;
	int leaseExpiry; 	// time at which this block will be returned to free list
	struct allocNode *next;	//pointer to next node;
}

/*********************************Functions************************************/

/*
Allocates the node 'data', using 'free' as the first free node
Returns true if successful, false if failed.
*/
bool allocate(allocNode *data, freeNode *free){
	while{ 
		if(data->allocated.size < free->hole.size){
			//If data can fit in the node, do so. Arrange values appropriately.
			data->allocated.start = free->hole.start;
			free->hole.size = free->hole.size - data->allocated.size;
			free->hole.start = free->hole.start + data->allocated.size;
			return true;
		} else {
			//If data cannot fit, see if there's another node. If so, move there. Return false otherwise
			if(free->next == NULL) return false;
			else free = free->free.next;
		}
	}
	return;
}

/*
Releases the node 'data' and turns it into a freeNode at the appropriate spot.
'free' is the first freeNode. 'nodeLocation' is the first allocNode.
Used for deleting 'data'.
*/
void releaseNode(allocNode &data, allocNode *nodeLocation, freeNode *free){
	//First, find where in the freeNode list to convert it to [the start of previous node and this node lies on each end of the data start.
	
	while((free->next->hole.start < data->allocated.start) && (free->next != NULL)){
		free = free->next;
	}
	//Spot located
	freeNode generatedNode = new freeNode;	//Create free node, drop it in spot
			generatedNode->next = free->next;
			generatedNode->hole.start = data->allocated.start;
			generatedNode->hole.size = data->allocated.size;
			free->next = *generatedNode;
	
	//Reset pointers for allocated nodes
	while(nodeLocation->next != *data){
		nodeLocation = nodeLocation->next;
	}
	nodeLocation->next = data->next;
	delete data;
	data = 0;
	return;
}

/*
Runs through the list of freeNodes and merges any side-by-side nodes.
Then deletes the latter node. 'free' points to the first node when fed.
*/
void mergeNodes(freeNode *free){
	freeNode *tmp = NULL;		//used for moving pointers
	while(free->next != NULL){ 	//While not at the end of the loop
		if(free->hole.start + free->hole.size = free->next->hole.start - 1){
			//If the previous node adds up to the next one
			free->hole.size += free->next->hole.size; 	//Add the second node's size
			tmp = free->next;
			free->next = free->next->next;				//Move the pointer
			delete tmp;									//Delete the old empty node
			tmp = NULL;
		}
		free = free->next;		//Move to next node;
		return;
	}
}
/*
Generates and returns a randomly made request.

*/
allocNode generateNode(){
	int sizeRange = MAX_SIZE - MIN_SIZE;		//Get the ranges
	int timeRange = MAX_LEASE - MIN_LEASE;		

	int size =  rand() % sizeRange + MIN_SIZE; //Get the random values
	
	return node;
}
/*
Sorts the nodes, putting all allocated nodes first, and pushes all freenodes back.
Does not merge any nodes.
*/
void sortNodes(allocNode* location, freeNode* freeLocation){
	while(location->next != NULL || freeLocation->next != NULL){
		if(freeLocation->hole.start < location->allocated.start){
			location->allocated.start = freeLocation->hole.start;
			freeLocation->hole.start = location->allocated.start + location->allocated.size + 1;
			if(location->next != NULL) location = location->next;
		} else {
			if (freeLocation->next != NULL) freeLocation = freeLocation->next;
			else location = location->next;
		}
	
	}

}

/******************************MAIN CODE***************************************/
int main(){
	long clock = 0;
	srand(time(NULL));
	int requestsMade = 0;
	int satisfiedRequests = 0;
	int unsatisfiedRequests = 0;
	int smallestBlockRequest = 0;
	int largestBlockRequest = 0;
	int averageBlockRequest = 0;
	int shortestLease = 0;
	int longestLease = 0;
	int averageLease = 0;
	int merges = 0;
	
	allocNode* allocList = NULL; //Points to the first node
	
	
	freeNode* freeList = new freeNode;	//Generate the free space
		freeList->next = NULL;
		freeList->hole.size = MEMORY_SIZE;
		freeList->hole.start = 0;
	

	
	
	repeat{
      /* generate a memory request */
      	allocNode request = generateNode();	//Makes a request
      	if (requestsMade = 0){				//Is it first request? If so, first time initialize
      		shortestLease = largestLease = averageLease = request->leaseExpiry;
      		smallestBlockRequest = largestBlockRequest = averageBlockRequest = request->allocated.size;
      	} else {
      		//Set the storage table
      		if (request->allocated.size < smallestBlockRequest) smallestBlockRequest = request->allocated.size;
      		if (request->allocated.size > largestBlockRequest) largestBlockRequest = request->allocated.size;
      		if (request->allocated.leaseExpiry < shortestLease) shortestLease = request->leaseExpiry;
      		if (request->allocated.leaseExpiry > longestLease) longestLease = request->leaseExpiry;
      		averageLease = (averageLease + request->leaseExpiry)/2;
      		averageBlockRequest = (averageBlockRequest + request->allocated.size)/2;
      	}
    	if(!allocate(request, freeList) {			//Attempt to allocate the request
    		sortNodes( allocList*, freeList*);		//If fail, sort and merge nodes, try again
    		mergeNodes(freeList*);
    		merges++;
    		if(!allocate(request, freeList){		//If it still fails then cancel the request
    		
     			delete request;
     			unsatisfiedRequests++;
			} else {								//If it works, checks out
				satisfiedRequests++;
			} 
      	}else {
      		satisfiedRequests++;
      	}
      	
      	requestsMade++;
      /* see if lease has expired  */
	}until ( ++clock == TIME_LIMIT);
	
	
}
/*****************************END OF CODE**************************************/int lease = rand() % timeRange + MIN_LEASE;
	
	allocNode node = new allocNode; 			//Create the requested node
		node->leaseExpiry = lease;
		node->allocated->size = size; 
	
	return node;
}
/*
Sorts the nodes, putting all allocated nodes first, and pushes all freenodes back.
Does not merge any nodes.
*/
void sortNodes(allocNode* location, freeNode* freeLocation){
	while(location->next != NULL || freeLocation->next != NULL){
		if(freeLocation->hole.start < location->allocated.start){
			location->allocated.start = freeLocation->hole.start;
			freeLocation->hole.start = location->allocated.start + location->allocated.size + 1;
			if(location->next != NULL) location = location->next;
		} else {
			if (freeLocation->next != NULL) freeLocation = freeLocation->next;
			else location = location->next;
		}
	
	}

}

/******************************MAIN CODE***************************************/
int main(){
	long clock = 0;
	srand(time(NULL));
	int requestsMade = 0;
	int satisfiedRequests = 0;
	int unsatisfiedRequests = 0;
	int smallestBlockRequest = 0;
	int largestBlockRequest = 0;
	int averageBlockRequest = 0;
	int shortestLease = 0;
	int longestLease = 0;
	int averageLease = 0;
	int merges = 0;
	
	allocNode* allocList = NULL; //Points to the first node
	
	
	freeNode* freeList = new freeNode;	//Generate the free space
		freeList->next = NULL;
		freeList->hole.size = MEMORY_SIZE;
		freeList->hole.start = 0;
	

	
	
	repeat{
      /* generate a memory request */
      	allocNode request = generateNode();	//Makes a request
      	if (requestsMade = 0){				//Is it first request? If so, first time initialize
      		shortestLease = largestLease = averageLease = request->leaseExpiry;
      		smallestBlockRequest = largestBlockRequest = averageBlockRequest = request->allocated.size;
      	} else {
      		//Set the storage table
      		if (request->allocated.size < smallestBlockRequest) smallestBlockRequest = request->allocated.size;
      		if (request->allocated.size > largestBlockRequest) largestBlockRequest = request->allocated.size;
      		if (request->allocated.leaseExpiry < shortestLease) shortestLease = request->leaseExpiry;
      		if (request->allocated.leaseExpiry > longestLease) longestLease = request->leaseExpiry;
      		averageLease = (averageLease + request->leaseExpiry)/2;
      		averageBlockRequest = (averageBlockRequest + request->allocated.size)/2;
      	}
    	if(!allocate(request, freeList) {			//Attempt to allocate the request
    		sortNodes( allocList*, freeList*);		//If fail, sort and merge nodes, try again
    		mergeNodes(freeList*);
    		merges++;
    		if(!allocate(request, freeList){		//If it still fails then cancel the request
    		
     			delete request;
     			unsatisfiedRequests++;
			} else {								//If it works, checks out
				satisfiedRequests++;
			} 
      	}else {
      		satisfiedRequests++;
      	}
      	
      	requestsMade++;
      /* see if lease has expired  */
	}until ( ++clock == TIME_LIMIT);
	
	
}
/*****************************END OF CODE**************************************/

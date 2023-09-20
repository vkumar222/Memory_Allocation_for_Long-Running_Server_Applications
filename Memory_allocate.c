#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

int *heap;

typedef struct Block_header{
    int status;
    int size;
}Block_header;

Block_header *last_alloc_block;


void initialize(){
    heap = (int*)malloc(sizeof(int)*SIZE);
    last_alloc_block = (Block_header*)(heap);
    last_alloc_block->status = 0;
    last_alloc_block->size = SIZE-sizeof(Block_header);
}


void coalese(int* add){
    Block_header* empty = (Block_header*)(add);
    
    int coalese_size = empty->size;

    void* mem2 = (void*)(add + sizeof(Block_header) + empty->size);

    Block_header* mem = (Block_header*)(mem2);

    int i = 0;
    while((((int*)mem < (int*)heap+SIZE)) && (mem->status == 0)){
        i += 1;
        mem += mem->size + sizeof(Block_header);
        coalese_size += mem->size;
    }

    empty->status = 0;

    empty->size = coalese_size;
}


//first fit
int* AllocationFf(int size){
    Block_header* mem = (Block_header*)(heap);
    
    while(((int*)mem < (int*)heap+SIZE) && ((mem->status == 1) || (mem->status == 0 && mem->size < size))){
        mem += mem->size + sizeof(Block_header); 
    }

    if((int*)mem > (int*)heap+SIZE) {
        
        coalese(heap);
        return NULL;
    }

    int residue_size = mem->size - size;

    mem->status = 1;
    mem->size = size;

    last_alloc_block = mem;

    mem = mem + sizeof(Block_header) + mem->size;
    
    if((int*)mem < (int*)heap+SIZE){
        mem->status = 0;
        mem->size = residue_size - sizeof(Block_header);
    }

    return (int*)(mem);
}

//Nest fit
int* AllocationNf(int size){
    Block_header* mem = (Block_header*)(last_alloc_block);
    
    while(((int*)mem < (int*)heap+SIZE) && ((mem->status == 1) || (mem->status == 0 && mem->size < size))){
        mem += mem->size + sizeof(Block_header); 
    }

    if((int*)mem > (int*)heap+SIZE) {
       
        coalese(heap);
        return NULL;
    }

    int left_size = mem->size - size;

    mem->status = 1;
    mem->size = size;

    last_alloc_block = mem;

    mem = mem + sizeof(Block_header) + mem->size;
    
    if((int*)mem < (int*)heap+SIZE){
        mem->status = 0;
        mem->size = left_size - sizeof(Block_header);
    }

    return (int*)(mem);
}


void fragmented(){
    Block_header* mem = (Block_header*)(heap);
    int frag_size=0;
    while((int*)mem < (int*)heap+SIZE){
        if(mem->status==0){
            frag_size += mem->size;
        } 
        mem += mem->size + sizeof(Block_header);
    }

    printf("total fragmetation size:%d", frag_size);
}




int main(){
    initialize();
    fragmented();
    printf("\n");
     printf("last alloc block:%d\n",last_alloc_block->status);
     printf("last block size:%d\n",last_alloc_block->size);
//Testing case1
     int *m1 = (int*)AllocationFf(200);
     if(m1!=NULL){
         printf("last alloc block:%d\n",last_alloc_block->status);
         printf("last block size:%d\n",last_alloc_block->size);
     }else{
         printf("NULL");
     }
//Testing case 2
    int *m2 = (int*)AllocationFf(900);
    if(m2!=NULL){
        printf("last alloc block:%d\n",last_alloc_block->status);
        printf("last block size:%d\n",last_alloc_block->size);
    }else{
        printf("NULL");
    }
//Testing case3
    int *m3 = (int*)AllocationFf(100);
    if(m3!=NULL){
        printf("last alloc block:%d\n",last_alloc_block->status);
        printf("last block size:%d\n",last_alloc_block->size);
    }else{
        printf("NULL");
    }
//Testing case4
    int *m4 = (int*)AllocationFf(8476-8);
    if(m4!=NULL){
        printf("last alloc block:%d\n",last_alloc_block->status);
        printf("last block size:%d\n",last_alloc_block->size);
    }else{
        printf("NULL");
    }
//Freeing
     coalese(m1);
//Testing case5
    int *m5 = (int*)AllocationFf(700);
    
    if(m5!=NULL){
        printf("last alloc block:%d\n",last_alloc_block->status);
        printf("last block size:%d\n",last_alloc_block->size);
    }else{
        printf("NULL");
    }

    //printf("%d", sizeof(Block_header));
//Testing Case 6 
    int *m6 =  (int*)AllocationNf(400);
     if(m6!=NULL){
        printf("last alloc block:%d\n",last_alloc_block->status);
        printf("last block size:%d\n",last_alloc_block->size);
    }else{
        printf("NULL");}
    return 0;
}
extern void * data;
int offset=0;

void * malloc(int i){

    char * address = data + offset;
    offset += i;

    return (void *) address;

}
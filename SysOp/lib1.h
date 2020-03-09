#ifndef lib1_h
#define lib1_h

struct pair
{
    char* file1;
    int size1;
    char* file2;
    int size2;
};

struct BlockArray
{
    int size;
    struct  Block** block_array;    
};

struct Block
{
    int size;
    char** opr;
};

struct BlockArray* create_block_array(int n);
struct pair* create_sequence(char* enter, int n);
void make_diff(struct pair* files, int n, char* tmp_file);
int create_block(struct BlockArray* block_array, char* tmp_file);
int get_block_size(struct Block* block);
void delete_block(struct BlockArray* block_array, int index);
void delete_opr(struct Block* block, char* opr);

#endif
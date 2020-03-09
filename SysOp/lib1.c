#include "Lib1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct BlockArray* create_block_array(int n)
{
    struct BlockArray* array = (struct BlockArray*)calloc(sizeof(struct BlockArray), 1);
    array->size = n;
    array->block_array = (struct Block**)calloc(sizeof(struct Block*), n);
    for(int i = 0; i < n; i++)
        array->block_array[i] = NULL;
    return array;
}

struct pair* create_sequence(char* enter, int n)
{
    struct pair* sequence = (struct pair*)calloc(sizeof(struct pair), n);
    for(int i = 0; i < n; i++)
    {
        sequence[i].file1 = (char*)calloc(sizeof(char), 30);
        sequence[i].file2 = (char*)calloc(sizeof(char), 30);
        sequence[i].size1 = 0;
        sequence[i].size2 = 0;
    }
    int j = 0; //block num
    int k = 0; //file 1 or 2
    for(int i = 0; enter[i] != 0; i++)
    {
        if(enter[i] == ' ')
        {
            j++; //go to next block
            k = 0;
        }   
        else if(enter[i] == ':')
        {
            k++; //go to next file
        }
        else
        {
            if(k == 0)
            {
                sequence[j].file1[sequence[j].size1++] = enter[i];
            }
            else
            {
                sequence[j].file2[sequence[j].size2++] = enter[i];
            }
        }
    }
    return sequence;
}

void make_diff(struct pair* files, int n, char* tmp_file)
{
    FILE* tmp = fopen(tmp_file, "w");
    fclose(tmp);
    char* command = (char*)calloc(sizeof(char), 255);
    for(int i = 0; i < n; i++)
    {
        for(int i = 0; i < 255; i++)
            command[i] = 0;
        strcpy(command, "diff ");
        strcat(command, files[i].file1);
        strcat(command, " ");
        strcat(command, files[i].file2);
        strcat(command, " >> ");
        strcat(command, tmp_file);
        system(command);
        FILE* tmp = fopen(tmp_file, "a");
        fprintf(tmp, "***\n");
        fclose(tmp);
    }
    free(command);
}

int create_block(struct BlockArray* block_array, char* tmp_file)
{
    int i = -1;
    for(int k = 0; k < block_array->size; k++) //find empty block slot
    if (block_array->block_array[k] == NULL)
    {
        i = k;
        break;
    }
    if(i == -1)
        return -1; //no empty slot was found
    block_array->block_array[i] = (struct Block*)calloc(sizeof(struct Block), block_array->size);
    block_array->block_array[i]->size = 0;
    block_array->block_array[i]->opr = (char**)calloc(sizeof(char*), 50);
    for(int j = 0; j < 50; j++)
        block_array->block_array[i]->opr[j] = NULL;

    FILE* tmp = fopen(tmp_file, "r");
    char* tmp_char = tmp_char = (char*)calloc(sizeof(char), 100);;

    while(1)
    {
        fgets(tmp_char, 100, tmp);
        if(!strcmp(tmp_char, "***\n"))
            break;
        block_array->block_array[i]->opr[block_array->block_array[i]->size++] = tmp_char;    
        tmp_char = (char*)calloc(sizeof(char), 100);
    }

    FILE* tmp2 = fopen("tmp_tmp.txt", "w");
    while(fgets(tmp_char, 100, tmp) != NULL)
    {
        fprintf(tmp2, tmp_char);
    }
    fclose(tmp);
    fclose(tmp2);
    remove("tmp.txt");
    rename("tmp_tmp.txt", "tmp.txt");

    return i;
}

int get_block_size(struct Block* block)
{
    return block->size;
}

void delete_block(struct BlockArray* block_array, int index)
{
    if(block_array->block_array[index] != NULL)
    {
        for(int i = 0; i < block_array->size; i++)
            if(block_array->block_array[index]->opr[i] != NULL)
                free(block_array->block_array[index]->opr[i]);
        free(block_array->block_array[index]->opr);
        free(block_array->block_array[index]);
        block_array->block_array[index] = NULL;
    }
}

void delete_opr(struct Block* block, char* opr)
{
    char* opr2 = (char*)calloc(sizeof(char), 255);
    strcpy(opr2, opr);
    strcat(opr2, "\n");
    for(int i = 0; i < block->size; i++)
        if(!strcmp(block->opr[i], opr2))
        {
            free(block->opr[i]);
            block->opr[i] = NULL;
        }
    free(opr2);
}
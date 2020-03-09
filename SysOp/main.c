#include <stdio.h>
#include "lib1.h"

int main()
{
    int n = 2;
    struct BlockArray* blc = create_block_array(n);
    char* enter = "file1.txt:file2.txt file3.txt:file4.txt";
    struct pair* seq = create_sequence(enter, n);
    for(int i = 0; i < n; i++)
    {
        printf(seq[i].file1);
        printf("\n");
        printf(seq[i].file2);
        printf("\n");
    }
    make_diff(seq, 2, "tmp.txt");

    create_block(blc, "tmp.txt");  
    create_block(blc, "tmp.txt");  

    for(int i = 0; i < n; i++)
    {
        printf("block %i:\n", i);
        if(blc->block_array[i] == NULL)
            printf("Empty\n");
        else
        {
            printf("%i\n", get_block_size(blc->block_array[i]));
            for(int j = 0; j < blc->block_array[i]->size; j++)
            {
                if(blc->block_array[i]->opr[j] == NULL)
                    printf("\n");
                else
                    printf(blc->block_array[i]->opr[j]);
            }
            printf("\n");
        }
    }


    delete_block(blc, 0);

    for(int i = 0; i < n; i++)
    {
        printf("block %i:\n", i);
        if(blc->block_array[i] == NULL)
            printf("Empty\n");
        else
        {
            printf("%i\n", get_block_size(blc->block_array[i]));
            for(int j = 0; j < blc->block_array[i]->size; j++)
            {
                if(blc->block_array[i]->opr[j] == NULL)
                    printf("\n");
                else
                    printf(blc->block_array[i]->opr[j]);
            }
            printf("\n");
        }
    }

    delete_opr(blc->block_array[1], "< hhh iii");

    for(int i = 0; i < n; i++)
    {
        printf("block %i:\n", i);
        if(blc->block_array[i] == NULL)
            printf("Empty\n");
        else
        {
            printf("%i\n", get_block_size(blc->block_array[i]));
            for(int j = 0; j < blc->block_array[i]->size; j++)
            {
                if(blc->block_array[i]->opr[j] == NULL)
                    printf("\n");
                else
                    printf(blc->block_array[i]->opr[j]);
            }
            printf("\n");
        }
    }
    return 0;
}
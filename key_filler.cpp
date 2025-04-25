#include <stdio.h>
#include <stdlib.h>
const char *  KEY_TO_CRACK = "S:\\Doc\\KEYCRACK.txt";

const size_t BUFFER_ADDR       = 0x0189;
const size_t RET_IN_STACK_ADDR = 0xFFFC;
const size_t NEW_RET           = 0x0149 ;


const size_t ZEROS_NUM = RET_IN_STACK_ADDR - BUFFER_ADDR - 2;

int main()
{
    FILE *dest = fopen(KEY_TO_CRACK, "wb");
    if (!dest)
        fprintf ( stdout, "SHITTY FILE\n" );


    char zero_data[ZEROS_NUM] = {};
    //for ( int i = 0; i < ZEROS_NUM; i++)
    //    zero_data[i] = 'H';
    char enter_ascii = 0x0D;
    //zero_data[1]= 'H';
    //zero_data[2]= 'U';
    //zero_data[3]= 'I';

    fwrite("$", 1, 1, dest);
    fwrite(zero_data, 1, ZEROS_NUM , dest);
    //fwrite ("0000", 4, 1, dest);
    //fwrite(&NEW_RET, 2, 1, dest);
    //fwrite(&enter_ascii, 1, 1, dest);
    //fwrite("eldadjfgdfeldajhgd", 17, 1, dest);
    fclose ( dest );
    return 0;
}

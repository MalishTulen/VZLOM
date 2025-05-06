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

    fwrite(zero_data, 1, ZEROS_NUM , dest);
    fwrite(&NEW_RET, 2, 1, dest);

    fclose ( dest );
    return 0;
}

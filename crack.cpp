#include <stdio.h>

#include "crack.h"

//const char* old_file = "S:\\Doc\\crackeme.com";
//const char* BALLS = "CRACKEME.COM";

const char *const DEST_FILE_NAME = "crackeme2.com";

int hack_machine()
{

    graffic ();

    FILE* crackeme = fopen ( DEST_FILE_NAME, "w+b" );
    if ( !crackeme )
    {
        fprintf ( stderr, "Failed to open file");
    }

    /*copy_file ( BALLS, crackeme );
    fclose ( crackeme );

    FILE* new_crackeme = fopen ( old_file, "r+b" );*/

    fprintf(stderr, "HACK STARTED\n");

    byte_changer ( crackeme );

    fprintf(stderr, "HACK STOPPED\n");

    fclose ( crackeme );

    return 0;

}


int byte_changer ( FILE* ptr_file )
{
    fseek( ptr_file, CMD_ADDR, SEEK_SET );
    fwrite( &NEW_COMMAND, 1, 1, ptr_file );

    return 0;
}

/*int copy_file ( const char* file_from_copy, FILE* file_to_copy )
{
    FILE *original_crackme = fopen ( file_from_copy, "rb" );

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), original_crackme)) != 0 )
    {
        printf ( "symbol copied\n");
        fwrite(buffer, 1, bytes_read, file_to_copy);
    }

    fclose ( original_crackme );

    return 0;
}*/


#include <stdio.h>
#include <stdlib.h>

#include "crack.h"

//#define GRAFIC

const size_t CMD_ADDR  = 0x2E;
const char   NEW_COMMAND = 0x00;

const char* const old_file = "S:\\Doc\\crackeme.com";
//const char* BALLS = "CRACKEME.COM";

int hack_machine()
{
    #ifdef GRAFIC
        graffic ();
    #endif

    FILE* crackeme = fopen ( old_file, "rb+" );
    if ( !crackeme )
    {
        fprintf ( stderr, "Failed to open file");
    }

    /*copy_file ( BALLS, crackeme );
    fclose ( crackeme );

    FILE* new_crackeme = fopen ( old_file, "r+b" );*/

    fprintf ( stderr, "HACK STARTED\n" );
    byte_changer ( crackeme );
    fprintf( stderr, "HACK STOPPED\n" );

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


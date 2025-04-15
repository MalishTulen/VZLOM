#ifndef CRACK_HEADER
#define CRACK_HEADER

const size_t CMD_ADDR  = 0x2E;
const char NEW_COMMAND = 0x00;

int byte_changer ( FILE* ptr_file );
int copy_file ( const char* file_from_copy, FILE* file_to_copy );
int hack_machine();
int graffic ();


#endif

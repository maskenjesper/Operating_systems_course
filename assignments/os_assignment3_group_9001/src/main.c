#include "dependencies/utilities.h"

uint16_t cardinality;

// argv[1] : filename for addresses
int main(int argc, char** argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "argument: Path to addresses.txt\n");
        exit(1);
    }

    uint16_t cardinality = 1000;
    FILE * file_ptr = fopen(argv[1], "r");
    address_struct adr_s;
    uint16_t physcial_address;
    uint16_t logical_address;
    int8_t value;

    init_kernel();

    if( file_ptr == NULL )
        perror("fopen");

    while(cardinality--)
    {
        read_input_file(&adr_s, file_ptr);
        value = read_address(&adr_s, &physcial_address);
        logical_address = ((uint8_t) adr_s.page << 8) + adr_s.offset;
        printf("logical_address: %d, physcial_address: %d, value: %d\n", logical_address, physcial_address, value);
    }

    get_performance_data();

    if( fclose(file_ptr) == -1 )
    perror("fclose");
}

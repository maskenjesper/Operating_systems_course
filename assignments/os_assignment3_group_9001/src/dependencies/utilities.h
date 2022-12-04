#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

typedef struct page_table_struct
{
    uint16_t frame_address;
    uint8_t valid_bit;
}page_table;

typedef struct page_and_offset_struct
{
    uint8_t page;
    uint8_t offset;
}address_struct;

typedef struct tbl_node
{
    uint16_t logical_address;
    uint16_t physcial_address;
}node;

typedef struct tbl_queue
{
    uint8_t in;
    uint8_t size;
    uint8_t max;
    node *fifo;
}tbl;

extern uint16_t cardinality;

void print_memory(uint16_t length);
void print_page_table();
void print_queue(void);
void get_page(page_table *, uint8_t *, uint16_t);
int8_t read_address(address_struct *, uint16_t *);

void init_kernel(void);

void get_performance_data(void);
void read_input_file(address_struct *, FILE *);


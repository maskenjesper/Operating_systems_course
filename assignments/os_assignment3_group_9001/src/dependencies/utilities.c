#include "utilities.h"

int8_t *memory;
page_table *pt_ptr;
tbl *tbl_ptr;

int disk_fd;
uint32_t page_faults = 0;
uint16_t next_frame_address = 0;
uint16_t tbl_hit = 0;
uint16_t tbl_miss = 0;

uint16_t tbl_lookup(uint8_t page_index);
void get_frame(uint8_t);
int8_t get_byte(uint8_t page_index, uint8_t offset);
int TBL_lookup(uint8_t page_index);
void save_frame_to_memory(int8_t *frame_buffer);
int8_t load_byte_from_memory(uint16_t frame_address, uint8_t offset);
void print_memory(uint16_t length);
void print_page_table();



        /*** PUBLIC FUNCTIONS ***/

void init_kernel()
{
    memory = calloc(256*256, 1); // 65536 bytes of zeros, 1 frame == 256 bytes
    pt_ptr = calloc(sizeof(page_table), 256);
    tbl_ptr = calloc(sizeof(tbl), 1);
    tbl_ptr->fifo = calloc(sizeof(node), 16);
    tbl_ptr->in = tbl_ptr->size = 0;
    tbl_ptr->max = 16;
}

int8_t read_address(address_struct *adr_ptr, uint16_t *physcial_address)
{
    int8_t ret;
    uint16_t frame;

    if( (frame = tbl_lookup(adr_ptr->page)) != (uint16_t) -1)
        ret = load_byte_from_memory(frame, adr_ptr->offset);
    else
        ret = get_byte(adr_ptr->page, adr_ptr->offset);

    *physcial_address = pt_ptr[adr_ptr->page].frame_address + adr_ptr->offset;
    return ret;
}

void read_input_file(address_struct *as_ptr, FILE * file_ptr)
{
    char *line = NULL;
    size_t length;
    ssize_t bytes_read;
    uint16_t address;

    getline(&line, &length, file_ptr);

    address = atoi(line);
    as_ptr->offset = address & 0x00ff;
    address = address >> 8;
    as_ptr->page = address & 0x00ff;
}

void get_performance_data()
{
    printf("****\npage fault rate: %d / 1000\ntbl hits: %d\ntbl_misses: %d\n****\n", page_faults, tbl_hit, tbl_miss);
}

        /*** TBL FUNCTIONS ***/

void tbl_enqueue(uint8_t page_index)
{
    // if fifo has empty nodes:
    if(tbl_ptr->size < tbl_ptr->max)
    {
        tbl_ptr->fifo[tbl_ptr->in].logical_address = page_index * 256;
        tbl_ptr->fifo[tbl_ptr->in].physcial_address = pt_ptr[page_index].frame_address;

        tbl_ptr->in++;
        tbl_ptr->size++;

        // prevents "in pointer" from accessing 2:nd node instead of 1:st 
        // the first time if-statement is false.
        if( tbl_ptr->in == tbl_ptr->max )
            tbl_ptr->in--;
        return;
    }
    // keeps "in pointer" in bounds.
    tbl_ptr->in = (tbl_ptr->in + 1) % tbl_ptr->max; 
    // assign new value to least new node
    tbl_ptr->fifo[tbl_ptr->in].logical_address = page_index * 256; 
    tbl_ptr->fifo[tbl_ptr->in].physcial_address = pt_ptr[page_index].frame_address;
    return;
}

uint16_t tbl_lookup(uint8_t page_index)
{
    for(int i = 0; i<tbl_ptr->size; i++)
        if(tbl_ptr->fifo[i].logical_address/256 == page_index)
        {
            tbl_hit++;
            return tbl_ptr->fifo[i].physcial_address;
        }
    tbl_miss++;
    return -1;
}
        /*** PAGE TABLE FUNCTIONS ***/

int8_t get_byte(uint8_t page_index, uint8_t offset)
{
    if( pt_ptr[page_index].valid_bit == 0 ) // Page fault
    {
        page_faults++;
        pt_ptr[page_index].frame_address = next_frame_address;
        get_frame(page_index);
        pt_ptr[page_index].valid_bit = 1;
        next_frame_address += 256;
    }
    // enqueue page into tbl
    tbl_enqueue(page_index);
    //copy memory frame into buffer
    return load_byte_from_memory(pt_ptr[page_index].frame_address, offset);
}
        /*** MEMORY FUNCTIONS ***/

int8_t load_byte_from_memory(uint16_t frame_address, uint8_t offset)
{
        return memory[frame_address + offset];
}
void save_frame_to_memory(int8_t *frame_buffer)
{
    for(int i = 0; i<256; i++)
    {
        memory[next_frame_address + i] = frame_buffer[i];
    }
}
void get_frame(uint8_t offset)
{
    int8_t *frame_buffer = calloc(256, 1);
    disk_fd = open("./dependencies/data/BACKING_STORE.bin", O_RDONLY);
    if( disk_fd == -1)
        perror("disk : open");

    lseek(disk_fd, offset * 256, SEEK_SET);
    read(disk_fd, frame_buffer, 256);

    if( close(disk_fd) == -1)
        perror("disk : close");
    save_frame_to_memory(frame_buffer);
    free(frame_buffer);
}

        /*** PRINTING FUNCTIONS ***/

void print_memory(uint16_t length)
{
    for(int i = 0; i<length * 256; i += 256)
    {
        printf("Frame: %d\n\n", i);
        for(int j = i; j<(i+256); j++)
            printf(" %d", memory[j]);
        printf("\n\n");
    }
}

void print_page_table()
{
    for(int i = 0; i<256; i++)
        printf("PT[%d]: Logical: %d Physical: %d, Valid bit: %d\n", i, i, (*(pt_ptr + i)).frame_address, (*(pt_ptr + i)).valid_bit); 
}

void print_queue()
{
    printf("TBL:\n");
    for(int i = 0; i<tbl_ptr->max; i++)
        printf("[%d]: logical_address: %d : physcial_address: %d\n", i, tbl_ptr->fifo[i].logical_address/256, tbl_ptr->fifo[i].physcial_address);
    printf("\n");
}





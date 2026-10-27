#ifndef PAGGING_PRV_H
#define PAGGING_PRV_H

#include "cpu/pagging/exp/pagging.h"

#define PAG_PAGE_DIR_P_OFFSET 0
#define PAG_PAGE_DIR_RW_OFFSET 1
#define PAG_PAGE_DIR_US_OFFSET 2
#define PAG_PAGE_DIR_PWT_OFFSET 3
#define PAG_PAGE_DIR_PCD_OFFSET 4
#define PAG_PAGE_DIR_A_OFFSET 5
#define PAG_PAGE_DIR_AVL_LOW_OFFSET 6
#define PAG_PAGE_DIR_AVL_HIGH_OFFSET 8

#define PAGE_PAGE_DIR_AVL_HIGH_MASK 0xFu /* 0b1111 */



#define PAG_PAGE_TABLE_P_OFFSET 0
#define PAG_PAGE_TABLE_RW_OFFSET 1
#define PAG_PAGE_TABLE_US_OFFSET 2
#define PAG_PAGE_TABLE_PWT_OFFSET 3
#define PAG_PAGE_TABLE_PCD_OFFSET 4
#define PAG_PAGE_TABLE_A_OFFSET 5
#define PAG_PAGE_TABLE_D_OFFSET 6
#define PAG_PAGE_TABLE_PAT_OFFSET 7
#define PAG_PAGE_TABLE_G_OFFSET 8
#define PAG_PAGE_TABLE_AVL_OFFSET 9

#define PAG_PAGE_TABLE_AVL_MASK 0x7u

#define PAG_PAGE4K_SIZE 0x1000
#define PAG_COUNT_4K_RECORD_FOR_1MB 0x100000 / 0x1000 // 1Mb / 4Kb = 256 records

#define PAG_PAGE_TABLE_RECORD_COUNT 1024

extern PAG_page_dir_entry_t PAG_identity_page_dir_table[1024];
extern PAG_page_table_entry_t PAG_identity_page_table_table[1024];


#endif

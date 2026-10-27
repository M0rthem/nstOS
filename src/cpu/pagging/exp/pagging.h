#ifndef PAGGING_H
#define PAGGING_H

#include <stdint.h>

typedef int32_t PAG_page_dir_entry_t;
typedef int32_t PAG_page_table_entry_t;

typedef struct page_dir_4k_arg {
	bool P : 1;
	bool RW : 1;
	bool US : 1;
	bool PWT : 1;
	bool PCD : 1;
	bool A : 1;
	unsigned int AVL_low : 1;
	unsigned int AVL_high : 4;
	uint32_t address;
} PAG_page_dir_4k_arg_t;

typedef struct page_table_arg {
	bool P : 1;
	bool RW : 1;
	bool US : 1;
	bool PWT : 1;
	bool PCD : 1;
	bool A : 1;
	bool D : 1;
	bool PAT : 1;
	bool G : 1;
	unsigned int AVL : 3;
	uint32_t address;
} PAG_page_table_arg_t;


PAG_page_dir_entry_t PAG_fill_page_dir_4kb(PAG_page_dir_4k_arg_t *args);
PAG_page_table_entry_t PAG_fill_page_table(PAG_page_table_arg_t *args);

void PAG_setup_identity_1Mb(void);
#endif

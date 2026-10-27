#include <stdint.h>
#include <stdbool.h>
/*private includes*/ 
#include "cpu/pagging/inc/pagging_prv.h"

/*common includes*/
#include "cpu/pagging/exp/pagging.h"
#include "asm/exp/asm.h"

PAG_page_dir_entry_t PAG_fill_page_dir_4kb(PAG_page_dir_4k_arg_t *args) {
	PAG_page_dir_entry_t entry = args->address & 0xFFFFF000;	
	entry |= args->P << PAG_PAGE_DIR_P_OFFSET;
	entry |= args->RW << PAG_PAGE_DIR_RW_OFFSET;
	entry |= args->US << PAG_PAGE_DIR_US_OFFSET;
	entry |= args->PWT << PAG_PAGE_DIR_PWT_OFFSET;
	entry |= args->PCD << PAG_PAGE_DIR_PCD_OFFSET;
	entry |= args->A << PAG_PAGE_DIR_A_OFFSET;
	entry |= args->AVL_low << PAG_PAGE_DIR_AVL_LOW_OFFSET; 
	entry |= (args->AVL_high & PAGE_PAGE_DIR_AVL_HIGH_MASK) << PAG_PAGE_DIR_AVL_HIGH_OFFSET; 

	return entry;
}


PAG_page_dir_entry_t PAG_fill_page_table(PAG_page_table_arg_t *args) {
	PAG_page_table_entry_t entry = args->address & 0xFFFFF000;	
	entry |= args->P << PAG_PAGE_TABLE_P_OFFSET;
	entry |= args->RW << PAG_PAGE_TABLE_RW_OFFSET;
	entry |= args->US << PAG_PAGE_TABLE_US_OFFSET;
	entry |= args->PWT << PAG_PAGE_TABLE_PWT_OFFSET;
	entry |= args->PCD << PAG_PAGE_TABLE_PCD_OFFSET;
	entry |= args->A << PAG_PAGE_TABLE_A_OFFSET;
	entry |= args->D << PAG_PAGE_TABLE_D_OFFSET;
	entry |= args->PAT << PAG_PAGE_TABLE_PAT_OFFSET;
	entry |= args->G << PAG_PAGE_TABLE_G_OFFSET;
	entry |= (args->AVL & PAG_PAGE_TABLE_AVL_MASK) << PAG_PAGE_TABLE_AVL_OFFSET;
	return entry;
}

void PAG_setup_identity_1Mb() {
	PAG_page_dir_4k_arg_t page_dir_args;
	page_dir_args.address = (uintptr_t) PAG_identity_page_table_table;
	page_dir_args.P = true;
	page_dir_args.RW = true;
	page_dir_args.US = true;
	page_dir_args.PWT = false;
	page_dir_args.PCD = false;
	page_dir_args.A = false;
	PAG_identity_page_dir_table[0] = PAG_fill_page_dir_4kb(&page_dir_args);

	page_dir_args.P = false;

	for (int i = 1; i != 1024; i++) {
        	PAG_identity_page_dir_table[i] = PAG_fill_page_dir_4kb(&page_dir_args);
	}

	PAG_page_table_arg_t page_table_args;
	page_table_args.P = true;
	page_table_args.RW = true;
	page_table_args.US = true;
	page_table_args.PWT = false;
	page_table_args.PCD = false;
	page_table_args.A = false;
	page_table_args.D = true;
	page_table_args.PAT = false;
	page_table_args.G = false;

	uintptr_t page_start = 0;

	for(int pte_num = 0; pte_num != PAG_COUNT_4K_RECORD_FOR_1MB; pte_num++) {
		page_table_args.address = page_start;
		PAG_identity_page_table_table[pte_num] = PAG_fill_page_table(&page_table_args);	
		page_start += PAG_PAGE4K_SIZE;
	}

	page_table_args.P = false;
	for(int pte_num = PAG_COUNT_4K_RECORD_FOR_1MB; pte_num != PAG_PAGE_TABLE_RECORD_COUNT; pte_num++) {
		PAG_identity_page_table_table[pte_num] = PAG_fill_page_table(&page_table_args);	
	}	

	write_cr3((uintptr_t)PAG_identity_page_dir_table);
	uint32_t cr0 = read_cr0();
	cr0 |= (1u << 31);
	write_cr0(cr0);

}

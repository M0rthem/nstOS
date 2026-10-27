section .pagetables

global PAG_identity_page_dir_table
PAG_identity_page_dir_table: times 1024 dd 0

global PAG_identity_page_table_table
PAG_identity_page_table_table: times 1024 dd 0

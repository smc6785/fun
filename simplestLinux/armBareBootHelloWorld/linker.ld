ENTRY(_Start)
SECTIONS
{
. = 0x10000;
startup : { startup.o(.text)}
.data : {*(.data)}
.bss : {*(.bss)}
.= ALIGN(8);
. = . + 0x500;
sp_top = .;
}

set auto-load local-gdbinit
set history save on
set history size 10000
set history filename ~/.gdb_history
set verbose off
set disassembly-flavor intel
set print elements 0
set print pretty on

define book-quit
	set confirm off
end

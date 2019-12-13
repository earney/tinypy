clean:
	rm -rf build
	mkdir build

CC = sdcc

OBJ= $(SRCC:.c=.rel)

build/%.rel: tinypy/%.c
	$(CC) $(CFLAGS) $(INC) -c $<


pack:
	packihx build/vm.ihx > build/vm.hex

bin:
	hex2bin -p 00 vm.ihex > vm.bin

test: $(OBJ)

test1:
	echo $(OBJ)



DEFINES = -DSDCC -DDEBUG_LEVEL=0
<<<<<<< HEAD
OPTIMIZE = --opt-code-size
CFLAGS = -mz80 --verbose $(DEFINES) --std-c99 --disable-warning 126 $(OPTIMIZE)
=======
CFLAGS = -nogcse -mz80 --verbose $(DEFINES) --std-c99 --opt-code-size --disable-warning 126
>>>>>>> 449ddbd57230ea1596a66c78dddfe5dc40e3ce01
##--stack-auto
INC = -I/usr/sbin/share/sdcc/include -I. -I./tinypy
CC = sdcc

vm: clean
	$(CC) $(CFLAGS) $(INC) -c tinypy/bc.c -o build/bc.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/builtins.c -o build/builtins.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/dict.c -o build/dict.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/gc.c -o build/gc.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/tp_list.c -o build/tp_list.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/misc.c -o build/misc.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/ops.c -o build/ops.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/tp.c -o build/tp.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/tp_string.c -o build/tp_string.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/vm.c -o build/vm.rel
	$(CC) $(CFLAGS) $(INC) -c tinypy/vmmain.c -o build/vmmain.rel

vm1:
	$(CC) $(CFLAGS) $(INC) build/bc.rel build/builtins.rel build/dict.rel build/gc.rel build/tp_list.rel build/misc.rel build/ops.rel build/tp.rel build/tp_string.rel build/vm.rel build/vmmain.rel -o build/vm.ihx

sim:
	sz80 build/vm.ihx

vm_test:
	./tinypy/vm tinpy/tests.tpc

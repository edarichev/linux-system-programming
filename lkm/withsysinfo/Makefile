PWD   := $(shell pwd)
#SRCS   = mymodule.c showsysinfo.c
#OBJS   = $(SRCS:.c=.o)
#obj-m += $(OBJS)
obj-m := mymodule.o
mymodule-objs := showsysinfo.o


all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
install:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules_install
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean

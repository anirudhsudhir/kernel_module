obj-m += mem_mod.o

PWD := $(CURDIR)
build:
	@echo "\n\nBuilding module\n"
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	@echo "\nCleaning module files\n"
	# $(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm *.mod.*
	rm *.o
	rm *.order
	rm *.symvers
	rm *.ko
	rm *.mod


obj-m += mem_mod.o

PWD := $(CURDIR)
build:
	@echo "\n\nBuilding module\n"
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	@echo "\nCleaning module files\n"
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

run: clean build
	@echo "\n\nBefore loading module\n"
	sudo dmesg -k -H -L --time-format=reltime
	@echo "\n"
	@sudo insmod mem_mod.ko
	@echo "After loading module\n"
	sudo dmesg -k -H -L --time-format=reltime
	@sudo rmmod mem_mod
	@echo "\n"
	@echo "After unloading module\n"
	sudo dmesg -k -H -L --time-format=reltime


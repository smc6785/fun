GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o

%.o: %.c
	gcc $(GCCPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARMS) -o $@ $<

myKernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: myKernel.bin
	sudo cp $< /boot/myKernel.bin

myKernel.iso: myKernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "my operating systemm" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/myKernel.bin' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: myKernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvmm "my VM OS" &


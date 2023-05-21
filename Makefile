build_dir = build
kernel_dir = kernel

disk:
	rm -f $(build_dir)/disk.img
	qemu-img create -f raw $(build_dir)/disk.img 512M

iso:
	rm -f $(build_dir)/os.iso
	mkdir -p $(build_dir)/iso/boot/grub
	cp $(kernel_dir)/grub.cfg $(build_dir)/iso/boot/grub
	grub-mkrescue -o $(build_dir)/os.iso $(build_dir)/iso

run: iso
	qemu-system-i386 -cdrom $(build_dir)/os.iso -s -drive format=raw,file=$(build_dir)/disk.img,media=disk,if=none,id=disk -device ahci,id=ahci -device ide-hd,drive=disk,bus=ahci.0
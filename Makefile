all: alpha.log armhf.log i386.log hppa.log m68k.log mips.log mips64.log mipsel.log mips64el.log native.log ppc.log ppc64.log riscv64.log sh4.log sparc64.log x86_64.log
	md5sum *.log

a.out: main.c
	gcc main.c -Wall -Wextra -Og

clean:
	rm -f a.out* *.log

#Per-arch builds

a.out.native: main.c
	gcc $< -static -o $@

a.out.alpha: main.c
	alpha-linux-gnu-gcc $< -static -o $@

a.out.armhf: main.c
	arm-linux-gnueabihf-gcc $< -static -o $@

a.out.hppa: main.c
	hppa-linux-gnu-gcc $< -static -o $@

a.out.m68k: main.c
	m68k-linux-gnu-gcc $< -static -o $@

a.out.mips: main.c
	mips-linux-gnu-gcc $< -static -o $@

a.out.mipsel: main.c
	mipsel-linux-gnu-gcc $< -static -o $@

a.out.mips64: main.c
	mips64-linux-gnuabi64-gcc $< -static -o $@

a.out.mips64el: main.c
	mips64el-linux-gnuabi64-gcc $< -static -o $@

a.out.ppc: main.c
	powerpc-linux-gnu-gcc $< -static -o $@

a.out.ppc64: main.c
	powerpc64-linux-gnu-gcc $< -static -o $@

a.out.riscv64: main.c
	riscv64-linux-gnu-gcc $< -static -o $@

a.out.sh4: main.c
	sh4-linux-gnu-gcc $< -static -o $@

a.out.sparc64: main.c
	sparc64-linux-gnu-gcc $< -static -o $@

a.out.i386: main.c
	i686-linux-gnu-gcc $< -static -o $@

a.out.x86_64: main.c
	x86_64-linux-gnu-gcc $< -static -o $@

#Per-arch runs

native.log: a.out.native
	./$< > $@

alpha.log: a.out.alpha
	qemu-alpha $< > $@

armhf.log: a.out.armhf
	qemu-armhf $< > $@

hppa.log: a.out.hppa
	qemu-hppa $< > $@

m68k.log: a.out.m68k
	qemu-m68k $< > $@

mips.log: a.out.mips
	qemu-mips $< > $@

mipsel.log: a.out.mipsel
	qemu-mipsel $< > $@

mips64.log: a.out.mips64
	qemu-mips64 $< > $@

mips64el.log: a.out.mips64el
	qemu-mips64el $< > $@

ppc.log: a.out.ppc
	qemu-ppc $< > $@

ppc64.log: a.out.ppc64
	qemu-ppc64 $< > $@

riscv64.log: a.out.riscv64
	qemu-riscv64 $< > $@

sh4.log: a.out.sh4
	qemu-sh4 $< > $@

sparc64.log: a.out.sparc64
	qemu-sparc64 $< > $@

i386.log: a.out.i386
	qemu-i386 $< > $@

x86_64.log: a.out.x86_64
	qemu-x86_64 $< > $@

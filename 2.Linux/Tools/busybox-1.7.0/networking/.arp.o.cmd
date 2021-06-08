cmd_networking/arp.o := /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/arm-linux-gcc -Wp,-MD,networking/.arp.o.d   -std=gnu99 -Iinclude -Ilibbb  -I/home/zion/gcc_jz2440/busybox-1.7.0/libbb -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.7.0)" -DBB_BT=AUTOCONF_TIMESTAMP -D_FORTIFY_SOURCE=2  -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes  -Wmissing-prototypes -Wmissing-declarations -Os -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -Wdeclaration-after-statement     -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(arp)"  -D"KBUILD_MODNAME=KBUILD_STR(arp)" -c -o networking/arp.o networking/arp.c

deps_networking/arp.o := \
  networking/arp.c \
    $(wildcard include/config/feature/clean/up.h) \
  include/libbb.h \
    $(wildcard include/config/selinux.h) \
    $(wildcard include/config/locale/support.h) \
    $(wildcard include/config/feature/shadowpasswds.h) \
    $(wildcard include/config/lfs.h) \
    $(wildcard include/config/feature/buffers/go/on/stack.h) \
    $(wildcard include/config/buffer.h) \
    $(wildcard include/config/ubuffer.h) \
    $(wildcard include/config/feature/buffers/go/in/bss.h) \
    $(wildcard include/config/feature/ipv6.h) \
    $(wildcard include/config/ture/ipv6.h) \
    $(wildcard include/config/feature/prefer/applets.h) \
    $(wildcard include/config/busybox/exec/path.h) \
    $(wildcard include/config/getopt/long.h) \
    $(wildcard include/config/feature/pidfile.h) \
    $(wildcard include/config/feature/syslog.h) \
    $(wildcard include/config/route.h) \
    $(wildcard include/config/gunzip.h) \
    $(wildcard include/config/ktop.h) \
    $(wildcard include/config/ioctl/hex2str/error.h) \
    $(wildcard include/config/feature/editing.h) \
    $(wildcard include/config/feature/editing/history.h) \
    $(wildcard include/config/ture/editing/savehistory.h) \
    $(wildcard include/config/feature/editing/savehistory.h) \
    $(wildcard include/config/feature/tab/completion.h) \
    $(wildcard include/config/feature/username/completion.h) \
    $(wildcard include/config/feature/editing/vi.h) \
    $(wildcard include/config/inux.h) \
    $(wildcard include/config/feature/devfs.h) \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config///.h) \
    $(wildcard include/config//nommu.h) \
    $(wildcard include/config//mmu.h) \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/byteswap.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/byteswap.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/endian.h \
    $(wildcard include/config/.h) \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/features.h \
    $(wildcard include/config/c99.h) \
    $(wildcard include/config/ix.h) \
    $(wildcard include/config/ix2.h) \
    $(wildcard include/config/ix199309.h) \
    $(wildcard include/config/ix199506.h) \
    $(wildcard include/config/en.h) \
    $(wildcard include/config/en/extended.h) \
    $(wildcard include/config/x98.h) \
    $(wildcard include/config/en2k.h) \
    $(wildcard include/config/gefile.h) \
    $(wildcard include/config/gefile64.h) \
    $(wildcard include/config/e/offset64.h) \
    $(wildcard include/config/d.h) \
    $(wildcard include/config/c.h) \
    $(wildcard include/config/ntrant.h) \
    $(wildcard include/config/tify/level.h) \
    $(wildcard include/config/i.h) \
    $(wildcard include/config/ern/inlines.h) \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/cdefs.h \
    $(wildcard include/config/espaces.h) \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/gnu/stubs.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/endian.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/arpa/inet.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/netinet/in.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/stdint.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/wchar.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/wordsize.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/socket.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/uio.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/types.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/types.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/include/stddef.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/typesizes.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/time.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/select.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/select.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigset.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/time.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/sysmacros.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/pthreadtypes.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sched.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/uio.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/socket.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/include/limits.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/include/syslimits.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/limits.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/posix1_lim.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/local_lim.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/linux/limits.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/posix2_lim.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/xopen_lim.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/stdio_lim.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sockaddr.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/socket.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/sockios.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/in.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/include/stdbool.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/mount.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/ioctl.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/ioctls.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/ioctls.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/ioctl.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/ioctl-types.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/ttydefaults.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/ctype.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/xlocale.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/dirent.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/dirent.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/errno.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/errno.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/linux/errno.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/errno.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/fcntl.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/fcntl.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/stat.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/stat.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/inttypes.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/mntent.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/stdio.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/paths.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/netdb.h \
    $(wildcard include/config/3/ascii/rules.h) \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/rpc/netdb.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/siginfo.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/netdb.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/setjmp.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/setjmp.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/signal.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/signum.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigaction.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigcontext.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/sigcontext.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigstack.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/ucontext.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/procfs.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/time.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/user.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigthread.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/libio.h \
    $(wildcard include/config/a.h) \
    $(wildcard include/config/ar/t.h) \
    $(wildcard include/config//io/file.h) \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/_G_config.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/wchar.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/gconv.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/include/stdarg.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sys_errlist.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/stdlib.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/waitflags.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/waitstatus.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/alloca.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/string.h \
    $(wildcard include/config/ing/inlines.h) \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/mman.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/mman.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/statfs.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/statfs.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/wait.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/resource.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/resource.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/termios.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/termios.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/unistd.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/posix_opt.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/environments.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/confname.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/getopt.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/utime.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/locale.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/locale.h \
  include/pwd_.h \
    $(wildcard include/config/use/bb/pwd/grp.h) \
  include/grp_.h \
  include/shadow_.h \
    $(wildcard include/config/use/bb/shadow.h) \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/param.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/linux/param.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/param.h \
  include/xatonum.h \
  include/inet_common.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/net/if.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/net/if_arp.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/netinet/ether.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/netinet/if_ether.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/linux/if_ether.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/net/ethernet.h \
  /home/zion/gcc_jz2440/arm-linux-gcc-3.4.5-glibc-2.3.6/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/netpacket/packet.h \

networking/arp.o: $(deps_networking/arp.o)

$(deps_networking/arp.o):

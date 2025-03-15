# Loadable Kernel Module

A Linux loadable kernel module to trace the memory map of a process and its children.

## Usage

```sh
chmod +x run.sh
./run.sh run <pid of process to trace> # eg: ./run.sh run 12345
```

This script builds the kernel module, loads it, displays logs from kernel ring buffer via `dmesg`, unloads it and cleans the directory of all build artifacts.

To use the provided sample program that forks and allocates memory on the heap,
run the following in another terminal session:

```sh
cd fork_alloc/
make
```

### Note: LSP Support

```sh
chmod +x run.sh
./run.sh compile_commands
```

This script generates a `compile_commands.json` for LSP support (tested only with clangd).

## References

- Kernel Module Programming Guide: [https://sysprog21.github.io/lkmpg/](https://sysprog21.github.io/lkmpg/)

- Accessing a process' memory map: [https://linux-kernel-labs.github.io/refs/heads/master/labs/memory_mapping.html#structures-used-for-memory-mapping](https://linux-kernel-labs.github.io/refs/heads/master/labs/memory_mapping.html#structures-used-for-memory-mapping)

- Memory areas: [https://litux.nl/mirror/kerneldevelopment/0672327201/ch14lev1sec2.html](https://litux.nl/mirror/kerneldevelopment/0672327201/ch14lev1sec2.html)

- Linux kernel list_entry(): [https://stackoverflow.com/questions/5550404/list-entry-in-linux](https://stackoverflow.com/questions/5550404/list-entry-in-linux)

- Linux kernel list_for_each_entry(): [https://stackoverflow.com/questions/16230524/explain-list-for-each-entry-and-list-for-each-entry-safe](https://stackoverflow.com/questions/16230524/explain-list-for-each-entry-and-list-for-each-entry-safe)

- Linux kernel source - Memory Segments: [https://github.com/torvalds/linux/blob/master/include/linux/mm.h#L956](https://github.com/torvalds/linux/blob/master/include/linux/mm.h#L956)

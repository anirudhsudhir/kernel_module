# Linux Kernel Module

A Linux kernel module to trace the memory map of a process and its children.

## Usage

```sh
chmod +x run.sh
./run.sh run <pid of process to trace> # eg: ./run.sh run 12345
```

This script builds the kernel module, loads it, displays logs from kernel ring buffer via `dmesg`, unloads it and cleans the directory of all build artifacts.

### Note: LSP Support

```
chmod +x run.sh
./run.sh compile_commands
```

This script generates a `compile_commands.json` for LSP support(tested only with clangd).

## References

- Kernel Module Programming Guide: [https://sysprog21.github.io/lkmpg/](https://sysprog21.github.io/lkmpg/)

- Accessing a process' memory map: [https://linux-kernel-labs.github.io/refs/heads/master/labs/memory_mapping.html#structures-used-for-memory-mapping](https://linux-kernel-labs.github.io/refs/heads/master/labs/memory_mapping.html#structures-used-for-memory-mapping)
- [https://stackoverflow.com/questions/39871740/read-running-processes-virtual-memory-from-mm-struct-in-linux](https://stackoverflow.com/questions/39871740/read-running-processes-virtual-memory-from-mm-struct-in-linux)


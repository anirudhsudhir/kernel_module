#!/bin/bash

compile_commands() {
  bear -- make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
}

run() {
  reset
  sudo dmesg -C
  make clean 1>/dev/null 2>&1
  make build 1>/dev/null 2>&1
  # echo -e "\n\nBefore loading module\n"
  # sudo dmesg -k -H -L -P --time-format=reltime
  echo -e "\n"
  echo -e "Loading module...\n"
  sudo insmod mem_mod.ko pid-int="$2"
  # sudo dmesg -k -H -L -P --time-format=reltime
  sudo rmmod mem_mod
  # echo -e "\n"
  echo -e "Unloading module...\n"
  sudo dmesg -k -H -L -P --time-format=reltime
  make clean 1>/dev/null 2>&1
}

case "$1" in
"compile_commands")
  compile_commands
  ;;
"run")
  run "$@"
  ;;
esac

compile_commands() {
  bear -- make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
}

run() {
  make clean
  make build
  echo "\n\nBefore loading module\n"
  sudo dmesg -k -H -L --time-format=reltime
  echo "\n"
  sudo insmod mem_mod.ko pid-int="$2"
  echo "After loading module\n"
  sudo dmesg -k -H -L --time-format=reltime
  sudo rmmod mem_mod
  echo "\n"
  echo "After unloading module\n"
  sudo dmesg -k -H -L --time-format=reltime
  make clean
}

case "$1" in
"compile_commands")
  compile_commands
  ;;
"run")
  run "$@"
  ;;
esac

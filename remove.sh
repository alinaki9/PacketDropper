#!/bin/bash

# for removing the module from the kernel
rmmod packet_drop

# checking whether the module was removed or not
lsmod | grep packet_drop

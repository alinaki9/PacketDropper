#!/bin/bash

# for inserting the module into the kernel
insmod packet_drop.ko

# checking whether the module has been inserted or not
lsmod | grep packet_drop

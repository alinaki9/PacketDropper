cmd_/work/modules.order := {   echo /work/packet_drop.ko; :; } | awk '!x[$$0]++' - > /work/modules.order

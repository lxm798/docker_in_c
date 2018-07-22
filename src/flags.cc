#include "flags.h"
DEFINE_string(image_name, "", "rootfs path");
DEFINE_string(cmd, "/bin/bash", "start cmd");
DEFINE_int32(cpu, 500000, "cpu usage");
DEFINE_int32(mem, 512, "mem usage");
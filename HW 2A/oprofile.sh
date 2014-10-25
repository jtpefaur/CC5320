#!/bin/sh
sudo opcontrol --init
sudo opcontrol --reset
sudo opcontrol --event=CPU_CLK_UNHALTED:75000 --start
./rgb.g > /dev/null
sudo opcontrol --shutdown
sudo opannotate --source

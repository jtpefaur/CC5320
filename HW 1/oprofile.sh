#!/bin/sh
sudo opcontrol --init
sudo opcontrol --reset
sudo opcontrol --event=CPU_CLK_UNHALTED:75000 --start
./pi.pg3
sudo opcontrol --shutdown
sudo opannotate --source

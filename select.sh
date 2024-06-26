#!/bin/bash
#xdotool key 199

xdotool mousemove $1 $2
xdotool click 1
#spam accept

#xdotool mousemove 1802 1402
xdotool mousemove $3 $4
xdotool click 1

for ((i = 0; i < (10 + $RANDOM % 7); i++))
do
#  sleep (1 + $RANDOM % 7) / 100
  xdotool click 1
  sleep .001
done

#sleep 1
##close window
#xdotool mousemove 2188 839
#xdotool click 1
#
#sleep .5

#xdotool mousemove 1607 170
#xdotool click 1

#xdotool key 199
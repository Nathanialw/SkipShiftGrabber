#!/bin/bash
x=$((1900 + $RANDOM % 100))
y=$((330 + $RANDOM % 50))
xdotool mousemove $x $y
xdotool mousedown 1


for ((j = 0; j < 103 + $RANDOM % 184; j++))
do
  a=$((0 + $RANDOM % 2))
  b=$((2 + $RANDOM % 2))
  xdotool mousemove_relative $a $b
done

xdotool mouseup 1
#!/bin/bash
echo "enter your age"
read $age
echo "your entered age is: $age"
if test  $age -lt 30
then 
echo "you are still under 30"
else
echo "you are above 30"
fi

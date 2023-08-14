#!/bin/sh
echo "arguments found: $#"
arg=$#;
a=3
if [ $arg==3 ]; then echo "$1 $2 $3";
else
	echo "three arguments not present";
fi

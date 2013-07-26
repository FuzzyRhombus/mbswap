#!/bin/bash

# Get current path
CURR_PATH="`dirname \"$0\"`"
cd $CURR_PATH

# Run make
make clean; make

# Now copy everything over
zero=0;
if [[ $? -eq $zero ]]; then
	INSTALL_PATH=/usr/bin
	sudo mv mbswap $INSTALL_PATH/mbswap
	sudo chown 0 $INSTALL_PATH/mbswap
	sudo chmod 755 $INSTALL_PATH/mbswap
	sudo install -g 0 -o 0 -m 644 mbswap.1 /usr/local/share/man/man1/
	sudo gzip /usr/local/share/man/man1/mbswap.1
fi

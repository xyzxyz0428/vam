# Simple makefile to help install HMI icons
# Location for icons
INSTALL_DIR=/mnt/ubi/exampleETSI

all:
	# Nothing to do

install:
	# Install python-pygame (needed by hmi-display.py)
	sudo apt-get -q -y install python-pygame
	# Put icons files in 'default' location
	mkdir -p ${INSTALL_DIR}/ui
	rsync -avz . ${INSTALL_DIR}/ui/

uninstall:
	rm -rf ${INSTALL_DIR}/ui

clean:
	# nothing to do

.PHONY: install clean all


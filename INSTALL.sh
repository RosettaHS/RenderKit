#!/bin/sh

###################################################################################
#                                                                                 #
#                               Copyright (c) 2021                                #
#                            Rosetta H&S International                            #
#                                                                                 #
#   Permission is hereby granted, free of charge, to any person obtaining a copy  #
#  of this software and associated documentation files (the "Software"), to deal  #
#   in the Software without restriction, including without limitation the right   #
#     to use, copy, modify, merge, publish, distribute, sublicense, and/or sell   #
#        copies of the Software, and to permit persons to whom the Software is    #
#           furnished to do so, subject to the following conditions:              #
#                                                                                 #
#  The above copyright notice and this permission notice shall be included in all #
#                 copies or substantial portions of the Software.                 #
#                                                                                 #
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     #
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       #
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    #
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         #
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  #
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  #
#  SOFTWARE.                                                                      #
#                                                                                 #
###################################################################################

AUTO_Y=false
QUIET=false
PREV_INST=false

### Startup

[ ! -e "INSTALL.sh" ] && { echo "RenderKit : Please run inside the directory this script is located in."; exit 1; }

[ "$(id -u)" -ne 0 ] && { echo "RenderKit : Please run as root."; exit 1; }

while getopts qy flag; do
	case $flag in
	q) QUIET=true;;
	y) AUTO_Y=true;;
	*) echo "RenderKit | ERROR! : Invalid Operand. Aborting"; exit 1;;
	esac
done

### Execution

if [ "$QUIET" = false ]; then
	clear
fi

# Check if system has "make", and if not, install it.
if ! dpkg -s "make" >/dev/null 2>&1; then 
	if [ "$AUTO_Y" = true ]; then
		echo 'RenderKit : Dependency "make" is not installed. Retrieving.'
	else
		printf 'RenderKit  : Dependency "make" is not installed. It is required for RenderKit to be compiled. Would you like to install this dependency? [Y/n] : '; read conf
		case ${conf} in
			[!Yy]) echo 'RenderKit : Aborted.'; exit 1;;
		esac
	fi

	echo "RenderKit : Working on installing Make."
	apt-get install "make" -y || { echo "RenderKit | ERROR! : Make could not be installed! Aborting."; exit 1; }
	echo "RenderKit : Make successfully installed."
fi

# Check if system has "libxcb1-dev", and if not, install it.
if ! dpkg -s "libxcb1-dev" >/dev/null 2>&1; then 
	if [ "$AUTO_Y" = true ]; then
		echo 'RenderKit : Dependency "libxcb1-dev" is not installed. Retrieving.'
	else
		printf 'RenderKit  : Dependency "libxcb1-dev" is not installed. It is required for RenderKit to be compiled. Would you like to install this dependency? [Y/n] : '; read conf
		case ${conf} in
			[!Yy]) echo "RenderKit : Aborted."; exit 1;;
		esac
	fi

	echo "RenderKit : Working on installing XCB." 
	apt-get install "libxcb1-dev" -y || { echo "RenderKit | ERROR! : XCB could not be installed! Aborting."; exit 1; }
	printf "\nRenderKit : XCB successfully installed.\n"
fi

# Check if RenderKit currently exists on this system, and if it does, remove the current version. 
if [ -e "/usr/lib/libRK.so" ]; then
	PREV_INST=true
	if [ "$AUTO_Y" = true ]; then
		echo "RenderKit : RenderKit is already installed, removing currently installed version for reinstall."
	else
		printf "RenderKit : RenderKit is already installed, would you like to reinstall? [Y/n] : "; read conf
		case ${conf} in
			[!Yy]) echo "RenderKit : Aborted."; exit 1;;
		esac
	fi
		rm -rf "/usr/include/.renderkit" >/dev/null 2>&1 || echo 'RenderKit | WARNING! : Current version include folder "/usr/include/.renderkit" not found, failed to remove.'
		rm "/usr/include/renderkit.h" >/dev/null 2>&1		|| echo 'RenderKit | WARNING! : Current version header file "/usr/include/renderkit.h" not found, failed to remove.'
		rm "/usr/lib/libRK.so" >/dev/null 2>&1			|| echo 'RenderKit | WARNING! : Current version source library "/usr/lib/libRK.so" not found, failed to remove.'
	echo "RenderKit : Current version successfully removed."
fi

# Ready to be installed. If flag "-y" is not set, ask for permisson to proceed.
if [ "$AUTO_Y" = false -a "$PREV_INST" = false ]; then
	printf 'RenderKit : RenderKit is ready to be installed. Would you like to proceed? [Y/n] : '; read conf
	case ${conf} in
		[!Yy]) echo 'RenderKit : Aborted.'; exit 1;;
	esac
fi

# Compiles the source code.
echo "RenderKit : Compiling source code..."
make shared >/dev/null || { echo "RenderKit : ERROR! Failed to compile source code! Aborting."; exit 1; }
echo "RenderKit : Successfully compiled OKit source code."

# Moves it to the "/usr/lib" directory.
cp "libRK.so" "/usr/lib/libRK.so" || { echo 'RenderKit : ERROR! Failed to copy compiled library as "/usr/lib/libRK.so"! Aborting.'; exit 1; }
echo "RenderKit : Copied RenderKit (libRK.so) to system libaries directory."

# Removes the compiled files from the current directory.
rm ./*.o ./*.so >/dev/null 2>&1

# Installs the header files from "src/include" into "/usr/include/.RenderKit".
echo "RenderKit : Working on installing header files..."
cp -R "src/include/" "/usr/include/.renderkit" || { echo 'RenderKit : ERROR! Failed to copy header files into "/usr/include/.renderkit"! Aborting.'; exit 1; }

# Installs the redirect header "src/SYSHEADER" as "usr/include/RenderKit".
cp "src/SYSHEADER" "/usr/include/renderkit.h" || { echo 'RenderKit : ERROR! Failed to copy redirect header as "/usr/include/renderkit.h"! Aborting.'; exit 1; }
echo 'RenderKit : Copied header files. Use "#include <renderkit.h>" in your C/C++ files to use these headers.'

# End ASCII
if [ "$QUIET" = false ]; then
	echo
	echo ".oOOOo.                                             oO"
	echo "o     o                                             OO"
	echo "O.                                                  oO"
	echo " \`OOoo.                                             Oo"
	echo "      \`O O   o  .oOo  .oOo  .oOo. .oOo  .oOo        oO"
	echo "       o o   O  O     O     OooO' \`Ooo. \`Ooo.         "
	echo "O.    .O O   o  o     o     O         O     O       Oo"
	echo " \`oooO'  \`OoO'o \`OoO' \`OoO' \`OoO' \`OoO' \`OoO'       oO"
	echo
fi

printf "\nRenderKit : RenderKit has been successfully installed. To compile your applications with the RenderKit, simply use the library flag \"-lRK\", and follow the documentation for more information.\n\n"

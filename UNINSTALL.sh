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

### Startup

[ ! -e "UNINSTALL.sh" ] && { echo "RenderKit : Please run inside the directory this script is located in."; exit 1; }

[ "$(id -u)" -ne 0 ] && { echo "RenderKit : Please run as root."; exit 1; }

while getopts qy flag; do
	case $flag in
	q) QUIET=true;;
	y) AUTO_Y=true;;
	*) echo "RenderKit | ERROR! : Invalid Operand. Aborting"; exit 1;;
	esac
done

### Execution

# Checks if RenderKit is installed on this system. If false, quits the installer.
[ -e "/usr/lib/libRK.so" ] || { echo "RenderKit | ERROR! : RenderKit is not installed on this system, cannot proceed!"; exit 1; }


if [ "$QUIET" = false ]; then
	clear
fi

# Asks for permission to continue the removal process.
if [ "$AUTO_Y" = false ]; then
	printf "RenderKit : RenderKit is eligible to be uninstalled. Would you like to proceed? [Y/n] : "; read conf
	case ${conf} in
		[!Yy])
			echo "RenderKit : Aborted."; exit 1;;
	esac
else
	echo "RenderKit : RenderKit is eligible to be uninstalled. Proceeding."
fi

# Removes the library file itself.
rm "/usr/lib/libRK.so" || { echo 'RenderKit | ERROR! : Failed to uninstall "libRK.so"! Aborting.'; exit 1; }
echo 'RenderKit : Uninstalled "libRK.so"'

# Checks if the header directory exists, and if it does, removes it and its content.
if [ -d "/usr/include/.renderkit" ]; then
	rm -rf "/usr/include/.renderkit" || { echo "RenderKit | ERROR! : Failed to uninstall RenderKit system headers! Aborting."; exit 1; }
	echo "RenderKit : Uninstalled RenderKit system headers."

	rm "/usr/include/renderkit.h" || { echo "RenderKit | ERROR! : Failed to uninstall RenderKit master header! Aborting."; exit 1; }
	echo "RenderKit : Uninstalled RenderKit master header."
fi

# Checks if XCB is still installed, and if it is, goes ahead and uninstalls it for you.
if dpkg -s "libxcb1-dev" > /dev/null 2>&1; then
	if [ "$AUTO_Y" = false ]; then
		printf "RenderKit : XCB was installed alongside RenderKit and is no longer needed. Would you like to uninstall XCB as well? [Y/n] : "; read conf
		case ${conf} in
			[Yy])
				echo 'RenderKit : Working on uninstalling "libxcb1-dev".'
				apt-get purge "libxcb1-dev" -y || { echo 'OrionAP | ERROR! : Failed to uninstall "libxcb1-dev"! Aborting.'; exit 1; }
				echo 'RenderKit : "libxcb1-dev" successfully uninstalled.';;
		esac
	else
		echo "RenderKit : XCB was installed alongside RenderKit and is no longer needed. Uninstalling."

		echo 'RenderKit : Working on uninstalling "libxcb1-dev".'
		apt-get purge "libxcb1-dev" -y || { echo 'OrionAP | ERROR! : Failed to uninstall "libxcb1-dev"! Aborting.'; exit 1; }
		printf "\nRenderKit : \"libxcb1-dev\" successfully uninstalled.\n"
	fi
fi

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

printf "\nRenderKit : RenderKit has been successfully uninstalled.\n\n"

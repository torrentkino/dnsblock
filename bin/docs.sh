#!/bin/sh

if [ ! $(which ronn) ]; then
	apt-cache show ruby-ronn
	echo "# sudo apt install ronn"
	exit
fi

ronn < README.md > debian/docs/dnsblock.1

cat > debian/dnsblock.manpages <<EOF
./debian/docs/dnsblock.1
EOF

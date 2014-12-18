#!/bin/sh

if [ ! $(which ronn) ]; then
	apt-cache show ruby-ronn
	echo "# sudo apt-get install ruby-ronn"
	exit
fi

ronn < README.md > debian/docs/dnsblock.1

cat > debian/dnsblock.manpages <<EOF
./debian/docs/dnsblock.1
EOF

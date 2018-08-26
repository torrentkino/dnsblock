dnsblock(1) -- Regex Hosts file
===============================

## MISSION

It becomes harder and harder to control to whom your computer wants to talk. While visiting a web page your computer contacts tracking services or even malware platforms all over the world. This may happen within email programs as well. Cloud services are fast moving targets with various backends and vendors. This line of defense focuses on DNS.

## DESCRIPTION

*dnsblock* is a NSS library that acts like the /etc/hosts file except that it makes use of regular expressions (PCRE) to match the hostname. Create a configuration file ~/.dnsblock and add *dnsblock* to your /etc/nsswitch.conf configuration to enable *dnsblock*.

## INSTALLATION

There is a simple installation helper for Debian/Ubuntu. Just run one of the
following commands to create a installable package.

	$ make debian
	$ make ubuntu

Otherwise, you may use

	$ make
	$ sudo make install

## CONFIGURATION

/etc/nsswitch.conf

	hosts: files dnsblock dns

## EXAMPLES

/etc/dnsblock

	# Early pass-through for all multicast DNS requests.
	* 			\.local$

	# Block ad servers like adserver.example.net.
	127.0.0.1	^adserver\.

	# Block tracking servers like tracking123.somedomain.com.
	127.0.0.2	^tracking\d*\.

	# Pass-through some TLDs.
	* 			\.nl$
	* 			\.se$
	* 			\.org$

	# Block everything else.
	127.0.0.3	.*

Have a look at *docs/dnsblock.example* for a real life example.

## LOGGING

*dnsblock* logs all DNS requests to your log environment.

	$ tail -f /var/log/messages
	$ journalctl -b -f

## FILES

dnsblock reads /etc/dnsblock and $HOME/.dnsblock in that particular order. Both files get parsed if they exist.

## CHROME NOTES

Chrome acts like a full featured OS within your OS and comes with its own DNS resolver. It was once possible to use the Linux OS DNS resolver. But it seems like this feature has been disabled now. Search for *experimental asynchronous DNS client* and *chrome://flags*.

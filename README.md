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

Add dnsblock to /etc/nsswitch.conf for regular use.

	hosts: files dnsblock dns

Add dnsblock_debug for debugging purposes.

  hosts: files dnsblock_debug dns

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

*dnsblock_debug* logs all DNS requests to your log environment.

	$ tail -f /var/log/messages
	$ journalctl -b -f

## FILES

dnsblock reads /etc/dnsblock and $HOME/.dnsblock in that particular order. Both files get parsed if they exist.

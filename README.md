dnsblock(1) -- Hosts file with regex support
============================================

## DESCRIPTION

*dnsblock* is a NSS library that acts like the /etc/hosts file except that it makes use of Perl regular expressions (PCRE) to match the hostname. Create a configuration file ~/.dnsblock and add *dnsblock* to your /etc/nsswitch.conf configuration to enable *dnsblock*.

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

	# Path through all multicast DNS requests
	- 			\.local$

	# Path through all DE domains
	- 			\.de$

	# Block ad servers like adserver.example.net
	127.0.0.1	^adserver\.

	# Block tracking servers like tracking123.somedomain.com
	127.0.0.2	^tracking\d*\.

	# Block social media plugins that keep tracking you with "Like" buttons
	::1			\.randombook\.(com|net)$

	# Block requests to specific TLDs
	::1			\.(gov|xxx)$

## LOGGING

*dnsblock* logs all DNS requests to your log environment.

	$ tail -f /var/log/messages
	$ journalctl -b -f

## FILES

dnsblock reads /etc/dnsblock and $HOME/.dnsblock in that particular order. Both files get parsed if they exist.

## CHROMIUM NOTES

chromium seems to use its own DNS resolver and bypasses the DNS resolver of your operating system. You can disable this behaviour by surfing to *chrome://flags/*. Disable the *experimental asynchronous DNS client*.

## FIREFOX NOTES

Firefox offers the following plugins, that make your surfing experience extremely uncomfortable. :)

	* NoScript
	* RequestPolicy
	* CookieMonster
	* Certificate Patrol
	* DNSSEC TLSA Validator
	* Various Adblockers

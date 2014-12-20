dnsblock(1) -- Hosts file with regex support
============================================

## DESCRIPTION

*dnsblock* is a NSS library that works like the /etc/hosts file except that it makes use of Perl regular expressions (PCRE) to determine the target. That makes it more suitable to block outgoing traffic than the /etc/hosts file itself. Create a configuration file /etc/dnsblock and add *dnsblock* to your /etc/nsswitch.conf configuration to make it work.

The major problem behind this is that it gets harder and harder to get knowledge of the ongoing outgoing traffic. Some people create huge /etc/hosts files that contain the exact hostnames of the offending servers. This is a little bit too static while cloud services throw out hundreds of new servers with random IP addresses every week.

Besides the battery problems, ad servers became an attractive attack platform in the past. Controlling ad servers enable attackers to deploy malware to bigger audiences on large websites. These ad platforms are controlled by random ad service providers and not necessarily by those large website operators.

*dnsblock* happens before the real DNS request. So it should not interfere with DNSSEC.

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

	# Block ad servers like adserver.example.net
	127.0.0.1	^adserver\.

	# Block tracking servers like tracking123.somedomain.com
	127.0.0.2	^tracking\d*\.

	# Block social media plugins that track you on every bigger site
	::1			\.randombook\.(com|net)$

	# Block requests to specific TLDs
	::1			\.(gov|xxx)$

## LOGGING

*dnsblock* logs all dns requests at the moment. An on/off switch will be made later. You can follow the lookup attempts with the following approaches depending on your system.

	$ tail -f /var/log/messages
	$ journalctl -b -f

## FILES

dnsblock tries to read /etc/dnsblock and $HOME/.dnsblock in that particular order. Both files get parsed if they exist.

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

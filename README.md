mbswap (switchMainDisplay) for Mac.
==================================

The original name of this utility is/was *switchMainDisplay*. However, this is cumbersome to type in a terminal, so it was changed to **mbswap**, meaning "menu bar" swap.

The need for this tool arose due to my use of a second external monitor on my MBP and somewhat ADD-like habits. In the middle of something I may decide to use a utility or play a game that requires fullscreen for a short period of time. However many apps only support fullscreen on the main display (the one containing the menu bar). In order to display them on the external I would have to switch the menu bar to the other display. Any Mac user knows how awful this is in System Prefs.

By simply calling `mbswap` with two displays connected, the menu bar will toggle between displays. **mbswap** works best with a tool like [TotalTerminal][1], that allows quick easy access to an always available terminal.

Installation
------------
A Makefile and install script are included to ease and explain the installation of **mbswap**. 

The install script assumes you have `gcc` and `make` installed. It will first invoke `make`, and on success copy the executable to `/usr/bin`. A man page will also be added for mbswap. The script makes use of sudo, so you will need to enter a password.

Usage
-----

**mbswap** has very simple usage - mainly designed to take no options. As such it does not have many features. It would not be hard to add more, but it would negate the intentional simplicity of the tool. If you would like more display options from command-line, check out [fb-rotate][2] or cscreen.

Other than the default usage, check the man page for a detailed explanation. Or just scan the code if you would like - it's short.

Credits
-------
**mbswap** was created by Ryan Mastrolia, and is available under the GNU GPL. See *COPYING.txt* for details.

Copyright © 2012, 2013 Ryan Mastrolia.
 

[1]: http://totalterminal.binaryage.com "TotalTerminal Mac"
[2]: https://github.com/CdLbB/fb-rotate "fb-rotate on github"
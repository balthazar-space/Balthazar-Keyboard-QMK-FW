Veronica Security Engine is a part of open-hardware laptop software and firmware computer modules.

Modules as presented at https://balthazar.space/wiki/Balthazar and at https://github.com/balthazar-space with the main aim for team access

# balthazarKeyboardQMK

Balthazar open-hardware laptop - QMK firmware https://docs.qmk.fm/ for keyboard and touchpad module.

Veronica Security engine is a collection of custom keyboard/boot software features that improve security through:

a) activating Balthazar's keyboard 
b) activating input readable on a small OLED screen positioned above the keyboard and just left of the track-pad/trackball
c) enabling user to choose a device to boot from
d) pasword required only once for the whole laptop to be unlocked and booted into and logged in user's session

Veronica's QMK firmware is a natural solution for ATmega 32u4 based keyboards. 
Copy the balthazar folder above into keyboards folder of your qmk_firmware installation. 

balthazar_default.hex is a compiled default keymap version. 
It is for caterina bootloader ATmega 32u4 chips taken from Chinese Sparkfun Pro Micro clones.

At this point only the default keymap is fully tested and working. 
There is rather limited touchpad-trackball support and no OLED display support yet, also the security activation password module is in an early testing "bazaar" phase.

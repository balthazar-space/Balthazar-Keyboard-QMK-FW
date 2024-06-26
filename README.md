# Balthazar

Open-hardware laptop computer modules description and concept.

These are electronic schematic modules as presented at https://balthazar.space/wiki/Balthazar with the main aim for team access. See the [main repository](https://github.com/balthazar-space/balthazar) for other designs.

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
There is rather limited touchpad-trackball support and WIP OLED display support, also the security activation password module is in an early testing "bazaar" phase.

**_beware:_** The password is saved plaintext in the microcontroller's EEPROM. It can be extracted with proper equipment and can easily be overwritten on the currently used ATmega32u4.

## License

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

See the [LICENSE.md](./LICENSE.md) file for more information.

## Funding

This project is funded through the [NGI Zero Entrust Fund](https://nlnet.nl/entrust), a fund
established by [NLnet](https://nlnet.nl) with financial support from the European Commission's
[Next Generation Internet](https://ngi.eu) program. Learn more on the [NLnet project page](https://nlnet.nl/project/Balthazar-Casing/).

[<img src="https://nlnet.nl/logo/banner.png" alt="NLNet foundation logo" width="300" />](https://nlnet.nl)
[<img src="https://nlnet.nl/image/logos/NGI0Entrust_tag.svg" alt="NGI0 Entrust Logo" width="300" />](https://nlnet.nl/entrust)

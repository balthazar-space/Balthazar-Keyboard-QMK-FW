# Balthazar

Open-hardware laptop computer modules description and concept.

These are electronic schematic modules as presented at https://balthazar.space/wiki/Balthazar with the main aim for team access. See the [main repository](https://github.com/balthazar-space/balthazar) for other designs.

# Balthazar--Keyboard-QMK-FW

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

You can find QMK firmware's original readme [here](./readme.qmk.md).

## Keyboard source

The current version of firmware source code is in [keyboards/handwired/balthazar3](./keyboards/handwired/balthazar3). The most feature-ful keymap variant (including both OLED and PS2 touchpad support) is [toucholed](./keyboards/handwired/balthazar3/keymaps/toucholed).

## Build instructions

This firmware is a keyboard variant of [QMK](https://qmk.fm/) version 0.25.9. It has been tested with an Atmel ATmega32U4 based Arduino ProMicro model. See [Balthazar keyboard 3](https://github.com/balthazar-space/balthazarKeyboard3) for hardware build instructions.

### QMK build environment

Full documentation can be found on [docs.qmk.fm](https://docs.qmk.fm/newbs_getting_started).
The following is a short recap for a (debian) linux based system setup:
- install `python3`, `python3-pip` and `python3-venv`: `sudo apt install python3 python3-pip python3-venv`
- setup a new python virtual environment: `python3 -m venv .venv`
- activate the virtual environment: `source .venv/bin/activate`
- install python dependencies: `pip3 install -r requirements.txt`
- install qmk helper: `pip3 install qmk`
- follow the qmk setup script: `qmk setup`

See [the official documentation](https://docs.qmk.fm/newbs_getting_started) if you run into problems.

#### build balthazar firmware

After activating the virtual environment (`source .venv/bin/activate`), you can build the firmware:

```bash
qmk compile -kb handwired/balthazar3 -km toucholed
```

Having the keyboard connected via USB, you can flash the firmware:
```bash
qmk flash -kb handwired/balthazar3 -km toucholed
```

To proceed with flashing, you may need to short the microcontroller's reset pin, depending on which model is used.

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

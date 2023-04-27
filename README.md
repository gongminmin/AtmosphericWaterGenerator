# Atmospheric Water Generator

[![License](https://img.shields.io/github/license/mashape/apistatus.svg)](LICENSE)

Atmospheric water generator (AWG) is a device for extracting fresh water from air. There are 0.0001% of water exists in the atmosphere. Even the desert air is not completely dry. Extract it for using is better than nothing. If the extraction is carried out near the ocean, where the air humidity is extremely high, the amount of fresh water obtained can be considerable. 

This is a simple open-source AWG design, suitable for home use. We'd like to make it easy to implement, so people can build it at home. The goals are:

* Low building cost. Off-shelve parts as much as possible.
* Easy to duplicate.
* Low operating cost and low power.
* Simple structure and easy maintenance.
* Small size and light weight.
* Safe and reliable.

## Principle

To extract water from air, we need a cold source. It condenses the water out for us to collect. The dry and cold air then be used to cool down the heat from the cold source device.

## Design

We use a [Peltier cooling plate](https://en.wikipedia.org/wiki/Thermoelectric_cooling) as the cold source. It's a solid semiconductor device, no moving part, easy to use. It as a cold side and a hot side. Two water cooling loops are circuiting between the surfaces of cooling plate to radiators. One loop carries the heat from a radiator to the cold side, makes the radiator cold. The other loop carries the heat from hot side to a radiator, exhaust the heat. The condensed water generated from the cold radiator drops down, collected by a bottle. The cooling plate is power consuming. We need a circuit to control it, keeping the temperature of the cold radiator in a certain range.

Most of the components are off-shelve ones. They are mounted to a frame by 3D printed adapters.

## Directories

* 3DModel folder is the 3D model design of some components. It's in STL format, ready for 3D printing.
* Circuit folder is the electric design of the system. The files can be open by [KiCad](https://kicad-pcb.org/)
* Code folder is the Arduino code for the control module.
* Doc folder contains some documents

## License

This project is distributed under the terms of MIT License. See [LICENSE](LICENSE) for details.

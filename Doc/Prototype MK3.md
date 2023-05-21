# Prototype MK3

We simplified the structure a lot in [prototype MK2](Prototype%20MK2.md). Now we need the circuit part.

Let's start with Arduino Mega 2560 and breadboard. First, we connect it with a LCD and a thermistor. With some code, we can measure the temperature.

![Thermometer](Img/MK3/Thermometer.jpg)

Then extern the pins of thermistor, add [the code to control](/Code/Control/Control.ino) the temperature into a range. The microcontroller's output is [connected to a MOSFET](/Circuit/AWG.kicad_sch) to turn on/off the cooling plate. Finally, two pumps, two fans, one Arduino are all connected to a 12V power source.

![Circuit](Img/MK3/Circuit.jpg)

In the MK2, the center of gravity is too high. To improve that, we need to reduce the size of the upper platform, so it can fit into the area between the air inlet and outlet. With a [sturdy 3D printed upper platform](/3DModel/UpperPlatform.stl), two water reservoirs and two water pumps can keep close.

![Upper Platform](Img/MK3/UpperPlatform.jpg)

The cooling plate and water blocks are installed into a container, which is then hanging at the bottom of the platform. Note that the room is still not enough for piping. We have to flip the water blocks, make the interface of them pointing to the back.

![Cooling Plate](Img/MK3/CoolingPlate.jpg)

The lower platform is also changed to [3D printed](/3DModel/LowerPlatform.stl) as well. We also used two pipe clamps to fix the pipe onto the platform. To overcome the gap between the clamp and the pipe, 2 layers of soft foam are wrapped around the pipe.

![Lower Platform](Img/MK3/LowerPlatform.jpg)

Now the updated MK3 looks like this.

![MK3](Img/MK3/PrototypeMK3.jpg)

## Conclusion

In MK3, with more 3D printed parts, almost all manual works are removed. It's more compact than MK2. The center of gravity is lowered for stability. There is a new problem. The circuit board is too preliminary. And there are still a lot of spots we can use to reduce the size of the device. We'll improve it in the next iteration.

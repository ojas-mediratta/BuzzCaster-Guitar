# BuzzCaster-Guitar
Documentation and project files for my CS 3651 (Prototyping Intelligent Devices) final project.

### Overview

The Buzzcaster is an electric guitar with a built-in, Teensy-based effects processing chain. It utilizes the tools and functions available in the Teensy audio library to modify an analog audio signal from an electric guitar pickup. The signal is then sent out via the output jack on the guitar to any speaker/PA system or guitar amp. This effectively eliminates the need for bulky and expensive guitar pedals that are often used by guitarists to change their electric guitar tone before sending it to an amplifier.

### Hardware

The pieces of hardware used in this project range from electronic parts and components, to 3D printed pieces, to the wood and metal for the electric guitar itself. The parts are listed as follows:

- Teensy 4.1
- Teensy Audio Shield Rev. D
- Unfinished Stratocaster Electric Guitar Kit (w/ all accompanying hardware)
- Clear acrylic Stratocaster scratch plate
- Humbucking electric guitar pickup
- 16x2 LCD display
- Rotary encoder knob
- Potentiometers (w/ resistances ranging from 20k – 100k)
- Arcade Momentary Push Button
- Soldered Protoboards
- Various DuPont and jumper wires

### Libraries and Code

My project did not involve the use of too many libraries beyond what was needed for the Teensy audio features to function. Other than those required libraries, I used the Liquidcrystal library to control the 16x2 lcd display.

\# include &lt;Liquidcrystal.h&gt;

\# include &lt;Audio.h&gt;

\# include &lt;Wire.h&gt;

\# include &lt;SPI.h&gt;

\# include &lt;SD.h&gt;

\# include &lt;SerialFlash.h&gt;

![SignalChain](https://github.com/user-attachments/assets/9b210053-f6b3-45e7-ad7f-4f43e9d7bd45)

_Audio signal path using the Teensy audio library_

### Custom Parts

I did a heavy amount of custom work on the guitar body to make it suitable for the project, including routing out large amounts of material to create enough space to house the electronics, as well as for routing wires for USB connectivity. I also designed and 3D printed a custom bracket to house the battery bank that I used to power my project. This was mounted to the back of the guitar body and fit the Anker Powercore 10,000 perfectly.

![bracket2](https://github.com/user-attachments/assets/6ca917ac-2bf2-47e7-9855-4d1e0ec19635)
![bracket1](https://github.com/user-attachments/assets/a73192cb-e79d-45ba-9e22-f51ecd4d0f21)

_Bracket for the battery bank_

### Skills and Iteration

Among the most important skills I learned to accomplish my goals with this project, was working with the equipment in the GVU prototyping lab. I spent a lot of time operating a hand mill, as well as the various saws and hand tools in the lab. I also used many of the skills I learned in the skill demos, especially 3D printing, Laser cutting, and the many wire connections that were practiced in the first skill demo.

After receiving each of my parts, I performed various initial parts tests to make sure that everything worked properly and that my parts were capable of behaving the way I wanted. After initial testing, I discovered a few issues that needed to be addressed; firstly, my project would not be sufficiently powered by just any battery bank. My Teensy, with its accompanying circuit, would not draw enough power from the battery bank such that it would remain powered on. Most battery banks have a circuit built in that powers them off when there is no longer any power draw (this way, they can conserve power when the device they’re charging, like a cell phone, is at full battery). The threshold for most battery banks was too high for the Teensy to keep them on, so I needed to purchase a special battery bank with a “trickle power” feature for low-power devices. Secondly, I found that the line-in input for my audio shield was too high impedance for my guitar pickup, so I needed to install an opamp breakout chip that behaved like a preamp for the guitar pickup before it went into the audio shield. Both of these solutions worked and enabled me to proceed with the project as planned.

### Challenges

Over the course of the project, many of the ideas and plans I was implementing worked great, except for a snag I hit the weekend before the demo; my Teensy died. It turns out that I was powering my rotary encoder with 5V of power, so every time I rotated it or pushed the switch, it was sending 5V to the I/O pins on my Teensy (this is very bad). The I/O pins on the Teensy are only 3.3V tolerant, so over time, this destroyed my chip before it finally met its demise two days before the final presentation. All hope was not lost, however, since there was a spare Teensy 4.0 in the classroom, but that had half the number of pins, and so I had to narrow the scope of what I hoped to achieve with my project. This solution didn’t end up working out, however, for a number of reasons. Firstly, the stacked combo of the Teensy 4.0 and the audio shield was too tall to fit inside the guitar cavity. I had ordered a second audio shield to solder to my original Teensy, which would have made the footprint the perfect height to fit inside the guitar, but it was too late for that, and I couldn’t solder the Teensy 4.0 to the new audio board. I attempted to use jumper wires to make all the connections, but this led to massive interference with the signal, and the project was effectively doomed. I do have a new Teensy 4.1 on order, which means I can finish the project after the demo presentation. I learned a lot about being careful with powered circuits and best practices for isolating issues when I was debugging after I killed my chip.

**UPDATE:**
I have since acquired a new Teensy 4.1 and have completed the project. Attached are images of the BuzzCaster in all its glory!!
<img src="https://github.com/user-attachments/assets/6fdb26fd-43b2-41ad-b42e-048c899a7712" width="300" height="350"/>
<img src="https://github.com/user-attachments/assets/73643905-2065-450d-9729-14479a710aca" width="300" height="350"/>
<img src="https://github.com/user-attachments/assets/e2e02827-631f-4b47-8e4c-e4ec9b27799c" width="300" height="350"/>

https://github.com/user-attachments/assets/42e8167a-9df4-4474-a0cd-3417d7db40c9



_The completed project_

### Resources

Teensy Audio Design Tool: [https://www.pjrc.com/teensy/gui/#](https://www.pjrc.com/teensy/gui/)

Rotary Encoders: <https://forum.arduino.cc/t/rotary-encoder-schematic-and-example-code/546111>

16x2 LCD Tutorial: <https://docs.arduino.cc/learn/electronics/lcd-displays/>

Teensy Freeverb Tutorial (This helped me understand how I could control different effects): <https://www.youtube.com/watch?v=4oFQf_HSwJQ&t=454s>

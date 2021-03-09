# Teensy 3.5 DDS Signal Generator
Using the integrated DAC of a Teensy 3.5 to generate arbitrary periodic waveforms<br>
This Signal Generator has been done as a project for my final High School Exam (Emanuele Coletta, ITIS Galileo Galilei Roma, a.s. 2020-2021) <br>

## How it works
The [Teensy 3.5](https://www.pjrc.com/store/teensy35.html) is a powerful Arduino-compatible microcontroller running an ARM Cortex-M4 at 120 MHz<br>
For the purpose of this project, it has been overclocked to 168MHz, running with the Fastest Pure Code+LTO optimizer<br>
It has two integrated DACs whose output can vary between 0v and 3.3V<br>
Using classical techniques from DDS (Direct Digital Synthesis) the Teensy can become a fully functional function generator<br>
In particular, the technique used here is the classic Phase Accumulator, together with a Lookup Table. This allows to precompute arbitrary periodic waveforms and then output them at the wanted frequency.<br>
Square waves of variable duty cycles can be generated by simply toggling a digital pin high and low and the correct time
Despite both sine and square wave being output by the teensy are quite clean and seem to have low noise and spurs levels at naked eye, advanced filtering techniques, like Chebyshev, Butterworth or Bessel filters with multiple stages are required.
The desired waveform, frequency and duty cycle can be selected using the I2C LCD Display and an incremental encoder with pushbutton

## Why two different microcontrollers
Each and every clock cycle of the Teensy 3.5 is meticulously used to generate waveforms and have them to be precise in frequency over time. Therefore, no clock cycle can be wasted reading external input or driving the LCD Display. For this purpose, an AtMega32U4 handles the I2C LCD Display, the incremental encoder and the analog inputs from the output stage.

## Amplification and offset
Amplification is done using an OpAmp inverting configuration. The non-inverting pin is wired to a voltage divider made with a potentiometer which varies between -12V and +12V to offset the wave.
Using a peak detector the peak-to-peak voltage of the wave can be measured. The peak-to-peak and offset voltage of the wave are then remapped in the range 0-5V using an inverting OpAmp with a ratio of 1/5 whose non-inverting input is fixed at 2.5V. Those two signals are then fed back to an analogic input of the AtMega 32U4 to be shown on the LCD Display


## Filters
Filters have been generated using [The Filter Wizard by Analog Devices](https://tools.analog.com/en/filterwizard/). <br>
A 6th order Bessel low-pass filter has been choosen to smooth out the transitory of the square wave, due to their fast switching times <br>
A 6th order Butterworth low-pass filter has been choosen to smooth out the wave generated by the DAC. <br>


## Credits
A lot of choices come from following this Degree dissertation paper (Direct Digital Synthesizers: Theory, Design and Applications by Jouko Vankka, Helsinki University of Technology, November 2000): http://lib.tkk.fi/Diss/2000/isbn9512253186/isbn9512253186.pdf<br>
<br>Analog Devices offers a lot of cool guides and papers about DDS, this is one of them: https://www.analog.com/media/en/training-seminars/design-handbooks/Technical-Tutorial-DDS/Section8.pdf<br>
<br>The website [ZipCPU](zipcpu.com) offers a variety of articles about sine wave generation using FPGAs<br>
- https://zipcpu.com/dsp/2017/08/26/quarterwave.html<br>
- https://zipcpu.com/dsp/2017/07/11/simplest-sinewave-generator.html

<br>Stackoverflow and the rest of the internet of course<br>
- https://stackoverflow.com/questions/13466623/how-to-look-up-sine-of-different-frequencies-from-a-fixed-sized-lookup-table<br>
- https://stackoverflow.com/questions/16889426/fm-synthesis-using-phase-accumulator<br>
- https://electronics.stackexchange.com/questions/438935/how-to-calculate-sampling-rate-for-dac-from-its-data-sheet<br>
- https://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml<br>

coherünce
=========

This is early-stage experimental software, developed in spare hacking time, that has the ability to drive dangerous laser performance equipment. 

IT SHOULD NOT BE USED BY ANYONE FOR ANY PURPOSE

#### Initial MVP plan:

- Support improvisational beat-synced laser performance
- Audio FFT and beat detection
- MIDI clock sync
- Controllable via external MIDI and OSC sequencers
- Support for a single laser
- Using the EtherDream DAC
- Mac OS X and Windows support

#### Build instructions (for project contributors)

1. Clone JUCE from [Github here](https://github.com/julianstorer/JUCE).
2. Check out the `4.1.0` tag:

    ```
    $ cd JUCE
    $ git checkout tags/4.1.0
    ```
    
3. Open the appropriate project for your platform from `JUCE/extras/Introjucer/Builds` and build the Introjucer.
4. Clone the coherünce repo into the same parent folder as the JUCE repo.
5. Build the appropriate project for your platform from `coherunce/app/Builds`.

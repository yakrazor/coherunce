coherünce
=========

This is early-stage experimental software, developed in spare hacking time, that has the ability to drive dangerous laser performance equipment. IT SHOULD NOT BE USED BY ANYONE FOR ANY PURPOSE.

> No Warranty. The Software is provided "as is" with all its faults, defects, and errors, and without warranty of any kind, either express or implied, including without limitation any implied warranties of condition, uninterrupted use, merchantability, fitness for a particular purpose, operational safety, compliance with regulations, or non-infringement.
> 
> The Authors of the Software do not promise that it will be free of bugs, errors, viruses, or other defects. The Authors will not be liable for anyone's use of, or inability to use, the Software, its content, or any associated service.
>
> No oral or written information or advice given by anyone involved in this project shall create a warranty, or in any way increase the scope of any warranty, and you may not rely on any such information or advice.

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

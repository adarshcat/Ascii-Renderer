# Ascii-Renderer

Does software based rasterization over the CPU and renders it onto the terminal using ASCII characters.

## Dependencies

No external dependencies.

## How to build

CMakeLists.txt is provided with the project. Create a build directory in the project folder and execute ``` cmake ../ ``` from within it. Make sure a valid generator is selected. After a makefile is generated, execute ``` make ```.

## How to use

Download the binary for your platform from the releases or build from source (steps specified in the section above).

Use ``` ./AsciiRenderer ``` to run the program at default resolution and framerate.

Use ``` ./AsciiRenderer 40 ``` to specify a resolution (characters per row/column).

Use ``` ./AsciiRenderer 40 15 ``` to specify a resolution (characters per row/column) and a frame rate.

## Tips

Try setting a small font-size (2) for the terminal and a high resolution (150) as the argument (it looks good). Setting the terminal font to something bold also seems to help. Get a CRT monitor if possible (lol).
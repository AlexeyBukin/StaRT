# Main manual

## Project structure
All source code lies in `src` directory and is splitted into several modules:
1) `srv` - server
    1) `cmd` - server parser/interpretator
1) `gpu` - rendering
    1) `mtl` - rendering on metal
    1) `vlk` - rendering on vulkan (to be implementeed)
1) `gui` - graphical user interface (gtk3)
1) `scn` - scene resource management
1) `err` - error shugar functions

## `main()` function
`main.c` contains `main()` that creates project struct `t_rt *rt` which contains all data and resources.

`main()` creates worker thread with server and initializes GUI.

When program quits normally `main()` also must `free()` `*rt` struct.


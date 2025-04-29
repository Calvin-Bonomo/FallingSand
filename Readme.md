Calvin Bonomo

# Build Instructions
```
# Run this and then the compiled binary is ./final
make
```

# Controls
```
ESC - Quits the program
SPACE - Cycle through elements
```

# Cells
1 - Air (Can delete other cells)
2 - Smoke
3 - Oil (Flammable)
4 - Water
5 - Sand
6 - Wood (Flammable)
7 - Wall
8 - Fire

# Details
I fought with C++ so much. I'm used to some C++98, so I thought that this would be a fairly easy ask to work move all my code from C to C++. I even thought that I could use a lot of features that I wasn't as used to working with. I was wrong. Templates were especially annoying, and, because I didn't fully understand the C++ linker, I had to rewrite a lot of my classes to accomodate them. I was pushed to be better about what I wanted to implement. This is really visible in the buffer and texture classes which I am more proud of implementing. Templates gave me an opportunity to take all the awful enums and void *'s that are required by OpenGL and abstract them away as simpler data types (see AddAttribute in VertexArrayObject). I wasn't entirely successful with abstracting away OpenGL as is visible with Textures and still needing to input OpenGL enums in the constructor.

To address the elephant in the room: I didn't end up using Python. Honestly, this is to do with time constraints. If I'm able on Thursday, it'll be there, but I just couldn't add fighting with another language to this project. The code is still included, so you can take a look if you'd like. Also, if I have time, I'll add an ImGUI selector, so you don't have to cycle through every single cell type manually.

In terms of time, I spent about 12 hours just making sure that textures weren't permanently black, so use that as a benchmark for the rest of it. Also my roommate Conall said the program is cool, so I'm happy with it.
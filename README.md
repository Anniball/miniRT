# MiniRT
A raytracer from scratch using the miniLibX. Now features texturing, bump mapping, normal mapping, directional lights and others!

### Important
Initially done for MacOS as part of my formation in C programming at the 42 school but currently working on a Linux compatible version.
The code is quite messy as I had to respect 42's restrictions about number of lines, number of functions, limitation of which functions I could call, ...
I intend to improve it once the code will be Linux-compatible.

# How to use it
Compile the source code using the `make` command in the MiniRT folder.
To execute the program just write `./miniRT` in your command prompt followed by the relative path to a ".rt" file.  
To quit the program just press the red cross on the corner or press the "esc" key.  
Example : `./miniRT scenes/scene_00_fov.rt`  
The images created by raytracing will be calculated more or less fast depending on your configuration file (number of objects, lights, quality of anti-aliasing, ...).  

### Save as a ".bmp" file
You can save a picture of the first camera view in ".bmp" format instead of looking at it on the program. To do that write `./miniRT path.rt --save` instead of `./miniRT path.rt --save`.  

# How to configure a ".rt" file
You can configure it by writing in the file as you would for a ".txt" file. Still there is some rules to respect if you want to correctly execute MiniRT.
All rules must be directly followed by newline and no empty lines must be present!  
There is many examples of configuration files in the "scenes" folder if you want to try them out. 

### Resolution
To define the resolution of the window write "R X Y" where you would replace "X" by the width and "Y" by the height. "X" and "Y" are both integers.  
Putting the resolution on first line is mandatory.  
Example : `R 600 325`

### Camera
To define a camera write "c x,y,z u,v,w f" where you would replace "x,y,z" by the position of the camera and "u,v,w" by the direction of the camera. "f" should be replaced by the field of vue of the camera. The field of vue should be an integer but all the others can be floats and the direction of the camera can't be "0,0,0".
Having at least one camera is mandatory but you can have many!  
If you put multiple cameras all the images will be calculated at the start of the program then you'll be able to change from one camera view to another using the "left" and "right" keys!  
Example : `c 0,0.2,0 0.12,0,-1 70` 

# Lights  

### Ambient/Global Light
To add an ambient light (also often called global light) write "A I r,g,b" where I is the intensity of the light and "r,g,b" is the color of the light. Intensity can be a float and "r,g,b" values must be between 0 included and 255 included.  
The ambient light is mandatory (even if you can put its intensity to 0). You can't have more than one ambient light since multiple ones would just add themselves to eachothers which is a suboptimal use of the program.  
Example : `A 0.2 255,127,50` 

### Point Light
To add a point light (a light defined only by its position) write "l x,y,z I r,g,b" where "x,y,z" is the position of the light, "I" is the intensity and "r,g,b," is the light's colour. All those values can be floats.  
The presence of directional light is optional and you can put as many as you want in your scenes!  
Example : `l -1.5,1,-2.5 0.08 85,85,255`  

### Directional Light
To add a directional light (a light defined only by its direction) write "d x,y,z I r,g,b"  where "x,y,z" is the direction of the light, "I" is the intensity and "r,g,b," is the light's colour. All those values can be floats.  
The presence of directional light is optional and you can put as many as you want in your scenes!  
Example : `l 0,0.5,-1 0.08 85,85,255`  

# Objects 
How to add different solids in this 3D space. All the objects are optionals and can be as many as you want (obviously a huge amount of objects will increase by a lot the picture's calculation time).  
By default on the line configuring the object you should add "r,g,b" values which represent the color of the object and are positive integers between 0 and 255 included.  
Except if told otherwise all the position, size and direction values described in this section can be floats.  

### Triangle  
To add a triangle on the scene write "tr x,y,z x,y,z x,y,z r,g,b" where each "x,y,z" represent the position of a point composing the triangle.  
Example : `tr 0.5,0.6,-2.8 1,0.9,-1 0,-0.5,-1.5 85,85,255`  

### Sphere  
To add a sphere on the scene write "sp x,y,z s r,g,b" where "x,y,z" represent the position of the sphere and s represents its size.  
Example : `sp 0,1,-3 1 240,255,153`  

### Plane  
To add a plane on the scene write "pl x,y,z u,v,w r,g,b" where "x,y,z" is the position of the plane and "u,v,w" is its direction.  
Example : `pl 1,0,-11 0,0.225,0 255,255,255`  

### Square  
To add a square on the scene write "pl x,y,z u,v,w s r,g,b" where "x,y,z" is the position of the square and "u,v,w" is its direction. "s" represents the size of this square.  
Example : `sq -3.5,0,-3 0.05,0.05,0.0 0.6 127,255,45`  

### Cylinder
To add a cylinder on the scene write "cy x,y,z u,v,w r,g,b d l" where "x,y,z" is the position of the cylinder and "u,v,w" is its direction. "l" represents its diameter and "l" is its length.  
Example : `cy -2.5,-0.5,-4 0.15,0.4,0 255,255,255 0.2 2`  

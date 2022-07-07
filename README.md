# MiniRT
A raytracer from scratch using the miniLibX. Now features texturing, bump mapping, normal mapping, directional lights, anti-aliasing, multithreading and others!

### Important
Initially done for MacOS as part of my formation in C programming at the 42 school but is currently Linux (at least Ubuntu) compatible version.
Note that for Linux a few packages must be installed before trying to create the executable : gcc, make, xorg, libxext-dev and libbsd-dev.

The code is quite messy as I had to respect 42's restrictions about number of lines, number of functions, limitation of which functions I could call, ...
I intend to improve it once the code will be fully Linux-compatible.

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
Below you can see what parameters of the camera can change on the picture.  

![cam1](https://user-images.githubusercontent.com/49061509/177520862-10ef9e6e-bf82-4276-b3af-1d6f4603a196.jpg)  ![cam2](https://user-images.githubusercontent.com/49061509/177520885-d030cf54-3f8f-4954-9f30-f85f955470e2.jpg)


# Lights  

### Ambient/Global Light
To add an ambient light (also often called global light) write "A I r,g,b" where I is the intensity of the light and "r,g,b" is the color of the light. Intensity can be a float and "r,g,b" values must be between 0 included and 255 included.  
The ambient light is mandatory (even if you can put its intensity to 0). You can't have more than one ambient light since multiple ones would just add themselves to eachothers which is a suboptimal use of the program.  
Example : `A 0.2 255,127,50`  
Below you can see a scene without and with a blue global light.  

![al1](https://user-images.githubusercontent.com/49061509/177522629-38ace457-410e-4d87-bc2f-9585a56f538d.jpg) ![al2](https://user-images.githubusercontent.com/49061509/177522654-aa1a0fd8-a7fc-4252-9a75-95f43377a14f.jpg)


### Point Light
To add a point light (a light defined only by its position) write "l x,y,z I r,g,b" where "x,y,z" is the position of the light, "I" is the intensity and "r,g,b," is the light's colour. All those values can be floats.  
The presence of directional light is optional and you can put as many as you want in your scenes!  
Example : `l -1.5,1,-2.5 0.08 85,85,255`  
Below you can see a scene without and with point lights.  

![point1](https://user-images.githubusercontent.com/49061509/177524433-d80c1d02-3015-43bb-92c9-03d5299b2682.jpg)  ![point2](https://user-images.githubusercontent.com/49061509/177524448-fa14bb31-a856-4f4b-931d-0dd91928bbd6.jpg)


### Directional Light
To add a directional light (a light defined only by its direction) write "d x,y,z I r,g,b"  where "x,y,z" is the direction of the light, "I" is the intensity and "r,g,b," is the light's colour. All those values can be floats.  
The presence of directional light is optional and you can put as many as you want in your scenes!  
Example : `l 0,0.5,-1 0.08 85,85,255`  
Below you can see a scene without and with a yellow directional light.  

![dir1](https://user-images.githubusercontent.com/49061509/177539053-59a8542d-4654-4de1-8f69-203b48a3cae8.jpg)  ![dir2](https://user-images.githubusercontent.com/49061509/177539127-a0e77127-ef07-4b82-a535-8f730a2523a8.jpg)


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

# Textures  
This section is about the configurations that will need a path to a texture file in the ".xpm" format. The maximum size taken is 4096 pixels on 4096 pixels.  

### Texture, normal map and bump map
Note that because of some 42 school limitations you can call normal maps and/or bump maps only if you called for a texture instead of a color. If you don't want one and not the others you can still replace the path by a "0".  
To be precise instead of "r,g,b" you will always have to write "t texturePath normalPath bumpPath" but if you want only texture you can write "t texturePath 0 0" or if you want only bump and normal maps but no texture you can write "t 0 normalPath bumpPath".  
Example : Instead of `pl 1,0,-11 0,0.225,0 255,255,255`  
you could write `pl 1,0,-11 0,0.225,0 t textures/bricks.xpm textures/bricks_normal.xpm textures/bricks_height.xpm`  

To illustrate the point of this section here is some picture from up to below : without any texture, with only color texture, with only normal map, with only bump map and with texture combined with normal map.  

![save](https://user-images.githubusercontent.com/49061509/177544237-c12ca734-dc3b-42cf-92de-48657fc4a25f.jpg)
![texture](https://user-images.githubusercontent.com/49061509/177544263-76a56b89-081f-48e4-836e-8155e0b08bca.jpg)
![normal](https://user-images.githubusercontent.com/49061509/177544278-fa2e8eb5-b22c-4468-9bdd-d2761e3bc043.jpg)
![bump](https://user-images.githubusercontent.com/49061509/177544294-7362ec28-7461-4452-9297-fc65ff52a4f8.jpg)
![normaltext](https://user-images.githubusercontent.com/49061509/177544324-99e25041-afea-456b-946f-d09ef0464608.jpg)

### Background  
You can add a background by writing "sky path" where "path" is the relative path to a texture in the correct format.  
Example : `sky textures/space.xpm`  

# Important Features  
I consider those features very important for aesthetic or performance reasons. Those features can be written on any line (except the first) and can be present only once in each file.

### Multithreading  
Will increase the speed of calculation on most of computers. I suggest you to compare once if the calculation is better with or without it and keep this configuration next. To use multithreading just write `mul` on any line (except the first) of the configuration file.  
Example : `mul`  

### Anti-Aliasing  
Will "smooth" the rendering by having a better approximation of the color of each pixel. To use anti-aliasing write "aa n" where n is an integer representing the quality of the anti-aliasing that you want. Be careful as the amount of calculation for each pixel will increase exponentially with the value of n : if n = 3 then the calculation will be 3*3=9 times bigger than without it. In this logic a n value of 0 or 1 will lead to no change.  
Example : `aa 5`  
Below you can see a scene without and with the anti-aliasing.  

![aa1](https://user-images.githubusercontent.com/49061509/177540482-966c56db-76b6-45ff-81cd-477fd868ba0b.jpg) ![aa2](https://user-images.githubusercontent.com/49061509/177540498-19593caa-09c9-4c72-9b5e-3fc3d3c3a6e3.jpg)


# More Features 

### Sepia Filter  
A basic sepia filter (a little bit more complicated than a simple monochromatic filter). Just write `sep` only once on one of the lines except the first.  
![sepia](https://user-images.githubusercontent.com/49061509/177512538-05ef6b31-5d0f-48c5-9828-f6b60e595c62.jpg)

### Checker  
A checker texture done by calculation. Useful to see how a real texture would behave on each solid. To use it on a solid write "c" instead of the classic "r,g,b".  
Example : `sp 1,0,-3 1 c` will show a sphere with a checker texture instead of `sp 1,0,-3 1 255,0,0` that would show a red sphere.  
![checker](https://user-images.githubusercontent.com/49061509/177512313-95469159-cd18-4fd4-8895-2f27b3bd294a.jpg)

### Normal Rainbow  
A texture where each color represent a direction of the normal vector at the surface of a solid (red for x, green for y and blue for z). Useful to see the true form of an object. To use it write "n" instead of the classic "r,g,b".  
Example : `sp 1,0,-3 1 n` will show a sphere with a normal texturing instead of `sp 1,0,-3 1 255,0,0` that would show a red sphere.  
![normal](https://user-images.githubusercontent.com/49061509/177512377-56cf175e-3f57-443c-8a78-83cc0790117f.jpg)

### Sinusoidal Normal
Change the normal of the object and give the impression of a "wave" at its surface. Not very useful or pretty. To use it write "d" instead of the classic "r,g,b".  
Example : `sp 1,0,-3 1 s` will show a sphere with a sinusoidal normal mapping instead of `sp 1,0,-3 1 255,0,0` that would show a red sphere.  
![sin](https://user-images.githubusercontent.com/49061509/177512446-7b1b1850-6412-41f4-b37e-b1b1667e4584.jpg)

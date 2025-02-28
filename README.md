This is one of my longest projects I've ever worked on (2 months) and I think that this is it for now. Started out in Java, then to C++, then ported to CUDA. I barely even knew any C++ before this let alone CUDA! I was so disappointed in the Java performance which forced me to learn C++ to be able to scale more, then CUDA as the final boss (thanks Omise31 for the idea). CUDA was definitely overkill, but it exposed me to the world of gpu programming! I might even do a 3D version of this in the future (90-100%).

I rarely use github (3rd or 4th time) so I have no idea what I'm doing right now. 

Scales up to 3-4M Particles at 6 substeps on my RTX 4070 before going under 60 fps so I think any NVIDIA gpu can handle this. Very memory bandwidth intensive!!!

Video:

https://www.youtube.com/watch?v=C_qEfIPdrrE&ab_channel=murk

**CONTROLS:**

E - Generate Softbody

R - Reset World

SPACE - Pause

G - Slow mo

LEFT CLICK - Particle mover

RIGHT CLICK - Move camera

**REQUIREMENTS TO COMPILE:**

GLEW

GLFW

Cuda Toolkit

**REQUIREMENTS TO RUN:**

NVIDIA GPU (Sucks to be an AMD user!!!!)


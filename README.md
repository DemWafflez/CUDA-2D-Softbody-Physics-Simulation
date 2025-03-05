🚨 THIS REPO IS GOING TO BE ARCHIVED 🚨

This project is pretty much final despite a lot of imperfections. I don't want to be held back by this project which is why I'm deciding to achive 👍.

------------------------


This is one of the longest projects I've ever worked on (2 months) and I think that this is it for now. I started out in Java, then to C++, then ported to CUDA. I barely even knew any C++ before this let alone CUDA. Java's performance sucked ass for this (no suprise) which led me to learn C++ to be able to scale more, then unexpectedly, CUDA (thanks Omise31 for the idea). CUDA was definitely overkill (nah), but it led me down the rabbit hole of gpu programming. Cant't look back anymore after realizing how much fucking faster and more efficient the gpu can do certain tasks. 

Scales up to 3-4M Particles at 6 substeps on my RTX 4070 before going under 60 fps. I wonder how much the RTX 5090 can do (2-3x?). Very memory bandwidth intensive!!!!

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


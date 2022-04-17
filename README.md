# Izhikevich neuron in c++

This is some c++ code to simulate Izhikevich spiking neurons, from the paper:

[https://www.izhikevich.org/publications/spikes.htm](paper)

## How to run it

For easier building there is a docker image

#### Build the docker:

```docker build -t izhi .```

#### Start the docker interactively with this (project) folder shared under `/izhi` for easy development:

```docker run --name izhi -v `pwd`:/izhi -it izhi /bin/bash```

(I dont know how `pwd` works on windows, but it's the absolute path to this folder on your computer)

#### Build the source code (in the interactive docker):
```
cd /izhi
mkdir build
cd build
cmake ..
make
./izhikevich
```

# TODO

Currently there is only the terminal output, because some how drawing images with OpenCV doesn't work in docker or something. Still have to look into that, will get back at that later!

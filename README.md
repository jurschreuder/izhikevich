# Izhikevich neuron in c++

This is some c++ code to simulate Izhikevich spiking neurons, from the paper:

[paper](https://www.izhikevich.org/publications/spikes.htm)

![Izhikevich neuron](output/out.jpg?raw=true "Izhikevich Neuron")

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

Output image will be in `output/out.jpg`


#### Some presets

```
Regular spiking:
./izhikevich 0.02 0.2 -65 8

Intrinsically bursting:
./izhikevich 0.02 0.2 -55 4

Chattering:
./izhikevich 0.02 0.2 -50 2

Fast spiking:
./izhikevich 0.1 0.2 -65 2

Thalamo-cortical:
./izhikevich 0.02 0.25 -65 0.05

Resonator:
./izhikevich 0.1 0.26 -65 2

Low-threshold spiking:
./izhikevich 0.02 0.25 -65 2 
```


## TODO

The fixed DC input drive does not have the correct value for all neuron simulations, for now the easiest way is to change it manually in the "step" loop in the code.

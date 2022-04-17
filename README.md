# Izhikevich neuron in c++

This is some c++ code to simulate Izhikevich spiking neurons, from the paper:

[https://www.izhikevich.org/publications/spikes.htm](paper)

## How to run it

Build the docker:
```docker build -t izhi .```

Start the docker interactively with this (project) folder shared under `/izhi` for easy development:
```docker run --name izi -v `pwd`:/izhi -it izhi /bin/bash```

Build the source code (in the interactive docker):
```
cd /izhi
mkdir build
cd build
cmake ..
make
./izhikevich
```



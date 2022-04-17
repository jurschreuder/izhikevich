FROM ubuntu:20.04

RUN apt-get update
ENV DEBIAN_FRONTEND=noninteractive 

RUN apt-get -y install build-essential libssl-dev cmake libopencv-dev



#!/bin/bash
docker run -v "/home/matiapa/x64barebones/":/home/matiapa/x64barebones --security-opt seccomp:unconfined -ti agodio/itba-so:1.0 /home/matiapa/x64barebones/compile.sh
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 #-s -S
make clean -s
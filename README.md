# Image Stack to Geometry Project

## Details

* Author: Paul Armstrong
* Date: August 2018
* Progress: 5%

## Description

With this project I plan to create a command line tool for transforming image stacks (in formats like .tif and .fits) into three-dimensional geometries (in formats like .obj, .dae, .gltf).

I started this project with Java, but I have decided to shift gears and use C++. This will allow me to delve into lower-level operations with C if I choose to.

I have started by creating a C++ script to parse .fits files. Currently the script will read a .fits file to retrieve the image stack's data, in the form of a three-dimensional matrix of bytes. Each byte corresponds to each pixel's darkness.

## Motivations

This project is inspired by (but separate from) the work I did at NIST. We visualized microscope images in the form of FITS image stacks. We used ImageJ to create a geometry from the image stacks.

I am now using what I learned about computer graphics to create my own algorithm for forming geometries.


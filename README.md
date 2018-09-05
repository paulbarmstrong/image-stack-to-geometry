# Image Stack to Geometry Project

## Details

* Author: Paul Armstrong
* Date: August 2018
* Progress: 13%

## Description

With this project I am creating a command line tool for transforming image stacks (in formats like .tif and .fits) into three-dimensional geometries (in formats like .obj, .dae, .gltf).

I have decided to use C++11 for this project. This will allow me to utilize object oriented techniques, but also delve into lower-level operations with C if I choose to.

Currently the images2geo command can read a .fits file to retrieve the image stack data in the form of a three-dimensional matrix of bytes. It will create a geometry and fill it based on the image stack data. Finally, it will save the geometry as a .obj file.

If you have make and g++, `make` in a linux shell will build the project. After that, the executable will be images2geo.

Doing `.\images2geo input.fits output.obj` will create a file output.obj which defines a geometry based on the input.fits image stack.

## Plans

* Explore ways to improve the speed and quality of the creation of the geometry.
* Add support for other file formats like (.tif) for input and (.dae, .gltf) for output.

## Motivations

This project is inspired by the [Wavefront .Obj plugin for ImageJ](https://imagej.net/Wavefront_.OBJ_...) which I used at NIST to create geometries from image stacks.

I am now using what I learned about computer graphics to create my own algorithm for forming geometries.


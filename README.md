# Image Stack to Geometry Project

## Details

* Author: Paul Armstrong
* Date: December 2018
* Progress: 35%

## Demonstration

![animated gif](https://i.imgur.com/SYUN5Gs.gif)

## Description

With this project I have created a command line tool for transforming image stacks (in the form of .tif and .fits image stacks) into three-dimensional geometries.

I have decided to use C++11 for this project. This allows me to utilize object oriented techniques, but also delve into lower-level operations with C when I choose to.

The tool parses input files byte by byte, and records the pixels of the images. It creates a geometry and fills it based on the image stack data. Finally, it writes the geometry information to a new 3D geometry file.

### Supported input formats
* .fits image stack
* .tif image stack (bilevel)

### Supported output formats
* .obj (Wavefront)

## Usage

If you have make and g++, doing `make` in a shell will build the project. After that, the executable will be images2geo. It takes two arguments:
* The name of the input file.
* The name of the output file to be created.

For example, doing `.\images2geo example.tif output.obj` creates a file output.obj which defines a geometry based on the example.tif image stack.

## Plans

* Explore ways to improve the speed and quality of the creation of the geometry.
* Expand support to other more sophisticated .tif versions.
* Add support for other output file formats (.dae and .gltf).



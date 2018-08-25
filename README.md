# Image Stack to Geometry Project

## Details

* Author: Paul Armstrong
* Date: August 2018
* Progress: 10%

## Description

With this project I am creating a command line tool for transforming image stacks (in formats like .tif and .fits) into three-dimensional geometries (in formats like .obj, .dae, .gltf).

I started this project with Java, but I have decided to shift gears and use C++. This will allow me to delve into lower-level operations with C if I choose to.

Currently the images2geometry script will read a .fits file to retrieve the image stack data in the form of a three-dimensional matrix of bytes. It will create a geometry and fill it based on the image stack data. Finally, it will save the geometry as a .obj file.

## Plans

* Improve the #include situation by using header files and ifndef statements.
* Create class ImageStack and have the image stack file name as a constructor argument to further abstract away the file parsing.
* Explore ways to improve the speed and quality of the creation of the geometry.
* Add support for other file formats like (.tif) for input and (.dae, .gltf) for output.

## Motivations

This project is inspired by (but separate from) the work I did at NIST. We visualized microscope images in the form of FITS image stacks. We used ImageJ to create a geometry from the image stacks.

I am now using what I learned about computer graphics to create my own algorithm for forming geometries.


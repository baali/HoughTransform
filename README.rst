Overview
--------

Simple addon of UI to OpenCV's `Hough Circle Transform <http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html>`_
to detect circles(spores) in an image.

Usage
-----

- There is a param.yml file to change the default values of various
  parameters used to calculate Hough Circular Transform.

- Compile all the files using make ::

  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
  
- To run the program pass image file as one of parameter ::

  $ build/particle_detection image-name

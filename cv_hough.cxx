#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;

/// Global Variables
Mat src, src_gray;
int maxRadius, maxRadiusUL, minRadius, minRadiusUL;
int edgeThreshold, edgeThresholdUL, centerThreshold, centerThresholdUL;
int centerDistance;
vector<Vec3f> circles;
char* window_name = "Hough Circle Transform";

/** @funtion to load config file */
int load_config()
{
  FileStorage fs("param.yml", FileStorage::READ);
  if( !fs.isOpened() )
  {       
      std::cout << "Parameter file missing.\n";
      return -1; 
  }
  maxRadius = (int)fs["maxRadius"];
  maxRadiusUL = (int)fs["maxRadiusUL"];
  minRadius = (int)fs["minRadius"];
  minRadiusUL = (int)fs["minRadiusUL"];
  edgeThreshold = (int)fs["edgeThreshold"];
  edgeThresholdUL = (int)fs["edgeThresholdUL"];
  centerThreshold = (int)fs["centerThreshold"];
  centerThresholdUL = (int)fs["centerThresholdUL"];
  centerDistance = (int)fs["centerDistance"];  
  fs.release();
  return 0;
}

/** @funtion for changing any trackbar */
void on_all_trackbars( int, void* )
{
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Apply the Hough Transform to find the circles
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, 
                centerDistance, 
                edgeThreshold, 
                centerThreshold, 
                minRadius, 
                maxRadius);
  
  std::cout << "Detected " << circles.size() << " Cirles\n";

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      circle( src_gray, center, radius, Scalar(0, 0, 0), 1.8, 8, 0 );
   }
  imwrite( "Spores.jpg", src_gray );
  imshow( window_name, src_gray );
}

/** @function main */
int main(int argc, char** argv)
{
  /// Read the image
  src = imread( argv[1], 1 );

  if( !src.data )
  {       
      std::cout << "Not able to open Image file.\n";
      return -1; 
  }

  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  if(load_config() == -1)
  {
      return -1; 
  }
  /// Create Trackbars
  createTrackbar( "Radius(lower limit)", window_name, 
                  &minRadius, 
                  minRadiusUL, 
                  on_all_trackbars );
  createTrackbar( "Radius(higher limit)", window_name, 
                  &maxRadius, 
                  maxRadiusUL, 
                  on_all_trackbars );
  createTrackbar( "Intensity(at center)", window_name, 
                  &centerThreshold, 
                  centerThresholdUL, 
                  on_all_trackbars );
  createTrackbar( "Intensity(at edge)", window_name, 
                  &edgeThreshold, 
                  edgeThresholdUL, 
                  on_all_trackbars );
  /// Show some stuff
  on_all_trackbars( minRadius, 0 );

  waitKey(0);
  return 0;
}

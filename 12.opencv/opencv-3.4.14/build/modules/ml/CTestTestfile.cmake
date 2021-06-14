# CMake generated Testfile for 
# Source directory: /home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/modules/ml
# Build directory: /home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/modules/ml
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_ml "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/bin/opencv_test_ml" "--gtest_output=xml:opencv_test_ml.xml")
set_tests_properties(opencv_test_ml PROPERTIES  LABELS "Main;opencv_ml;Accuracy" WORKING_DIRECTORY "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/test-reports/accuracy")

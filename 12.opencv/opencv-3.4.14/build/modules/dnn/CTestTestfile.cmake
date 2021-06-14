# CMake generated Testfile for 
# Source directory: /home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/modules/dnn
# Build directory: /home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/modules/dnn
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_dnn "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/bin/opencv_test_dnn" "--gtest_output=xml:opencv_test_dnn.xml")
set_tests_properties(opencv_test_dnn PROPERTIES  LABELS "Main;opencv_dnn;Accuracy" WORKING_DIRECTORY "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/test-reports/accuracy")
add_test(opencv_perf_dnn "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/bin/opencv_perf_dnn" "--gtest_output=xml:opencv_perf_dnn.xml")
set_tests_properties(opencv_perf_dnn PROPERTIES  LABELS "Main;opencv_dnn;Performance" WORKING_DIRECTORY "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/test-reports/performance")
add_test(opencv_sanity_dnn "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/bin/opencv_perf_dnn" "--gtest_output=xml:opencv_perf_dnn.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_dnn PROPERTIES  LABELS "Main;opencv_dnn;Sanity" WORKING_DIRECTORY "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/test-reports/sanity")

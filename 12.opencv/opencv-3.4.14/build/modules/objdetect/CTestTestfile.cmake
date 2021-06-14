# CMake generated Testfile for 
# Source directory: /home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/modules/objdetect
# Build directory: /home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/modules/objdetect
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_objdetect "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/bin/opencv_test_objdetect" "--gtest_output=xml:opencv_test_objdetect.xml")
set_tests_properties(opencv_test_objdetect PROPERTIES  LABELS "Main;opencv_objdetect;Accuracy" WORKING_DIRECTORY "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/test-reports/accuracy")
add_test(opencv_perf_objdetect "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/bin/opencv_perf_objdetect" "--gtest_output=xml:opencv_perf_objdetect.xml")
set_tests_properties(opencv_perf_objdetect PROPERTIES  LABELS "Main;opencv_objdetect;Performance" WORKING_DIRECTORY "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/test-reports/performance")
add_test(opencv_sanity_objdetect "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/bin/opencv_perf_objdetect" "--gtest_output=xml:opencv_perf_objdetect.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_objdetect PROPERTIES  LABELS "Main;opencv_objdetect;Sanity" WORKING_DIRECTORY "/home/zion/Desktop/CPP-study/12.opencv/opencv-3.4.14/build/test-reports/sanity")

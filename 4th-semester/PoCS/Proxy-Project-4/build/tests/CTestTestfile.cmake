# CMake generated Testfile for 
# Source directory: /home/baabbabai/GitHub/Project_Mireacle/4th-semester/PoCS/Proxy-Project-3/tests
# Build directory: /home/baabbabai/GitHub/Project_Mireacle/4th-semester/PoCS/Proxy-Project-3/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ProxyUnitTests "/home/baabbabai/GitHub/Project_Mireacle/4th-semester/PoCS/Proxy-Project-3/build/tests/unit_tests")
set_tests_properties(ProxyUnitTests PROPERTIES  _BACKTRACE_TRIPLES "/home/baabbabai/GitHub/Project_Mireacle/4th-semester/PoCS/Proxy-Project-3/tests/CMakeLists.txt;29;add_test;/home/baabbabai/GitHub/Project_Mireacle/4th-semester/PoCS/Proxy-Project-3/tests/CMakeLists.txt;0;")
add_test(ProxyScenarioTests "/home/baabbabai/GitHub/Project_Mireacle/4th-semester/PoCS/Proxy-Project-3/build/tests/scenario_tests")
set_tests_properties(ProxyScenarioTests PROPERTIES  _BACKTRACE_TRIPLES "/home/baabbabai/GitHub/Project_Mireacle/4th-semester/PoCS/Proxy-Project-3/tests/CMakeLists.txt;30;add_test;/home/baabbabai/GitHub/Project_Mireacle/4th-semester/PoCS/Proxy-Project-3/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")

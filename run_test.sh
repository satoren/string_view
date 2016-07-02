set -e
build_test_cxx_flags=("-std=c++03" "-std=c++11" "-std=c++14")

build_and_exec_test(){
  if [ ! -e "build$1" ]; then
    mkdir "build$1"
  fi
  cd "build$1"
  cmake ../ -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_CXX_FLAGS=$1 -DCOVERAGE=On
  make -j4
  CTEST_OUTPUT_ON_FAILURE=1 make test
  cd ../
}

for cxxflag in "${build_test_cxx_flags[@]}"
do
  build_and_exec_test $cxxflag
done

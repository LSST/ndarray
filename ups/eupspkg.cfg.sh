build()
{
	(mkdir build && cd build && cmake -DNDARRAY_PYBIND11=ON -DFFTW_ROOT=$FFTW_DIR -DBOOST_ROOT=$BOOST_DIR -DEIGEN3_INCLUDE_DIR=$EIGEN_DIR/include -DCMAKE_INSTALL_PREFIX=$PREFIX .. && make && make test)
}

install()
{
	clean_old_install
	(cd build && make install)
	install_ups
}


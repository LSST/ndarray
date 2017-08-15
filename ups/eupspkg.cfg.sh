build()
{
	(mkdir build && cd build && cmake -DNDARRAY_SWIG=OFF -DNDARRAY_PYBIND11=ON -DFFTW_ROOT=$FFTW_DIR -DBOOST_ROOT=$BOOST_DIR -DCMAKE_INSTALL_PREFIX=$PREFIX .. && make && make test)
}

install()
{
	clean_old_install
	(cd build && make install)
	install_ups
}


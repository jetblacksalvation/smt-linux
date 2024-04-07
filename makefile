make:
	./quickbuild.sh


run:
	(cd bin; ./CMakeSFMLProject)
clean:
	(rm -r build)
	(rm -f ./bin/CMakeSFMLProject)
CFLAGS = -g

ReadImage.o:	image.h ReadImage.cpp
	g++ -c $(CFLAGS) ReadImage.cpp

ReadImageHeader.o:	image.h ReadImageHeader.cpp
	g++ -c $(CFLAGS) ReadImageHeader.cpp

WriteImage.o:	image.h WriteImage.cpp
	g++ -c $(CFLAGS) WriteImage.cpp

image.o:	image.h image.cpp
	g++ -c $(CFLAGS) image.cpp

averaging:	image.h image.o ReadImage.o ReadImageHeader.o WriteImage.o \
		averaging.cpp
	g++ -o averaging $(CFLAGS) image.o ReadImage.o ReadImageHeader.o \
					WriteImage.o averaging.cpp

gaussian:	image.h image.o ReadImage.o ReadImageHeader.o WriteImage.o \
		gaussian.cpp
	g++ -o gaussian $(CFLAGS) image.o ReadImage.o ReadImageHeader.o \
					WriteImage.o gaussian.cpp

Correlation:	image.h image.o ReadImage.o ReadImageHeader.o WriteImage.o \
		Correlation.cpp
	g++ -o Correlation $(CFLAGS) image.o ReadImage.o ReadImageHeader.o \
					WriteImage.o Correlation.cpp

median:	image.h image.o ReadImage.o ReadImageHeader.o WriteImage.o \
		median.cpp
	g++ -o median $(CFLAGS) image.o ReadImage.o ReadImageHeader.o \
					WriteImage.o median.cpp

unsharpMasking:	image.h image.o ReadImage.o ReadImageHeader.o WriteImage.o \
		unsharpMasking.cpp
	g++ -o unsharpMasking $(CFLAGS) image.o ReadImage.o ReadImageHeader.o \
					WriteImage.o unsharpMasking.cpp

highBoost:	image.h image.o ReadImage.o ReadImageHeader.o WriteImage.o \
		highBoost.cpp
	g++ -o highBoost $(CFLAGS) image.o ReadImage.o ReadImageHeader.o \
					WriteImage.o highBoost.cpp

gradient:	image.h image.o ReadImage.o ReadImageHeader.o WriteImage.o \
		gradient.cpp
	g++ -o gradient $(CFLAGS) image.o ReadImage.o ReadImageHeader.o \
					WriteImage.o gradient.cpp

laplacian:	image.h image.o ReadImage.o ReadImageHeader.o WriteImage.o \
		laplacian.cpp
	g++ -o laplacian $(CFLAGS) image.o ReadImage.o ReadImageHeader.o \
					WriteImage.o laplacian.cpp
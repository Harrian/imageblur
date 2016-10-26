Members:
	Tyler Rau

Brief Summary:
	Image Blur

Names of files:
	sequential:	/home/f16/p615/imageblur/paraproject.cpp
	parallel:	/home/f16/p615/imageblur/multiout.cpp

Build:
	sequential: 	g++ filename
	parallel:	g++ filename -std=c++11 -fopenmp
	(It was really painful to avoid c++17 and c++14 for this :P)

Run:
	sequential:
		% ./a.out INPUT.bmp NUMOFBLURS
	parallel:
		% ./a.out INPUT.bmp NUMOFBLURS OUTPUTEVERYX

Notes:
	You will notice a minor slow down on small images with low number
	blurs when using parallel

	HOWEVER YOU'LL GET THAT SWEET MEGA SPEED UP WITH LARGE IMAGE

	sequential only outputs one file at the end of all blurs
	Example:
		% ./a.out dock.bmp 40
		output file name: dock40.bmp

	parallel will only print the last blur if NUMBEROFBLURS is
	a multiple of OUTPUTEVERYX
	Example:
		% ./a.out dock.bmp 40 10
		Output files:
				dock10.bmp
				dock20.bmp
				dock30.bmp
				dock40.bmp

To get visual results you'll need to copy these to a machine that
can give visualizations of *.bmp files.

I would recommend creating a directory with the program and the original
and then copying all those images using scp or ftp.

	For example:
		% mkdir dockblurs
		% cp dock.bmp ./dockblurs/.
		% cp a.out ./dockblurs/.
		% cd dockblurs
		% ./a.out dock.bmp 40 10

		Switch to destination machine
		scp USERNAME@cs.dsunix.net:PATHTODOCKBLUR/*.bmp .

Included Example files:
	dock.bmp 	800x600
	road.bmp 	3386x2123
	tunnel.bmp	3840x2160
	towers.bmp	7776x5184

	para version can do in 2 minutes what it takes to do in 48 minutes
	with the seq version. (on a 24 thread machine) 

	Be careful with disk space.

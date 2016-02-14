
TARGETS=yc_test.exe
TARGETS+=ad_test.exe

#make rule
all : $(TARGETS)

yc_test.exe : Makefile_yc
	make -f $<

ad_test.exe : Makefile_ad
	make -f $<

clean: Makefile_ad Makefile_yc
	make -f Makefile_ad clean
	make -f Makefile_yc clean


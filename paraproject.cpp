#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
class pixal{
	private:
		unsigned char red;
		unsigned char blue;
		unsigned char green;
	public:
		pixal(unsigned char a, unsigned char b, unsigned char c);
		unsigned char getRed(void){return red;}
		unsigned char getBlue(void){return blue;}
		unsigned char getGreen(void){return green;}
};
pixal::pixal(unsigned char a, unsigned char b, unsigned char c){
	red=a;
	blue=b;
	green=c;
}
int main(int argv, char ** argc){
	//read image
	FILE * bitmapfile = fopen(argc[1],"r");
	unsigned char * infotable = new unsigned char[54];
	fread(infotable,sizeof(unsigned char),54,bitmapfile);
	int imagewidth = *(int*)(infotable+18);
	int imageheight = *(int*)(infotable+22);
	std::vector< std::vector<pixal *> * > bigoldarrayofpixals(imageheight,NULL);
	for(int i=imageheight-1;i>=0;i--){
		bigoldarrayofpixals[i]=new std::vector<pixal *>;
		for(int j=0;j<imagewidth;j++){
			unsigned char * readpixal = new unsigned char[3];
			fread(readpixal,sizeof(unsigned char),3,bitmapfile);
//			std::cout<<(int)*(readpixal+2)<<" "<<(int)*(readpixal+1)<<" "<<(int)*(readpixal)<<std::endl;
			bigoldarrayofpixals[i]->push_back(new pixal(*(readpixal+2),*(readpixal+1),*(readpixal)));
			delete readpixal;
		}
	}
	fclose(bitmapfile);
	FILE * attempttocopy = fopen("attempttocopy.bmp","w");
	fwrite(infotable,sizeof(unsigned char),54,attempttocopy);
	unsigned char * img = new unsigned char[3*imageheight*imagewidth];
	memset(img,0,sizeof(img));
	for(int i=0;i<imageheight;i++){
		std::vector<pixal *> * magic(bigoldarrayofpixals[imageheight-i-1]);
		for(int j=0;j<imagewidth;j++){
//			std::cout<<(i*imagewidth+j)*3<<" ";
			img[(i*imagewidth+j)*3]=magic->at(j)->getGreen();
//			img[(i*imagewidth+j)*3+1]=magic->at(j)->getBlue();
//			img[(i*imagewidth+j)*3+2]=magic->at(j)->getRed();
		}
//		std::cout<<std::endl;
	}
	fwrite(img,sizeof(unsigned char),3*imageheight*imagewidth,attempttocopy);
	fclose(attempttocopy);
		
	//std::cout<<bigoldarrayofpixals[0][0]->getRed()<<" "<<bigoldarrayofpixals[0][0]->getBlue()<<" "<<bigoldarrayofpixals[0][0]->getGreen()<<std::endl;
	return 0;
}
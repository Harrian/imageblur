#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
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
int realMod( int a, int b ){
	int r=a%b;
	return r<0?r+b:r;
}
void blurPixals(std::vector< std::vector<pixal *> * > * &aop,int h,int w){
	std::vector< std::vector<pixal *> * > * newaop = new std::vector< std::vector<pixal *> * > (h,NULL);
	//process blur
	for(int i=0;i<h;i++){
		newaop->at(i)=new std::vector<pixal *>;
		for(int j=0;j<w;j++){
				unsigned int sumOfReds=0;
				unsigned int sumOfBlues=0;
				unsigned int sumOfGreens=0;
				for(int k=-1;k<2;k++)
					for(int l=-1;l<2;l++)
						sumOfReds+=aop->at(realMod(i+k,h))->at(realMod(j+l,w))->getRed(),
						sumOfGreens+=aop->at(realMod(i+k,h))->at(realMod(j+l,w))->getGreen(),
						sumOfBlues+=aop->at(realMod(i+k,h))->at(realMod(j+l,w))->getBlue();
				newaop->at(i)->push_back(new pixal((unsigned char)(sumOfReds/9),(unsigned char)(sumOfBlues/9),(unsigned char)(sumOfGreens/9)));
		}
	}
	//clean up original
	while(!aop->empty()){
		while(!aop->back()->empty())
			delete aop->back()->back(),aop->back()->pop_back();
		delete aop->back();
		aop->pop_back();
	}
	delete aop;
	aop=newaop;
}
void blurPixalsAndWrite(std::vector< std::vector<pixal *> * > * &aop,int h,int w,unsigned char * &header,std::string outputFile){
	std::vector< std::vector<pixal *> * > * newaop = new std::vector< std::vector<pixal *> * > (h,NULL);
	//prepare file
	FILE * attempttocopy = fopen(outputFile.c_str(),"w");
	fwrite(header,sizeof(unsigned char),54,attempttocopy);
	unsigned char * img = new unsigned char[3*h*w];

	//process blur
	for(int i=0;i<h;i++){
		newaop->at(i)=new std::vector<pixal *>;
		for(int j=0;j<w;j++){
				unsigned int sumOfReds=0;
				unsigned int sumOfBlues=0;
				unsigned int sumOfGreens=0;
				for(int k=-1;k<2;k++)
					for(int l=-1;l<2;l++)
						sumOfReds+=aop->at(realMod(i+k,h))->at(realMod(j+l,w))->getRed(),
						sumOfGreens+=aop->at(realMod(i+k,h))->at(realMod(j+l,w))->getGreen(),
						sumOfBlues+=aop->at(realMod(i+k,h))->at(realMod(j+l,w))->getBlue();
				newaop->at(i)->push_back(new pixal((unsigned char)(sumOfReds/9),(unsigned char)(sumOfBlues/9),(unsigned char)(sumOfGreens/9)));
				//store in image
				img[((h-i-1)*w+j)*3]=newaop->at(i)->at(j)->getBlue();
				img[((h-i-1)*w+j)*3+1]=newaop->at(i)->at(j)->getGreen();
				img[((h-i-1)*w+j)*3+2]=newaop->at(i)->at(j)->getRed();
		}
	}
	//clean up original
	for(int i=0;i<h;i++){
		while(!aop->at(i)->empty())
			delete aop->at(i)->back(),aop->at(i)->pop_back();
		delete aop->at(i);
	}
	//write out image
	fwrite(img,sizeof(unsigned char),3*h*w,attempttocopy);
	fclose(attempttocopy);
	
	mongocxx::uri uri("mongodb://localhost:3001");
    mongocxx::client conn(uri);

    bsoncxx::builder::stream::document document{};

    auto collection = conn["meteor"]["leftImages"];
    document << "disklocation" << "/"+outputFile;

    collection.insert_one(document.view());

	delete[] img;
	while(!aop->empty())
		aop->pop_back();
	delete aop;
	aop=newaop;
}
int main(int argv, char ** argc){
	//read image
	FILE * bitmapfile = fopen(argc[1],"r");
	unsigned char * infotable = new unsigned char[54];
	fread(infotable,sizeof(unsigned char),54,bitmapfile);
	int imagewidth = *(int*)(infotable+18);
	int imageheight = *(int*)(infotable+22);
	std::vector< std::vector<pixal *> * > * bigoldarrayofpixals = new std::vector< std::vector<pixal *> * > (imageheight,NULL);
	for(int i=imageheight-1;i>=0;i--){
		bigoldarrayofpixals->at(i)=new std::vector<pixal *>;
		for(int j=0;j<imagewidth;j++){
			unsigned char * readpixal = new unsigned char[3];
			fread(readpixal,sizeof(unsigned char),3,bitmapfile);
//			std::cout<<(int)*(readpixal+2)<<" "<<(int)*(readpixal+1)<<" "<<(int)*(readpixal)<<std::endl;
			bigoldarrayofpixals->at(i)->push_back(new pixal(*(readpixal+2),*(readpixal),*(readpixal+1)));
			delete[] readpixal;
		}
	}
	fclose(bitmapfile);
	
		//clear meteor mongo leftImages
	mongocxx::uri uri("mongodb://localhost:3001");
    mongocxx::client conn(uri);
    bsoncxx::builder::stream::document document{};
    auto collection = conn["meteor"]["leftImages"];
	collection.drop();
	
	std::string duplicate(argc[1]);
	std::string name(duplicate.substr(0,duplicate.find(".")));
	for(int i=0;i<atoi(argc[2]);i++)
		(i+1)%atoi(argc[3])?blurPixals(bigoldarrayofpixals,imageheight,imagewidth):blurPixalsAndWrite(bigoldarrayofpixals,imageheight,imagewidth,infotable,name+std::to_string(i+1)+"seq.bmp");

	//blurpixals(bigoldarrayofpixals,imageheight,imagewidth);
	//std::cout<<bigoldarrayofpixals[0][0]->getRed()<<" "<<bigoldarrayofpixals[0][0]->getBlue()<<" "<<bigoldarrayofpixals[0][0]->getGreen()<<std::endl;
	return 0;
}

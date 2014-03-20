//draw marker

#ifndef Marker_hpp
#define Marker_hpp

#define MERIDIAN 1
#define PARALLEL 2  
#define POINT 3

class Marker {
private:
	int mode;  	//type of markers
	double latitude;    //North is positive and South is negative 
	double longitude;   //East is positive and West is negative 	
	  

public:
	Marker(int m, double lati, double longi);
	~Marker() {};

	void draw();
};


#endif
/* File was written by [Author Name] and last edited on 1/16/2025.
This program is designed to use an Iterated Function System (IFS) where a point
is transformed into a new location and stored in each iteration. This set of
transformed points can be used to draw a fractal image of a fern.
*/
#include <iostream>
using std::cin;
using std::cout;

const int width = 228; // set width as desired
const int height = 100; // set height as desired as long as width * height is a multiple of 8
const double xMax = 2.75; // DO NOT CHANGE
const double yMax = 10.1; // DO NOT CHANGE

const int probabilities[4] = {1, 7, 7, 85};
const double transformations[4][6] = {
	{0.0, 0.0, 0.0, 0.0, 0.16, 0.0},
	{0.2, -0.26, 0.0, 0.23, 0.22, 1.6},
	{-0.15, 0.28, 0.0, 0.26, 0.24, 0.44},
	{0.85, 0.04, 0.0, -0.04, 0.85, 1.6}
};

//Declares the functions used in ths program
void performIterations(int iterations, unsigned char* image);
int selectTransformation();
void applyTransformation(double& x, double& y, const double* transformation);
void setPixel(double x, double y, unsigned char* image);
bool getPixel(int row, int col, unsigned char* image);
void drawImage(unsigned char* image);

/**
* Prompts the user for number of desired iterations then runs the fern program.
*/
int main(){
	unsigned char pixelArray[(width * height) / 8] {};

	int iterations;
	cout << "Please enter the number of iterations: ";
	cin >> iterations;

	if(cin.fail() || iterations <= 0){
		cout << "Entry was not a positive integer.";
		return 0;
	}

	performIterations(iterations, pixelArray);
	drawImage(pixelArray);
}

/**
* Performs the desired number of iterations by applying a random transformation
and setting the resulting pixel.
* @param iterations - The number of times transformations will occur.
* @param image - The pixel array.
*/
void performIterations(int iterations, unsigned char* image){
	double x = 0.0;
	double y = 0.0;

	for(int i = 0; i < iterations; i++){
		int transformation = selectTransformation();
		applyTransformation(x, y, transformations[transformation]);
		setPixel(x, y, image);
	}
}

/**
* Randomly chooses one of the four transformations used to draw the fern.
* @return The number associated with one of the transformations.
*/
int selectTransformation(){
	int randomNumber = std::rand() % 100;
	if(randomNumber == 0){
		return 0;
	} else if(randomNumber < 8){
		return 1;
	} else if(randomNumber < 15){
		return 2;
	} else{
		return 3;
	}
}

/**
* Applies the desired transformation to a designated x-y pair.
* @param x - The x coordinate of a point.
* @param y - The y coordinate of a point.
* @param transformation - The desired transformation to be performed.
*/
void applyTransformation(double& x, double& y, const double* transformation){
	double xCopy = x;
	x = (transformation[0] * x) + (transformation[1] * y) + transformation[2];
	y = (transformation[3] * xCopy) + (transformation[4] * y) + transformation[5];
}

/**
* Sets a pixel to be drawn in the image by breaking the image byte's and shifting
their corresponding bits.
* @param x - The x coordinate of a point.
* @param y - The y coordinate of a point.
* @param image - The pixel array.
*/
void setPixel(double x, double y, unsigned char* image){
	int pixelX = (int)(width / 2 * (1 + x / xMax));
	int pixelY = (int)(height * (1 - y / yMax));
	int byteLocation = ((pixelY * width) + pixelX) / 8; //Determines which byte the pixel is in.
	int bitLocation = pixelX % 8; //Determines the pixel bit.
	image[byteLocation] = image[byteLocation] | (1 << bitLocation);
}
/**
* Returns true if the desired pixel has been set to a value of 1.
* @param row - The row the pixel is in the image.
* @param col - The column the pixel is in the image.
* @param image - The pixel array.
* @return True if the designated pixel is already set.
*/
bool getPixel(int row, int col, unsigned char* image){
	int byteLocation = ((row * width) + col) / 8; //Determines which byte the pixel is in.
	int bitLocation = col % 8; //Determines the pixel bit.
	return image[byteLocation] & (1 << bitLocation);
}

/**
* Draws the fern by printing "#" to the terminal for all pixels that are set.
* @param image - The pixel array.
*/
void drawImage(unsigned char* image){
	for(int row = 0; row < height; row++){
		for(int col = 0; col < width; col++){
			if(getPixel(row, col, image)){
				cout << "#";
			} else {
				cout << " ";
			}
		}
		cout << std::endl;
	}
}

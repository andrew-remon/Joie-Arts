// This file is Part 2 of Assignment 1 (CS213).
// It implements several image filters and a menu system to test them.
// Link to our team's google drive that has a video explaining the app and document containing
// more details about our team and a diagram is here :
// https://drive.google.com/drive/u/2/folders/1RGNOCiMWfK1G72d6raB_XjhekJpsMMff
//
// GitHub Repo's link: https://github.com/andrew-remon/Joy_Animation_App-Filter_Application
//
// Remaining Details Below.
//
// Student 1 Name: Ahmed Yasser
// ID: 20240061
// Section: S7-8
// Worked On:
// - Filter: 1, 4, 7, 10
// - Github
// Working On:
// - Grand Competition GUI
//
// Student 2 Name: Andrew Remon
// ID: 20240094
// Section: S7-8
// Worked On:
// - Filter: 2 , 5 , 8, 11
// - Menu
// - Class Setup
// - Github
// - Diagram
// Working on :
// - linking the menu with the gui
//
// Student 3 Name: Joy Magdy
// ID: 20240149
// Section: S7-8
// Worked On:
// Filter: 3 , 6 , 9 , 12 , 13 , 14 , 15
// Menu
// Working On:
// - Filter: 16, 17, 18, bonus filters
// - Testing Multiple Filter Optimization options
//

#include <iostream>
#include <string>
#include <stack>
#include <algorithm> // for clamp in resize filter
#include <cmath>  // for floor in resize filter
#include "Image_Class.h"
using namespace std;

bool isExit = false;
static Image image;
stack <Image> stUndo;
stack <Image> stRedo;

enum mainMenuChoice
{
    Load = 1,
    AddFrame = 2, AddFilmFrame = 3, BlackAndWhite = 4, Blur = 5, CelShading = 6,
    Crop = 7, DarkenOrLighten = 8, DetectEdge = 9, Emboss = 10,
    FishEye = 11, Flip = 12, Glitch = 13, Grayscale = 14,
    Invert = 15, Merge = 16, Midnight = 17, NaturalSunlight = 18, OilPainting = 19,
    OldTv = 20, PixelArt = 21, Purpling = 22, RedScale = 23,
    Resize = 24, Rotate = 25, Sharpen = 26, Skew = 27,
    Save = 28, Undo = 29, Redo = 30, End = 31
};

class InputValidation
{
public:
    static bool isNumberBetween(int number, int from, int to)
    {
        return (number >= from && number <= to);
    }

    static int readIntNumber(string errorMessage = "Invalid Input, Please enter a Number")
    {
        string input;
        int number;
        bool notValid;
        cout << "Please enter a Number: ";
        do
        {
            cin.clear();
            getline(cin, input);
            notValid = false;

            try
            {
                size_t pos;
                number = stoi(input, &pos);
                if (pos != input.length())
                {
                    throw invalid_argument("Trailing characters");
                }
            }
            catch(...)
            {
                cout << errorMessage << endl;
                notValid = true;
            }
        } while (notValid);
        return number;
    }

    static int readIntNumberBetween(int from, int to, string errorMessage)
    {
        while (true)
        {
            int number = readIntNumber();
            if (isNumberBetween(number, from, to)) return number;
            else cout << errorMessage << endl;
        }
    }

    static Image getImagePath()
    {
        bool isFound = false;
        Image img;
        do
        {
            string filename;
            try
            {
                cout << "Please enter an image: ";
                getline(cin, filename);

                img = Image(filename);
                isFound = true;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                cout << "\nImage Not Found, Please Try Again.\n";
            }
        } while (!isFound);

        return img;
    }
};

class Filter
{
private:
    static double cubicInterpolate(double p[4], double x)
    {
        return p[1] + 0.5 * x *
        (
            p[2] - p[0] + x * (2.0 * p[0] - 5.0 * p[1] + 4.0 * p[2] - p[3] +
            x * (3.0 * (p[1] - p[2]) + p[3] - p[0]))
        );
    }

    static double bicubicInterpolate(double p[4][4], double x, double y)
    {
        double arr[4];
        arr[0] = cubicInterpolate(p[0], y);
        arr[1] = cubicInterpolate(p[1], y);
        arr[2] = cubicInterpolate(p[2], y);
        arr[3] = cubicInterpolate(p[3], y);
        return cubicInterpolate(arr, x);
    }

    static Image nearestNeighborResize(Image &image, int newWidth, int newHeight)
    {
        Image resized(newWidth, newHeight);

        float iRatio = (float)image.width / newWidth;
        float jRatio = (float)image.height / newHeight;

        for (int i = 0; i < newWidth; i++)
        {
            for (int j = 0; j < newHeight; j++)
            {
                int n_i = (int)(i * iRatio + 0.5f); // n = nearest
                int n_j = (int)(j * jRatio + 0.5f);

                n_i = min(image.width  - 1, max(0, n_i));
                n_j = min(image.height - 1, max(0, n_j));

                for (int k = 0; k < 3; k++)
                    resized(i, j, k) = image(n_i, n_j, k);
            }
        }

        return resized;
    }

    static Image lighten(Image &image , float strength = 1.5f)
    {
        for (int i = 0 ; i < image.width ; i++)
        {
            for (int j = 0 ; j < image.height ; j++)
            {
                for (int k = 0 ; k < image.channels ; k++)
                {
                    if (image(i, j, k) * strength  > 255)
                        image(i, j, k) = 255;
                    else
                        image(i, j, k) = image(i, j, k) * strength;
                }
            }
        }

        return image;
    }

    static Image darken(Image &image , float strength = 0.5f)
    {
        for (int i = 0 ; i < image.width ; i++)
        {
            for (int j = 0 ; j < image.height ; j++)
            {
                for (int k = 0 ; k < image.channels ; k++)
                {
                    if (image(i, j, k) * strength  > 255)
                        image(i, j, k) = 255;
                    else
                        image(i, j, k) = image(i, j, k) * strength;
                }
            }
        }

        return image;
    }

    static Image vignette(Image &image , float strength = 0.8f)
    {
        float centerX = image.width/ 2.0f  , centerY = image.height/ 2.0f;
        float maxDistance = sqrt(centerX * centerX + centerY * centerY);

        for (int i = 0; i < image.width; i++)
        {
            for(int j = 0; j < image.height; j++)
            {
                float distance = sqrt((i - centerX) * (i - centerX) + (j - centerY) * (j - centerY));
                float factor = 1 - strength * (distance/maxDistance);

                if (factor < 0) factor = 0;

                for (int k = 0; k < 3; k++)
                    image(i , j , k) = image(i,j,k) * factor;
            }
        }

        return image;
    }

    static Image noise(Image &image, int amount = 20)
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int noise = (rand() % (2 * amount + 1)) - amount;
                    int val = image(i, j, k) + noise;

                    if (val < 0) val = 0;
                    if (val > 255) val = 255;
                    image(i, j, k) = val;
                }
            }
        }

        return image;
    }

    static Image contrast(Image &image , float strength = 40.0f)
    {
        float factor = 1.0f + (strength/100.0f);
        Image contrasted(image.width, image.height);

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    float val = ((image(i, j, k) -128)* factor ) + 128;
                    val = max(0.0f,min(255.0f,val));
                    contrasted(i, j, k) = val;
                }
            }
        }

        return contrasted;
    }

    static Image scanLines(Image &image , float freq = 3.14f)
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                float factor = 0.7f + 0.3f * sin ((float)j * freq * 3.14159f / image.height);

                for (int k = 0; k < 3; k++)
                    image(i, j, k) = image(i, j, k) * factor;
            }
        }

        return image;
    }

    static Image gamma(Image &image, float gamma = 1.0f)
    {
    // pass nums less than 1 to lighten , more than 1 to darken
    for (int i = 0 ; i < image.width ; i++)
    {
        for (int j = 0 ; j < image.height ; j++)
        {
            for (int k = 0 ; k < image.channels ; k++)
            {
                float val = 255 * pow( (float)(image(i,j,k)/255.0f) , gamma);
                val = max(0.0f,min(255.0f,val));
                image(i,j,k) = val;
            }
        }
    }

    return image;
}

public:
    static Image grayscaleFilter(Image &image)
    {
        for (int i = 0 ; i < image.width ; ++i)
        {
            for (int j = 0 ; j < image.height ; ++j)
            {
                unsigned int avg = 0;
                for (int k = 0 ; k < image.channels ; ++k)
                    avg += image(i, j, k);

                avg /= image.channels;
                // avg = avg / image.channels;
                for (int k = 0 ; k < image.channels ; ++k)
                    image(i, j, k) = avg;
            }
        }

        return image;
    }

    static Image blackAndWhiteFilter(Image &image)
    {
        for (int i = 0 ; i < image.width ; ++i)
        {
            for (int j = 0 ; j < image.height ; ++j)
            {
                unsigned int avg = 0;
                for (int k = 0 ; k < image.channels ; ++k)
                    avg += image(i, j, k);

                avg = avg / image.channels;

                if (avg > 255/2)
                {
                    for (int k = 0 ; k < image.channels ; ++k)
                        image(i,j, k) = 255;
                }
                else
                {
                    for (int k = 0 ; k < image.channels ; ++k)
                        image(i,j, k) = 0;
                }
            }
        }

        return image;
    }

    static Image invertFilter(Image &image)
    {
        for (int i = 0 ; i < image.width ; ++i)
        {
            for (int j = 0 ; j < image.height ; ++j)
            {
                for (int k = 0 ; k < image.channels ; ++k)
                    image(i,j,k) = 255 - image(i,j,k);
            }
        }

        return image;
    }

    static Image flipFilter(Image &image)
    {
        cout << "\nDo you want a Horizontal or Vertical Flip ?\n";
        cout << "Enter 1 for Horizontal and 2 for Vertical\n";

        int x = InputValidation::readIntNumberBetween(1, 2, "Please Enter 1 or 2\n");

        Image flippedImage(image.width,image.height);

        if (x == 1)
        {
            for (int i = 0 ; i < image.width ; i++)
            {
                for (int j = 0 ; j < image.height ; j++)
                {
                    for (int k = 0 ; k < image.channels ; k++)
                        flippedImage(i,j,k) = image(image.width -1-i,j,k);
                }
            }
        }
        else if (x == 2)
        {
            for (int i = 0 ; i < image.width ; i++)
            {
                for (int j = 0 ; j < image.height ; j++)
                {
                    for (int k = 0 ; k < image.channels ; k++)
                        flippedImage(i,j,k) = image(i,image.height -1-j,k);
                }
            }
        }
        else
        {
            cout << "Error , Enter a Valid Choice\n";
            return flipFilter(image);
        }

        return flippedImage;
    }

    static Image rotateFilter(Image &image)
    {
        cout << "Do you want a 90 or 180 or 270 degree Rotation ?\n";
        cout << "Enter 1 for 90 degree Rotation and 2 for 180 degree Rotation and 3 for 270 degree Rotation\n";

        int x = InputValidation::readIntNumberBetween(1, 3, "Please Enter a number from 1 to 3\n");

        Image rotatedImage;

        if (x == 1)
        {
            rotatedImage = Image(image.height, image.width);
            for (int i = 0 ; i < image.width ; i++)
            {
                for (int j = 0 ; j < image.height ; j++)
                {
                    for (int k = 0 ; k < image.channels ; k++)
                        rotatedImage(j,image.width -1 -i,k) = image(i,j,k);
                }
            }
        }
        else if (x == 2)
        {
            rotatedImage = Image(image.width, image.height);

            for (int i = 0 ; i < image.width ; i++)
            {
                for (int j = 0 ; j < image.height ; j++)
                {
                    for (int k = 0 ; k < image.channels ; k++)
                        rotatedImage(image.width-1-i,image.height -1 -j,k) = image(i,j,k);
                }
            }
        }
        else if (x == 3)
        {
            rotatedImage = Image(image.height, image.width);
            for (int i = 0 ; i < image.width ; i++)
            {
                for (int j = 0 ; j < image.height ; j++)
                {
                    for (int k = 0 ; k < image.channels ; k++)
                        rotatedImage(image.height-1-j,i,k) = image(i , j ,k);
                }
            }
        }
        else
        {
            cout << "Error , Enter a Valid Number\n";
            rotateFilter(image);
        }

        return rotatedImage;
    }

    static Image darkenOrLightenFilter(Image &image)
    {
        cout << "Do you want to Darken or Lighten it?\n";
        cout << "Enter 1 to Darken and 2 to Lighten\n";

        int x = InputValidation::readIntNumberBetween(1, 2, "Please Enter a number from 1 to 2\n");

        if (x == 1)
            image = darken(image);
        else if (x == 2)
            image = lighten(image);
        else
        {
            cout << "Error , invalid input\n";
            darkenOrLightenFilter(image);
        }

        return image;
    }

    static Image resizeFilter(const Image &image)
    {
        string widthInput, heightInput;

        cout << "\nThe new width? \n";
        int newWidth = InputValidation::readIntNumber();
        cout << "\nThe new height? \n";
        int newHeight = InputValidation::readIntNumber();

        Image output(newWidth, newHeight);

        double scaleX = (double)image.width / newWidth;
        double scaleY = (double)image.height / newHeight;

        for (int j = 0; j < newHeight; j++)
        {
            for (int i = 0; i < newWidth; i++)
            {
                double xIn = i * scaleX;
                double yIn = j * scaleY;

                int xBase = (int)floor(xIn) - 1;
                int yBase = (int)floor(yIn) - 1;

                double dx = xIn - floor(xIn);
                double dy = yIn - floor(yIn);

                for (int k = 0; k < image.channels; k++) // R,G,B loop
                {
                    double p[4][4];
                    for (int m = 0; m < 4; m++)
                    {
                        for (int n = 0; n < 4; n++)
                        {
                            int xx = std::clamp(xBase + n, 0, image.width - 1);
                            int yy = std::clamp(yBase + m, 0, image.height - 1);
                            p[m][n] = image(xx, yy, k);
                        }
                    }

                    double value = bicubicInterpolate(p, dx, dy);
                    output(i, j, k) = (unsigned char)std::clamp(value, 0.0, 255.0);
                }
            }
        }

        return output;
    }

    static Image detectBlackEdgeFilter(Image &image)
    {
        float kernel[3][3] =
        {
            {-1, -1, -1},
            {-1,  8, -1},                // outline kernel
            {-1, -1, -1}
        };

        image = grayscaleFilter(image);
        Image detected(image.width-2, image.height-2);

        for (int i = 1; i < image.width-1; i++)
        {
            for (int j = 1; j < image.height-1; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    float val =
                        image (i-1 ,j-1 , k) * kernel[0][0]
                    +   image (i   ,j-1 , k) * kernel[1][0]
                    +   image (i+1 ,j-1 , k) * kernel[2][0]
                    +   image (i-1 ,j   , k) * kernel[0][1]
                    +   image (i   ,j   , k) * kernel[1][1]
                    +   image (i+1 ,j   , k) * kernel[2][1]
                    +   image (i-1 ,j+1 , k) * kernel[0][2]
                    +   image (i   ,j+1 , k) * kernel[1][2]
                    +   image (i+1 ,j+1 , k) * kernel[2][2];

                    val = max(0.0f, min(255.0f, val)); // clamp
                    detected(i-1, j-1, k) = 255 - val; //invert pixel
                }
            }
        }

        return detected;
    }

    static Image addFrameFilter(Image &image , int thickness =5, unsigned char R = 255, unsigned char G =255, unsigned char B=255)
    {
        Image framed(image.width, image.height);

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                bool isFrame = (i < thickness) || (i >= image.width - thickness) || (j < thickness) || (j >= image.height - thickness);

                if (isFrame)
                {
                    framed(i, j, 0) = R;
                    framed(i, j, 1) = G;
                    framed(i, j, 2) = B;
                }
                else
                {
                    framed(i, j, 0) = image(i, j, 0);
                    framed(i, j, 1) = image(i, j, 1);
                    framed(i, j, 2) = image(i, j, 2);
                }
            }
        }

        return framed;
    }

    static Image addFilmFrameFilter(Image &image)
    {
        int minDim = min(image.width, image.height);
        int thickness = max(10, minDim / 30);
        int holeSize = max(5, minDim / 60);
        int holeSpacing = max(8, minDim / 40);

        Image framed(image.width, image.height);
        image = addFrameFilter(image , thickness + thickness/2,0,0,0);

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                bool isFrame = (j < thickness) || (j >= image.height - thickness);
                if (j < thickness && (i % (holeSize + holeSpacing) < holeSize))
                    isFrame = false;

                if (j >= image.height - thickness && (i % (holeSize + holeSpacing) < holeSize))
                    isFrame = false;

                if (isFrame)
                {
                    for (int k = 0; k < 3; k++)
                        framed(i, j, k) = 190;
                }
                else
                {
                    for (int k = 0; k < 3; k++)
                        framed(i, j, k) = image(i, j, k);
                }
            }
        }

        return framed;
    }

    static Image addDoubleFrameFilter(Image &image, int outerThickness = 12, int innerThickness = 8, int gap = 10, int R = 255, int G = 255, int B = 255)
    {
        int w = image.width;
        int h = image.height;
        Image framed(w, h);

        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                bool isOuterFrame = (i < outerThickness) || (i >= w - outerThickness) ||
                                    (j < outerThickness) || (j >= h - outerThickness);

                bool isInnerFrame = (i >= outerThickness + gap && i < outerThickness + gap + innerThickness) ||
                                    (i >= w - (outerThickness + gap + innerThickness) && i < w - (outerThickness + gap)) ||
                                    (j >= outerThickness + gap && j < outerThickness + gap + innerThickness) ||
                                    (j >= h - (outerThickness + gap + innerThickness) && j < h - (outerThickness + gap));

                if (isOuterFrame || isInnerFrame)
                {
                    framed(i, j, 0) = R;
                    framed(i, j, 1) = G;
                    framed(i, j, 2) = B;
                }

                else
                {
                    framed(i, j, 0) = image(i, j, 0);
                    framed(i, j, 1) = image(i, j, 1);
                    framed(i, j, 2) = image(i, j, 2);
                }
            }
        }

        return framed;
    }

    static Image blurFilter(Image &image)
    {
        float kernel[3][3] =
        {
            {0.111, 0.111, 0.111},
            {0.111, 0.111, 0.111},
            {0.111, 0.111, 0.111}
        };

        Image blurred(image.width, image.height);

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    blurred(i,j,k) =
                        image (max(i-1, 0), max(j-1, 0), k) * kernel[0][0]
                    +   image (i, max(j-1, 0), k) * kernel[1][0]
                    +   image (min(i+1,image.width-1), max(j-1, 0), k) * kernel[2][0]
                    +   image (max(i-1,0),j, k) * kernel[0][1]
                    +   image (i, j, k) * kernel[1][1]
                    +   image (min(i+1,image.width-1), j, k) * kernel[2][1]
                    +   image (max(i-1, 0), min(j+1, image.height-1), k) * kernel[0][2]
                    +   image (i, min(j+1,image.height-1), k) * kernel[1][2]
                    +   image (min(i+1, image.width-1), min(j+1, image.height-1), k) * kernel[2][2];
                }
            }
        }

        return blurred;
    }

    static Image mergeFilter(Image &image)
    {
        cout << "Enter 2nd Image Path\n";

        Image secondImage = InputValidation::getImagePath();

        int largestWidth = max(image.width, secondImage.width);
        int largestHeight = max(image.height, secondImage.height);

        secondImage = nearestNeighborResize(secondImage, largestWidth, largestHeight);
        image = nearestNeighborResize(image, largestWidth, largestHeight);

        Image merged(largestWidth, largestHeight);

        float alpha = 0.5;
        float beta = 1 - alpha;
        float constant = 0;

        for (int i = 0; i < largestWidth; i++)
        {
            for (int j = 0; j < largestHeight; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    merged(i, j, k) = alpha*image(i, j, k)
                    + beta*secondImage(i, j, k) + constant;
                }
            }
        }

        return merged;
    }

    static Image midnightFilter(Image &image)
    {
        image = darken(image);
        image = purplingFilter(image);
        image = redScaleFilter(image);
        image = invertFilter(image);

        return image;
    }

    static Image oldTVFilter(Image &image)
    {
        int width = image.width, height = image.height;

        for (int i = 0; i < 3; i++)
            image = blurFilter(image);

        image = nearestNeighborResize(image, width, height);
        image = scanLines(image , 30);
        image = noise(image ,35);
        image = vignette(image,0.7f);
        image = lighten(image);

        return image;
    }

    static Image oilPaintingFilter(Image &image)
    {
        int radius = 3;

        Image oiledUp(image.width, image.height);

        for (int i = radius; i < image.width - radius; i++)
        {
            for (int j = radius; j < image.height - radius; j++)
            {
                int lvls = 256; // levels of brightnesses to reduce computations and to make it look more blocky or painted
                int intensityCount [lvls] = {0};
                int sumR[lvls] = {0} , sumG[lvls] = {0} , sumB[lvls] = {0} ;

                for (int n_i = -radius ; n_i <= radius ; n_i++) // n = nearest
                {
                    for (int n_j = -radius ; n_j <= radius ; n_j++)
                    {
                        int r = image (i+n_i, j+n_j , 0);
                        int g = image(i+n_i, j+n_j , 1);
                        int b = image(i+n_i, j+n_j , 2);

                        int intensity = ((r + g + b) * (lvls -1)) / 765;   // adds count for the most dominant color
                        if (intensity >= lvls) intensity = lvls - 1;       // to not exceed the lvl brightness
                        intensityCount[intensity]++;

                        sumR [intensity] += r;
                        sumG [intensity] += g;   // add values of the colors
                        sumB [intensity] += b;
                    }
                }

                int maxCount = 0, maxIndex = 0;

                for (int k = 0; k < lvls; k++)
                {
                    if (intensityCount[k] > maxCount)
                    {
                        maxCount = intensityCount[k];           // find the most repeated intensity
                        maxIndex = k;
                    }
                }

                if (maxCount > 0) // safety condition to not divide by 0
                {
                    oiledUp(i,j,0) = sumR[maxIndex] / maxCount;
                    oiledUp(i,j,1) = sumG[maxIndex] / maxCount;    // divide value by count to find avr
                    oiledUp(i,j,2) = sumB[maxIndex] / maxCount;
                }
                else
                {
                    oiledUp(i,j,0) = image(i,j,0);
                    oiledUp(i,j,1) = image(i,j,1);
                    oiledUp(i,j,2) = image(i,j,2);
                }
            }
        }

        return oiledUp;
    }

    static Image naturalSunLightFilter(Image &image)
    {
        image = lighten(image,1.1);
        image = contrast(image ,10);

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                float val = image(i, j, 0)*1.15f;
                if (val > 255) val = 255;
                image(i, j, 0) = (int)val;

                val = image(i, j, 1)*1.1f;
                if (val > 255) val = 255;
                image(i, j, 1) = (int)val;

                val = image(i, j, 1)*0.8f;
                image(i, j, 2) = (int)val;
            }
        }

        return image;
    }

    static Image cropFilter(Image &image)
    {
        int x = 0, y = 0;
        int w = 0, h = 0;

        cout << "Upper left corner of the part to keep pixel coordinates\n";
        cout << "Enter x point: \n" ; x = InputValidation::readIntNumber();
        cout << "Enter y point: \n" ; y = InputValidation::readIntNumber();
        cout << "Enter Dimensions to cut \n";
        cout << "Enter width: \n" ; w = InputValidation::readIntNumber();
        cout << "Enter height: \n" ; h = InputValidation::readIntNumber();

        Image cropped(w , h);

        for (int i = 0 ; i < w ; i++)
        {
            for (int j = 0 ; j < h ; j++)
            {
                for (int k = 0 ; k < 3 ; k++)
                    cropped (i , j , k) = image(x+i,y+j,k);
            }
        }

        return cropped;
    }

    static Image redScaleFilter(Image &image)
    {
        float red_f = .6 , green_f = 1.7 , blue_f = 1.7;
        int invert = 255;

        for (int i = 0 ; i < image.width ; ++i)
        {
            for (int j = 0 ; j < image.height ; ++j)
            {
                int val = image(i, j, 0) * red_f;
                if (val > 255) {val = 255;}
                image (i,j,0) = invert - val;

                val = image(i, j, 1) * green_f;
                if (val > 255) {val = 255;}
                image (i,j,1) = invert - val;

                val = image(i, j, 2) * blue_f;
                if (val > 255) {val = 255;}
                image (i,j,2) = invert - val;
            }
        }

        image = gamma(image , .5f);
        return image;
    }

    static Image purplingFilter(Image &image)
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                float val = image(i, j, 0)*1.1f;
                if (val > 255) {val = 255;}
                image(i, j, 0) = (int)val;

                val = image(i, j, 1)*0.7f;
                if (val > 255) {val = 255;}
                image(i, j, 1) = (int)val;

                val = image(i, j, 2)*1.1f;
                if (val > 255) {val = 255;}
                image(i, j, 2) = (int)val;
            }
        }

        return image;
    }

    static Image skewFilter(Image &image, float degree = 40.0f)
    {
        float rad = degree * M_PI / 180.0f;
        float skewFactor = tan(rad);
        int baseOffset = image.height * skewFactor;

        int newWidth = image.width + abs(baseOffset);
        int newHeight = image.height;

        Image skewed(newWidth, newHeight);

        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                // -ve j to make it bend to the right not left
                int offsetX = -j * skewFactor + baseOffset;
                int newX = i + offsetX;

                if (newX >= 0 && newX < newWidth)
                {
                    for (int k = 0; k < image.channels; ++k)
                        skewed(newX, j, k) = image(i, j, k);
                }
            }
        }

        return skewed;
    }

    static Image glitchFilter(Image &image, int max_shift = 5)
    {
        for (int i = 0; i < image.width; i++)
        {
            int shiftR = rand() % (2 * max_shift + 1) - max_shift;
            int shiftG = rand() % (2 * max_shift + 1) - max_shift;
            int shiftB = rand() % (2 * max_shift + 1) - max_shift;

            for (int j = 0; j < image.height; j++)
            {   // src = source
                int srcR = max(0 ,min(image.width -1 , i + shiftR));
                int srcG = max(0 ,min(image.width -1 , i + shiftG));
                int srcB = max(0 ,min(image.width -1 , i + shiftB));

                image(i, j, 0) = image(srcR, j, 0);
                image(i, j, 1) = image(srcG, j, 1);
                image(i, j, 2) = image(srcB, j, 2);
            }
        }

        return image;
    }

    static Image fishEyeAndVignetteFilter(Image &image, float vignette_strength = 0.8f)
    {
        Image result(image.width, image.height);

        float centerX = image.width / 2.0f;
        float centerY = image.height / 2.0f;
        float radius = min(centerX, centerY);

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                float x = (i - centerX) / radius;
                float y = (j - centerY) / radius;
                float r = sqrt(x * x + y * y);

                float srcX = i;
                float srcY = j;

                if (r < 1.0f)
                {
                    float new_r = (r + (1 - sqrt(1 - r * r))) / 2.0f;
                    float theta = atan2(y, x);
                    srcX = centerX + new_r * radius * cos(theta);
                    srcY = centerY + new_r * radius * sin(theta);
                }

                for (int k = 0; k < image.channels; k++)
                {
                    result(i, j, k) =
                    image(max(0, min(image.width-1,(int)srcX )), max(0, min(image.height-1,(int)srcY )), k);
                }
            }
        }

        result = vignette(result);
        return result;
    }

    static Image celShadingFilter(Image &image, int color_levels = 8)
    {
        Image result(image.width, image.height);

        float step = 255.0f / (color_levels - 1);

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    float val = image(i, j, k);
                    val = round(val / step) * step;  // quantize color
                    result(i, j, k) = max(0.0f,min(255.0f, val));
                }
            }
        }

        return result;
    }

    static Image pixelArtFilter(Image &image)
    {
        int factor = 4;

        if (image.width > 1500 && image.height > 1500)
            factor = 8;

        if (image.width > 3000 && image.height > 3000)
            factor = 16;

        int org_width = image.width , org_height = image.height;
        image = nearestNeighborResize(image , image.width /factor , image.height/factor);
        image = nearestNeighborResize(image , org_width, org_height);

        return image;
    }

    static Image sharpenFilter(Image &image)
    {
        float kernel[3][3] =
        {
            {0 , -1,  0},
            {-1,  5, -1},
            {0 , -1,  0}
        };

        Image sharpened(image.width, image.height);

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    float val =
                        image (max(i-1, 0), max(j-1, 0), k) * kernel[0][0]
                    +   image (i,max(j-1, 0), k) * kernel[1][0]
                    +   image (min(i+1, image.width-1), max(j-1, 0), k) * kernel[2][0]
                    +   image (max(i-1,0), j, k) * kernel[0][1]
                    +   image (i, j, k) * kernel[1][1]
                    +   image (min(i+1, image.width-1), j, k) * kernel[2][1]
                    +   image (max(i-1, 0), min(j+1,image.height-1), k) * kernel[0][2]
                    +   image (i, min(j+1, image.height-1), k) * kernel[1][2]
                    +   image (min(i+1, image.width-1), min(j+1,image.height-1), k) * kernel[2][2];

                    val = max(0.0f, min(255.0f, val)); // clamp
                    sharpened(i, j, k) = val;
                }
            }
        }

        return sharpened;
    }

    static Image embossFilter(Image &image)
    {
        float kernel[3][3] =
        {
            {-2, -1,  0},
            {-1,  1,  1},
            { 0,  1,  2}
        };

        Image embossed(image.width, image.height);

        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    float val =
                        image (max(i-1, 0), max(j-1, 0), k) * kernel[0][0]
                    +   image (i, max(j-1, 0), k) * kernel[1][0]
                    +   image (min(i+1, image.width-1), max(j-1, 0), k) * kernel[2][0]
                    +   image (max(i-1, 0), j, k) * kernel[0][1]
                    +   image (i, j, k) * kernel[1][1]
                    +   image (min(i+1, image.width-1), j, k) * kernel[2][1]
                    +   image (max(i-1, 0), min(j+1, image.height-1), k) * kernel[0][2]
                    +   image (i, min(j+1, image.height-1), k) * kernel[1][2]
                    +   image (min(i+1, image.width-1), min(j+1,image.height-1), k) * kernel[2][2];

                    val = max(0.0f, min(255.0f, val)); // clamp
                    embossed(i, j, k) = val;
                }
            }
        }

        return embossed;
    }
};

class Main
{
private:
    static Image loadImage()
    {
        image = InputValidation::getImagePath();
        cout << "Image Loaded Successfully.\n";
        stUndo.push(image);

        return image;
    }

    static Image saveImage()
    {
        cout << "Pls enter image name to save new image,\n";
        cout << "Specify extension .jpg/.bmp/.png/.jpeg: ";

        string filename;
        getline(cin, filename);

        image.saveImage(filename);

        cout << "\nImage Saved Successfully.\n";
        return image;
    }

    static void applyFilter()
    {
        string ans;
        cout << "\nDo You want to save this filter? (Y/N) \n";
        getline(cin, ans);
        if (!ans.empty() && (ans[0] == 'Y' || ans[0] == 'y'))
            image = saveImage();
    }

    static void undoFilter()
    {
        cout << "\nAre You Sure you want to undo this filter? (Y/N)\n";
        string ans = "";
        getline(cin, ans);
        if (!ans.empty() && (ans[0] == 'Y' || ans[0] == 'y'))
        {
            if (!stUndo.empty() && stUndo.size() >= 2)
            {
                stUndo.pop();
                image = stUndo.top();
            }
            else cout << "Sorry, There's No filter to Undo.\n";
        }
    }

    static void redoFilter()
    {
        cout << "\nAre You Sure you want to redo to the last filter? (Y/N)\n";
        string ans = "";
        getline(cin, ans);
        if (!ans.empty() && (ans[0] == 'Y' || ans[0] == 'y'))
        {
            if (!stRedo.empty() && stRedo.size() >= 1)
            {
                stUndo.push(stRedo.top());
                image = stRedo.top();
                stRedo.pop();
            }
            else cout << "Sorry, There's No filter to redo.\n";
        }
    }

    static void performMainMenuChoice(mainMenuChoice choice)
    {
        switch (choice)
        {
            case mainMenuChoice::Load :
            {
                image = loadImage();
                break;
            }
            case mainMenuChoice::Save :
            {
                image = saveImage();
                break;
            }
            case mainMenuChoice::Grayscale :
            {
                image = Filter::grayscaleFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::BlackAndWhite :
            {
                image = Filter::blackAndWhiteFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Invert :
            {
                image = Filter::invertFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Flip :
            {
                image = Filter::flipFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Rotate :
            {
                image = Filter::rotateFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Resize :
            {
                image = Filter::resizeFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::DarkenOrLighten :
            {
                image = Filter::darkenOrLightenFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::DetectEdge :
            {
                image = Filter::detectBlackEdgeFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::AddFrame :
            {
                image = Filter::addFrameFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::AddFilmFrame :
            {
                cout << "\nDo You want Single or Double Film Frame?\n";
                cout << "Enter 1 for single and 2 for double\n";

                int x = InputValidation::readIntNumberBetween(1, 2, "Please Enter 1 or 2\n");

                if (x == 1) image = Filter::addFilmFrameFilter(image);
                else image = Filter::addDoubleFrameFilter(image);

                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Blur :
            {
                image = Filter::blurFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Merge :
            {
                image = Filter::mergeFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Midnight :
            {
                image = Filter::midnightFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::OldTv :
            {
                image = Filter::oldTVFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::OilPainting :
            {
                image = Filter::oilPaintingFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::NaturalSunlight :
            {
                image = Filter::naturalSunLightFilter(image);
                stUndo.push(image);
                applyFilter();
                // displayMainMenu();
                break;
            }
            case mainMenuChoice::Crop :
            {
                image = Filter::cropFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::CelShading :
            {
                image = Filter::celShadingFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Emboss :
            {
                image = Filter::embossFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::FishEye :
            {
                image = Filter::fishEyeAndVignetteFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Glitch :
            {
                image = Filter::glitchFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::PixelArt :
            {
                image = Filter::pixelArtFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Purpling :
            {
                image = Filter::purplingFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::RedScale :
            {
                image = Filter::redScaleFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Sharpen :
            {
                image = Filter::sharpenFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Skew :
            {
                image = Filter::skewFilter(image);
                stUndo.push(image);
                applyFilter();
                break;
            }
            case mainMenuChoice::Undo :
            {
                undoFilter();
                break;
            }
            case mainMenuChoice::Redo :
            {
                redoFilter();
                break;
            }
            case mainMenuChoice::End :
            {
                isExit = true;

                cout << "Have You saved before exit? (Y/N) ";
                string answer = "";
                getline(cin, answer);

                if (!answer.empty() && (answer[0] == 'N' || answer[0] == 'n'))
                {
                    cout << "Do You Want to save your image? (Y/N) ";
                    string ans = "";
                    getline(cin, ans);
                    if (!ans.empty() && (ans[0] == 'Y' || ans[0] == 'y'))
                        image = saveImage();
                }
                cout << "Program Terminates Successfully. :)\n";
                break;
            }
            default :
            {
                cout << "Undefined choice, Please Try Again Later.\n";
                isExit = true;
                break;

            }
        }
    }

public:
    static void displayMainMenu()
    {
        cout << "\nWhat is in your Mind?\n";
        cout << "Choose The number corresponding to your choice: \n";
        cout << "[1]  Load a new Image.\n";
        cout << "[2]  Add Frame Filter\n";
        cout << "[3]  Add Film Frame Filter\n";
        cout << "[4]  BlackAndWhite Filter\n";
        cout << "[5]  Blur Filter\n";
        cout << "[6]  CelShading Filter\n";
        cout << "[7]  Crop Filter\n";
        cout << "[8]  DarkenOrLighten Filter\n";
        cout << "[9]  DetectEdge Filter\n";
        cout << "[10] Emboss Filter\n";
        cout << "[11] FishEye Filter\n";
        cout << "[12] Flip Filter\n";
        cout << "[13] Glitch Filter\n";
        cout << "[14] GrayScale Filter\n";
        cout << "[15] Invert Filter\n";
        cout << "[16] Merge Filter\n";
        cout << "[17] Midnight Filter\n";
        cout << "[18] Natural Sunlight Filter\n";
        cout << "[19] Oil Painting Filter\n";
        cout << "[20] Old TV Filter\n";
        cout << "[21] PixelArt Filter\n";
        cout << "[22] Purpling Filter\n";
        cout << "[23] RedScale Filter\n";
        cout << "[24] Resize Filter\n";
        cout << "[25] Rotate Filter\n";
        cout << "[26] Sharpen Filter\n";
        cout << "[27] Skew Filter\n";
        cout << "[28] Save the image.\n";
        cout << "[29] Undo the Filter.\n";
        cout << "[30] Redo the Filter.\n";
        cout << "[31] Exit\n";
        performMainMenuChoice((mainMenuChoice)InputValidation::readIntNumberBetween(1, 31, "Please Enter a number between 1 and 31"));
    }

    static void beginProgram()
    {
        image = loadImage();
    }
};

int main()
{
    Main::beginProgram();
    while(!isExit)
    {
        Main::displayMainMenu();
    }
}

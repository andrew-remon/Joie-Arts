#include "filters_class.h"
#include "Image_Class.h"
#include <stack>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
using namespace std ;

Image currentImage;
Image secondImage;
std::stack <Image> stUndo;
std::stack <Image> stRedo;
choice::FlipFilter Flip_key;
choice::RotationAngle Rotation_key;
choice::mode Mode_key;

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

    static Image nearestNeighborResize(Image &image, int newWidth, int newHeight) {
        Image resized(newWidth, newHeight);

        float i_ratio = (float)image.width / newWidth;
        float j_ratio = (float)image.height / newHeight;

        for (int i = 0; i < newWidth; i++) {
            for (int j = 0; j < newHeight; j++) {
                int n_i = (int)(i * i_ratio + 0.5f); // n = nearest
                int n_j = (int)(j * j_ratio + 0.5f);

                n_i = min(image.width  - 1, max(0, n_i));
                n_j = min(image.height - 1, max(0, n_j));

                for (int k = 0; k < 3; k++) {
                    resized(i, j, k) = image(n_i, n_j, k);
                }
            }
        }
        return resized;
    }

    static Image lighten(Image &image , float strength = 1.5f) {
        for (int i = 0 ; i < image.width ; i++) {
            for (int j = 0 ; j < image.height ; j++) {
                for (int k = 0 ; k < image.channels ; k++) {
                    if (image(i, j, k) * strength  > 255) { image(i, j, k) = 255;}
                    else{ image(i, j, k) = image(i, j, k) * strength;}
                }
            }
        }
        return image;
    }

    static Image darken(Image &image , float strength = 0.5f) {
        for (int i = 0 ; i < image.width ; i++) {
            for (int j = 0 ; j < image.height ; j++) {
                for (int k = 0 ; k < image.channels ; k++) {
                    if (image(i, j, k) * strength  > 255) { image(i, j, k) = 255;}
                    else{ image(i, j, k) = image(i, j, k) * strength;}
                }
            }
        }
        return image;
    }

    static Image scanLines(Image &image , float freq = 3.14f) {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                float factor = 0.7f + 0.3f * sin ((float)j * freq * 3.14159f / image.height);
                for (int k = 0; k < 3; k++) {
                    image(i, j, k) = image(i, j, k) * factor;
                }
            }
        }
        return image;
    }

public:

    static Image Filter_Hue(Image &image , float Red = 1.0f , float Green = 1.0f , float Blue = 1.0f ) {

        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {

                float val = image(i,j,0) *(Red/255);
                if (val > 255) {val = 255;}
                image (i , j , 0) = val;

                val = image(i,j,1) *(Green/255);
                if (val > 255) {val = 255;}
                image (i , j , 1) = val;

                val = image(i,j,2) *(Blue/255);
                if (val > 255) {val = 255;}
                image (i , j , 2) = val;
            }
        }
        return image;
    }

    static Image vignette(Image &image , float strength = 0.8f) {
        float center_x = image.width/ 2.0f  , center_y = image.height/ 2.0f;
        float max_distance = sqrt(center_x * center_x + center_y * center_y);

        for (int i = 0; i < image.width; i++) {
            for(int j = 0; j < image.height; j++) {
                float distance = sqrt((i - center_x) * (i - center_x) + (j - center_y) * (j - center_y));
                float factor = 1 - strength * (distance/max_distance);

                if (factor < 0) factor = 0;
                for (int k = 0; k < 3; k++) {
                    image (i , j , k) = image(i,j,k) * factor;
                }
            }
        }
        return image;
    }

    static Image noise(Image &image, int amount = 20) {

        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
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

    static Image contrast(Image &image , float strength ) {
        float factor = 1.0f + strength;
        Image contrasted(image.width, image.height);
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    float val = ((image(i, j, k) -128)* factor ) + 128;
                    val = max(0.0f,min(255.0f,val));
                    contrasted(i, j, k) = val;
                }
            }
        }
        return contrasted;
    }

    static Image gamma(Image &image, float gamma = 1.0f) {
        for (int i = 0 ; i < image.width ; i++) {
            for (int j = 0 ; j < image.height ; j++) {
                for (int k = 0 ; k < image.channels ; k++) {
                    float val = 255 * pow( (float)(image(i,j,k)/255.0f) , gamma);
                    val = max(0.0f,min(255.0f,val));
                    image(i,j,k) = val;
                }
            }
        }
        return image;
    }

    static Image grayscaleFilter(Image& image)
    {
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                unsigned int avg = 0;
                for (int k = 0; k < image.channels; ++k)
                    avg += image(i, j, k);

                avg /= image.channels;
                for (int k = 0; k < image.channels; ++k)
                    image(i, j, k) = avg;
            }
        }
        return image;
    }

    static Image blackAndWhiteFilter(Image& image)
    {
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                unsigned int avg = 0;
                for (int k = 0; k < image.channels; ++k)
                    avg += image(i, j, k);

                avg = avg / image.channels;

                if (avg > 255 / 2)
                {
                    for (int k = 0; k < image.channels; ++k)
                        image(i, j, k) = 255;
                }
                else
                {
                    for (int k = 0; k < image.channels; ++k)
                        image(i, j, k) = 0;
                }
            }
        }
        return image;
    }

    static Image invertFilter(Image& image)
    {
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < image.channels; ++k)
                    image(i, j, k) = 255 - image(i, j, k);
            }
        }
        return image;
    }

    static Image flipFilter(Image& image , choice::FlipFilter x)
    {
        Image flippedImage(image.width, image.height);
        switch(x){
        case choice::FlipFilter::Horizontal:
        {
            for (int i = 0; i < image.width; i++)
            {
                for (int j = 0; j < image.height; j++)
                {
                    for (int k = 0; k < image.channels; k++)
                        flippedImage(i, j, k) = image(image.width - 1 - i, j, k);
                }
            }
        }
        break;
        case choice::FlipFilter::Vertical:
        {
            for (int i = 0; i < image.width; i++)
            {
                for (int j = 0; j < image.height; j++)
                {
                    for (int k = 0; k < image.channels; k++)
                        flippedImage(i, j, k) = image(i, image.height - 1 - j, k);
                }
            }
        }
        break;
        }
        return flippedImage;
    }

    static Image rotateFilter(Image& image , choice::RotationAngle y)
    {


        Image rotatedImage;

        if (y == choice::RotationAngle::_90degrees)
        {
            rotatedImage = Image(image.height, image.width);
            for (int i = 0; i < image.width; i++)
            {
                for (int j = 0; j < image.height; j++)
                {
                    for (int k = 0; k < image.channels; k++)
                        rotatedImage(j, image.width - 1 - i, k) = image(i, j, k);
                }
            }
        }
        else if (y ==choice::RotationAngle::_180degrees)
        {
            rotatedImage = Image(image.width, image.height);

            for (int i = 0; i < image.width; i++)
            {
                for (int j = 0; j < image.height; j++)
                {
                    for (int k = 0; k < image.channels; k++)
                        rotatedImage(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                }
            }
        }
        else if (y == choice::RotationAngle::_270degrees)
        {
            rotatedImage = Image(image.height, image.width);
            for (int i = 0; i < image.width; i++)
            {
                for (int j = 0; j < image.height; j++)
                {
                    for (int k = 0; k < image.channels; k++)
                        rotatedImage(image.height - 1 - j, i, k) = image(i, j, k);
                }
            }
        }

        return rotatedImage;
    }

    static Image darkenOrLightenFilter(Image& image , float strength)
    {

        if (strength < 1.0f)
        {
            darken(image, strength);
        }
        else if (strength >= 1.0f)
        {
            lighten(image , strength);
        }

        return image;
    }

    static Image resizeFilter(const Image& image  ,int newWidth ,int newHeight)
    {
        string widthInput, heightInput;


        Image output(newWidth, newHeight);

        double scaleX = (double)image.width / newWidth;
        double scaleY = (double)image.height / newHeight;

        for (int j = 0; j < newHeight; j++)
        {
            for (int i = 0; i < newWidth; i++)
            {
                double x_in = i * scaleX;
                double y_in = j * scaleY;

                int x_base = (int)floor(x_in) - 1;
                int y_base = (int)floor(y_in) - 1;

                double dx = x_in - floor(x_in);
                double dy = y_in - floor(y_in);

                for (int k = 0; k < image.channels; k++)
                {
                    double p[4][4];
                    for (int m = 0; m < 4; m++)
                    {
                        for (int n = 0; n < 4; n++)
                        {
                            int xx = std::clamp(x_base + n, 0, image.width - 1);
                            int yy = std::clamp(y_base + m, 0, image.height - 1);
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
                {-1,  8, -1},
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

                        val = max(0.0f, min(255.0f, val));
                        detected(i-1, j-1, k) = 255 - val;
                    }
                }
            }

            return detected;
        }

    static Image addFrameFilter(Image &image , int thickness =5, unsigned int R = 255, unsigned int G =255, unsigned int B=255)
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

    static Image addFilmFrameFilter(Image &image){

        int minDim = min(image.width, image.height);
        int thickness = max(10, minDim / 30);
        int holeSize = max(5, minDim / 60);
        int holeSpacing = max(8, minDim / 40);

        Image framed(image.width, image.height);
        image = addFrameFilter(image , thickness + thickness/2,0,0,0);
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {

                bool isFrame = (j < thickness) || (j >= image.height - thickness);
                if (j < thickness && (i % (holeSize + holeSpacing) < holeSize)){
                    isFrame = false;
                }
                if (j >= image.height - thickness && (i % (holeSize + holeSpacing) < holeSize)) {
                    isFrame = false;
                }
                if (isFrame) {
                    for (int k = 0; k < 3; k++) {
                        framed(i, j, k) = 190;
                    }
                }
                else {
                    for (int k = 0; k < 3; k++) {
                        framed(i, j, k) = image(i, j, k);
                    }
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

        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {

                bool isOuterFrame = (i < outerThickness) || (i >= w - outerThickness) ||
                                    (j < outerThickness) || (j >= h - outerThickness);

                bool isInnerFrame = (i >= outerThickness + gap && i < outerThickness + gap + innerThickness) ||
                                    (i >= w - (outerThickness + gap + innerThickness) && i < w - (outerThickness + gap)) ||
                                    (j >= outerThickness + gap && j < outerThickness + gap + innerThickness) ||
                                    (j >= h - (outerThickness + gap + innerThickness) && j < h - (outerThickness + gap));

                if (isOuterFrame || isInnerFrame) {
                    framed(i, j, 0) = R;
                    framed(i, j, 1) = G;
                    framed(i, j, 2) = B;
                }
                else {
                    framed(i, j, 0) = image(i, j, 0);
                    framed(i, j, 1) = image(i, j, 1);
                    framed(i, j, 2) = image(i, j, 2);
                }
            }
        }
        return framed;
    }

    static Image blurFilter(Image &image) {

        float kernel[3][3] = {
          {0.111, 0.111, 0.111},
          {0.111, 0.111, 0.111},
          {0.111, 0.111, 0.111}    };

        Image blurred(image.width, image.height);
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    blurred(i,j,k) =
                            image              (max(i-1 , 0) ,max(j-1 , 0), k) * kernel[0][0]
                        +   image                          (i,max(j-1 , 0), k) * kernel[1][0]
                        +   image   (min(i+1,image.width-1) ,max(j-1 , 0) , k) * kernel[2][0]
                        +   image                           (max(i-1,0),j , k) * kernel[0][1]
                        +   image                                     (i,j, k) * kernel[1][1]
                        +   image               (min(i+1,image.width-1) ,j, k) * kernel[2][1]
                        +   image   (max(i-1 , 0) ,min(j+1,image.height-1), k) * kernel[0][2]
                        +   image               (i,min(j+1,image.height-1), k) * kernel[1][2]
                        +   image   (min(i+1 ,image.width-1),min(j+1,image.height-1), k) * kernel[2][2];
                }
            }
        }
        return blurred;
    }

    static Image mergeFilter(Image &image , Image second_image, int key)
    {
        int width;
        int heigth;

        switch (key){
        case 1:
            width = max(image.width, second_image.width);
            heigth = max(image.height, second_image.height);
            second_image = nearestNeighborResize(second_image, width, heigth);
            image = nearestNeighborResize(image, width, heigth);
            break;
        case 2:
            width = min(image.width, second_image.width);
            heigth = min(image.height, second_image.height);
            break;
        }


        Image merged(width, heigth);

        float alpha = 0.5;
        float beta = 1 - alpha;
        float constant = 0;

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < heigth; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    merged(i, j, k) = alpha*image(i, j, k)
                    + beta*second_image(i, j, k) + constant;
                }
            }
        }

        return merged;
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

        Image oiled_up(image.width, image.height);

        for (int i = radius; i < image.width - radius; i++)
        {
            for (int j = radius; j < image.height - radius; j++)
            {
                int lvls = 256;
                vector <int> intensityCount (lvls) ;
                vector <int> sumR(lvls);
                vector <int> sumG(lvls);
                vector <int> sumB(lvls);

                for (int n_i = -radius ; n_i <= radius ; n_i++)
                {
                    for (int n_j = -radius ; n_j <= radius ; n_j++)
                    {
                        int r = image (i+n_i, j+n_j , 0);
                        int g = image(i+n_i, j+n_j , 1);
                        int b = image(i+n_i, j+n_j , 2);

                        int intensity = ((r + g + b) * (lvls -1)) / 765;
                        if (intensity >= lvls) intensity = lvls - 1;
                        intensityCount[intensity]++;

                        sumR [intensity] += r;
                        sumG [intensity] += g;
                        sumB [intensity] += b;
                    }
                }

                int maxCount = 0, maxIndex = 0;

                for (int k = 0; k < lvls; k++)
                {
                    if (intensityCount[k] > maxCount)
                    {
                        maxCount = intensityCount[k];
                        maxIndex = k;
                    }
                }

                if (maxCount > 0)
                {
                    oiled_up(i,j,0) = sumR[maxIndex] / maxCount;
                    oiled_up(i,j,1) = sumG[maxIndex] / maxCount;
                    oiled_up(i,j,2) = sumB[maxIndex] / maxCount;
                }
                else
                {
                    oiled_up(i,j,0) = image(i,j,0);
                    oiled_up(i,j,1) = image(i,j,1);
                    oiled_up(i,j,2) = image(i,j,2);
                }
            }
        }

        return oiled_up;
    }

    static Image naturalSunLightFilter(Image &image)
    {
        image = lighten(image,1.1);
        image = contrast(image ,1.0);

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

    static Image cropFilter(Image &image ,int x = 0, int y = 0, int w = 0, int h = 0 )
    {
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

    static Image infraRed(Image &image) {

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

    static Image midNight(Image &image) {

        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {

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

    static Image Skew(Image &image, float degree = 40.0f) {

        if (degree >=0){
        float rad = degree * M_PI / 180.0f;
        float skewFactor = tan(rad);
        int baseOffset = image.height * skewFactor;

        int newWidth = image.width + abs(baseOffset);
        int newHeight = image.height;

        Image skewed(newWidth, newHeight);

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                int offsetX = -j * skewFactor + baseOffset;
                int newX = i + offsetX;

                if (newX >= 0 && newX < newWidth) {
                    for (int k = 0; k < image.channels; ++k) {
                        skewed(newX, j, k) = image(i, j, k);
                    }
                }
            }
        }
        return skewed;
        }else{
            float rad = -degree * M_PI / 180.0f;
            float skewFactor = tan(rad);
            int baseOffset = image.height * skewFactor;

            int newWidth = image.width + abs(baseOffset);
            int newHeight = image.height;

            Image skewed(newWidth, newHeight);

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    int offsetX = j * skewFactor  ;
                    int newX = i + offsetX;

                    if (newX >= 0 && newX < newWidth) {
                        for (int k = 0; k < image.channels; ++k) {
                            skewed(newX, j, k) = image(i, j, k);
                        }
                    }
                }
            }
            return skewed;
        }
    }

    static Image Filter_Emboss(Image &image) {
        float kernel[3][3] = {
            {-2, -1,  0},
            {-1,  1,  1},
            { 0,  1,  2}
        };

        Image embossed(image.width, image.height);

        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    float val =
                        image (max(i-1 , 0)           ,max(j-1 , 0)           , k) * kernel[0][0]
                        +   image (i                          ,max(j-1 , 0)           , k) * kernel[1][0]
                        +   image (min(i+1,image.width-1) ,max(j-1 , 0)           , k) * kernel[2][0]
                        +   image (max(i-1,0)             ,j                          , k) * kernel[0][1]
                        +   image (i                          ,j                          , k) * kernel[1][1]
                        +   image (min(i+1,image.width-1) ,j                          , k) * kernel[2][1]
                        +   image (max(i-1 , 0)           ,min(j+1,image.height-1), k) * kernel[0][2]
                        +   image (i                          ,min(j+1,image.height-1), k) * kernel[1][2]
                        +   image (min(i+1 ,image.width-1),min(j+1,image.height-1), k) * kernel[2][2];

                    val = max(0.0f, min(255.0f, val));
                    embossed(i, j, k) = val;
                }
            }
        }
        return embossed;
    }

    static Image Filter_FishEye_Vignette(Image &image, float vignette_strength = 0.8f) {
        Image result(image.width, image.height);

        float centerX = image.width / 2.0f;
        float centerY = image.height / 2.0f;
        float radius = min(centerX, centerY);

        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                float x = (i - centerX) / radius;
                float y = (j - centerY) / radius;
                float r = sqrt(x * x + y * y);

                float srcX = i;
                float srcY = j;

                if (r < 1.0f) {
                    float new_r = (r + (1 - sqrt(1 - r * r))) / 2.0f;
                    float theta = atan2(y, x);
                    srcX = centerX + new_r * radius * cos(theta);
                    srcY = centerY + new_r * radius * sin(theta);
                }

                for (int k = 0; k < image.channels; k++) {
                    result(i, j, k) = image(
                        max(0, min(image.width-1,(int)srcX )),
                        max(0, min(image.height-1,(int)srcY )), k);
                }
            }
        }
        result = vignette(result);
        return result;
    }

    static Image Filter_Cel_Shading(Image &image, int color_levels = 8) {
        Image result(image.width, image.height);

        float step = 255.0f / (color_levels - 1);

        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    float val = image(i, j, k);
                    val = round(val / step) * step;
                    result(i, j, k) = max(0.0f,min(255.0f, val));
                }
            }
        }

        return result;
    }

    static Image Filter_Glitch(Image &image, int max_shift = 5) {
        for (int i = 0; i < image.width; i++) {
            int shiftR = rand() % (2 * max_shift + 1) - max_shift;
            int shiftG = rand() % (2 * max_shift + 1) - max_shift;
            int shiftB = rand() % (2 * max_shift + 1) - max_shift;

            for (int j = 0; j < image.height; j++) {   // src = source
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

    static Image PixelArt(Image &image) {
        int factor = 4;
        if (image.width > 1500 && image.height > 1500) {
            factor = 8;
        }
        if (image.width > 3000 && image.height > 3000) {
            factor = 16;
        }
        int org_width = image.width , org_height = image.height;
        image = nearestNeighborResize(image , image.width /factor , image.height/factor);
        image = nearestNeighborResize(image , org_width, org_height);
        return image;
    }

    static Image Filter_Sharpen(Image &image) {

        float kernel[3][3] = {
            {0 , -1,  0},
            {-1,  5, -1},
            {0 , -1,  0}
        };

        Image sharpened(image.width, image.height);
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    float val =
                        image (max(i-1 , 0)           ,max(j-1 , 0)           , k) * kernel[0][0]
                        +   image (i                          ,max(j-1 , 0)           , k) * kernel[1][0]
                        +   image (min(i+1,image.width-1) ,max(j-1 , 0)           , k) * kernel[2][0]
                        +   image (max(i-1,0)             ,j                          , k) * kernel[0][1]
                        +   image (i                          ,j                          , k) * kernel[1][1]
                        +   image (min(i+1,image.width-1) ,j                          , k) * kernel[2][1]
                        +   image (max(i-1 , 0)           ,min(j+1,image.height-1), k) * kernel[0][2]
                        +   image (i                          ,min(j+1,image.height-1), k) * kernel[1][2]
                        +   image (min(i+1 ,image.width-1),min(j+1,image.height-1), k) * kernel[2][2];

                    val = max(0.0f, min(255.0f, val));
                    sharpened(i, j, k) = val;
                }
            }
        }
        return sharpened;
    }

    static void undoFilter()
    {
        if (stUndo.size() > 1) {
            stRedo.push(currentImage);
            currentImage = stUndo.top();
            stUndo.pop();
        }


    }

    static void redoFilter()
    {

        if (!stRedo.empty()) {
            stUndo.push(currentImage);
            currentImage = stRedo.top();
            stRedo.pop();
        }
};
};

void Filters_Class::updatePreview()
{
    qDebug() << "Current image size:" << currentImage.width << "x" << currentImage.height;
    QImage qimg(currentImage.width, currentImage.height, QImage::Format_RGB888);

    for (int y = 0; y < currentImage.height; ++y)
    {
        for (int x = 0; x < currentImage.width; ++x)
        {
            int r = currentImage(x, y, 0);
            int g = currentImage(x, y, 1);
            int b = currentImage(x, y, 2);
            qimg.setPixelColor(x, y, QColor(r, g, b));
        }
    }

    QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QDir().mkpath(tempPath);
    tempPath += "/applied_filter.png";

    bool saved = qimg.save(tempPath);
    qDebug() << "Saving preview to:" << tempPath << "Result:" << saved;

    m_imageSource = QUrl(QString("file:///%1?time=%2").arg(tempPath).arg(QDateTime::currentMSecsSinceEpoch()));
    emit imageSourceChanged();
}

QUrl Filters_Class::imageSource() const
{
    return m_imageSource;
}

Filters_Class::Filters_Class(QObject *parent) {

}

void Filters_Class::loadImage(const QString &path)
{
    qDebug() << "Loading image from path:" << path;
    QString localPath = path;
    if (path.startsWith("file:///"))
        localPath = QUrl(path).toLocalFile();

    m_imageSource = QUrl::fromLocalFile(localPath);
    m_image.load(localPath);

    std::string cppPath = localPath.toStdString();
    currentImage.loadNewImage(cppPath);
    while (!stUndo.empty()) stUndo.pop();
    while (!stRedo.empty()) stRedo.pop();
    stUndo.push(currentImage);

    qDebug() << "Loaded image with size:" << currentImage.width << "x" << currentImage.height;
    emit imageSourceChanged();

}
void Filters_Class::loadSecondImage(const QString &path)
{
    qDebug() << "Loading second image from path:" << path;
    QString localPath = path;
    if (path.startsWith("file:///"))
        localPath = QUrl(path).toLocalFile();

    std::string cppPath = localPath.toStdString();
    secondImage.loadNewImage(cppPath);

    qDebug() << "Second image loaded with size:" << secondImage.width << "x" << secondImage.height;
}
void Filters_Class::applyGrayscale()
{
    qDebug() << "Applying grayscale filter...";
    stUndo.push(currentImage);
    Filter::grayscaleFilter(currentImage);
    updatePreview();}
void Filters_Class::saveImage(const QString &path)
{
    QUrl url(path);
    QString localPath = url.toLocalFile();
    currentImage.saveImage(localPath.toStdString());
    qDebug() << "Saved image to" << localPath;
}
void Filters_Class::applyBnW()
{
    qDebug() << "Applying Black And White filter...";
    stUndo.push(currentImage);
    Filter::blackAndWhiteFilter(currentImage);
    updatePreview();}
void Filters_Class::applyInvert(){
    qDebug() << "Applying Inverting filter...";
    stUndo.push(currentImage);
    Filter::invertFilter(currentImage);
    updatePreview();
};
void Filters_Class::applyFlipFilter(int key){
    qDebug() << "FLipping Image...";
    stUndo.push(currentImage);
    qDebug() << key ;
    currentImage = Filter::flipFilter(currentImage , static_cast<choice::FlipFilter>(key));
    updatePreview();
};
void Filters_Class::applyDarkenOrLighten(float x){
    qDebug() << "Applying Darken Or Lighten filter...";
    stUndo.push(currentImage);
    Filter::darkenOrLightenFilter(currentImage , x);
    updatePreview();
};
void Filters_Class::applyRotatefilter(int key){
    qDebug() << "Rotating Image...";
    stUndo.push(currentImage);
    currentImage = Filter::rotateFilter(currentImage , static_cast<choice::RotationAngle>(key));
    updatePreview();
};
void Filters_Class::applyResizeFilter(){

};
void Filters_Class::applyInfraRedFilter(){

};
void Filters_Class::applyCropFilter(){

};
void Filters_Class::applyEdgeDetetction(){
    qDebug() << "Detecting Image's Edges...";
    stUndo.push(currentImage);
    currentImage = Filter::detectBlackEdgeFilter(currentImage);
    updatePreview();
};
void Filters_Class::applyBlur(){
    qDebug() << "Blurring Image...";
    stUndo.push(currentImage);
    currentImage = Filter::blurFilter(currentImage);
    updatePreview();
};
void Filters_Class::applyTVstatic(){
    qDebug() << "Applying Old Tv Static Filter...";
    stUndo.push(currentImage);
    currentImage = Filter::oldTVFilter(currentImage);
    updatePreview();
}
void Filters_Class::applyOilFilter(){
    qDebug() << "Applying Oil Painting Filter...";
    stUndo.push(currentImage);
    currentImage = Filter::oilPaintingFilter(currentImage);
    updatePreview();
}
void Filters_Class::applyNaturalSunlight(){
    qDebug() << "Applying Sunny Filter...";
    stUndo.push(currentImage);
    currentImage = Filter::naturalSunLightFilter(currentImage);
    updatePreview();
}
void Filters_Class::applyMergeFilter(int key){
    qDebug() << "Merging Images...";
    stUndo.push(currentImage);
    currentImage = Filter::mergeFilter(currentImage , secondImage , key);
    updatePreview();
}
void Filters_Class::undo(){
    qDebug() << "Undoing Latest Edit...";
    Filter::undoFilter();
    updatePreview();
}
void Filters_Class::redo(){
    qDebug() << "Redoing latest Edit...";
    Filter::redoFilter();
    updatePreview();

}
void Filters_Class::resize(int x , int y){
    qDebug() <<"Resizing Image...";
    stUndo.push(currentImage);
    currentImage=Filter::resizeFilter(currentImage, x , y);
    updatePreview();
};
void Filters_Class::crop(int x , int y , int w , int h){
    qDebug() <<"Cropping Image...";
    stUndo.push(currentImage);
    currentImage=Filter::cropFilter(currentImage, x , y , w , h);
    updatePreview();
}
void Filters_Class::applyInfraRed(){
    qDebug() << "Applying InfraRed Filter...";
    stUndo.push(currentImage);
    currentImage = Filter::infraRed(currentImage);
    updatePreview();
};
void Filters_Class::applyMidNight(){
    qDebug() << "Applying Midnight effect...";
    stUndo.push(currentImage);
    currentImage = Filter::midNight(currentImage);
    updatePreview();
};
void Filters_Class::skewImage(float x){
    qDebug() << "Skewing Image...";
    stUndo.push(currentImage);
    currentImage = Filter::Skew(currentImage , x);
    updatePreview();
};
void Filters_Class::applyGamma(float x){
    qDebug() << "Applying Gamma Change...";
    stUndo.push(currentImage);
    currentImage = Filter::gamma(currentImage , x);
    updatePreview();

};
void Filters_Class::applyContrast(float x){
    qDebug() << "Applying Contrast Change...";
    stUndo.push(currentImage);
    currentImage = Filter::contrast(currentImage , x);
    updatePreview();
};
void Filters_Class::applyHue(float x , float y , float z){
    qDebug() << "Applying Hue Change...";
    stUndo.push(currentImage);
    currentImage = Filter::Filter_Hue(currentImage , x , y, z);
    updatePreview();
};

void Filters_Class::applyVignette(float x){
    qDebug() << "Applying Vignette Change...";
    stUndo.push(currentImage);
    currentImage = Filter::vignette(currentImage , x);
    updatePreview();
};
void Filters_Class::applyNoise(float x){
    qDebug() << "Applying Noise Change...";
    stUndo.push(currentImage);
    currentImage = Filter::noise(currentImage , x);
    updatePreview();
};
void Filters_Class::applyFishEye(){
    qDebug() << "Applying Noise Change...";
    stUndo.push(currentImage);
    currentImage = Filter::Filter_FishEye_Vignette(currentImage);
    updatePreview();
};
void Filters_Class::applyToonyEffect(){
    qDebug() << "Applying Toon Change...";
    stUndo.push(currentImage);
    currentImage = Filter::Filter_Cel_Shading(currentImage);
    updatePreview();
};
void Filters_Class::applyEmboss(){
    qDebug() << "Applying Emboss Change...";
    stUndo.push(currentImage);
    currentImage = Filter::Filter_Emboss(currentImage);
    updatePreview();
};
void Filters_Class::applyFrame(int frameType , int thickness , int inner=0 , int gap=0 ,unsigned int R=255 , unsigned int G =255, unsigned int B=255 ){
    qDebug() << "Adding Frame.....";
    stUndo.push(currentImage);
    switch(frameType){
    case 1:
        currentImage = Filter::addFrameFilter(currentImage , thickness , R , G , B);
        break;
    case 2:
        currentImage = Filter::addFilmFrameFilter(currentImage);
        break;
    case 3:
        currentImage = Filter::addDoubleFrameFilter(currentImage , thickness , inner, gap , R ,G , B );
        break;
    }
    updatePreview();
}
void Filters_Class::applyGlitch(){
    qDebug() << "Applying Glitch effect...";
    stUndo.push(currentImage);
    currentImage = Filter::Filter_Glitch(currentImage);
    updatePreview();
}

void Filters_Class::applyPixelArt(){
    qDebug() << "Applying PixelArt effect...";
    stUndo.push(currentImage);
    currentImage = Filter::PixelArt(currentImage);
    updatePreview();
}
void Filters_Class::sharpen(){
    qDebug() << "Sharpening Image...";
    stUndo.push(currentImage);
    currentImage = Filter::Filter_Sharpen(currentImage);
    updatePreview();
}
void Filters_Class::applyNightyeffect(){
    qDebug() << "Nighty effect...";
    stUndo.push(currentImage);
    currentImage = Filter::darkenOrLightenFilter(currentImage , 0.5f);
    currentImage = Filter::midNight(currentImage);
    currentImage = Filter::infraRed(currentImage);
    currentImage = Filter::invertFilter(currentImage);
    updatePreview();
}

void Filters_Class::reset(){
    if (!stUndo.empty()){
    while (stUndo.size() != 1) stUndo.pop();
    currentImage = stUndo.top();
    while (!stRedo.empty()) stRedo.pop();
    updatePreview();
    }
}

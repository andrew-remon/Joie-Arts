#include <iostream>
#include <string>
#include <algorithm> // for clamp in resize filter
#include <cmath>  // for floor in resize filter
#include "Image_Class.h"
using namespace std;

bool isExit = false;
static Image image;

enum mainMenuChoice
{
    load = 1,
    Grayscale = 2, BlackAndWhite = 3, Invert = 4,
    Flip = 5, Rotate = 6, DarkenOrLighten = 7, Resize = 8,
    save = 9, end = 10
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

        int x = InputValidation::readIntNumber();

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

        int x = InputValidation::readIntNumber();

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
        cout << "Do you want to Darken or Lighten it?" << endl;
        cout << "Enter 1 to Darken and 2 to Lighten" << endl;

        int x = InputValidation::readIntNumber();

        if (x == 1)
        {
            for (int i = 0 ; i < image.width ; i++)
            {
                for (int j = 0 ; j < image.height ; j++)
                {
                    for (int k = 0 ; k < image.channels ; k++)
                        image(i, j, k) = image(i, j, k) * 0.5;
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
                    {
                        if (image(i, j, k) * 1.5 > 255) image(i, j, k) = 255;
                        else image(i, j, k) = image(i, j, k) *1.5;
                    }
                }
            }
        }
        else
        {
            cout << "Error , invalid input" << endl;
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
                double x_in = i * scaleX;
                double y_in = j * scaleY;

                int x_base = (int)floor(x_in) - 1;
                int y_base = (int)floor(y_in) - 1;

                double dx = x_in - floor(x_in);
                double dy = y_in - floor(y_in);

                for (int k = 0; k < image.channels; k++) // R,G,B loop
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

};

class Main
{
private:

    static Image loadImage()
    {
        bool isFound = false;
        do
        {
            string filename;
            try
            {
                cout << "Please enter an image: ";
                getline(cin, filename);

                image = Image(filename);
                isFound = true;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                cout << "\nImage Not Found, Please Try Again.\n";
            }
        } while (!isFound);

        cout << "Image Loaded Successfully.\n";

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
        std::string ans;
        cout << "\nDo You want to save this filter? (Y/N) \n";
        getline(std::cin, ans);
        if (!ans.empty() && (ans[0] == 'Y' || ans[0] == 'y'))
            image = saveImage();
    }

    static void performMainMenuChoice(mainMenuChoice choice)
    {
        switch (choice)
        {
        case mainMenuChoice::load :
        {
            image = loadImage();
            displayMainMenu();
            break;
        }
        case mainMenuChoice::save :
        {
            image = saveImage();
            displayMainMenu();
            break;
        }
        case mainMenuChoice::Grayscale :
        {
            image = Filter::grayscaleFilter(image);
            applyFilter();
            displayMainMenu();
            break;
        }
        case mainMenuChoice::BlackAndWhite :
        {
            image = Filter::blackAndWhiteFilter(image);
            applyFilter();
            displayMainMenu();
            break;
        }
        case mainMenuChoice::Invert :
        {
            image = Filter::invertFilter(image);
            applyFilter();
            displayMainMenu();
            break;
        }
        case mainMenuChoice::Flip :
        {
            image = Filter::flipFilter(image);
            applyFilter();
            displayMainMenu();
            break;
        }
        case mainMenuChoice::Rotate :
        {
            image = Filter::rotateFilter(image);
            applyFilter();
            displayMainMenu();
            break;
        }
        case mainMenuChoice::Resize :
        {
            image = Filter::resizeFilter(image);
            applyFilter();
            displayMainMenu();
            break;
        }
        case mainMenuChoice::DarkenOrLighten :
        {
            image = Filter::darkenOrLightenFilter(image);
            applyFilter();
            displayMainMenu();
            break;
        }
        case mainMenuChoice::end :
        {
            isExit = true;

            char Answer;
            cout << "Have You saved before exit? (Y/N) ";
            cin >> Answer;

            if (tolower(Answer) == 'n')
            {
                char ans;
                cout << "Do You to save your image? (Y/N) ";
                cin >> ans;

                if (tolower(ans) == 'y') image = saveImage();
            }

            cout << "Program Terminates Successfully. :)\n";
            break;
        }
        default:
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
        cout << "[1] Load a new Image.\n";
        cout << "[2] GrayScale Filter\n";
        cout << "[3] BlackAndWhite Filter\n";
        cout << "[4] Invert Filter\n";
        cout << "[5] Flip Filter\n";
        cout << "[6] Rotate Filter\n";
        cout << "[7] DarkenOrLighten Filter\n";
        cout << "[8] Resize Filter\n";
        cout << "[9] Save the image.\n";
        cout << "[10] Exit\n";
        performMainMenuChoice((mainMenuChoice)InputValidation::readIntNumberBetween(1, 10, "Please Enter a number between 1 and 10"));
    }

    static void beginProgram()
    {
        image = loadImage();
        displayMainMenu();
    }
};


int main()
{
    while(!isExit)
    {
        Main::beginProgram();
    }
}

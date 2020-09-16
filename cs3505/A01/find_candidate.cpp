/*
 *  Author: Leon Tran
 *  Date: 8/31/2020
 *  Assignment 01
 *  
 *  I wrote this file from scratch by myself.
 */ 

// The c++ iostream library is used when console (or shell) I/O is needed.
#include <iostream>

// The c++ vector library, functions like an array.
#include <vector>

// The c++ fstream library is used when file I/O is needed.
#include <fstream>

// The c++ library that provides mathematical functions like square root, pow, etc.
#include <cmath>

//  The header file that define the struct pntvec
#include "pntvec.h"

/*
 *  Print the values of each dimension x,y,z of a pntvec object in a single line with single space between.
 * 
 *  Note: 
 *      -'const' because the parameter is read-only.
 *      -'&' because the parameter is passed by reference so that the program doesn't make a copy of it.
 * 
 *  Parameter: 
 *      -point: a 3D point to print to the console.
 * 
 *  Returns:
 *      -Nothing
 */ 
void printPoint(const pntvec& point)
{
    std::cout << point.x << " " << point.y << " " << point.z << "\n";
}

/**
 *  Compute the best fit point of the points from point_cloud text file from the given vector of candidate points 
 * 
 *  Notes:
 *      -'const' because the parameter is read-only.
 *      -'&' because the parameter is passed by reference so that the program doesn't make a copy of it.
 * 
 *  Parameters:
 *      -candidates: the vector of pntvec objects, which are the candidate points.
 *      -points: the vector of pntvec objects, which are the points in the point cloud.
 * 
 *  Returns:
 *      -bestFit: an object of type pntvec, which has the lowest fit score amongst the pntvec candidates.
 */
pntvec findBestFit(const std::vector<pntvec>& candidates, const std::vector<pntvec>& points)
{
    //  Initialize the lowest score with the highest possible double value
    double lowestScore = 1.79769e+308;

    //Declare the bestFit, which is the return of this method
    pntvec bestFit;

    //Loop the candidates vector, evaluate every single element
    for(int i = 0; i < candidates.size(); ++i)
    {
        //The current candidate variable
        pntvec curCandidate = candidates[i];

        //Instantiate the score of the current candidate with 0.0
        double score = 0.0;

        //Loop the points vector, which contains the points in the point cloud.
        for(int j = 0; j < points.size(); ++j)
        {
            //The current point in point cloud
            pntvec curPoint = points[j];

            // According to the formula, distance = square root ( (delta x)^2 + (delta y)^2 + (delta z)^2)
            double distance = std::sqrt((curCandidate.x - curPoint.x)*(curCandidate.x - curPoint.x)
                         + (curCandidate.y - curPoint.y)*(curCandidate.y - curPoint.y)
                         + (curCandidate.z - curPoint.z)*(curCandidate.z - curPoint.z));
            //According to the formula, the score = distance ^ 2
            score += std::pow(distance, 2.0);
        }
        //Compare the score with the lowest score and update the lowest score on the record, also update 
        //the bestFit pntvec object, which is the one with the lowest score
        if(score < lowestScore)
        {
            lowestScore = score;
            bestFit = curCandidate;
        }
    }
    //Print the lowest score
    std::cout << lowestScore << "\n";

    //Return the bestFit pntvec object
    return bestFit;
}


/**
 *  Collect Points from the file, which is the parameter
 * 
 *  Parameter: 
 *      -fileName, which is a pointer type char to the first character of the file name
 *  Returns:
 *      -points: a vector type pntvec which contains pntvec objects which are the points collected from the file.
 */
std::vector<pntvec> collectPointsFromFile(const char* fileName)
{
    //Vector contains points
    std::vector<pntvec> points;

    //Vector contains point coordinates, which are the double values read from the file
    std::vector<double> pointsCoords;

    //ifstream object, which is used to read the input file
    std::ifstream infile;

    //Open the file
    infile.open(fileName);

    //The arbitrary variable num that is used to store the double value read from the file
    double num;

    //While the file still has double value to read, assign such value to num
    while(infile >> num)
    {
        //Push the coordinate value to the pointsCoords vector
        pointsCoords.push_back(num);

        //When ever the size of the pointsCoords is divisible by 3, convert the last 3 values to a pntvec object
        //Then pass such object to the points vector.
        //We don't have to worry about the case where size = 0 because the line of code above ensure that this
        //procedure starts when the size is at least 1. Also because that the file is non-empty, given by the instructions.
        if(pointsCoords.size() % 3 == 0)
        {
            pntvec point;
            point.x = *(pointsCoords.end() - 3);
            point.y = *(pointsCoords.end() - 2);
            point.z = *(pointsCoords.end() - 1);
            points.push_back(point);
        }
    }
    //Close the infile stream
    infile.close();

    //Return the points vector
    return points;
}

/**
 *  Main -- the application entry point
 * 
 *  Returns:
 *      -an integer exit code, we return non-zero value if an error occured. 
 */
int main()
{
    // Instantiate the char* variables that contain the name of the files
    char* point_cloud_file = "point_cloud.txt";
    char* candidates_file = "candidates.txt";

    //The vector that contains the points in the point_cloud text file
    std::vector<pntvec> pointsCloud = collectPointsFromFile(point_cloud_file);

    //The vector that contains the points in the candidates text file
    std::vector<pntvec> candidates = collectPointsFromFile(candidates_file);

    //The bestFit point, calculated from the 2 vectors above by using findBestFit method
    pntvec bestFit = findBestFit(candidates,pointsCloud);

    //Print the pntvec bestFit
    printPoint(bestFit);
    return 0;
}
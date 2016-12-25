//***********************************************************************//
//
//	File Name:      main.cpp
//	Author:         Ramsundar K G (ramsundar@asu.edu, kgram007@gmail.com)
//	Date:           December 22, 2016
//
//	Description: C++ implementation of the paper:
//               "Eulerian Video Magnification for Revealing
//               Subtle Changes in the World", using OpenCV library
//
//***********************************************************************//

#include "EulerianMotionMag.h"

#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

int main(int argc, char **argv)
{
    string input_filename;
    string output_filename;
    int input_width;
    int input_height;
    int output_width;
    int output_height;
    double alpha;
    double lambda_c;
    double cutoff_freq_low;
    double cutoff_freq_high;
    double chrom_attenuation;
    double exaggeration_factor;
    double delta;
    double lambda;
    int levels;

    if (argc <= 1)
    {
        cerr << "Error: Input param filename must be specified!" << endl;
        return -1;
    }

    // Read input param file
    ifstream file(argv[1]);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open param file: " << string(argv[1]) << endl;
        return -1;
    }

    // Parse param file for getting parameter values
    po::options_description desc("Eulerian-Motion-Magnification");
    desc.add_options()
            ("help,h", "produce help message")
            ("input_filename", po::value<string>(&input_filename)->default_value( "" ))
            ("output_filename", po::value<string>(&output_filename)->default_value( "" ))
            ("input_width", po::value<int>(&input_width)->default_value( 0 ))
            ("input_height", po::value<int>(&input_height)->default_value( 0 ))
            ("output_width", po::value<int>(&output_width)->default_value( 0 ))
            ("output_height", po::value<int>(&output_height)->default_value( 0 ))
            ("alpha", po::value<double>(&alpha)->default_value( 20 ))
            ("lambda_c", po::value<double>(&lambda_c)->default_value( 16 ))
            ("cutoff_freq_low", po::value<double>(&cutoff_freq_low)->default_value( 0.05 ))
            ("cutoff_freq_high", po::value<double>(&cutoff_freq_high)->default_value( 0.4 ))
            ("chrom_attenuation", po::value<double>(&chrom_attenuation)->default_value( 0.1 ))
            ("exaggeration_factor", po::value<double>(&exaggeration_factor)->default_value( 2.0 ))
            ("delta", po::value<double>(&delta)->default_value( 0 ))
            ("lambda", po::value<double>(&lambda)->default_value( 0 ))
            ("levels", po::value<int>(&levels)->default_value( 5 ))
            ;
    po::variables_map vm;
    po::store(po::parse_config_file(file, desc), vm);
    po::notify(vm);

    // EulerianMotionMag
    EulerianMotionMag* motion_mag = new EulerianMotionMag();

    // Set params
    motion_mag->setInputFileName(input_filename);
    motion_mag->setOutputFileName(output_filename);
    motion_mag->setInputImgWidth(input_width);
    motion_mag->setInputImgHeight(input_height);
    motion_mag->setOutputImgWidth(output_width);
    motion_mag->setOutputImgHeight(output_height);
    motion_mag->setAlpha(alpha);
    motion_mag->setLambdaC(lambda_c);
    motion_mag->setCutoffFreqLow(cutoff_freq_low);
    motion_mag->setCutoffFreqHigh(cutoff_freq_high);
    motion_mag->setChromAttenuation(chrom_attenuation);
    motion_mag->setExaggerationFactor(exaggeration_factor);
    motion_mag->setDelta(delta);
    motion_mag->setLambda(lambda);
    motion_mag->setLapPyramidLevels(levels);

    // Init Motion Magnification object
    bool init_status = motion_mag->init();
    if (!init_status)
        return -1;

    // Run Motion Magnification
    motion_mag->run();

    // Exit
    delete motion_mag;
    return 0;
}


//*****************************************************************************
// Copyright 2016 Ramsundar K G. All Rights Reserved.
//
// This source code is licensed as defined by the LICENSE file found in the
// root directory of this source tree.
//
// Author: Ramsundar K G (kgram007@gmail.com)
//
// This file is a part of C++ implementation of Eulerian Motion Magnification
// adapted from https://github.com/wzpan/QtEVM
//
//*****************************************************************************

#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>

#include "eulerian_motion_mag.h"

namespace po = boost::program_options;

int main(int argc, char **argv)
{
    std::string input_filename;
    std::string output_filename;
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
        std::cerr << "Error: Input param filename must be specified!" << std::endl;
        return 1;
    }

    // Read input param file
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open param file: " << std::string(argv[1]) << std::endl;
        return 1;
    }

    // Parse param file for getting parameter values
    po::options_description desc("Eulerian-Motion-Magnification");
    desc.add_options()
        ("help,h", "produce help message")
        ("input_filename", po::value<std::string>(&input_filename)->default_value( "" ))  // NOLINT [whitespace/parens]
        ("output_filename", po::value<std::string>(&output_filename)->default_value( "" ))  // NOLINT [whitespace/parens]
        ("input_width", po::value<int>(&input_width)->default_value( 0 ))  // NOLINT [whitespace/parens]
        ("input_height", po::value<int>(&input_height)->default_value( 0 ))  // NOLINT [whitespace/parens]
        ("output_width", po::value<int>(&output_width)->default_value( 0 ))  // NOLINT [whitespace/parens]
        ("output_height", po::value<int>(&output_height)->default_value( 0 ))  // NOLINT [whitespace/parens]
        ("alpha", po::value<double>(&alpha)->default_value( 20 ))  // NOLINT [whitespace/parens]
        ("lambda_c", po::value<double>(&lambda_c)->default_value( 16 ))  // NOLINT [whitespace/parens]
        ("cutoff_freq_low", po::value<double>(&cutoff_freq_low)->default_value( 0.05 ))  // NOLINT [whitespace/parens]
        ("cutoff_freq_high", po::value<double>(&cutoff_freq_high)->default_value( 0.4 ))  // NOLINT [whitespace/parens]
        ("chrom_attenuation", po::value<double>(&chrom_attenuation)->default_value( 0.1 ))  // NOLINT [whitespace/parens]
        ("exaggeration_factor", po::value<double>(&exaggeration_factor)->default_value( 2.0 ))  // NOLINT [whitespace/parens]
        ("delta", po::value<double>(&delta)->default_value( 0 ))  // NOLINT [whitespace/parens]
        ("lambda", po::value<double>(&lambda)->default_value( 0 ))  // NOLINT [whitespace/parens]
        ("levels", po::value<int>(&levels)->default_value( 5 ))  // NOLINT [whitespace/parens]
    ;  // NOLINT [whitespace/semicolon]
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
        return 1;

    // Run Motion Magnification
    motion_mag->run();

    // Exit
    delete motion_mag;
    return 0;
}


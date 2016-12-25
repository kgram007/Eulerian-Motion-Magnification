//***********************************************************************//
//
//	File Name:		EulerianMotionMag.cpp
//	Author:			Ramsundar K G (ramsundar@asu.edu)
//	Date:			December 22, 2016
//
//	Description:	Header file for class EulerianMotionMag
//
//***********************************************************************//

#pragma once

#include "Timer.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <omp.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define DISPLAY_WINDOW_NAME     ("Motion Magnified Output")

class EulerianMotionMag
{
// Methods:
public:
    EulerianMotionMag();
    ~EulerianMotionMag();

    bool init();
    void run();

private:
    int getCodecNumber(std::string file_name);
    cv::Mat LaplacianPyr(cv::Mat img);
    bool buildLaplacianPyramid(const cv::Mat& img, const int levels, std::vector< cv::Mat >& pyramid);
    void reconImgFromLaplacianPyramid(const std::vector< cv::Mat >& pyramid, const int levels, cv::Mat& dst);
    void temporalIIRFilter(const cv::Mat& src, cv::Mat& dst, int level);
    void amplify(const cv::Mat& src, cv::Mat& dst, int level);
    void attenuate(cv::Mat& src, cv::Mat& dst);


// Properties:
public:
    const std::string& getInputFileName() const                         { return input_file_name_; }
    void setInputFileName(const std::string& inputFileName)             { input_file_name_ = inputFileName; }

    int getInputImgWidth() const                                        { return input_img_width_; }
    void setInputImgWidth(int width)                                    { input_img_width_ = width; }

    int getInputImgHeight() const                                       { return input_img_height_; }
    void setInputImgHeight(int height)                                  { input_img_height_ = height; }

    const std::string& getOutputFileName() const                        { return output_file_name_; }
    void setOutputFileName(const std::string& outputFileName)           { output_file_name_ = outputFileName; }

    int getOutputImgWidth() const                                       { return output_img_width_; }
    void setOutputImgWidth(int width)                                   { output_img_width_ = width; }

    int getOutputImgHeight() const                                      { return output_img_height_; }
    void setOutputImgHeight(int height)                                 { output_img_height_ = height; }

    double getAlpha() const                                             {return alpha_; }
    void setAlpha(double alpha)                                         {alpha_ = alpha; }

    double getChromAttenuation() const                                  {return chrom_attenuation_; }
    void setChromAttenuation(double chromAttenuation)                   {chrom_attenuation_ = chromAttenuation; }

    double getCutoffFreqHigh() const                                    {return cutoff_freq_high_; }
    void setCutoffFreqHigh(double cutoffFreqHigh)                       {cutoff_freq_high_ = cutoffFreqHigh; }

    double getCutoffFreqLow() const                                     {return cutoff_freq_low_; }
    void setCutoffFreqLow(double cutoffFreqLow)                         {cutoff_freq_low_ = cutoffFreqLow; }

    double getDelta() const                                             {return delta_; }
    void setDelta(double delta)                                         {delta_ = delta; }

    double getExaggerationFactor() const                                {return exaggeration_factor_; }
    void setExaggerationFactor(double exaggerationFactor)               {exaggeration_factor_ = exaggerationFactor; }

    double getLambda() const                                            {return lambda_; }
    void setLambda(double lambda)                                       {lambda_ = lambda; }

    double getLambdaC() const                                           {return lambda_c_; }
    void setLambdaC(double lambdaC)                                     {lambda_c_ = lambdaC; }

    int getLapPyramidLevels() const                                     { return lap_pyramid_levels_; }
    void setLapPyramidLevels(int lapPyramidLevels)                      { lap_pyramid_levels_ = lapPyramidLevels; }

private:
    std::string input_file_name_;
    std::string output_file_name_;

    int input_img_width_;
    int input_img_height_;
    cv::VideoCapture* input_cap_;

    int output_img_width_;
    int output_img_height_;
    cv::VideoWriter* output_cap_;
    bool write_output_file_;

    cv::Mat img_input_;
    cv::Mat img_input_lab_;
    cv::Mat img_spatial_filter_;
    cv::Mat img_motion_;
    cv::Mat img_motion_mag_;
    std::vector< cv::Mat > img_vec_lap_pyramid_;
    std::vector< cv::Mat > img_vec_lowpass_1_;
    std::vector< cv::Mat > img_vec_lowpass_2_;
    std::vector< cv::Mat > img_vec_filtered_;

    int lap_pyramid_levels_;
    double cutoff_freq_low_;
    double cutoff_freq_high_;
    double lambda_c_;
    double alpha_;
    double chrom_attenuation_;
    double exaggeration_factor_;
    double delta_;
    double lambda_;

    Timer timer_;
    double loop_time_ms_;
    int frame_num_;
    int frame_count_;
    double input_fps_;
};

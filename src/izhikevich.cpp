#include <iostream>
#include <cstdlib>

#include<opencv2/highgui/highgui.hpp>

class IzhiNeuron{
    public:

        double v;
        double u;

        double a;
        double b;
        double c;
        double d;

        IzhiNeuron(){
            a = 0.02; // recovery value, lower values result in slower recovery
            b = 0.2;  // sensitivity of u to sub-threshold activation of v
            c = -65;  // mV, after reset membrane potential
            d = 2;    // after spike recovery of of u

            // set initial values
            v = c; // membrane potential, mV
            u = b*v; // recovery variable

        } 

        void step(double input, double step_ms){
            // spike recovery
            if( v >= 30 /* mV */ ){
                v = c;
                u = u + d;
            }

            // calculate membrane potential
            double v_delta = 0.04*v*v + 5*v + 140 - u + input;

            // calculate recovery variable
            double u_delta = step_ms * a * (b*v - u);

            // finer grained steps
            v_delta *= step_ms;
            u_delta *= step_ms;

            // set the new values
            v += v_delta;
            u += u_delta;
        }
};

int main(int argc, char **argv) {
    std::cout<<"Izhikevich neuron simulator\n\n";
    std::cout<<"Run with: ./izhikevich <a> <b> <c> <d>\n\n";
    std::cout<<"If no values are chosen, 0.02 0.2 -65 2 will be used\n\n";

    // initialize an Izhikevich neuron
    auto neur = new IzhiNeuron();

    // parse command line values
    if(argc > 1){ neur->a = std::atof(argv[1]); }
    if(argc > 2){ neur->b = std::atof(argv[2]); }
    if(argc > 3){ neur->c = std::atof(argv[3]); }
    if(argc > 4){ neur->d = std::atof(argv[4]); }


    int steps_n = 2000;
    double ms_per_step = 0.25;

    // output image
    cv::Mat img(240, steps_n, CV_8UC3, cv::Scalar(255,255,255));
    cv::Vec3b black(0,0,0);

    double input = 0;
    int last_v = int(neur->v)+100;
    for(int i = 0; i < steps_n; i++){ // simulate 1 second, with 0.5ms steps
        if(i == 20){ input = 10; } // after 20 steps, input 10mV DC current into the neuron

        // debug
        //std::cout<<"i: "<<i<<" v: "<<neur->v<<"\n";

        neur->step(input, ms_per_step); // step 0.5 ms further in time

        // draw graph
        int v = int(neur->v)+100; 
        if(v > 1 && last_v > 1 && v < 240 && last_v < 240){
            for(int y = last_v; y <= v; y++){
                img.at<cv::Vec3b>(cv::Point(i,240-y)) = black;
            }
            for(int y = v; y <= last_v; y++){
                img.at<cv::Vec3b>(cv::Point(i,240-y)) = black;
            }
        }
        last_v = v;
    }

    // save output image
    cv::imwrite("../output/out.jpg", img);

    std::cout<<"Image saved to ../output/out.jpg\n"; 
}

#include <iostream>

//#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;

class IzhiNeuron{
    public:

        float v;
        float u;

        float a;
        float b;
        float c;
        float d;

        IzhiNeuron(){
            a = 0.02; // recovery value, lower values result in slower recovery
            b = 0.2;  // sensitivity of u to sub-threshold activation of v
            c = -65;  // mV, after reset membrane potential
            d = 8;    // after spike recovery of of u

            // set initial values
            v = c; // membrane potential, mV
            u = b*v; // recovery variable

        } 

        void step(float input, float step_ms){
            // spike recovery
            if( v >= 30 /* mV */ ){
                // debug
                //std::cout<<"fire!\n";
                v = c;
                u = u + d;
            }

            // calculate membrane potential
            float v_delta = 0.04*v*v + 5*v + 140 - u + input;

            // calculate recovery variable
            float u_delta = step_ms * a * (b*v - u);

            // finer grained steps
            v_delta *= step_ms;
            u_delta *= step_ms;

            // debug
            //std::cout<<"v_delta: "<<v_delta<<"\tu_delta: "<<u_delta<<"\n";

            // set the new values
            v += v_delta;
            u += u_delta;
        }
};

int main(int argc, char **argv) {
    std::cout<<"Izhikevich neuron simulator\n";

    // initialize an Izhikevich neuron
    auto neur = new IzhiNeuron();

    int steps_n = 2000;
    float ms_per_step = 0.2;

    // output image
    /*
    Mat img(ms_per_step, 400, CV_8UC3, Scalar(255,255,255));
    Vec3b black(0,0,0);
    if(img.empty()){
        std::cout << "Could not load image, something wrong with OpenCV\n";
        return -1;
    }
    */


    float input = 0;
    for(int i = 0; i < steps_n; i++){ // simulate 1 second, with 0.5ms steps
        if(i == 20){ input = 10; } // after 20 steps, input 10mV DC current into the neuron

        neur->step(input, ms_per_step); // step 0.5 ms further in time

        if(neur->v > -100 && neur->v < 300){
            //img.at<Vec3b>(Point(i,neur->v+100)) = black;

            // terminal graph
            for(int j = 0; j < neur->v+100; j++){
                std::cout<<"*";
            }
            std::cout<<"\n";
        }

        // debug output
        //std::cout << "i: " << i << "\tv: " << neur->v << "\tu: " << neur->u << "\n";
    }

    // save output image
    //imwrite("output/out.jpg", img);

}

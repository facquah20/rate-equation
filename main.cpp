#include <iostream>
#include <cmath>
#include <fstream>

using std::fstream;
using std::exp;
using std::pow;
using std::string;
using std::cin;
using std::cout;
using std::endl;

struct RateLaw{
    float order;
    float rate_constant;
    float total_time;
    float dt;
    float initialConcentration;
    string filename;
};

void _simulate_rate_reaction(RateLaw &rateLaw){
    fstream file;
    file.open(rateLaw.filename,std::ios::out);
    file<<"Time,current-concentration,reduced-concentration,order"<<endl;
    if(rateLaw.order == 1){
        cout<<"The equation for the rate law is: "<<"N(t) = N_oe^-ct"<<endl;

        for(float t = 0.0; t <= rateLaw.total_time; t += rateLaw.dt){
            double remainingConcentration = rateLaw.initialConcentration*exp(t*-rateLaw.rate_constant);
            double concentrationUsed = rateLaw.initialConcentration-remainingConcentration;

            file<<t<<","<<remainingConcentration<<","<<concentrationUsed<<","<<rateLaw.order<<endl;
        }
    }
    else{
        float exponent = rateLaw.order-1; 
        cout<<"The equation for the rate law is: "<<"N(t) = (1/N_o^"<<exponent<<" + "<<exponent<<"ct"<<" )^"<<-1/exponent<<endl;
        
        for(float t = 0.0; t <= rateLaw.total_time; t += rateLaw.dt){
            double insideCal = 1/pow(rateLaw.initialConcentration,exponent)+(exponent*rateLaw.rate_constant*t);
            double remainingConcentration = pow((insideCal),(-1/exponent))  ;
            double concentrationUsed = rateLaw.initialConcentration-remainingConcentration;

            file<<t<<","<<remainingConcentration<<","<<concentrationUsed<<","<<rateLaw.order<<endl;
        }
    }

    file.close();

    cout<<"Check "<<rateLaw.filename<<" for your values!"<<endl;
    cout<<"Done"<<endl;


}

int main(){

    /* taking parameters for the rate law*/
    float reaction_order = 0;
    float rate_constant = 0; 

    /* taking parameters to simulate the reaction*/
    float initialConcentration = 0; // in case of radioactive decay this refers to the initial amount
    float totalTime = 0 ; // total time to run simulation
    float interval = 0; // time t to calculate the new concentration or remaining nuclide present

    string filename = "";

    /*Taking inputs from the user*/
    cout<<"\nEnter the following parameters for the rate law (order, rate_constant): ";
    cin>>reaction_order>>rate_constant;
    
    cout<<endl;
    cout<<endl;

    cout<<"\nEnter the following initial values (initial_concentration, totalTime, t): ";
    cin>>initialConcentration>>totalTime>>interval;

    /*Print the values to the console for use to view*/
    cout<<"\nYou entered the following values: \n";
    cout<<"order: "<<reaction_order<<endl;
    cout<<"rate constant: "<<rate_constant<<endl;
    cout<<"initial concentration: "<<initialConcentration<<endl;
    cout<<"Duration of Simulation: "<<totalTime<<endl;
    cout<<"dt: "<<interval<<endl;

    cout<<"Enter the name of your file to output your results: ";
    cin>>filename;

    RateLaw rateLaw{reaction_order,rate_constant,totalTime,interval,initialConcentration,filename};

    //where simulation occurs
    _simulate_rate_reaction(rateLaw);

    return 0;
    

}
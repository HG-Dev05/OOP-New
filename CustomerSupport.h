#ifndef CUSTOMERSUPPORT_H
#define CUSTOMERSUPPORT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "MovieManager.h"

using namespace std;

class CustomerSupport {
public:
    CustomerSupport();
    bool loginCustomerSupport();
    void readCustomerFeedback();
    void statistics();

private:
    MovieManager movieManager;
};

#endif
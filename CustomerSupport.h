#ifndef CUSTOMERSUPPORT_H
#define CUSTOMERSUPPORT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "MovieManager.h"

class CustomerSupport {
public:
    CustomerSupport();
    bool loginCustomerSupport();
    void readCustomerFeedback();
    void statistics();

private:
    MovieManager movieManager;
};

#endif // CUSTOMERSUPPORT_H

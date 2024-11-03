#ifndef CUSTOMERSUPPORT_H
#define CUSTOMERSUPPORT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class CustomerSupport {
public:
    CustomerSupport();
    bool loginCustomerSupport();
    void readCustomerFeedback();
    void readFeedbackByMovie(const std::string& movieName);
    void loadFeedbacks();

private:
    std::vector<std::string> feedbacks;
};

#endif // CUSTOMERSUPPORT_H

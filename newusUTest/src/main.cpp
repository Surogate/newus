/* 
 * File:   main.cpp
 * Author: fancel
 *
 * Created on 28 July 2011, 23:50
 */

#include <iostream>

#include "FeedManager.hpp"
#include "RequestForge.hpp"

int main(void) {
    FeedManager manager;

    RequestForge forge(manager);

    forge.ConnectTo("rockpapershotgun.com");
    forge.GetRequest("rockpapershotgun.com", "/xmlrpc.php");

    return 0;
}


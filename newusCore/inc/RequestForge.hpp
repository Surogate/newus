/* 
 * File:   RequestForge.hpp
 * Author: fancel
 *
 * Created on 29 July 2011, 00:28
 */

#ifndef REQUESTFORGE_HPP
#define	REQUESTFORGE_HPP

class FeedManager;

#include <boost/asio.hpp>

class RequestForge {
public:
    typedef boost::asio::ip::tcp::socket Socket;

    RequestForge(FeedManager& owner);

private:
    Socket _socket;
};

#endif	/* REQUESTFORGE_HPP */


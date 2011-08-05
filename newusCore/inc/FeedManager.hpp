/* 
 * File:   FeedManager.hpp
 * Author: fancel
 *
 * Created on 29 July 2011, 00:35
 */

#ifndef FEEDMANAGER_HPP
#define	FEEDMANAGER_HPP

#include <boost/asio.hpp>

class FeedManager {
public:
    typedef boost::asio::io_service Io_service;

    FeedManager();

    Io_service& getIo_service();
    const Io_service& getIo_service() const;

private:
    Io_service _io_service;
};

#endif	/* FEEDMANAGER_HPP */



#include "FeedManager.hpp"
#include "RequestForge.hpp"

FeedManager::FeedManager() : _io_service()
{}

FeedManager::Io_service& FeedManager::getIo_service() {
    return _io_service;
}

const FeedManager::Io_service& FeedManager::getIo_service() const {
    return _io_service;
}

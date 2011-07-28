
#include "RequestForge.hpp"
#include "FeedManager.hpp"

RequestForge::RequestForge(FeedManager& owner) : _socket(owner.getIo_service())
{}

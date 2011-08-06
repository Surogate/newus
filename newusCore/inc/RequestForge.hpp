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
	~RequestForge();
    bool ConnectTo(const std::string& addr);
    bool Connected() const;
    bool GetRequest(const std::string& host, const std::string& path);
	void Disconnect();

private:
    Socket _socket;

    bool ValidResponse(const std::istream& response_stream, const std::string& http_version) {
        return !(!response_stream || http_version.substr(0, 5) != "HTTP/");
    }

	bool Connect(boost::asio::ip::tcp::resolver::iterator& endpoint_iterator);

    void SetGetRequest(std::ostream& in, const std::string& host, const std::string& path);
	void SetPostRequest(std::ostream& in, const std::string& host, const std::string& path);
    bool HandleResponse();
    bool DisplayBody(boost::asio::streambuf& response, std::istream& response_stream);
    bool DisplayBodyHeader(boost::asio::streambuf& response, std::istream& response_stream);
    bool DisplayBodyBody(boost::asio::streambuf& response, std::istream& response_stream);
	
	inline const std::string endline() {
		return "\r\n";
	}


};

#endif	/* REQUESTFORGE_HPP */



#include <boost/asio.hpp>

#include <iostream>
#include <iosfwd>

#include "RequestForge.hpp"
#include "FeedManager.hpp"

RequestForge::RequestForge(FeedManager& owner) : _socket(owner.getIo_service()), _error(NONE) {
}

RequestForge::~RequestForge() {
	Disconnect();
}

bool RequestForge::ConnectTo(const std::string& addr) {
	boost::asio::ip::tcp::resolver resolver(_socket.get_io_service());

	boost::asio::ip::tcp::resolver::query query(addr, "http");
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

	return Connect(endpoint_iterator);
}

bool RequestForge::Connect(boost::asio::ip::tcp::resolver::iterator& endpoint_iterator) {
	boost::asio::ip::tcp::resolver::iterator end;
	boost::system::error_code error = boost::asio::error::host_not_found;

	while (endpoint_iterator != end && error) {
		_socket.close();
		_socket.connect(*endpoint_iterator, error);
		++endpoint_iterator;
	}

	return _socket.is_open() && !error;
}

bool RequestForge::Connected() const {
	return _socket.is_open();
}

void RequestForge::Disconnect() {
	boost::system::error_code error;

	_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
	_socket.close(error);
}

void RequestForge::SetGetRequest(std::ostream& request_stream, const std::string& host, const std::string& path) {
	request_stream << "GET " << path << " HTTP/1.1" << endline();
	request_stream << "Host: " << host << endline();
	request_stream << "User-Agent: Newus/0.1" << endline();
	request_stream << "Accept: */*" << endline() << endline();
}

void RequestForge::SetPostRequest(std::ostream& request_stream, const std::string& host, const std::string& path) {
	request_stream << "POST " << path << " HTTP/1.1" << endline();
	request_stream << "Host: " << host << endline();
	request_stream << "User-Agent: Newus/0.1" << endline();
	request_stream << "Content-Length: 0" << endline();
	request_stream << "Content-Type: application/x-www-form-urlencoded" << endline() << endline();
}

bool RequestForge::GetRequest(const std::string& host, const std::string& path) {
	std::cout << "host " << host << std::endl;
	std::cout << "path " << path << std::endl;
	bool result = false;
	if (Connected()) {
		boost::system::error_code error;
		boost::asio::streambuf request;
		std::ostream request_stream(&request);

		SetGetRequest(request_stream, host, path);

		boost::asio::write(_socket, request, boost::asio::transfer_all(), error);
		if (!error) {
			result = HandleResponse();
		} else {
			_error = SENDING_REQUEST_FAIL;
		}
	} else {
		_error = NOT_CONNECTED;
	}
	return result;
}


bool RequestForge::DisplayResponse() {
	boost::system::error_code error;
	bool result = false;
	boost::asio::streambuf response;
	boost::asio::read_until(_socket, response, endline(), error);
	if (!error) {
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		response_stream >> status_message;
		std::getline(response_stream, status_message);

		if (ValidResponse(response_stream, http_version)) {
			if (status_code == 200) {
				result = DisplayBody(response, response_stream);
			} else {
				_error = INVALID_RESPONSE;
				std::cout << "status code " << status_code << std::endl;
			}
			_error = INVALID_FORMAT;
		}
	} else {
		_error = READ_HEADER_FAIL;
	}
	return result;
}

bool RequestForge::HandleResponse() {
	boost::system::error_code error;
	bool result = false;
	std::stringstream streambuffer(_buffer);
	boost::asio::streambuf response;

	boost::asio::read_until(_socket, response, endline(), error);
	if (!error) {
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		response_stream >> status_message;
		std::getline(response_stream, status_message);

		if (ValidResponse(response_stream, http_version)) {
			if (status_code == 200) {
				result = GetBody(response, response_stream, streambuffer);
				_buffer = streambuffer.str();
			} else {
				_error = INVALID_RESPONSE;
				std::cout << "status code " << status_code << std::endl;
			}
		} else {
			_error = INVALID_FORMAT;
		}
	} else {
		_error = READ_HEADER_FAIL;
	}
	return result;
}

bool RequestForge::DisplayBody(boost::asio::streambuf& response, std::istream& response_stream) {
	return DisplayBodyHeader(response, response_stream)
			&& DisplayBodyBody(response, response_stream);
}

bool RequestForge::DisplayBodyHeader(boost::asio::streambuf& response, std::istream& response_stream) {
	std::string header;
	boost::system::error_code error;
	boost::asio::read_until(_socket, response, "\r\n\r\n", error);
	while (std::getline(response_stream, header) && header != "\r")
		std::cout << header.size() << " " << header << std::endl;
	return !error;
}

bool RequestForge::DisplayBodyBody(boost::asio::streambuf& response, std::istream& response_stream) {
	bool result = false;
	if (response.size() > 0)
		std::cout << &response;
	boost::system::error_code error;
	while (boost::asio::read(_socket, response, boost::asio::transfer_at_least(1), error))
		std::cout << &response;
	if (error == boost::asio::error::eof)
		result = true;
	else
		_error = READ_BODY_FAIL;
	return result;
}

bool RequestForge::GetBody(boost::asio::streambuf& response, std::istream& response_stream, std::stringstream& in) {
	return ConsumeBodyHeader(response, response_stream)
			&& GetBodyBody(response, response_stream, in);
}

bool RequestForge::ConsumeBodyHeader(boost::asio::streambuf& response, std::istream& response_stream) {
	std::string header;
	boost::system::error_code error;
	boost::asio::read_until(_socket, response, "\r\n\r\n", error);
	while (std::getline(response_stream, header) && header != "\r");
	return !error;
}

bool RequestForge::GetBodyBody(boost::asio::streambuf& response, std::istream& response_stream, std::stringstream& in) {
	bool result = false;
	if (response.size() > 0)
		in << &response;
	boost::system::error_code error;
	while (boost::asio::read(_socket, response, boost::asio::transfer_at_least(1), error))
		in << &response;
	if (error == boost::asio::error::eof)
		result = true;
	else
		_error = READ_BODY_FAIL;
	return result;
}

RequestForge::Error RequestForge::getError() const {
	return _error;
}

const std::string& RequestForge::getResponse() const {
	return _buffer;
}


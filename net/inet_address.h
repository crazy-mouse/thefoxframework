#ifndef _THEFOX_NET_INETADDRESS_H
#define _THEFOX_NET_INETADDRESS_H

#include <base/types.h>

#ifdef WIN32
#include <Winsock2.h>
#else
#include <netinet/in.h>
#endif

namespace thefox
{

class InetAddress
{
public:
    InetAddress()
    {
        memset(&_addr, 0, sizeof(_addr));
    }
    InetAddress(uint16_t port)
    {
        memset(&_addr, 0, sizeof(_addr));
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = htonl(INADDR_ANY);
        _addr.sin_port = htons(port);
    }

    InetAddress(const std::string &ip, uint16_t port)
    {
        memset(&_addr, 0, sizeof(_addr));
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = inet_addr(ip.c_str());
        _addr.sin_port = htons(port);
    }

    InetAddress(const struct sockaddr_in &addr)
    : _addr(addr)
    {}

    std::string toIp() const
    {
        char *host = inet_ntoa(_addr.sin_addr);
        if (NULL != host)
            return host;
        else
            return "INVALID";
    }
    
    std::string toIpPort() const
    {
        char buf[32];
        _snprintf(buf, sizeof(buf), "%s:%u", toIp().c_str(), ntohs(_addr.sin_port));
        return buf;
    }

    // default copy/assignment are Okay

    const struct sockaddr_in &getSockAddrInet() const { return _addr; }
    void setSockAddrInet(const struct sockaddr_in &addr) { _addr = addr; }

    uint32_t ipNetEndian() const { return _addr.sin_addr.s_addr; }
    uint16_t portNetEndian() const { return _addr.sin_port; }

	void operator=(struct sockaddr_in addr)
	{ _addr = addr; }

private:
    struct sockaddr_in _addr;
};

} // namespace thefox

#endif  // _THEFOX_NET_INETADDRESS_H

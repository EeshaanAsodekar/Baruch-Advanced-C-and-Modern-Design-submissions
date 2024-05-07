#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <string>

// defining the tags for our bimap; better readability
struct IpAddress {};
struct DomainName {};

// Subquestion (a)
// defining the bimap type
typedef boost::bimap<
    boost::bimaps::unordered_set_of<boost::bimaps::tagged<boost::uuids::uuid, IpAddress>>,
    boost::bimaps::unordered_set_of<boost::bimaps::tagged<std::string, DomainName>>
> DNS;

// function to find a domain name for a given IP address
std::string findDomainName(const DNS& dns, const boost::uuids::uuid& ip) {
    auto it = dns.by<IpAddress>().find(ip);
    return it != dns.by<IpAddress>().end() ? it->get<DomainName>() : "Not found";
}

// Subquestion (b)
// function to find an IP address for a given domain name
boost::uuids::uuid findIpAddress(const DNS& dns, const std::string& domain) {
    auto it = dns.by<DomainName>().find(domain);
    return it != dns.by<DomainName>().end() ? it->get<IpAddress>() : boost::uuids::nil_uuid();
}

// Subquestion (b)
// function to print the contents of the DNS 'database'
void printDNS(const DNS& dns) {
    std::cout << "\nprinting database:" << std::endl;
    for (const auto& entry : dns) {
        std::cout << entry.get<DomainName>() << " <-> " << entry.get<IpAddress>() << std::endl;
    }
}

int main() {
    
    DNS dns;

    // adding ip<->website pair onto the bimap
    boost::uuids::random_generator generator;
    dns.insert(DNS::value_type(generator(), "example.com"));
    dns.insert(DNS::value_type(generator(), "boost.org"));

    // Subquestion (b)
    boost::uuids::uuid ip = dns.by<DomainName>().find("example.com")->get<IpAddress>();
    
    // find a domain name for a given IP address
    std::cout << "IP: " << ip << " -> Domain: " << findDomainName(dns, ip) << std::endl;

    // find an IP address for a given domain name
    std::string domain = "boost.org";
    std::cout << "Domain: " << domain << " -> IP: " << findIpAddress(dns, domain) << std::endl;

    // Subquestion (c)
    // print the contents of the DNS 'database'
    printDNS(dns);

    return 0;
}

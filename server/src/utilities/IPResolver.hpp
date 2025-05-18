#pragma once
#include <asio.hpp>
#include <iostream>
#include <string>

/**
 * @class IPResolver
 * @brief Utility class for resolving the server's IP address.
 *
 * Provides a static method to determine the actual IP address of the server
 * using ASIO's resolver functionality. This is particularly useful for network
 * configurations where the server's IP needs to be dynamically determined.
 */
class IPResolver {
   public:
    /**
     * @brief Gets the actual IP address of the server.
     *
     * Resolves and returns the non-loopback IPv4 address of the server. If unable
     * to determine the address, defaults to returning localhost (127.0.0.1).
     * 
     * @param io_context ASIO IO context used for resolving the IP address.
     * @return std::string The resolved IP address as a string, or "127.0.0.1" if unable to resolve.
     */
    static std::string getActualIP(asio::io_context& io_context) {
        try {
            asio::ip::tcp::resolver resolver(io_context);
            asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(asio::ip::host_name(), "");

            for (auto it = endpoints.begin(); it != endpoints.end(); ++it) {
                asio::ip::address addr = it->endpoint().address();
                if (addr.is_v4() && !addr.is_loopback()) {
                    return addr.to_string();
                }
            }
        } catch (std::exception& e) {
            std::cerr << "Could not get local IP address: " << e.what() << std::endl;
        }
        return "127.0.0.1";
    }
};

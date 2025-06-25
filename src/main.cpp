#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <regex>
#include <filesystem>
#include <functional>
#include <span>
#include <array>

std::vector<uint8_t> read_file(const char* file_name)
{
    auto file = std::ifstream(file_name, std::ios::binary | std::ios::ate);
    if (!file)
        return {};

    const auto size = file.tellg();
    std::vector<uint8_t> data(size);

    file.seekg(0);
    file.read(reinterpret_cast<char*>(data.data()), size);

    return data;
}

std::string bytes_to_hex(const uint8_t* begin)
{
    constexpr size_t len = 64;

    std::string result = {};
    result.reserve(len * 2);

    for (size_t idx = 0; idx < len; idx++)
        result += std::format("{:02x}", begin[idx]);

    return result;
}

std::string bytes_to_ida(const std::string& bytes)
{
    constexpr size_t prefix_bytes = 32;

    size_t prefix_len = prefix_bytes * 2;
    if (bytes.size() < prefix_len)
        prefix_len = bytes.size();

    std::string result;
    for (size_t idx = 0; idx < prefix_len; idx += 2)
    {
        if (idx != 0)
            result += ' ';

        result += bytes.substr(idx, 2);
    }

    return result;
}

std::vector<size_t> find_all_occurrences(std::span<const uint8_t> data, std::span<const uint8_t> signature)
{
    std::vector<size_t> positions = {};
    if (signature.empty() || data.size() < signature.size())
        return positions;

    auto searcher = std::boyer_moore_horspool_searcher(signature.begin(), signature.end());
    auto it = data.begin();

    for (;;)
    {
        auto res = std::search(it, data.end(), searcher);
        if (res == data.end())
            break;

        positions.push_back(std::distance(data.begin(), res));
        it = res + 1;
    }

    return positions;
}

std::string find_key(const std::string& data, const std::regex& pattern)
{
    std::smatch match;
    if (!std::regex_search(data, match, pattern))
        return {};

    const std::string& matched_str = match.str(0);
    constexpr size_t segment_length = 8;

    std::vector<size_t> indices;
    for (size_t idx = 6; idx < 120; idx += 14)
    {
        if (idx == 34) 
            idx += 8;

        indices.push_back(idx);
    }

    std::string key;
    key.reserve(indices.size() * segment_length);

    for (size_t idx : indices)
        key += matched_str.substr(idx, segment_length);

    return key;
}

int32_t main(int32_t arg_c, const char* arg_v[])
{
    std::cout << "github.com/clauadv/ue_aes_finder\n\n";
    if (arg_c != 2)
    {
        std::cerr << "usage: ue_aes_finder.exe <executable_path>\n";
        std::cerr << "       or just drag and drop the file onto this executable\n";
        std::cin.get();

        return 1;
    }

    const auto start = std::chrono::high_resolution_clock::now();

    const auto data = read_file(arg_v[1]);
    if (data.empty())
    {
        std::cerr << "error: could not open or read the specified file\n";
        std::cin.get();
        return 1;
    }

    static const std::regex pattern{
        R"(c745d0\w{8}c745d4\w{16}c745d8\w{8}c745dc\w{8}c745e0\w{8}c745e4\w{8}c745e8\w{8}c745ec\w{8})",
        std::regex::optimize
    };

    constexpr std::array<uint8_t, 4> protection_sig1 = { 0xcc, 0xcc, 0xc7, 0x01 };
    constexpr std::array<uint8_t, 4> protection_sig2 = { 0xcc, 0xcc, 0xc7, 0x41 };

    const auto is_protected = find_all_occurrences(data, protection_sig1).empty() && find_all_occurrences(data, protection_sig2).empty();
    if (is_protected)
    {
        std::cerr << "error: detected a protected executable, extraction aborted\n";
        std::cerr << "       try dumping the game using scylla and try again\n";
        std::cin.get();
        return 1;
    }

    constexpr std::array<uint8_t, 3> key_sig = { 0xc7, 0x45, 0xd0 };
    auto hits = find_all_occurrences(data, key_sig);

    std::string key = {};
    std::string ida_hex = {};

    for (auto idx : hits)
    {
        const auto hex_segment = bytes_to_hex(&data[idx]);
        key = find_key(hex_segment, pattern);
        if (!key.empty())
        {
            ida_hex = bytes_to_ida(hex_segment);
            break;
        }
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const auto elapsed = std::chrono::duration<double>(end - start).count();

    if (key.empty())
    {
        std::cerr << "error: no matching key pattern found in the executable\n";
        std::cerr << "       open a github issue and specify the game\n";
        std::cerr << "       https://github.com/clauadv/ue_aes_finder/issues/new\n";
        std::cin.get();
    }
    else
    {
        std::cout << std::format("bytes:\n{}\n\n", ida_hex);
        std::cout << std::format("key:\n0x{}\n\n", key);
        std::cout << std::format("operation completed in {:.1f} seconds", elapsed);
        std::cin.get();
    }

    return 0;
}

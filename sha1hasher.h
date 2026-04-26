#ifndef SHA1HASHER_H
#define SHA1HASHER_H

#include <QString>
#include <cstdint>
#include <array>
#include <vector>

/**
 * @class SHA1Hasher
 * @brief Implements SHA-1 hashing algorithm from scratch
 * 
 * This class provides a clean, object-oriented interface for computing
 * SHA-1 hashes of text input. The implementation follows RFC 3174.
 */
class SHA1Hasher
{
public:
    /**
     * Compute SHA-1 hash of the given input string
     * @param input The input string to hash
     * @return The SHA-1 hash as a 40-character hexadecimal string
     */
    QString hash(const QString& input);

private:
    // SHA-1 constants
    static constexpr uint32_t K0 = 0x5A827999;
    static constexpr uint32_t K1 = 0x6ED9EBA1;
    static constexpr uint32_t K2 = 0x8F1BBCDC;
    static constexpr uint32_t K3 = 0xCA62C1D6;

    // Initial hash values
    static constexpr uint32_t H0 = 0x67452301;
    static constexpr uint32_t H1 = 0xEFCDAB89;
    static constexpr uint32_t H2 = 0x98BADCFE;
    static constexpr uint32_t H3 = 0x10325476;
    static constexpr uint32_t H4 = 0xC3D2E1F0;

    /**
     * Process a single 512-bit (64-byte) block of data
     */
    void processBlock(const uint8_t* block);

    /**
     * Convert an unsigned 32-bit integer to a big-endian 4-byte array
     */
    static void uint32ToBigEndian(uint32_t value, uint8_t* bytes);

    /**
     * Convert a big-endian 4-byte array to an unsigned 32-bit integer
     */
    static uint32_t bigEndianToUint32(const uint8_t* bytes);

    /**
     * Rotate left operation
     */
    static uint32_t rotateLeft(uint32_t value, int shift);

    // Hash state variables
    uint32_t m_h0, m_h1, m_h2, m_h3, m_h4;
};

#endif // SHA1HASHER_H

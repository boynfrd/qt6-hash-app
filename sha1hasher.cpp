#include "sha1hasher.h"
#include <QByteArray>
#include <cstring>
#include <algorithm>

QString SHA1Hasher::hash(const QString& input)
{
    // Convert QString to UTF-8 bytes
    QByteArray inputBytes = input.toUtf8();
    const uint8_t* data = reinterpret_cast<const uint8_t*>(inputBytes.constData());
    uint64_t dataLen = inputBytes.length();

    // Initialize hash values
    m_h0 = H0;
    m_h1 = H1;
    m_h2 = H2;
    m_h3 = H3;
    m_h4 = H4;

    // Pre-processing: padding and length appending
    // Calculate padded message length (must be multiple of 64 bytes)
    uint64_t originalBitLen = dataLen * 8;
    uint64_t paddedLen = ((dataLen + 8) / 64 + 1) * 64;

    // Create padded message
    std::vector<uint8_t> paddedMessage(paddedLen, 0);
    std::memcpy(paddedMessage.data(), data, dataLen);

    // Append '1' bit (0x80)
    paddedMessage[dataLen] = 0x80;

    // Append original message length as 64-bit big-endian integer
    uint64_t bitLen = originalBitLen;
    for (int i = 7; i >= 0; --i) {
        paddedMessage[paddedLen - 8 + i] = static_cast<uint8_t>(bitLen & 0xFF);
        bitLen >>= 8;
    }

    // Process each 512-bit (64-byte) block
    for (uint64_t i = 0; i < paddedLen; i += 64) {
        processBlock(paddedMessage.data() + i);
    }

    // Produce the final hash value (big-endian)
    uint8_t hashBytes[20];
    uint32ToBigEndian(m_h0, hashBytes + 0);
    uint32ToBigEndian(m_h1, hashBytes + 4);
    uint32ToBigEndian(m_h2, hashBytes + 8);
    uint32ToBigEndian(m_h3, hashBytes + 12);
    uint32ToBigEndian(m_h4, hashBytes + 16);

    // Convert to hexadecimal string
    QString result;
    for (int i = 0; i < 20; ++i) {
        result += QString("%1").arg(hashBytes[i], 2, 16, QChar('0'));
    }

    return result;
}

void SHA1Hasher::processBlock(const uint8_t* block)
{
    // Break block into 16 32-bit big-endian words
    std::array<uint32_t, 80> w;
    for (int i = 0; i < 16; ++i) {
        w[i] = bigEndianToUint32(block + i * 4);
    }

    // Extend the 16 32-bit words into 80 32-bit words
    for (int i = 16; i < 80; ++i) {
        w[i] = rotateLeft(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
    }

    // Initialize working variables
    uint32_t a = m_h0;
    uint32_t b = m_h1;
    uint32_t c = m_h2;
    uint32_t d = m_h3;
    uint32_t e = m_h4;

    // Main loop
    for (int i = 0; i < 80; ++i) {
        uint32_t f, k;

        if (i < 20) {
            f = (b & c) | ((~b) & d);
            k = K0;
        } else if (i < 40) {
            f = b ^ c ^ d;
            k = K1;
        } else if (i < 60) {
            f = (b & c) | (b & d) | (c & d);
            k = K2;
        } else {
            f = b ^ c ^ d;
            k = K3;
        }

        uint32_t temp = rotateLeft(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = rotateLeft(b, 30);
        b = a;
        a = temp;
    }

    // Add this block's hash to result so far
    m_h0 += a;
    m_h1 += b;
    m_h2 += c;
    m_h3 += d;
    m_h4 += e;
}

void SHA1Hasher::uint32ToBigEndian(uint32_t value, uint8_t* bytes)
{
    bytes[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
    bytes[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
    bytes[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
    bytes[3] = static_cast<uint8_t>(value & 0xFF);
}

uint32_t SHA1Hasher::bigEndianToUint32(const uint8_t* bytes)
{
    return (static_cast<uint32_t>(bytes[0]) << 24) |
           (static_cast<uint32_t>(bytes[1]) << 16) |
           (static_cast<uint32_t>(bytes[2]) << 8) |
           static_cast<uint32_t>(bytes[3]);
}

uint32_t SHA1Hasher::rotateLeft(uint32_t value, int shift)
{
    return (value << shift) | (value >> (32 - shift));
}

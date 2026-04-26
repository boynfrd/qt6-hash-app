#ifndef SHA256HASHER_H
#define SHA256HASHER_H

#include <QString>

/**
 * @class SHA256Hasher
 * @brief Wrapper for SHA-256 hashing using Qt's QCryptographicHash
 * 
 * This class provides a clean, object-oriented interface for computing
 * SHA-256 hashes using Qt6's built-in cryptographic library.
 */
class SHA256Hasher
{
public:
    /**
     * Compute SHA-256 hash of the given input string
     * @param input The input string to hash
     * @return The SHA-256 hash as a 64-character hexadecimal string
     */
    QString hash(const QString& input) const;
};

#endif // SHA256HASHER_H

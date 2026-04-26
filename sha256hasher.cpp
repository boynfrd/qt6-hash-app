#include "sha256hasher.h"
#include <QCryptographicHash>
#include <QByteArray>

QString SHA256Hasher::hash(const QString& input) const
{
    // Convert QString to UTF-8 bytes
    QByteArray inputBytes = input.toUtf8();

    // Compute SHA-256 hash
    QByteArray hashBytes = QCryptographicHash::hash(inputBytes, QCryptographicHash::Sha256);

    // Convert to hexadecimal string
    return hashBytes.toHex();
}

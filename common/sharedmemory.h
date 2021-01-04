#ifndef ESI_SHAREDMEMORY_H
#define ESI_SHAREDMEMORY_H

#include <QString>
#include <QBuffer>
#include <memory>
#include <QSharedMemory>
#include "common_global.h"
#include "global.h"

BEGIN_NAMESPACE_ESI

class COMMON_EXPORT SharedMemory {
public:
    SharedMemory(const QString &key);

protected:
    std::unique_ptr<QSharedMemory> m_memory;

public:
    int create(const size_t size);
    int attach();
};

class COMMON_EXPORT SharedMemoryForImage : public SharedMemory {
public:
    SharedMemoryForImage();
    int saveImage(QImage &image);
    int loadImage(QImage &image);

public:
    const static size_t SIZE;
    const static QString KEY;
};

END_NAMESPACE_ESI

#endif // ESI_SHAREDMEMORY_H

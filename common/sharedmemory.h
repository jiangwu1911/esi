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
    SharedMemory();
    int createAll();
    int saveImage(QImage &image);
    int loadImage(QImage &image);

private:
    QSharedMemory m_memoryForImage;
    const static size_t IMAGE_AREA_SIZE;

private:
    int create(QSharedMemory &shm, int size);
    int attach(QSharedMemory &shm);
};

END_NAMESPACE_ESI

#endif // ESI_SHAREDMEMORY_H

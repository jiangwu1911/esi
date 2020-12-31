#include <QDataStream>
#include <QDebug>
#include <QImage>
#include "sharedmemory.h"
#include "exception.h"

BEGIN_NAMESPACE_ESI

const size_t SharedMemory::IMAGE_AREA_SIZE = 1024000;

SharedMemory::SharedMemory() :
    //m_memoryForImage("EsiImage") {
    m_memoryForImage("QSharedMemoryExample") {
}

int SharedMemory::create(QSharedMemory &shm, int size) {
    QString key = shm.nativeKey();
    qDebug() << "Shared memory's native key is" << key;

    if (shm.attach()) {
        // Shared memory already exists
    } else {
        if (!shm.create(size)) {
            qCritical() << shm.error() << shm.errorString();
            throw Exception("Cannot create shared memory.");
        }
    }
    return(0);
}

int SharedMemory::createAll() {
    create(m_memoryForImage, IMAGE_AREA_SIZE);
    return(0);
}

int SharedMemory::attach(QSharedMemory &shm) {
    if (!shm.attach(QSharedMemory::ReadWrite)) {
        qWarning() << "Cannot attach shared memory";
        qWarning() << shm.error() << shm.errorString();
        return(-1);
    }
    qDebug() << "shm attached, size=" << shm.size();
    return(0);
}

int SharedMemory::saveImage(QImage &image) {
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << image;

    m_memoryForImage.attach();
    m_memoryForImage.lock();
    int size = buffer.size();
    qDebug() << "buffer.size" << size;
    qDebug() << "m_memoryForImage.size" << m_memoryForImage.size();

    char *to = (char *)m_memoryForImage.data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(m_memoryForImage.size(), size));
    m_memoryForImage.unlock();
    return 0;
}

int SharedMemory::loadImage(QImage &image) {
    QBuffer buffer;
    QDataStream in(&buffer);

    m_memoryForImage.attach();
    m_memoryForImage.lock();
    qDebug() << "m_memoryForImage.size" << m_memoryForImage.size();

    buffer.setData((char *)m_memoryForImage.constData(), m_memoryForImage.size());
    buffer.open(QBuffer::ReadOnly);
    in >> image;
    m_memoryForImage.unlock();
    return 0;
}

END_NAMESPACE_ESI

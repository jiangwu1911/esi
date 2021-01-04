#include <QDataStream>
#include <QDebug>
#include <QImage>
#include "sharedmemory.h"
#include "exception.h"

BEGIN_NAMESPACE_ESI

SharedMemory::SharedMemory(const QString &key) {
    m_memory  = std::unique_ptr<QSharedMemory>(new QSharedMemory(key, nullptr));
}

int SharedMemory::create(const size_t size) {
    QString key = m_memory->nativeKey();
    qDebug() << "Shared memory's native key is" << key;

    if (m_memory->attach()) {
        qDebug() << "Shared memory" << key << "already exists.";
    } else {
        if (!m_memory->create(size)) {
            qCritical() << m_memory->error() << m_memory->errorString();
            throw Exception("Cannot create shared memory.");
        }
    }
    return(0);
}

int SharedMemory::attach() {
    if (m_memory->attach(QSharedMemory::ReadWrite)) {
        qWarning() << "Cannot attach shared memory";
        qWarning() << m_memory->error() << m_memory->errorString();
        return(-1);
    }
    qDebug() << "shm attached, size=" << m_memory->size();
    return(0);
}

const QString SharedMemoryForImage::KEY = "EsiImage";
const size_t SharedMemoryForImage::SIZE = 1024000;

SharedMemoryForImage::SharedMemoryForImage() :
    SharedMemory(SharedMemoryForImage::KEY)
{}

int SharedMemoryForImage::saveImage(QImage &image) {
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << image;

    this->attach();
    m_memory->lock();
    int size = buffer.size();
    qDebug() << "buffer.size" << size;
    qDebug() << "m_memory.size" << m_memory->size();

    char *to = (char *)m_memory->data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(m_memory->size(), size));
    m_memory->unlock();
    return 0;
}

int SharedMemoryForImage::loadImage(QImage &image) {
    QBuffer buffer;
    QDataStream in(&buffer);

    m_memory->attach();
    m_memory->lock();
    qDebug() << "m_memory.size" << m_memory->size();

    buffer.setData((char *)m_memory->constData(), m_memory->size());
    buffer.open(QBuffer::ReadOnly);
    in >> image;
    m_memory->unlock();
    return 0;
}

END_NAMESPACE_ESI

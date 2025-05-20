/*
 * This is the source code of tgnet library v. 1.1
 * It is licensed under GNU GPL v. 2 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Nikolai Kudashov, 2015-2018.
 */

#include <stdlib.h>
#include <memory.h>
#include <iomanip>
#include "ByteArray.h"
#include "FileLog.h"

ByteArray::ByteArray() {
    bytes = nullptr;
    length = 0;
}

ByteArray::ByteArray(uint32_t len) {
    bytes = new uint8_t[len];
    if (bytes == nullptr) {
        if (LOGS_ENABLED) DEBUG_E("unable to allocate byte buffer %u", len);
        exit(1);
    }
    length = len;
}


ByteArray::ByteArray(ByteArray *byteArray) {
    bytes = new uint8_t[byteArray->length];
    if (bytes == nullptr) {
        if (LOGS_ENABLED) DEBUG_E("unable to allocate byte buffer %u", byteArray->length);
        exit(1);
    }
    length = byteArray->length;
    memcpy(bytes, byteArray->bytes, length);
}

ByteArray::ByteArray(uint8_t *buffer, uint32_t len) {
    bytes = new uint8_t[len];
    if (bytes == nullptr) {
        if (LOGS_ENABLED) DEBUG_E("unable to allocate byte buffer %u", len);
        exit(1);
    }
    length = len;
    memcpy(bytes, buffer, length);
}

ByteArray::~ByteArray() {
    if (bytes != nullptr) {
        delete[] bytes;
        bytes = nullptr;
    }
}

void ByteArray::alloc(uint32_t len) {
    if (bytes != nullptr) {
        delete[] bytes;
        bytes = nullptr;
    }
    bytes = new uint8_t[len];
    if (bytes == nullptr) {
        if (LOGS_ENABLED) DEBUG_E("unable to allocate byte buffer %u", len);
        exit(1);
    }
    length = len;
}

bool ByteArray::isEqualTo(ByteArray *byteArray) {
    return byteArray->length == length && !memcmp(byteArray->bytes, bytes, length);
}


//std::string printByteArray(ByteArray *data) {
//    uint8_t *bytes = data->bytes;
//    char *strBuf = new char[data->length * 3 + 1];
//    char *ptr = strBuf;
//    for (int i = 0; i < data->length; i++) {
//        ptr += sprintf(ptr, "%02X ", bytes[i]);
//    }
//    //if (LOGS_ENABLED) DEBUG_D("[+] [%s]", strBuf);
//    std::string s(strBuf);
//    delete strBuf;
//    strBuf = nullptr;
//    return move(s);
//}
std::string ByteArray::bytesToHexString(ByteArray *datas) {
    if (nullptr == datas) return "";

    uint8_t *data = datas->bytes;
    uint32_t length = datas->length;
    std::ostringstream oss;
    oss << std::hex << std::uppercase; // 设置为16进制格式，并使用大写字母
    for (size_t i = 0; i < length; ++i) {
        oss << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }

    return oss.str();
}

std::string ByteArray::bytesToHexString() {
    uint8_t *data = bytes;
    uint32_t length = length;
    std::ostringstream oss;
    oss << std::hex << std::uppercase; // 设置为16进制格式，并使用大写字母
    for (size_t i = 0; i < length; ++i) {
        oss << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }

    return oss.str();
}
//
//  BPTreeKey.cpp
//  MiniSQL
//
//  Created by fan wu on 10/25/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "BPTreeKey.hpp"

BPTreeKey::BPTreeKey() {
    keyLen = 0;
    intData = 0;
    floatData = 0.0f;
    charData[0] = '\0';
    type = DataType::UNDEFINED;
}

BPTreeKey::BPTreeKey(const BPTreeKey &key) {
    keyLen = key.keyLen;
    intData = key.intData;
    floatData = key.floatData;
    memcpy(charData, key.charData, keyLen);
    memcpy(rawData, key.rawData, 256);
    type = key.type;
}

BPTreeKey::BPTreeKey(const Attribute &attri) {
    keyLen = attri.length;
    intData = attri.intdata;
    floatData = attri.floatdata;
    memcpy(charData, attri.chardata, keyLen);
    memcpy(rawData, attri.rawdata, 256);
    switch (attri.type) {
        case DataType::INT :
            type = DataType::INT;
            break;
        
        case DataType::FLOAT :
            type = DataType::FLOAT;
            break;
            
        case DataType::CHAR :
            type = DataType::CHAR;
            break;
            
        default:
            type = DataType::UNDEFINED;
            break;
    }
}

BPTreeKey::~BPTreeKey() {
}

int BPTreeKey::getKeyDataLength() {
    switch (type) {
        case DataType::CHAR:
            return keyLen;
            break;
        
        case DataType::FLOAT:
            return sizeof(float);
            break;
            
        case DataType::INT:
            return sizeof(int);
            break;
            
        case DataType::UNDEFINED:
            return 0;
            break;
            
        default:
            break;
    }
}

int BPTreeKey::compare(const BPTreeKey &key) {
    assert(type == key.type);
    assert(type != DataType::UNDEFINED);
    switch (type) {
        case DataType::INT: {
            if (intData > key.intData)
                return 1;
            else if (intData == key.intData)
                return 0;
            else return -1;
            break;
        }
        
        case DataType::FLOAT: {
            if (floatData > key.floatData)
                return 1;
            else if ( fabs(floatData - key.floatData) < 0.000001)
                return 0;
            else return -1;
            break;
        }
            
        case DataType::CHAR: {
            return strncmp(charData, key.charData, keyLen);
            break;
        }
            
        default:
            return 0;
            break;
    }
}

void BPTreeKey::convertToRawData() {
//    assert(type != DataType::UNDEFINED); For leaf
    
    switch (type) {
        case DataType::INT: {
            keyLen = sizeof(int);
            memcpy(rawData, &intData, keyLen);
            break;
        }
            
        case DataType::FLOAT: {
            keyLen = sizeof(float);
            memcpy(rawData, &floatData, keyLen);
            break;
        }
            
        case DataType::CHAR: {
            assert(keyLen >= 0);
            assert(keyLen <= 255);
            memcpy(rawData, charData, keyLen);
            break;
        }
            
        default:
            break;
    }
}

void BPTreeKey::parseFromRawData() {
    assert(type != DataType::UNDEFINED);
    keyLen = getKeyDataLength();
    switch (type) {
        case DataType::INT: {
            assert(keyLen == sizeof(int));
            memcpy(&intData, rawData, keyLen);
            break;
        }
            
        case DataType::FLOAT: {
            assert(keyLen == sizeof(float));
            memcpy(&floatData, rawData, keyLen);
            break;
        }
            
        case DataType::CHAR: {
            assert(keyLen >= 0);
            assert(keyLen <= 255);
            memcpy(charData, rawData, keyLen);
            break;
        }
            
        default:
            break;
    }
}

bool BPTreeKey::operator< (const BPTreeKey &key) {
    return compare(key) < 0;
}

bool BPTreeKey::operator==(const BPTreeKey &key) {
    return compare(key) == 0;
}

bool BPTreeKey::operator> (const BPTreeKey &key) {
    return compare(key) > 0;
}

bool BPTreeKey::operator>=(const BPTreeKey &key) {
    return (*this > key) || (*this == key);
}
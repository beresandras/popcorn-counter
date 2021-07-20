#include "NeuralNetwork.h"

unsigned char model_tflite[] = {
    0x1c, 0x00, 0x00, 0x00, 0x54, 0x46, 0x4c, 0x33, 0x14, 0x00, 0x20, 0x00,
    0x04, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x1c, 0x00, 0x14, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00,
    0x1c, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x50, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x98, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x18, 0x06, 0x00, 0x00,
    0x14, 0x06, 0x00, 0x00, 0x28, 0x05, 0x00, 0x00, 0x98, 0x01, 0x00, 0x00,
    0x08, 0x06, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00,
    0x04, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x05, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x6d, 0x69, 0x6e, 0x5f,
    0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x5f, 0x76, 0x65, 0x72, 0x73,
    0x69, 0x6f, 0x6e, 0x00, 0x26, 0xfb, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x31, 0x2e, 0x35, 0x2e, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
    0x4d, 0x4c, 0x49, 0x52, 0x20, 0x43, 0x6f, 0x6e, 0x76, 0x65, 0x72, 0x74,
    0x65, 0x64, 0x2e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x04, 0x00,
    0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x14, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
    0x2c, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x14, 0x05, 0x00, 0x00, 0xa0, 0x04, 0x00, 0x00, 0x20, 0x04, 0x00, 0x00,
    0x98, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x1c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e,
    0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00,
    0x07, 0x00, 0x10, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x30, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x10, 0x00, 0x0e, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0f, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0xa4, 0xfb, 0xff, 0xff,
    0x14, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x49, 0x64, 0x65, 0x6e,
    0x74, 0x69, 0x74, 0x79, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0x20, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x8c, 0xfb, 0xff, 0xff, 0x7a, 0xfc, 0xff, 0xff,
    0x04, 0x00, 0x00, 0x00, 0x24, 0x03, 0x00, 0x00, 0x84, 0x15, 0x67, 0xb4,
    0x98, 0x4e, 0x86, 0x34, 0x06, 0xd5, 0x78, 0xb4, 0xa8, 0xfd, 0xc0, 0xb3,
    0x02, 0x73, 0x54, 0xb4, 0xcb, 0x28, 0x8f, 0xb4, 0xdb, 0xde, 0x73, 0xb4,
    0xe8, 0x9d, 0xbc, 0xb4, 0x24, 0x3b, 0xa1, 0x34, 0x71, 0xf4, 0x3c, 0xb4,
    0x2c, 0xbf, 0xda, 0x34, 0x56, 0x79, 0xf4, 0x34, 0xb0, 0x52, 0x54, 0xb3,
    0x3f, 0x4c, 0x28, 0x35, 0x66, 0x95, 0x91, 0xb4, 0x75, 0x2c, 0xfc, 0x34,
    0x39, 0xa3, 0x04, 0xb5, 0xac, 0x5c, 0xf4, 0x33, 0x90, 0xda, 0x03, 0x32,
    0x8f, 0xa3, 0x4e, 0xb5, 0x74, 0xab, 0x36, 0x35, 0x65, 0xe9, 0x3d, 0xb5,
    0x5c, 0xe8, 0x02, 0x35, 0x91, 0x18, 0x08, 0xb5, 0x5c, 0xbe, 0x48, 0x33,
    0x0a, 0x2e, 0x09, 0x33, 0x17, 0xf1, 0x48, 0xb4, 0x9c, 0xc2, 0x38, 0x35,
    0x76, 0x9b, 0x15, 0xb5, 0x08, 0xbc, 0x61, 0x34, 0x77, 0x84, 0x00, 0xb5,
    0x8c, 0xc6, 0xc9, 0xb3, 0xf6, 0x0c, 0xac, 0xb4, 0x9d, 0x13, 0xda, 0xb3,
    0x37, 0x32, 0x12, 0x34, 0x14, 0xa4, 0x77, 0xb4, 0xbc, 0xd2, 0x1f, 0x35,
    0x94, 0x7a, 0xba, 0x34, 0xa4, 0x97, 0x2f, 0x35, 0x5c, 0xb2, 0xf7, 0x34,
    0x3f, 0xe2, 0xd7, 0x34, 0xdc, 0xc5, 0xcc, 0x34, 0xa1, 0x54, 0x8f, 0xb3,
    0xe3, 0x99, 0x80, 0x35, 0xd5, 0xe4, 0x88, 0xb3, 0xe4, 0xbc, 0xbc, 0x34,
    0xc2, 0x78, 0xd9, 0x33, 0x8c, 0xe4, 0xa4, 0xb2, 0xcc, 0x89, 0x54, 0x35,
    0x48, 0x77, 0x28, 0xb4, 0x2a, 0xab, 0xc2, 0x35, 0x90, 0xa8, 0x11, 0xb3,
    0x92, 0xc1, 0xa1, 0x35, 0xf2, 0x0a, 0x95, 0x35, 0x59, 0x77, 0xd8, 0x34,
    0x2d, 0x1d, 0xe0, 0x35, 0xa2, 0xc7, 0x4b, 0xb4, 0x99, 0xe9, 0x89, 0x35,
    0xc1, 0x32, 0x03, 0xb5, 0x6f, 0x87, 0xc9, 0x34, 0xa6, 0xd5, 0xeb, 0x34,
    0xc1, 0xaa, 0xde, 0xb4, 0x01, 0xf4, 0x83, 0x35, 0x19, 0x1a, 0x89, 0xb4,
    0x84, 0x31, 0xee, 0x34, 0x95, 0x74, 0x1b, 0x35, 0x1c, 0x6a, 0x35, 0x35,
    0x1d, 0x51, 0x32, 0x35, 0xf9, 0x32, 0xce, 0x34, 0x7f, 0x9a, 0xa5, 0x34,
    0xa0, 0xdb, 0xcb, 0x34, 0x28, 0x27, 0x60, 0xb4, 0x50, 0x72, 0xa3, 0x34,
    0xf7, 0xb1, 0x78, 0xb4, 0x04, 0x80, 0xdd, 0xb4, 0xb2, 0x47, 0xac, 0x33,
    0x58, 0x15, 0x85, 0xb4, 0xee, 0xa2, 0xea, 0x34, 0x88, 0x40, 0x1f, 0x35,
    0x26, 0x62, 0xcb, 0x34, 0x56, 0x9e, 0x3b, 0x35, 0xbc, 0xc6, 0xd5, 0xb2,
    0x02, 0xd4, 0x65, 0x35, 0xc1, 0x72, 0x78, 0x34, 0x86, 0x1f, 0x8f, 0xb4,
    0x8f, 0xbb, 0x28, 0x35, 0xa0, 0x49, 0x5b, 0xb5, 0x2d, 0xd6, 0xa5, 0x33,
    0x54, 0x00, 0x80, 0xb4, 0xb6, 0x3b, 0xb5, 0xb3, 0x22, 0xd4, 0x2e, 0x34,
    0x08, 0x98, 0x25, 0xb5, 0x28, 0x96, 0x3d, 0x35, 0x6c, 0xa0, 0x29, 0xb5,
    0x89, 0x72, 0x9e, 0x34, 0x45, 0xf2, 0x33, 0x35, 0x92, 0x2e, 0xc1, 0xb4,
    0x64, 0x3e, 0xd4, 0x34, 0xdd, 0x73, 0x35, 0xb5, 0x5d, 0x12, 0xa6, 0x34,
    0x75, 0xa2, 0x45, 0xb5, 0x50, 0x66, 0xd7, 0xb3, 0xde, 0x1a, 0x18, 0xb5,
    0x34, 0xc7, 0x80, 0xb5, 0xae, 0x11, 0x9a, 0xb4, 0x9c, 0xc8, 0x8e, 0xb3,
    0x00, 0xc0, 0x36, 0x31, 0x5e, 0xa2, 0xd0, 0x34, 0x80, 0x56, 0x28, 0x35,
    0x0a, 0x21, 0xe2, 0xb4, 0x3e, 0x3b, 0x9a, 0x34, 0xc4, 0x8b, 0x4f, 0x34,
    0x3c, 0xd2, 0xb3, 0x33, 0x00, 0xe1, 0x2a, 0x31, 0x60, 0x8c, 0xf7, 0xb2,
    0x4c, 0xc2, 0xd4, 0xb3, 0x64, 0xa2, 0xda, 0xb4, 0x4c, 0x26, 0x68, 0x34,
    0xe6, 0x35, 0xfd, 0x34, 0xa6, 0xb9, 0xbe, 0xb4, 0x9f, 0x83, 0x3a, 0x35,
    0x70, 0xe7, 0x42, 0x35, 0x20, 0x53, 0x4a, 0x35, 0x7f, 0x3d, 0xda, 0x35,
    0xd0, 0x75, 0x8f, 0x35, 0xb2, 0x41, 0xab, 0x35, 0x42, 0x09, 0x2d, 0x35,
    0x55, 0xfb, 0x39, 0x35, 0x45, 0x88, 0x11, 0x35, 0x64, 0xa4, 0x1c, 0x34,
    0xdc, 0xac, 0x8f, 0x34, 0x7f, 0x87, 0xeb, 0x34, 0x30, 0x80, 0xea, 0xb2,
    0xc6, 0xbc, 0xc3, 0x35, 0xf9, 0xb1, 0x81, 0x35, 0x90, 0x4a, 0x90, 0x35,
    0xff, 0x1e, 0xe0, 0x35, 0xf2, 0xe4, 0xeb, 0x34, 0x6d, 0x60, 0xe7, 0x35,
    0xa7, 0x0f, 0x0d, 0x35, 0x94, 0x83, 0x99, 0x35, 0x51, 0x43, 0x50, 0x35,
    0x1e, 0x7a, 0x5f, 0xb4, 0xac, 0x7b, 0x3a, 0x35, 0x0e, 0xc5, 0x93, 0xb4,
    0xc9, 0x40, 0x08, 0x35, 0x54, 0xb8, 0xed, 0x34, 0x38, 0xe1, 0x40, 0x34,
    0xd9, 0x18, 0x85, 0x35, 0x22, 0x36, 0xdf, 0x34, 0x2f, 0x81, 0x5a, 0x35,
    0x12, 0x8f, 0x89, 0x35, 0x24, 0xb7, 0x69, 0x34, 0x5b, 0xda, 0x48, 0x35,
    0x66, 0x61, 0x90, 0xb4, 0xb5, 0x93, 0xb3, 0x34, 0x01, 0xf6, 0x57, 0xb4,
    0x07, 0xa2, 0x97, 0xb3, 0x24, 0xf8, 0x3d, 0x34, 0xe4, 0x18, 0x93, 0xb4,
    0x6b, 0x73, 0x94, 0x34, 0x84, 0x75, 0x06, 0xb4, 0x74, 0x49, 0x7a, 0x34,
    0xde, 0x6b, 0xe1, 0x33, 0x0c, 0x47, 0xe5, 0x34, 0x65, 0xd1, 0x11, 0x34,
    0x5e, 0x67, 0x83, 0x34, 0x28, 0xfe, 0x9c, 0x32, 0xc0, 0x81, 0x76, 0xb3,
    0xf8, 0x00, 0xb7, 0xb4, 0x4a, 0xba, 0x0a, 0xb5, 0x0c, 0x68, 0xe7, 0xb4,
    0x5b, 0xde, 0xa7, 0xb5, 0xe4, 0x9f, 0xfd, 0xb4, 0x51, 0x73, 0x55, 0xb5,
    0xaa, 0x0a, 0xef, 0xb4, 0xf4, 0x47, 0xd5, 0xb3, 0x4a, 0x2e, 0xa0, 0xb4,
    0x37, 0xde, 0x9f, 0x34, 0x8c, 0xd2, 0x1b, 0xb5, 0x77, 0x15, 0x98, 0x34,
    0xf6, 0xb6, 0x02, 0xb5, 0xee, 0x8a, 0x0f, 0xb5, 0x9d, 0xa1, 0xcf, 0xb4,
    0x8c, 0x1b, 0x73, 0xb5, 0x21, 0x8f, 0x16, 0xb5, 0x6a, 0x82, 0x4c, 0xb5,
    0x88, 0xf3, 0xb2, 0xb4, 0x4b, 0x5c, 0xb6, 0xb4, 0x66, 0x0b, 0x83, 0xb4,
    0x60, 0x62, 0xa2, 0x34, 0x2e, 0xe6, 0x3f, 0xb4, 0x18, 0x31, 0x90, 0x34,
    0xb3, 0xbd, 0x4b, 0xb4, 0xe0, 0xa2, 0xa6, 0xb2, 0x90, 0x55, 0xcd, 0xb4,
    0xae, 0xc4, 0xa3, 0xb4, 0x20, 0xdc, 0xd5, 0xb4, 0x4f, 0x0c, 0x57, 0xb5,
    0x5e, 0x2a, 0xbe, 0xb4, 0xed, 0xc9, 0x2f, 0xb5, 0x92, 0xff, 0xff, 0xff,
    0x10, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0xc9, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x1e, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69,
    0x61, 0x6c, 0x5f, 0x33, 0x36, 0x2f, 0x63, 0x6f, 0x6e, 0x76, 0x32, 0x64,
    0x5f, 0x36, 0x33, 0x2f, 0x43, 0x6f, 0x6e, 0x76, 0x32, 0x44, 0x00, 0x00,
    0x04, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
    0x08, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x4c, 0x7a, 0xe0, 0xb9, 0x00, 0x00, 0x0e, 0x00,
    0x14, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75,
    0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x33, 0x36, 0x2f, 0x63, 0x6f,
    0x6e, 0x76, 0x32, 0x64, 0x5f, 0x36, 0x33, 0x2f, 0x42, 0x69, 0x61, 0x73,
    0x41, 0x64, 0x64, 0x2f, 0x52, 0x65, 0x61, 0x64, 0x56, 0x61, 0x72, 0x69,
    0x61, 0x62, 0x6c, 0x65, 0x4f, 0x70, 0x2f, 0x72, 0x65, 0x73, 0x6f, 0x75,
    0x72, 0x63, 0x65, 0x00, 0x94, 0xff, 0xff, 0xff, 0x14, 0x00, 0x18, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x14, 0x00, 0x14, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0xe8, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x69, 0x6e, 0x70, 0x75, 0x74, 0x5f, 0x33, 0x37,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
    0xe8, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00};

NeuralNetwork::NeuralNetwork() : errorReporter(), model(tflite::GetModel(model_tflite)), resolver() {
    // check model version
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        TF_LITE_REPORT_ERROR(
            &errorReporter, "Model provided is schema version %d not equal to supported version %d.",
            model->version(), TFLITE_SCHEMA_VERSION);
        return;
    }

    // add required operations to the resolver
    resolver.AddConv2D();
    resolver.AddRelu();

    // create interpreter
    interpreter = new tflite::MicroInterpreter(model, resolver, tensorArena, tensorArenaSize, &errorReporter);
    TfLiteStatus status = interpreter->AllocateTensors();
    if (status != kTfLiteOk) {
        TF_LITE_REPORT_ERROR(&errorReporter, "AllocateTensors() failed\n");
        return;
    }
    TF_LITE_REPORT_ERROR(&errorReporter, "Used bytes %d\n", interpreter->arena_used_bytes());

    // save the input and output pointers
    input = interpreter->input(0);
    output = interpreter->output(0);
}

float NeuralNetwork::predict(const float* pInputBuffer, const int inputSize, const int outputSize) {
    // copy input tensor
    for (int i = 0; i < inputSize; i++) {
        input->data.f[i] = pInputBuffer[i];
    }

    // run network
    interpreter->Invoke();

    // sum output tensor
    float result = 0.0f;
    for (int i = 0; i < outputSize; i++) {
        result += output->data.f[i];
    }
    return result;
}

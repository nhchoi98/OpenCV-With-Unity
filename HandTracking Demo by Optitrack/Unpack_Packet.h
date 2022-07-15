#pragma once

// Packet unpacking functions
char* Unpack(char* pPacketIn);
char* UnpackPacketHeader(char* ptr, int& messageID, int& nBytes, int& nBytesTotal);
// Frame data
char* UnpackFrameData(char* inptr, int nBytes, int major, int minor);
char* UnpackFramePrefixData(char* ptr, int major, int minor);
char* UnpackMarkersetData(char* ptr, int major, int minor);
char* UnpackRigidBodyData(char* ptr, int major, int minor);
char* UnpackSkeletonData(char* ptr, int major, int minor);
char* UnpackLabeledMarkerData(char* ptr, int major, int minor);
char* UnpackForcePlateData(char* ptr, int major, int minor);
char* UnpackDeviceData(char* ptr, int major, int minor);
char* UnpackFrameSuffixData(char* ptr, int major, int minor);
// Descriptions
char* UnpackDescription(char* inptr, int nBytes, int major, int minor);
char* UnpackMarkersetDescription(char* ptr, char* targetPtr, int major, int minor);
char* UnpackRigidBodyDescription(char* ptr, char* targetPtr, int major, int minor);
char* UnpackSkeletonDescription(char* ptr, char* targetPtr, int major, int minor);
char* UnpackForcePlateDescription(char* ptr, char* targetPtr, int major, int minor);
char* UnpackDeviceDescription(char* ptr, char* targetPtr, int major, int minor);
char* UnpackCameraDescription(char* ptr, char* targetPtr, int major, int minor);


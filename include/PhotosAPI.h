#ifndef PHOTOSAPI_H
#define PHOTOSAPI_H

#include "Global.h"
#include "Result.h"
#include "Permission.h"
#include <string>
#include <QVector>

using namespace std;

class Request;

class  PhotosAPI
{
public:
    PhotosAPI(Request *request);

private:
    Request *m_request;
};

#endif  //PHOTOSAPI_H

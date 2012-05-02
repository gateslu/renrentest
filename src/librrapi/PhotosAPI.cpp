#define RRAPI_LIB_MAIN
#include "../../include/PhotosAPI.h"
#include "../libhttp/Http.h"
#include "Config.h"
#include "Method.h"
#include "Utility.h"
#include <json/json.h>

PhotosAPI::PhotosAPI(Request *request)
{
    m_request = request;
}

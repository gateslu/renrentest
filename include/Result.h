#ifndef RESULT_H
#define RESULT_H

typedef unsigned long Result;

#define RRAPI_GET_RESULT_DESCRIPTION(name)		name##_D

#define RESULT_OK							0L
#define RESULT_USER                         40000L
#define RESULT_BUFFER_TOO_SMALL				RESULT_USER + 1L
#define RESULT_NULL_POINTER					RESULT_USER + 2L
#define RESULT_CANNOT_CONNECT_TO_SERVER		RESULT_USER + 3L
#define RESULT_CALLBACK_INVALID				RESULT_USER + 4L
#define RESULT_JSON_INVALID					RESULT_USER + 5L
#define RESULT_PARAMETER_INVALID			RESULT_USER + 6L
#define RESULT_NOTIFICATIONS_TOO_MANY       RESULT_USER + 7L

#define RESULT_OK_D							"Ok"
#define RESULT_BUFFER_TOO_SMALL_D			"Buffer too small"
#define RESULT_NULL_POINTER_D				"Pointer should not be NULL"
#define RESULT_CANNOT_CONNECT_TO_SERVER_D	"Cannot connect to server"
#define RESULT_CALLBACK_INVALID_D			"Invalid callback format"
#define RESULT_JSON_INVALID_D				"Invalid JSON format"
#define RESULT_PARAMETER_INVALID_D			"Invalid parameter"
#define RESULT_NOTIFICATIONS_TOO_MANY_D     "Too many notifications(must be less than 20 at once)"

#endif	//RESULT_H
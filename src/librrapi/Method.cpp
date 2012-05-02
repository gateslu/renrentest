#include "Method.h"

METHOD_DEFINE(ADMIN_GET_ALLOCATION,         "admin.getAllocation");

METHOD_DEFINE(FRIENDS_GET,                  "friends.get");
METHOD_DEFINE(FRIENDS_ARE_FRIENDS,          "friends.areFriends");
METHOD_DEFINE(FRIENDS_GET_FRIENDS,          "friends.getFriends");
METHOD_DEFINE(FRIENDS_GET_APP_FRIENDS,      "friends.getAppFriends");

METHOD_DEFINE(INVITATIONS_CREATE_LINK,      "invitations.createLink");
METHOD_DEFINE(INVITATIONS_GET_INFO,         "invitations.getInfo");

METHOD_DEFINE(NOTIFICATIONS_SEND,           "notifications.send");
METHOD_DEFINE(NOTIFICATIONS_SEND_EMAIL,     "notifications.sendEmail");

METHOD_DEFINE(PAGES_IS_FAN,                 "pages.isFan");

METHOD_DEFINE(PAY_IS_COMPLETED,             "pay.isCompleted");
METHOD_DEFINE(PAY_REG_ORDER,                "pay.regOrder");
METHOD_DEFINE(PAY_IS_COMPLETED_4_TEST,      "pay4Test.isCompleted");
METHOD_DEFINE(PAY_REG_ORDER_4_TEST,         "pay4Test.regOrder");

METHOD_DEFINE(USERS_GET_LOGGED_IN_USER,     "users.getLoggedInUser");
METHOD_DEFINE(USERS_GET_INFO,               "users.getInfo");
METHOD_DEFINE(USERS_HAS_APP_PERMISSION,     "users.hasAppPermission");
METHOD_DEFINE(USERS_IS_APP_USER,            "users.isAppUser");

METHOD_DEFINE(STATUS_GETS,                  "status.gets");
METHOD_DEFINE(STATUS_SET,                   "status.set");
METHOD_DEFINE(STATUS_GET,                   "status.get");
METHOD_DEFINE(STATUS_GET_COMMENT,           "status.getComment");

METHOD_DEFINE(PHOTOS_CREATE_ALBUM,          "photos.createAlbum");
METHOD_DEFINE(PHOTOS_GET_ALBUMS,            "photos.getAlbums");
METHOD_DEFINE(PHOTOS_UPLOAD,                "photos.upload");
METHOD_DEFINE(PHOTOS_GET,                   "photos.get");

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cJson.h";
#include "cJSON.c";

typedef enum {
    TYPE_STR,
    TYPE_INT
} ValueType;

typedef struct {
    const char* key;
    ValueType type;
    int maxLength;
    void* value;
} JsonKey;

typedef struct {
    int notificationId;
    char userName[50];
    char timeZone[50];
    char currentCamName[50];
    int currentMon;
    char nextCamName[50];
    int currentCam;
    int playbackMon;
    char roomName[50];
    int errorCode;
    int playbackCam;
    char prevCamName[50];
} NotificationParams;

void parseNotification(const char* notification, JsonKey jsonKeysList[], int numKeys) {
    cJSON* root = cJSON_Parse(notification);
    if (root == NULL) {
        printf("No Notification List found\n");
        return;
    }



    for (int i = 0; i < numKeys; i++) {

        const char* key = jsonKeysList[i].key;

        cJSON* value = cJSON_GetObjectItemCaseSensitive(root, key);
        if (value != NULL) {
            if (jsonKeysList[i].type == TYPE_INT) {

                if (cJSON_IsNumber(value)) {
                    int intValue = value->valueint;
                    *((int*)jsonKeysList[i].value) = intValue;
                }
            } else if (jsonKeysList[i].type == TYPE_STR) {

                if (cJSON_IsString(value)) {
                    const char* strValue = value->valuestring;

                    int maxLength = jsonKeysList[i].maxLength;

                    strncpy((char*)jsonKeysList[i].value, strValue, maxLength);
                    ((char*)jsonKeysList[i].value)[maxLength] = '\0';
                }
            }
        }
    }

}

int main() {
    NotificationParams noitifParams;

    JsonKey jsonKeysList[] = {
        {"ID", TYPE_INT, 0, &noitifParams.notificationId},
        {"UN", TYPE_STR, 50, noitifParams.userName},
        {"TZ", TYPE_STR, 50, noitifParams.timeZone},
        {"CCAMN", TYPE_STR, 50, noitifParams.currentCamName},
        {"CMON", TYPE_INT, 0, &noitifParams.currentMon},
        {"NCAMN", TYPE_STR, 50, noitifParams.nextCamName},
        {"CCAM", TYPE_INT, 0, &noitifParams.currentCam},
        {"PMON", TYPE_INT, 0, &noitifParams.playbackMon},
        {"RM", TYPE_STR, 50, noitifParams.roomName},
        {"ERR", TYPE_INT, 0, &noitifParams.errorCode},
        {"PCAM", TYPE_INT, 0, &noitifParams.playbackCam},
        {"PCAMN", TYPE_STR, 50, noitifParams.prevCamName}
    };
    int numKeys = sizeof(jsonKeysList) / sizeof(JsonKey);

    const char* notification = "{\"ID\": 1, \"UN\": \"John Doe\", \"TZ\": \"12:02:06\"}";
    
    parseNotification(notification, jsonKeysList, numKeys);
    //printf("numkeys: %d \n , notification : %s\n", numKeys, notification);

    printf("ID: %d\n", noitifParams.notificationId);
    printf("UN: %s\n", noitifParams.userName);
    printf("TZ: %s\n", noitifParams.timeZone);

    notification = "{\"ID\": 1, \"UN\": \"null\"}";

    parseNotification(notification, jsonKeysList, numKeys);
  //  printf("numkeys: %d\n, notification : %s\n", numKeys, notification);

    printf("ID: %d\n", noitifParams.notificationId);
    printf("UN: %s\n", noitifParams.userName);

    notification = "{\"ID\": 2, \"CMON\": 4, \"CCAMN\": \"Training Room\", \"NCAMN\": \"Training Room Corridor\", \"PCAMN\": \"Rear Stairwell\"}";
   // printf("numkeys: %d \n, notification : %s\n", numKeys, notification);

    parseNotification(notification, jsonKeysList, numKeys);

    printf("ID: %d\n", noitifParams.notificationId);
    printf("CMON: %d\n", noitifParams.currentMon);
    printf("CCAMN: %s\n", noitifParams.currentCamName);
    printf("NCAMN: %s\n", noitifParams.nextCamName);
    printf("PCAMN: %s\n", noitifParams.prevCamName);

    return 0;
}

#include JsonPaser.h

/*
Notifications strings examples:
Login: { "ID":1,"UN":"John Doe", “SN”:”victor”, "DT":"02/08/2022", "TM":"12:01:06" }
Logout: { "ID":1,"UN":null }
Mon command-1: { "ID":2, "CMON": 4, “CCAMN”:”Training Room”, “NCAMN”:”Training Room Corridor”, “LCAMN”:”Rear Stairwell” }
Mon command-2: { "ID":2, "CMON": 4,"CCAM": 1027, “CCAMN”:null, “NCAMN”:”Training Room Corridor”, “LCAMN”:”Rear Stairwell” }
Cam notification: { "ID":3, "CMON": 4, “CCAMN”:”Training Room”, “NCAMN”:”Training Room Corridor”, “LCAMN”:”Rear Stairwell” }
Play notification: {"ID":4,"RM":"Training Room Rear","PMON":127,"PCAM":1009,"DT":"02/08/2022","TM":"12:01:06","TZ":"EST"}
Error: {"ID":5,"ERR":1}
*/

NotificationParams noitifParams = {0};

JsonKey jsonKeysList[i]
{
    // To be populated based on JSON notifications strings
    {"CCAMN", TYPE_STR, CURRENT_CAM_NAME_MAXCHR_LIMIT, noitifParams.currentCamName}, // CURRENT CAM NAME KEY
        /* Above example means 'If key name "CCAMN" is present in JSON:
            - Parse it's value in string form
            - Max lenght of value can be CURRENT_CAM_NAME_MAXCHR_LIMIT bytes
            - Store value in variable
        */
        {"CMON", TYPE_INT, 0, &noitifParams.currentMon},
        // Add items to this list based on the unique keys for all notifications
        {"PCAM", TYPE_STR, PREV_CAM_NAME_MAXCHR_LIMIT, notifParams.prevCamName}, // Pervious Name Key

        {"NCAMN", TYPE_STR, NEXT_CAM_NAME_MAXCHAR_LIMIT, notifParams.nextCamName}, // NextName Key

        //"LCMAN" ,  TYPE_STR  // LastName Key
        {"SN", TYPE_STR, USERNAME_MAXCHAR_LINIT, notifParams.userName}, // USERNAME KEY

        {"ID", TYPE_INT, 0, &notifParams.notificationId}, // ID KEY

        {"RM", TYPE_STR, ROOM_NAME_MAXCHAR_LIMIT, notifParams.roomName}, // ROOMNAME KEY

        {"PMON", TYPE_INT, 0, &notifParams.currentMon},

        {"CCAM", TYPE_INT, 0, &notifParams.currentCam},

        {"TM", TYPE_INT, 0, notifParams.time}, // TIME KEY

        {"TZ", TYPE_STR, TIMEZONE_TZ_TIMEZONE_MAXCHAR_LIMIT, notifParams.timeZone}, // TIMEZONE KEY

        {"DT", TYPE_INT, 0, notifiParamas.date}, // DATE KEY

    {
        "ERR", TYPE_INT, 0, &notifParamas.errorcode
    } // ERRORCODE KEY
}
int parseNotification(const char *const notifStr)
{
    // This will caculates the total length of jsonkeylists
    int numKeys = sizeof(jsonKeysList) / sizeof(jsonKeysList[0]);

    for (int i = 0; i < numKeys; i++)
    {
        const char *key = jsonKeysList[i].key;
        const char *value = strstr(notifStr, key);
     
        if (value != NULL)
        {
            value += strlen(key) + 3;               
            int valueLength = strcspn(value, "\""); 
            // Checking the string vaules in theese function
            if (jsonKeysList[i].type == TYPE_STR)
            {
                strncpy((char *)jsonKeysList[i].value, value, jsonKeysList[i].maxLength - 1);
                ((char *)jsonKeysList[i].value)[jsonKeysList[i].maxLength - 1] = '\0';
            }

            // These code will create in c code
            else  (jsonKeysList[i].type == TYPE_INT)
            {
                int intValue = atoi(value);
                *(int *)jsonKeysList[i].value = intValue;
            
        }
        else{
            printf(" Key Not found");
        }
    }

    return 0;
}

int main()
{
    parseNotification(char, notifStr);
    return 0;
}

// #endif //__JSON_PARSER_H__
